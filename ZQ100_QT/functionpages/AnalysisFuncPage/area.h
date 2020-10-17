#ifndef ANALYSISAREA_H
#define ANALYSISAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#define PADDING 5
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };

class Area : public QWidget
{
    Q_OBJECT
public:
    Area(QWidget *parent, int id = -1);

    void move(int x, int y);
    inline void move(QPoint point);
    void show();
    inline void setGeometry(int x, int y, int w, int h);
    void setGeometry(const QRect &);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void region(const QPoint &cursorGlobalPoint);

private slots:
    void longPressSlot();

private:
    QPoint dragPosition;
    int m_id;
    bool isPressed;
    int singleStep;
    int singleStepTemp;
    QTimer *longPressTimer;

    bool isLeftPressDown;  // 判断左键是否按下
//    QPoint dragPosition;   // 窗口移动拖动时需要记住的点
    Direction dir;        // 窗口大小改变时，记录改变方向
};

#endif // ANALYSISAREA_H
