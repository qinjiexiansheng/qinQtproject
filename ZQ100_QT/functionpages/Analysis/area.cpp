#include "area.h"
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QPixmap>
#include <QBitmap>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#endif
#define AREA_DEFWIDTH   100
#define AREA_DEFSIZE    QSize(AREA_DEFWIDTH, AREA_DEFWIDTH)
#define LONGPRESSDURATION   250


Area::Area(QWidget *parent, int id) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::StrongFocus);
    resize(AREA_DEFSIZE);

    m_id = id;
    isPressed = false;
    singleStep = 1;
    singleStepTemp = singleStep;

    isLeftPressDown = false;
    this->dir = NONE;
    this->setMouseTracking(true);

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    updateTempTimer = new QTimer(this);
    connect(updateTempTimer, SIGNAL(timeout()), this, SLOT(updateTempSlot()));

    m_label = new QLabel(parent);
    m_label->setStyleSheet("color: black; background-color: red");
    m_label->setFont(QFont(font().family(), 10));
    m_label->setScaledContents(true);
    m_label->setWindowFlags(Qt::FramelessWindowHint);
    m_label->setAttribute(Qt::WA_DeleteOnClose,true);
    m_label->setAttribute(Qt::WA_TranslucentBackground, true);
    m_label->lower();

    m_maxCursor = new QLabel(parent);
    m_minCursor = new QLabel(parent);
    //    m_avgCursor = new QLabel;

    QImage *img = new QImage;
    float scale = 0.5;

    if(img->load(":/pics/D300/area_max.png")) //加载图像
    {
        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    m_maxCursor->setPixmap(QPixmap::fromImage(*img));
    m_maxCursor->lower();
    m_maxCursor->setFixedSize(img->size());
    m_maxCursor->setMask(QBitmap(QPixmap::fromImage(*img).mask()));

    if(img->load(":/pics/D300/area_min.png")) //加载图像
    {
        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    m_minCursor->setPixmap(QPixmap::fromImage(*img));
    m_minCursor->setFixedSize(img->size());
    m_minCursor->setMask(QBitmap(QPixmap::fromImage(*img).mask()));

    //    if(img->load(":/pics/D300/area_avera.png")) //加载图像
    //    {
    //        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    //    }
    //    m_avgCursor->setPixmap(QPixmap::fromImage(*img));
    //    m_avgCursor->resize(img->width(), img->height());

    m_maxCursor->move(QPoint(geometry().topLeft().x()-m_maxCursor->width()/2,
                             geometry().topLeft().y()-m_maxCursor->height()/2));
    m_minCursor->move(QPoint(geometry().bottomRight().x()-m_minCursor->width()/2,
                             geometry().bottomRight().y()-m_minCursor->height()/2));
}

void Area::move(int x, int y)
{
    x = (x < 0 ? 0 : x);
    x = (x > SCREEN_WIDTH-width() ? SCREEN_WIDTH-width() : x);
    y = (y < 0 ? 0 : y);
    y = (y > SCREEN_HEIGHT-height() ? SCREEN_HEIGHT-height() : y);

    QWidget::move(x, y);
    updateTempSlot();
}

inline void Area::move(QPoint point)
{
    move(point.x(), point.y());
}

void Area::show()
{
    lower();
    setFocus();
    QWidget::show();

    updateTempTimer->start(1000);
}

void Area::hide()
{
    QWidget::hide();
    updateTempTimer->stop();
}

void Area::close()
{
    m_label->close();
    QWidget::close();
}

inline void Area::setGeometry(int x, int y, int w, int h)
{
    setGeometry(QRect(x, y, w, h));
}

void Area::setGeometry(const QRect &rect)
{
    QRect rectTemp = rect;
    rectTemp.setX(rect.x() < 0 ? 0 : rect.x());
    rectTemp.setY(rect.y() < 0 ? 0 : rect.y());
    rectTemp.setWidth(rectTemp.x() + rectTemp.width() > SCREEN_WIDTH ? SCREEN_WIDTH-rectTemp.x() : rectTemp.width());
    rectTemp.setHeight(rectTemp.y() + rectTemp.height() > SCREEN_HEIGHT ? SCREEN_HEIGHT-rectTemp.y() : rectTemp.height());

    QWidget::setGeometry(rectTemp);
    updateTempSlot();
}

void Area::updateText()
{
    QString text = QString("Area %1").arg(m_id);
    float total = abs(m_maxTemp) + abs(m_minTemp)+ abs(m_avgTemp);
    QString maxTempText = QString("\nMax:")
            + (!total ? QString(">>>>>") : (QString::number(m_maxTemp, 'f', 1)));
    QString minTempText = QString("\nMin:")
            + (!total ? QString(">>>>>") : (QString::number(m_minTemp, 'f', 1)));
    QString avgTempText = QString("\nAvg:")
            + (!total ? QString(">>>>>") : (QString::number(m_avgTemp, 'f', 1)));

    text += maxTempText + minTempText + avgTempText;
    m_label->setText(text);
    m_label->adjustSize();

    QPoint defPos = QPoint(SCREEN_WIDTH-m_label->width()-20,
                           (SCREEN_HEIGHT-m_label->height())/2);
    if(m_label->pos() != defPos)
        m_label->move(defPos);
}

void Area::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(0, 0, geometry().width()-1, geometry().height()-1);

    if(hasFocus())
    {
        painter.setPen(Qt::green);
        painter.drawRect(0+2, 0+2, geometry().width()-1-4, geometry().height()-1-4);
    }

    painter.setPen(Qt::white);
    //    painter.setFont(QFont(font().family(), 7));

    //    painter.drawText(rect().topLeft()+QPoint(1, 10), QString("A%1(%2, %3)").arg(m_id).arg(pos().x()).arg(pos().y()));
    painter.drawText(rect().topLeft()+QPoint(1, 15), QString("A%1").arg(m_id));
}

