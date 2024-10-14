#include "car.h"
#include <QtWidgets/QtWidgets>
#include <qmath.h>
#include <QDebug> 
#include <iostream> 
#include <QPixmap>
#include <QImage>

QRectF Car::boundingRect() const {
    return QRectF(-50, -140, 100, 180);  // 扩大边界以包含摄像头视野
}

// 将在widght中创建的sence传入car类中，这样才能让car类摄像头访问到sence,将m_scene初始化值设置为scene
Car::Car(QGraphicsScene *scene) 
    : m_scene(scene),color(Qt::green), wheelsAngle(0), speed(0), trackPosition(0), imageLabel(nullptr), commandLabel(nullptr) {
    if (m_scene) {
        qDebug() << "Car initialized with a valid scene.";
    } else {
        qDebug() << "Car initialized with an invalid (null) scene.";
    }
    startTimer(1000 / 33);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache); // 使用设备坐标缓存减少残影
}

void Car::accelerate() {
    if (speed < 10)
        ++speed;
}

void Car::decelerate() {
    if (speed > -10)
        --speed;
}

void Car::turnLeft() {
    if (wheelsAngle > -30)
        wheelsAngle -= 5;
}

void Car::turnRight() {
    if (wheelsAngle < 30)
        wheelsAngle += 5;
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::gray);
    painter->drawRect(-20, -58, 40, 2); // front axel
    painter->drawRect(-20, 7, 40, 2);   // rear axel

    painter->setBrush(color);
    painter->drawRect(-25, -79, 50, 10); // front wing

    painter->drawEllipse(-25, -48, 50, 20); // side pods
    painter->drawRect(-25, -38, 50, 35);    // side pods
    painter->drawRect(-5, 9, 10, 10);       // back pod

    painter->drawEllipse(-10, -81, 20, 100); // main body

    painter->drawRect(-17, 19, 34, 15); // rear wing

    painter->setBrush(Qt::black);
    painter->drawPie(-5, -51, 10, 15, 0, 180 * 16);
    painter->drawRect(-5, -44, 10, 10); // cocpit

    painter->save();
    painter->translate(-20, -58);
    painter->rotate(wheelsAngle);
    painter->drawRect(-10, -7, 10, 15); // front left
    painter->restore();

    painter->save();
    painter->translate(20, -58);
    painter->rotate(wheelsAngle);
    painter->drawRect(0, -7, 10, 15); // front left
    painter->restore();

    painter->drawRect(-30, 0, 12, 17); // rear left
    painter->drawRect(19, 0, 12, 17);  // rear right

    //绘制小车边界矩形的边框
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::green, 2)); // 绿色边框，宽度为2
    painter->drawRect(boundingRect()); // 绘制边界矩形


    drawCameraView(painter);           // 调用绘制摄像头范围的函数
}

void Car::drawCameraView(QPainter *painter) {
    if (!m_scene) {
        qDebug() << "Scene is null. Cannot render camera view.";
        return;
    }

    // 定义摄像头视野范围矩形
  //  QRectF cameraRect(-20, -110, 40, 40);
   // qDebug() << "Camera view rectangle:" << cameraRect;

    // 获取小车的当前位置
    QPointF carPos = pos();

    // 使用场景的矩形范围作为摄像头捕捉的区域
    //QRectF cameraRect = m_scene->sceneRect()
    QRectF cameraRect(carPos.x() - 50,carPos.y() - 140,100, 80); // 设定摄像头捕捉的矩形区域
    QRectF cameraRect_cp2(-50, -140,100, 80); // 复制一个区域，用于边框的绘制

    qDebug() << "Camera view rectangle:" << cameraRect;

    // 创建用于渲染的 QImage，大小与 cameraRect 相匹配
    QImage image(cameraRect.size().toSize(), QImage::Format_ARGB32);
    //QImage image(cameraRect.width(), cameraRect.height(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter imgPainter(&image);
    //imgPainter.translate(-cameraRect.topLeft()); // 平移到正确的区域

    // 输出场景渲染前的状态
    qDebug() << "Rendering scene to image...";
    m_scene->render(&imgPainter, QRectF(image.rect()), cameraRect);
    imgPainter.end();

    // 查看渲染结果是否有内容
    if (image.isNull()) {
        qDebug() << "Rendered image is null.";
    } else {
        qDebug() << "Rendered image size:" << image.size();
        qDebug() << "Sample pixel color (0,0):" << image.pixelColor(0, 0);
    }



    // 添加边框绘制
    if (painter) {
        // 设置画笔来定义边框颜色和宽度
        QPen pen(Qt::red); // 红色边框
        pen.setWidth(2);   // 边框宽度为 2 像素

        painter->setPen(pen);
	painter->setBrush(Qt::NoBrush);
        // 绘制摄像头区域的边框
        painter->drawRect(cameraRect_cp2);
	painter->drawEllipse(carPos, 5, 5); // 在小车位置绘制半径为5的圆点
    }

    // 进行摄像头图像分析
    creamViewanalize(image);
}

