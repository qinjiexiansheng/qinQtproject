#include "littlewidget.h"

SatButton::SatButton(const QString &nText, QWidget *parent):QPushButton(nText, parent)
{
 //  connect(this, SIGNAL(clicked()), this, SLOT(switchOnState()) );
}


void SatButton::switchOnState()
{
    qDebug("SatButton::switchOnState()");

    ::system("/mnt/sd/adjust_k.sh");
    qDebug("/mnt/sd/adjust_k.sh");


}

void SatButton::keyPressEvent(QKeyEvent *event){

    qDebug("[D]Lin >> SatButton--keyPressEvent()");
  //  QPushButton::keyPressEvent(event);
      event->ignore();
}

/*
void SatButton::enterEvent(QEvent *)
{
    qDebug("SatButton::enterEvent");
    setStyleSheet("SatButton{background-color:rgb(255,255,0)}");
}
void SatButton::leaveEvent(QEvent *)
{
    qDebug("SatButton::leaveEvent");
    setStyleSheet("SatButton{background-color:rgb(17,17,17)}");
}
*/
