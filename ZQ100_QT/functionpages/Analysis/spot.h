#ifndef ANALYSISSPOT_H
#define ANALYSISSPOT_H

#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMoveEvent>
#include <QFocusEvent>

class SpotPropertyWnd;

class Spot : public QWidget
{
    Q_OBJECT
public:
    explicit Spot(QWidget *parent, int id = -1);

    int id();
    void move(int, int);
    inline void move(QPoint);
    void show();
    void hide();
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
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void updateText();
    void longPressSlot();
    void updateTempSlot();

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
    QTimer *updateTempTimer;


    float m_curTemp;
    SpotPropertyWnd *propertyWnd;
};

#endif // ANALYSISSPOT_H
