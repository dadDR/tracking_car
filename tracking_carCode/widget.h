#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

//声明自定义绘图行为
protected:
    //添加绘图行为声明
    //void paintEvent(QPaintEvent *event) override;
    //添加图像分析说明
    //void cremaAnalize(const QImage &image);

private:
    Ui::Widget *ui;
    //引入视图和场景	
    QGraphicsView *view;       // 视图，用于显示场景
    QGraphicsScene *scene;     // 场景，用于管理和显示图形项
    // 小车位置
    int carX;
    int carY;
    //声明汽车的速度变化量变量和汽车的X轴速度和Y轴速度和汽车速度的最大限制和最小限制
    int carSpeedchange;
    int carSpeedX;
    int carSpeedY;
    int carSpeedlimitMax;
    int carSpeedlimitMin; 
    //摄像头视角
    QRect cameraView;

    // 定时器用于更新小车位置
    QTimer *timer;

private slots:
    //void updateCarPosition(); // 更新小车位置

};






#endif // WIDGET_H
