#include "line.h"
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#endif
#define LINEWIDGET_WIDTH    SCREEN_WIDTH
#define LINEWIDGET_HEIGHT   30
#define TRIANGLE_LENGTH     16
#define TOP_TRIANGEL        (height()/2-TRIANGLE_LENGTH)
#define BOTTOM_TRIANGEL     (height()/2+TRIANGLE_LENGTH)
#define TOP_TEXT        (height()/2)
#define BOTTOM_TEXT     (height()/2+10)
#define LEFT_TEXT        (trianglePosX-72)
#define RIGHT_TEXT     (trianglePosX+5)
#define LONGPRESSDURATION   250


Line::Line(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(LINEWIDGET_WIDTH, LINEWIDGET_HEIGHT);
    trianglePosX  = width()/2;
    trianglePosY = height()/2-TRIANGLE_LENGTH;
    textLabelX = trianglePosX+5;
    textLabelY = height()/2+10;
    isDragging = false;
    isPressed = false;
    singleStep = 1;
    singleStepTemp = singleStep;


    setFocus();

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));
}

void Line::move(int x, int y)
{
    y = y < -height()/2 ? -height()/2 : y;
    y = y >= SCREEN_HEIGHT-1-height()/2 ? SCREEN_HEIGHT-1-height()/2 : y;
    if(y+height()/2 < SCREEN_HEIGHT/2)
    {
        trianglePosY = BOTTOM_TRIANGEL;
        textLabelY = BOTTOM_TEXT;
    }
    else
    {
        trianglePosY = TOP_TRIANGEL;
        textLabelY = TOP_TEXT;
    }
    trianglePosX  = trianglePosX < 0 ? 0 : trianglePosX;
    trianglePosX  = trianglePosX >= width()-1 ? width()-1 : trianglePosX;
    if(trianglePosX < width()/2)
        textLabelX = RIGHT_TEXT;
    else
        textLabelX = LEFT_TEXT;
    QWidget::move(x, y);
    update();
}

inline void Line::move(QPoint point)
{
    move(point.x(), point.y());
}

void Line::show()
{
//    raise();
    lower();
    setFocus();

    QWidget::show();
}

void Line::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPoint points[3] = {
        QPoint(trianglePosX-TRIANGLE_LENGTH/2, trianglePosY),
        QPoint(trianglePosX+TRIANGLE_LENGTH/2, trianglePosY),
        QPoint(trianglePosX,height()/2),
    };

    QPainter painter(this);

    painter.setPen(Qt::blue);

    painter.drawLine(0, height()/2, width(), height()/2);

    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawPolygon(points, 3);

    painter.drawText(textLabelX, textLabelY, QString("(%1, %2)").arg(trianglePosX).arg(pos().y()+height()/2));
}

void Line::mousePressEvent(QMouseEvent *event)
{
    if(!QRect(trianglePosX-TRIANGLE_LENGTH/2, height()/2-TRIANGLE_LENGTH,
              TRIANGLE_LENGTH, 2*TRIANGLE_LENGTH).contains(event->pos()))
        return;
    isDragging = true;
    if(event->button() == Qt::LeftButton)
    {
////        raise();
//        setFocus();
        dragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
//    if(event->button() == Qt::RightButton)
//    {
//        close();
//    }
}

void Line::mouseReleaseEvent(QMouseEvent *event)
{
    isDragging = false;
    QWidget::mouseReleaseEvent(event);
}

void Line::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging && event->buttons() & Qt::LeftButton)
    {
        QPoint position = event->globalPos()-dragPosition;

        trianglePosX = event->pos().x();
        trianglePosY = event->pos().y();
        move(pos().x(), position.y());
        event->accept();
    }
}

void Line::mouseDoubleClickEvent(QMouseEvent *event)
{
    QMessageBox::information(this, QString("Line"), "I am Line!", QMessageBox::Ok);
}

void Line::keyPressEvent(QKeyEvent *event)
{
    if(!isPressed )
    {
        isPressed = true;
        longPressTimer->start(LONGPRESSDURATION);
        singleStepTemp = singleStep;
    }

    QPoint position(pos());

    if(event->key() == Qt::Key_Escape)
        event->ignore();
//    else
    {
        if(event->key() == Qt::Key_Left)
        {
            trianglePosX = trianglePosX-singleStep;
        }
        else if(event->key() == Qt::Key_Right)
        {
            trianglePosX = trianglePosX+singleStep;
        }
        if(event->key() == Qt::Key_Up)
        {
            position.setY(position.y()-singleStep);
        }
        else if(event->key() == Qt::Key_Down)
        {
            position.setY(position.y()+singleStep);
        }
        move(pos().x(), position.y());
    }
}

void Line::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat() && isPressed)
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    QWidget::keyReleaseEvent(event);
}

void Line::longPressSlot()
{
    if(!hasFocus())
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    else
    {
        if(isPressed)
        {
            singleStep += 1;
        }
    }
}
