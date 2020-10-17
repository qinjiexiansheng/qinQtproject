#include "nwidget.h"
#include <QDebug>

nWidget::nWidget(QWidget *parent) :
    QWidget(parent), btn1(this), btn2(this), btn3(this)
{
    resize(200, 180);
    setFixedSize(200, 180);

    nVboxLay = new QVBoxLayout;

    btn1.setText("btn1");
    btn2.setText("btn2");
    btn3.setText("btn3");

    nVboxLay->addWidget(&btn1);
    nVboxLay->addWidget(&btn2);
    nVboxLay->addWidget(&btn3);

    this->setLayout(nVboxLay);
}

nWidget::~nWidget()
{
    qDebug("~nWidget()");
}
