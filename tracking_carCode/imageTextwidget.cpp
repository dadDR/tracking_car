#include "imageTextwidget.h"
#include <QVBoxLayout>
#include <QPixmap>

imageTextwidget::imageTextwidget(QWidget *parent) 
    : QWidget(parent), imageLabel(new QLabel(this)), textLabel(new QLabel(this)) {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(textLabel);
    setLayout(layout);
}

void imageTextwidget::setImage(const QImage &image) {
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void imageTextwidget::setText(const QString &text) {
    textLabel->setText(text);
}

