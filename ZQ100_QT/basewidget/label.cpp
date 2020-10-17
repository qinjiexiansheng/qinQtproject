#include "label.h"

Label::Label(QWidget *parent) : QLabel(parent)
{

}

void Label::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit click();
    else
        QLabel::mousePressEvent(event);
}