void Area::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //        //        raise();
        //        setFocus();
        isLeftPressDown = true;
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        event->accept();
    }
    //    if(event->button() == Qt::RightButton)
    //    {
    //        close();
    //    }
}

void Area::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void Area::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {
        this->region(gloPoint);
    }
    else {
        if(dir != NONE) {
            QRect rMove(pos().x(), pos().y(), width(), height());

            switch(dir) {
            case LEFT:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                break;
            case RIGHT:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                break;
            case UP:
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case DOWN:
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            case LEFTTOP:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case RIGHTTOP:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                rMove.setY(pos().y()+(gloPoint.y() - tl.y()));
                rMove.setHeight(this->geometry().height()-(gloPoint.y() - tl.y()));
                break;
            case LEFTBOTTOM:
                rMove.setX(pos().x()+(gloPoint.x() - tl.x()));
                rMove.setWidth(this->geometry().width()-(gloPoint.x() - tl.x()));
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(this->geometry().width()-(rb.x() - gloPoint.x()));
                rMove.setHeight(this->geometry().height()-(rb.y() - gloPoint.y()));
                break;
            default:
                break;
            }
            if( !(rMove.width() < 0 || rMove.height() < 0
                  || (abs(rMove.topLeft().x() - rMove.bottomRight().x()) < 5*PADDING)
                  || (abs(rMove.topLeft().y() - rMove.bottomRight().y()) < 5*PADDING)))
                setGeometry(rMove);
        } else {
            QPoint position = event->globalPos()-dragPosition;
            move(position);
            event->accept();
        }
        update();
    }
}

void Area::mouseDoubleClickEvent(QMouseEvent *event)
{
    QMessageBox::information(this, QString("Area"), QString("I am Area %1!").arg(m_id), QMessageBox::Ok);
}

void Area::keyPressEvent(QKeyEvent *event)
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

void Area::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat() && isPressed)
    {
        isPressed = false;
        longPressTimer->stop();
        singleStep = singleStepTemp;
    }
    QWidget::keyReleaseEvent(event);
}

void Area::longPressSlot()
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

void Area::region(const QPoint &cursorGlobalPoint)
{
    //获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Area::focusInEvent(QFocusEvent *event)
{
    m_label->show();
    QWidget::focusInEvent(event);
}

void Area::focusOutEvent(QFocusEvent *event)
{
    m_label->hide();
    QWidget::focusOutEvent(event);
}

void Area::updateTempSlot()
{
    m_areaPoint.xlt = rect().topLeft().x();
    m_areaPoint.ylt = rect().topLeft().y();
    m_areaPoint.xrb = rect().bottomLeft().x();
    m_areaPoint.yrb = rect().bottomLeft().y();

    if( GlobalParam::getFPGA()->getAreaTemp(GlobalParam::getFPGA()->readTempSetup(),
                                            m_id, m_areaPoint, m_areaVal, m_areaTemp) < 0 )
    {
        qWarning("read spot temp failed");
    }
    else
    {
        m_maxTemp = m_areaTemp._max.temp;
        m_minTemp = m_areaTemp._min.temp;
        m_avgTemp = m_areaTemp._averg.temp;

        updateText();

        //        const QPoint cursorPos[10] =
        //        {

        //        };

//        qsrand(QTime(m_id,m_id,m_id).secsTo(QTime::currentTime()));
//        unsigned int max_xOffset = qrand()%width();
//        unsigned int max_yOffset = qrand()%height();
//        unsigned int min_xOffset = qrand()%width();
//        unsigned int min_yOffset = qrand()%height();

//        QPoint startPoint = QPoint(geometry().topLeft().x()-m_minCursor->width()/2,
//                                   geometry().topLeft().y()-m_minCursor->height()/2);
//        QPoint maxPoint, minPoint;

//        maxPoint.setX(startPoint.x()+max_xOffset);
//        maxPoint.setY(startPoint.y()+max_yOffset);

//        minPoint.setX(startPoint.x()+min_xOffset);
//        minPoint.setY(startPoint.y()+min_yOffset);

//        //qDebug()<<maxPoint<<", "<<minPoint;

//        m_maxCursor->move(maxPoint);
//        m_minCursor->move(minPoint);

        if(!(m_areaVal.maxX > geometry().topLeft().x()+width()+m_minCursor->width()/2 ||
             m_areaVal.minX > geometry().topLeft().x()+width()+m_minCursor->width()/2 ||
             m_areaVal.maxY > geometry().topLeft().y()+height()+m_minCursor->height()/2 ||
             m_areaVal.minY > geometry().topLeft().y()+height()+m_minCursor->height()/2))
        {
            m_maxCursor->move(m_areaVal.maxX, m_areaVal.maxY);
            m_minCursor->move(m_areaVal.minX, m_areaVal.minY);
            if(m_maxCursor->isHidden())
            {
                m_maxCursor->show();
                m_minCursor->show();
            }
        }
    }
}
