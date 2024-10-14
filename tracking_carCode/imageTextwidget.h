#ifndef IMAGETEXTWIDGET_H
#define IMAGETEXTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class imageTextwidget : public QWidget {
    Q_OBJECT

public:
    explicit imageTextwidget(QWidget *parent = nullptr);
    //显示虚拟摄像头图像和显示小车文字的函数
    void setImage(const QImage &image);
    void setText(const QString &text);

private:
    //两个Lable ， 一个显示图像，一个显示文字
    QLabel *imageLabel;
    QLabel *textLabel;
};

#endif

