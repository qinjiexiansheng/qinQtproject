#include "line.h"

#define LINEWIDGET_WIDTH    SCREEN_WIDTH
#define LINEWIDGET_HEIGHT   30
#define TRIANGLE_LENGTH     12
#define TOP_TRIANGEL        (height()/2-TRIANGLE_LENGTH)
#define BOTTOM_TRIANGEL     (height()/2+TRIANGLE_LENGTH)
#define TOP_TEXT        (height()/2-2)
#define BOTTOM_TEXT     (height()/2+13)
#define LEFT_TEXT        (trianglePosX-40)
#define RIGHT_TEXT     (trianglePosX+10)
#define LONGPRESSDURATION   250

/**
 * @name    Line(QWidget *parent)
 * @details Line构造函数。实现线测温的显示和功能
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-12-20
**/
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

    m_curTemp = -1;

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    updateTempTimer = new QTimer(this);
    connect(updateTempTimer, SIGNAL(timeout()), this, SLOT(updateTempSlot()));
}

/**
 * @name    void move(int x, int y)
 * @details 重写move函数，限制x，y的值，并刷新温度
 * @param   x   横坐标
 * @param   y   纵坐标
 * @author  lee
 * @date    2018-12-20
**/
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
    updateTempSlot();
    update();
}

/**
 * @name    inline void move(QPoint p)
 * @details 重写move函数，限制x，y的值
 * @param   p   移动点的坐标
 * @author  lee
 * @date    2018-12-20
**/
inline void Line::move(QPoint point)
{
    move(point.x(), point.y());
}

/**
 * @name    void show()
 * @details 重写show函数，显示时获取焦点，并启动刷新温度定时器
 * @author  lee
 * @date    2018-12-20
**/
void Line::show()
{
//    raise();
    setFocus();
    QWidget::show();
    updateTempTimer->start(1000);
}

/**
 * @name    void hide()
 * @details 重写hide函数，隐藏时关闭刷新温度定时器
 * @author  lee
 * @date    2018-12-20
**/
void Line::hide()
{
    QWidget::hide();
    updateTempTimer->stop();
}

/**
 * @name    void paintEvent(QPaintEvent *event)
 * @details 绘图事件，刷新线的位置和温度显示
 * @param   event   绘图事件指针
 * @author  lee
 * @date    2018-12-20
**/
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

#ifdef SHOWTEMP
    painter.drawText(textLabelX, textLabelY,
                     QString("%1").arg(m_curTemp == -1 ? ">>>>" : QString::number(m_curTemp, 'f', 1)));
#else
    painter.drawText(textLabelX, textLabelY,
                     QString("%1").arg(m_irtempstru.AD <= 0 ? ">>>>" : QString::number(m_irtempstru.AD, 16)));
#endif
}

/**
 * @name    void mousePressEvent(QMouseEvent *event)
 * @details 鼠标点击事件。鼠标点击时记录点击位置，为拖动功能提供数据。
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void mouseReleaseEvent(QMouseEvent *event)
 * @details 鼠标释放事件
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Line::mouseReleaseEvent(QMouseEvent *event)
{
    isDragging = false;
    QWidget::mouseReleaseEvent(event);
}

/**
 * @name    void mouseMoveEvent(QMouseEvent *event)
 * @details 鼠标移动事件。实现该Line在鼠标拖动状态下跟随移动。
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void mouseDoubleClickEvent(QMouseEvent *event)
 * @details 鼠标双击事件。保留
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Line::mouseDoubleClickEvent(QMouseEvent *event)
{
    QMessageBox::information(this, QString("Line"), "I am Line!", QMessageBox::Ok);
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 按下按键事件。方向键移动Line位置，回车键唤出属性窗口。长按时启动长按定时器，修改移动步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void keyReleaseEvent(QKeyEvent *event)
 * @details 释放按键事件。停止长按定时器，并重置步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void updateTempSlot()
 * @details 刷新温度槽，从底层读取温度数据并刷新显示
 * @date    2018-12-21
**/
void Line::updateTempSlot()
{
    if(GlobalParam::getFPGA()->getLineTemp(pos(), m_irtempstru) < 0)
    {
        //                qWarning("read line temp failed");
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        m_curTemp = qrand()%100+qrand()%10*0.1;
    }
    else
        m_curTemp = m_irtempstru.temp;
    update();
}

/**
 * @name    void longPressSlot()
 * @details 长按处理槽，改变移动的步进值
 * @date    2018-12-21
**/
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
