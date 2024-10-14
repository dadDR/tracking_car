#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include "car.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , view(new QGraphicsView(this))
    , scene(new QGraphicsScene(this))
    , carX(40)
    , carY(40)
    , carSpeedchange(1)
    , carSpeedX(5)
    , carSpeedY(0)
    , carSpeedlimitMax(10)
    , carSpeedlimitMin(-10)
{
    ui->setupUi(this);
    // 设置场景大小
    scene->setSceneRect(-500, -500, 1000, 1000);

    // 创建小车对象并添加到场景中
    //Car *car = new Car(scene);
    //scene->addItem(car);  // 将小车添加到场景中

    // 设置视图的场景
    view->setScene(scene);//将当前的视图绑定在创建的场景中
    view->setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
    view->setBackgroundBrush(Qt::darkGray);       // 设置背景颜色
    view->setGeometry(0, 0, 800, 600);            // 设置视图的大小和位置
    view->centerOn(0, 0);
    // 创建并绘制一个黑色的正方形轨迹
    QPen pen(Qt::black, 5);  // 轨迹线条设置为黑色，宽度为5
    QGraphicsRectItem *squareTrack = new QGraphicsRectItem(-100, -100, 200, 200); // 轨迹大小200x200
    squareTrack->setPen(pen);
    Car *car = new Car(scene);
    //设置小车和赛道的图层
    //要求小车在赛道之上
    squareTrack->setZValue(0); // 设置赛道的图层在较低位置
    car->setZValue(1);          // 设置小车的图层在较高位置
    scene->addItem(squareTrack); // 将正方形轨迹添加到场景中
    scene->addItem(car);//绘制小车

    //初始化定时器用于模拟小车巡线
    //timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &Widget::updateCarPosition);//当定时器中断发生后，更新车的位置
    //timer->start(100); // 每100毫秒更新一次

}

Widget::~Widget()
{
    delete ui;
    // 释放资源
    delete view;
    delete scene;
}


/*
void Widget::cremaAnalize(const QImage &image)
{
    //int carCentX = carX + 10;
    //int carCentY = carY - 10;    
    // 转换图像为灰度，并检测黑色区域的位置
    // 获取输入图像的宽度和高度
    int width = image.width();
    int height = image.height();

    // 左侧和右侧的黑色像素数量
    int leftBlackcount = 0;
    int rightBlackcount = 0;

    //遍历图像，检测黑色像素
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            // 假设黑色是 R, G, B 都低于 50 的像素
            if (pixelColor.red() < 50 && pixelColor.green() < 50 && pixelColor.blue() < 50) {
                if (x < width / 2) {
                    leftBlackcount++;
                } else {
                    rightBlackcount++;
                }
            }
        }
    }

    // 根据检测的结果调整小车方向
    if (leftBlackcount > rightBlackcount) {
        carX -= 5; // 向左移动
    } else if (rightBlackcount > leftBlackcount) {
        carX += 5; // 向右移动
    }

    // 限制小车的移动范围
    if (carX < 0) carX = 0;
    if (carX > 180) carX = 180;
}



//修改视窗文件，添加绘图的代码
void Widget::paintEvent(QPaintEvent *event)
{
     //创建画笔
     QPainter painter(this);
     //创建笔触
     QPen pen;
     //创建小车的笔触
     QPen carPen(Qt::NoPen);
     //创建摄像头的笔触
     QPen creamPen(Qt::red);
     //小车笔触没边框
     //设置线条宽度
     pen.setWidth(5);//线宽
     pen.setColor(Qt::black);//黑色
     //黑色
     painter.setPen(pen);

     //设置视口和窗口
     painter.setWindow(QRect(0,0,200,200));
     //绘制赛道
     painter.drawRect(50,50,100,100);

    // 设置小车颜色
    painter.setBrush(Qt::yellow);
    //设置笔触
    painter.setPen(carPen);
    // 绘制小车
    painter.drawRect(carX, carY, 20, 20); // 用黄色方块表示小车

    // 模拟摄像头视角 (小车前方区域)(绘制出它)
    QRect cameraView(carX + 20, carY, 20, 20);  // 视角区域 ()
    painter.setPen(creamPen);//设置笔触
    painter.setBrush(Qt::NoBrush); // 不填充任何颜色
    painter.drawRect(cameraView);  // 用红色边框标记摄像头视角

    //模拟摄像头检测区
    int camerWidth = cameraView.width();
    int camerHeight = cameraView.height();
    painter.setPen(Qt::green);//绿色


    // 提取摄像头视角图像(这样写会出现无限循环后报错)
    //QImage image = this->grab(cameraView).toImage();
    //进行图像分析
    //cremaAnalize(image);


}*/

//小车转向函数
//向南转
/*
void Widget::car_Turndown()
{
    carX += 20;
}*/


/*
// 更新小车位置
// 定时器中断时调用它
// 需要修改为动态调用
void Widget::updateCarPosition()
{
    //QRect cameraView(carX + 20, carY, 20, 20);  // 视角区域 ()	
    // 触发重绘
    // 提取摄像头视角图像
    QImage image = this->grab(cameraView).toImage();
    //进行图像分析
    cremaAnalize(image);
    //重新绘制
    update();
}
*/



