#include "spot.h"
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include "spotpropertywnd.h"

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

    propertyWnd = new SpotPropertyWnd(this);

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    updateTempTimer = new QTimer(this);
    connect(updateTempTimer, SIGNAL(timeout()), this, SLOT(updateTempSlot()));

    m_label = new QLabel(parent);
    m_label->setStyleSheet("color: white; background-color: black");
    m_label->setFont(QFont(font().family(), 11*width()/64));
    m_label->setScaledContents(true);
    m_label->setWindowFlags(Qt::FramelessWindowHint);
    m_label->setAttribute(Qt::WA_DeleteOnClose,true);
    m_label->setAttribute(Qt::WA_TranslucentBackground, true);

    const QPoint SpotPosBuf[MAXSPOTNUM] = {
        QPoint((SCREEN_WIDTH-width())/2, (SCREEN_HEIGHT-height())/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH*3/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT*3/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT*3/6-height()/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
        QPoint(SCREEN_WIDTH*3/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
    };

    move(SpotPosBuf[id]);
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
    //    if(event->button() == Qt::RightButton)
    //    {
    //        close();
    //    }
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
    //    QMessageBox::information(this, QString("Spot %1").arg(m_id), "I am Spot!", QMessageBox::Ok);
    propertyWnd->exec();
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
    if(event->key() == Qt::Key_Return)
        mouseDoubleClickEvent(0);
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
    updateTempSlot();
}

inline void Spot::move(QPoint p)
{
    move(p.x(), p.y());
}

void Spot::show()
{
    //    raise();
    setFocus();
    m_label->show();
    QWidget::show();
    updateTempTimer->start(1000);
}

void Spot::hide()
{
    m_label->hide();
    QWidget::hide();
    updateTempTimer->stop();
}

void Spot::close()
{
    m_label->close();

    QWidget::close();
}

int Spot::id()
{
    return m_id;
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

    QWidget::moveEvent(event);
}

void Spot::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
//    this->raise();
}

void Spot::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
//    this->lower();
}

void Spot::updateText()
{
    //    QString text = QString("Spot %1").arg(m_id);
    QString text = QString("%1:").arg(m_id);
    QString posText = QString("\n(%1, %2)").arg(pos().x()+SPOT_WIDTH/2).arg(pos().y()+SPOT_WIDTH/2);
    //    QString tempText = QString("\n") + (!m_curTemp ? QString(">>>>>") :
    //                                                     (QString::number(m_curTemp, 'f', 1) + QString(GlobalParam::getTempUnit() ? "°F" : "°C")));
    QString tempText =(!m_curTemp ? QString(">>>>>") :
                                    (QString::number(m_curTemp, 'f', 1)));
    //    text += tempText + posText;

    text += tempText;
    m_label->setText(text);
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

void Spot::updateTempSlot()
{
    IrTempStru m_irtempstru;
    if(GlobalParam::getFPGA()->getSpotTemp(GlobalParam::getFPGA()->readTempSetup(),
                                           m_id, pos(), m_irtempstru, 0) < 0)
        qWarning("read spot temp failed");
    else
    {
        m_curTemp = m_irtempstru.temp;
        updateText();
    }
}
