#ifndef ANALYSISSPOT_H
#define ANALYSISSPOT_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMoveEvent>

class Spot : public QWidget
{
    Q_OBJECT
public:
    explicit Spot(QWidget *parent, int id = -1);

    void move(int, int);
    inline void move(QPoint);
    void show();
    void close();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moveEvent(QMoveEvent *event);

private slots:
    void changeText();
    void longPressSlot();

private:
    void startLongPressTimer();
    void stopLongPressTimer();

private:
    QPoint dragPosition;
    QString data;
    int m_id;
    QPixmap normalPix, focusPix;
    QLabel *m_label;
    bool isPressed;
    int singleStep;
    int singleStepTemp;
    QTimer *longPressTimer;
};

#endif // ANALYSISSPOT_H
