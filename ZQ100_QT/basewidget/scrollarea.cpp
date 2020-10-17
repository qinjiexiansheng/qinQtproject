#include "scrollarea.h"

#define DEFHEIGHT 17

/**
 * @name    ScrollArea(QWidget *parent)
 * @details 构造函数
 *          继承QScrollArea类,实现自定义的滑动选项的效果和按键功能
 * @param   parent  父窗口指针

 * @date    2018-11-15
**/
ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    m_itemSize = QSize(width(), DEFHEIGHT);
    m_itemNum = 0;
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 按键事件
 *          上下按键滑动窗口,左右按键切换焦点
 * @param   e  按键事件对象

 * @date    2018-11-15
**/
void ScrollArea::keyPressEvent(QKeyEvent *e)
{
    //QScrollArea::keyPressEvent(e);
    if(e->key() == Qt::Key_Down)
    {
        if(verticalScrollBar()->value()< m_itemNum*m_itemSize.height())
            verticalScrollBar()->setValue(verticalScrollBar()->value()+m_itemSize.height());
    }
    else if(e->key() == Qt::Key_Up)
    {
        verticalScrollBar()->setValue(verticalScrollBar()->value()-m_itemSize.height());
    }
    else if(e->key() == Qt::Key_Left)
        focusPreviousChild();
    else if(e->key() == Qt::Key_Right)
        focusNextChild();
    else
        e->ignore();
}

/**
 * @name    void mousePressEvent(QMouseEvent *e)
 * @details 鼠标按键事件
 *          当左键按下时,记录当前点击的坐标
 * @param   e  鼠标事件对象

 * @date    2018-11-15
**/
void ScrollArea::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_firstPoint = e->pos();
        //        qWarning("mousePressEvent");
    }

}

/**
 * @name    void mouseMoveEvent(QMouseEvent *e)
 * @details 鼠标移动事件
 *          根据纵坐标的移动进行窗口的滑动显示
 * @param   e  鼠标事件对象

 * @date    2018-11-15
**/
void ScrollArea::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() | Qt::LeftButton)
    {
        m_secondPoint = e->pos();
        //前后坐标的差值除以一个常熟,减少滑动的灵敏度
        int offset = (m_firstPoint.y() - m_secondPoint.y())/10;
        if(verticalScrollBar()->value()+offset-m_itemSize.height()/2
                < m_itemNum*m_itemSize.height())
            verticalScrollBar()->setValue(verticalScrollBar()->value()+offset);
        //        qWarning("mouseMoveEvent");

    }
}

/**
 * @name    void mouseReleaseEvent(QMouseEvent *e)
 * @details 鼠标释放事件
 *          滑动到对应的item位置
 * @param   e  鼠标事件对象

 * @date    2018-11-15
**/
void ScrollArea::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        int curPos = verticalScrollBar()->value();
        if(curPos%m_itemSize.height() != 0)
        {
            curPos = curPos/m_itemSize.height()*m_itemSize.height();
        }
        //        secondPoint = e->globalPos();
        verticalScrollBar()->setValue(curPos);
        //        qWarning("mouseReleaseEvent");
    }
}

/**
 * @name    void wheelEvent(QWheelEvent *e)
 * @details 鼠标滑轮事件
 *          屏蔽滑轮
 * @param   e  鼠标滑轮事件

 * @date    2018-11-15
**/
void ScrollArea::wheelEvent(QWheelEvent *e)
{

}

/**
 * @name    void focusInEvent(QFocusEvent *event)
 * @details 获取焦点事件，保留
 * @param   event  焦点事件指针

 * @date    2018-11-15
**/
void ScrollArea::focusInEvent(QFocusEvent *event)
{
//    qWarning(".....focusInEvent");
    QScrollArea::focusInEvent(event);
//    setStyleSheet("background-color: rgb(0, 180, 180)");
}

/**
 * @name    void focusOutEvent(QFocusEvent *event)
 * @details 失去焦点事件，保留
 * @param   event  焦点事件指针

 * @date    2018-11-15
**/
void ScrollArea::focusOutEvent(QFocusEvent *event)
{
    QScrollArea::focusOutEvent(event);
//    setStyleSheet("");
}

/**
 * @name    void setItemSize(const QSize &size)
 * @details 设置item的大小,用于提供滑动的步进值
 * @param   size  item大小

 * @date    2018-11-15
**/
void ScrollArea::setItemSize(const QSize &size)
{
    m_itemSize = size;
}

/**
 * @name    void setItemNum(const int num)
 * @details 设置item的数量,限制滑动的范围
 * @param   num  item的数量

 * @date    2018-11-15
**/
void ScrollArea::setItemNum(const int num)
{
    m_itemNum = num-1;
}
