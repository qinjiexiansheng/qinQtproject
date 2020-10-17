#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),testBtn(this)
{
    setGeometry(100,100,285,150);

    testBtn.setText("test btn");

    connect(&testBtn, SIGNAL(clicked()), this, SLOT(TestBtn_Clicked()));


}


void Widget::TestBtn_Clicked()
{
    qDebug("======dlg.exec() == QDialog::Accepted======bigin ");

    QLoginDialog dlg;
    if( dlg.exec() == QDialog::Accepted )
    {

        qDebug("======dlg.exec() == QDialog::Accepted====== end ");
        qDebug() << "User: " + dlg.getUser();
       qDebug() << "Pwd: " + dlg.getPwd();
    }

}
Widget::~Widget()
{

}
