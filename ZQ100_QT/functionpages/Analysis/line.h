#ifndef ANALYSISLINE_H
#define ANALYSISLINE_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>

class QTimer;

class Line : public QWidget
{
    Q_OBJECT
public:
    explicit Line(QWidget *parent);

    void move(int x, int y);
    inline void move(QPoint point);
    void show();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void longPressSlot();

private:
    QPoint dragPosition;
    int trianglePosX, trianglePosY;
    int textLabelX, textLabelY;
    bool isDragging;
    bool isPressed;
    int singleStep;
    int singleStepTemp;
    QTimer *longPressTimer;
};

#endif // ANALYSISLINE_H
