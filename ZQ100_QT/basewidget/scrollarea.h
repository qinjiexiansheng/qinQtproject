#ifndef TSCROLLAREA_H
#define TSCROLLAREA_H

#include "globalparam.h"

class ScrollArea : public QScrollArea
{
public:
    ScrollArea(QWidget *parent = 0);
    void setItemSize(const QSize &size);
    void setItemNum(const int num);

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    QPoint m_firstPoint;
    QPoint m_secondPoint;
    //数据item的大小
    QSize m_itemSize;
    //数据item的数量
    int m_itemNum;
};

#endif // TSCROLLAREA_H