void Car::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    const qreal axelDistance = 54;
    qreal wheelsAngleRads = qDegreesToRadians(wheelsAngle);
    qreal turnDistance = ::cos(wheelsAngleRads) * axelDistance * 2;
    qreal turnRateRads = wheelsAngleRads / turnDistance; // rough estimate
    qreal turnRate = qRadiansToDegrees(turnRateRads);
    qreal rotation = speed * turnRate;

    setTransform(QTransform().rotate(rotation), true);
    setTransform(QTransform::fromTranslate(0, -speed), true);
    update();
}

int Car::creamViewanalize(QImage image) {
    int width = image.width();
    int height = image.height();

    // 检查图像是否为空
    if (image.isNull()) {
        std::cout << "Error: Image is null!" << std::endl;
        return 0;
    }

    // 打印部分像素的颜色值
    
    QColor pixelColor = image.pixelColor(width / 2, height / 2); // 中心像素
    std::cout << "Center Pixel - R: " << pixelColor.red()
              << ", G: " << pixelColor.green()
              << ", B: " << pixelColor.blue() << std::endl;

    int leftBlackcount = 0;
    int rightBlackcount = 0;

    // 遍历图像，检测黑色像素
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            if (pixelColor.red() < 5 && pixelColor.green() < 5 && pixelColor.blue() < 5) {
                if (x < width / 2) {
                    leftBlackcount++;
                } else {
                    rightBlackcount++;
                }
            }
        }
    }

    //打印黑色像素（左边和右边）
    std::cout << "leftBlackcount" << leftBlackcount << "\n";
    std::cout << "rightBlackcount" << rightBlackcount << "\n";



    if (leftBlackcount > rightBlackcount) {
        trackPosition = -1; // 轨迹在左侧
        std::cout << "Track Position: " << trackPosition << " - Turn Left" << std::endl;
	commandText = "Turn Left";
    } else if (rightBlackcount > leftBlackcount) {
        trackPosition = 1; // 轨迹在右侧
        std::cout << "Track Position: " << trackPosition << " - Turn Right" << std::endl;
	commandText = "Turn Right";
    } else if(rightBlackcount == leftBlackcount){
        trackPosition = 0; // 轨迹在中间
        std::cout << "Track Position: " << trackPosition << " - Go Straight" << std::endl;
	commandText = "Go Straight";
    }

    if (!imageLabel)
    {
        imageLabel = new QLabel;
        imageLabel->setWindowTitle("Analyzed Image");
        imageLabel->resize(image.size());
        imageLabel->show();
    }


    //显示小车指令
    if(!commandLabel)
    {
   	commandLabel = new QLabel;
        commandLabel->setWindowTitle("Command Display");
        commandLabel->resize(300, 100);  // 设置窗口大小
        commandLabel->setAlignment(Qt::AlignCenter);  // 设置文字居中
        commandLabel->show();  // 显示窗口	
    }


    // 获取小车的当前位置
    QPointF carPos = pos();


    // 更新 QLabel 的内容
    QPixmap pixmap = QPixmap::fromImage(image);
    imageLabel->setPixmap(pixmap);
    //imageLabel->update();
    // 计算 QLabel 的新位置，使其与小车相对静止
//    QPointF newLabelPos(carPos.x() - 40, carPos.y() - 140); // 根据需要调整偏移
//    imageLabel->move(newLabelPos.toPoint());
    // 设置指令文本并更新窗口
    commandLabel->setText(commandText);
    commandLabel->update();  // 更新窗口内容

   /* 
    if (!creamLabelwidget) {
        creamLabelwidget = new imageTextwidget;
        creamLabelwidget->setWindowTitle("Analyzed Image and Commands");
        creamLabelwidget->resize(image.size().width(), image.size().height() + 50); // 为文字留出空间
        creamLabelwidget->show();
    }
    // 确保 QImage 有效并且不为空
    if (!image.isNull()) {
        // 使用 QMetaObject::invokeMethod 确保 UI 操作在主线程中完成
        QMetaObject::invokeMethod(creamLabelwidget, "setImage", Qt::QueuedConnection, Q_ARG(QImage, image));
    } else {
        std::cout << "Invalid image passed to setImage!" << std::endl;
    }

    // 检查 commandText 是否为空
    if (!commandText.isEmpty()) {
        // 使用 QMetaObject::invokeMethod 确保 UI 操作在主线程中完成
        QMetaObject::invokeMethod(creamLabelwidget, "setText", Qt::QueuedConnection, Q_ARG(QString, commandText));
    } else {
        std::cout << "Empty commandText passed to setText!" << std::endl;
    }*/
    //之前只使用这两句代码会导致段错误，原因：未知
    //creamLabelwidget->setImage(image);
    //creamLabelwidget->setText(commandText);
    return trackPosition;
}

