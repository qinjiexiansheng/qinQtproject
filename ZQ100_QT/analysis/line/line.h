#ifndef ANALYSISLINE_H
#define ANALYSISLINE_H

#include "globalparam.h"

class Line : public QWidget
{
    Q_OBJECT
public:
    explicit Line(QWidget *parent);

    void move(int x, int y);
    inline void move(QPoint point);
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void updateTempSlot();
    void longPressSlot();

private:
    //拖动的起始位置
    QPoint dragPosition;
    int trianglePosX, trianglePosY;
    int textLabelX, textLabelY;
    bool isDragging;
    bool isPressed;
    //移动的步进值
    int singleStep;
    int singleStepTemp;
    //长按定时器、刷新温度定时器
    QTimer *longPressTimer;
    QTimer *updateTempTimer;
    //Line的温度
    float m_curTemp;
    IrTempStru m_irtempstru;
};

#endif // ANALYSISLINE_H
