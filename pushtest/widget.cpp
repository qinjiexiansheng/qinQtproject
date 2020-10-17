#include "widget.h"
#include "ui_widget.h"
#include "QPushButton"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{

    setFixedSize(320,200);
    this->move(300,100);

    btn1 = new QPushButton("btn1",this);
    btn1->move(10,10);
    btn1->setFixedSize(38,38);



}

Widget::~Widget()
{
}
