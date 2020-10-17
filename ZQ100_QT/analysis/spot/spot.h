#ifndef ANALYSISSPOT_H
#define ANALYSISSPOT_H

#include "globalparam.h"
#include "spotpropertywnd.h"

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

    float getTemp();

    void initProperty();
    void _setProperty(SpotProperty);

//    int getDisplay();
//    int getMode();
//    int getPosShow();
//    int getTempShow();
//    int getBackground();
//    int getAlarmMode();
//    float getAlarmTemp();
    SpotProperty _getProperty();

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
    void updateAlarmWarning();
    void adjustLabelPos();

public slots:
    void setDisplay(int);
    void setMode(int);
    void setPosShow(int);
    void setTempShow(int);
    void setBackground(int);
    void setAlarmMode(int);
    void setAlarmTemp(float);

    void rollbackProperty();
    void commitProperty();

private:
    //标示id
    int m_id;
    //背景显示图片
    QPixmap normalPix;
    QPixmap focusPix;
    //温度显示label
    QLabel *m_label;
    //鼠标拖动
    QPoint dragPosition;
    //按键按下标志
    bool isPressed;
    //按键移动的步进值
    int singleStep;
    int singleStepTemp;
    //长按定时器
    QTimer *longPressTimer;
    //更新温度定时器
    QTimer *updateTempTimer;
    //温度变量
    float m_curTemp;
    IrTempStru m_irtempstru;
    //属性变量
    SpotProperty m_property;
    SpotProperty m_property_temp;
    //属性窗口
    SpotPropertyWnd *propertyWnd;
};

#endif // ANALYSISSPOT_H
