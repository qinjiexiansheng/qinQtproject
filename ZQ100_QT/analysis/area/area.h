#ifndef ANALYSISAREA_H
#define ANALYSISAREA_H

#include "globalparam.h"
#include "areapropertywnd.h"

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
    void hide();
    void close();
    inline void setGeometry(int x, int y, int w, int h);
    void setGeometry(const QRect &);
    int id();

    AreaTemp getTemp();

    void initProperty();
    void _setProperty(AreaProperty);

//    int getDisplay();
//    int getMaxShow();
//    int getMinShow();
//    int getAvgShow();
    AreaProperty _getProperty();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void region(const QPoint &cursorGlobalPoint);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void updateText();
    void updateCursor();
    void longPressSlot();
    void updateTempSlot();

public slots:
    void setDisplay(int);
    void setMaxShow(int);
    void setMinShow(int);
    void setAvgShow(int);


    void rollbackProperty();
    void commitProperty();

private:
    QPoint dragPosition; // 窗口移动拖动时需要记住的点
    int m_id;//标示id
    bool isPressed;
    //移动步进值
    int singleStep;
    int singleStepTemp;
    //长按定时器
    QTimer *longPressTimer;

    bool isLeftPressDown;  // 判断左键是否按下
    Direction dir;        // 窗口大小改变时，记录改变方向
    //刷新温度定时器
    QTimer *updateTempTimer;
    //详细信息显示label
    QLabel *m_label;
    //测温区域
    AreaRect m_areaRect;
    //底层测温返回的数据
    AreaVal m_areaVal;
    AreaTemp m_areaTemp;
    //保存温度值
    float m_maxTemp;
    float m_minTemp;
    float m_avgTemp;

    //显示温度的最大最小值的坐标点
    QLabel *m_maxCursor;
    QLabel *m_minCursor;
    QLabel *m_avgCursor;

    //Area属性相关
    AreaProperty m_property;
    AreaProperty m_property_temp;
    AreaPropertyWnd *propertyWnd;
};

#endif // ANALYSISAREA_H
