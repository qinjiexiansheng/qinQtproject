#include "spot.h"
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QTime>
#include <QTimer>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#endif
#define SPOT_WIDTH  50
#define SPOT_SIZE QSize(SPOT_WIDTH, SPOT_WIDTH)
#define LONGPRESSDURATION   250


Spot::Spot(QWidget *parent, int id) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    //    setAttribute(Qt::WA_TranslucentBackground, true);

    setFocusPolicy(Qt::StrongFocus);

    normalPix.load(":/pics/D300/cursor_1.png", nullptr,
                   Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    normalPix = normalPix.scaled(SPOT_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    focusPix.load(":/pics/D300/cursor_0.png", nullptr,
                  Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    focusPix = focusPix.scaled(SPOT_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setFixedSize(normalPix.size());
    setMask(QBitmap(normalPix.mask()));

    m_id = id;
    isPressed = false;
    singleStep = 1;
    singleStepTemp = singleStep;

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    m_label = new QLabel(QString("label %1").arg(m_id), parent);
    m_label->setFont(QFont(font().family(), 11*width()/64));
    m_label->setScaledContents(true);
    changeText();
    m_label->setWindowFlags(Qt::FramelessWindowHint);
    m_label->setAttribute(Qt::WA_DeleteOnClose,true);
    m_label->setAttribute(Qt::WA_TranslucentBackground, true);
    m_label->show();
}

void Spot::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
////        raise();
//        setFocus();
        dragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton)
    {
        close();
    }
}

void Spot::mouseMoveEvent(QMouseEvent *event)
{
    if(/*isPressed &&*/ event->buttons() & Qt::LeftButton)
    {
        QPoint position = event->globalPos()-dragPosition;
        move(position);
        event->accept();
    }
}

void Spot::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void Spot::mouseDoubleClickEvent(QMouseEvent *event)
{
    QMessageBox::information(this, QString("Spot %1").arg(m_id), "I am Spot!", QMessageBox::Ok);
}

void Spot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(hasFocus())
        painter.drawPixmap(0, 0, normalPix);
    else
        painter.drawPixmap(0, 0, focusPix);

    QWidget::paintEvent(event);
}

void Spot::keyPressEvent(QKeyEvent *event)
{
    QPoint position(pos());
    if(!isPressed )
    {
        isPressed = true;
        longPressTimer->start(LONGPRESSDURATION);
        singleStepTemp = singleStep;
    }
    if(event->key() == Qt::Key_Escape)
        event->ignore();
//    else
    {
        if(event->key() == Qt::Key_Left)
        {
            position.setX(position.x()-singleStep);
        }
        else if(event->key() == Qt::Key_Right)
        {
            position.setX(position.x()+singleStep);
        }
        if(event->key() == Qt::Key_Up)
        {
            position.setY(position.y()-singleStep);
        }
        else if(event->key() == Qt::Key_Down)
        {
            position.setY(position.y()+singleStep);
        }
        move(position);
    }
}

void Spot::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat() && isPressed)
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    QWidget::keyReleaseEvent(event);
}

void Spot::move(int x, int y)
{
    x = (x < -width()/2 ? -width()/2 : x);
    x = (x > SCREEN_WIDTH-width()/2 ? SCREEN_WIDTH-width()/2 : x);
    y = (y < -height()/2 ? -height()/2 : y);
    y = (y > SCREEN_HEIGHT-height()/2 ? SCREEN_HEIGHT-height()/2 : y);

    QWidget::move(x, y);
}

inline void Spot::move(QPoint p)
{
    move(p.x(), p.y());
}

void Spot::show()
{
//    raise();
    setFocus();

    QWidget::show();
}

void Spot::close()
{
    m_label->close();

    QWidget::close();
}

void Spot::moveEvent(QMoveEvent *event)
{
    QPoint labelPos = pos()+QPoint(width()/2, height()/2);
    int spacing = 3;
    if(labelPos.x() < SCREEN_WIDTH/2)
        labelPos.setX(labelPos.x()+spacing);
    else
        labelPos.setX(labelPos.x()-m_label->width()-spacing);
    if(labelPos.y() < SCREEN_HEIGHT/2)
        labelPos.setY(labelPos.y()+spacing);
    else
        labelPos.setY(labelPos.y()-m_label->height()-spacing);

    m_label->move(labelPos);

    changeText();
    QWidget::moveEvent(event);
}

void Spot::changeText()
{
//    QString temp = QString::number(m_id)+":"+QTime::currentTime().toString("ss.mm");
//    if(temp != m_label->text())
//    {
//        m_label->setText(temp);
//        repaint();
//    }
    m_label->setText(QString("S%1:(%2, %3)").arg(m_id).arg(pos().x()+SPOT_WIDTH/2).arg(pos().y()+SPOT_WIDTH/2));
    m_label->adjustSize();
}

void Spot::longPressSlot()
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
