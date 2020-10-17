#include "spot.h"

#define SPOT_WIDTH  50
#define SPOT_SIZE QSize(SPOT_WIDTH, SPOT_WIDTH)
#define LONGPRESSDURATION   250

#define LABEL_TEXT_COLOR      QString("color: white;")
#define LABEL_SHOW_BACKGROUND QString("background-color: rgba(0, 0, 0, 255);")
#define LABEL_HIDE_BACKGROUND QString("background-color: rgba(0, 0, 0, 0);")
#define LABEL_STYLESHEET      QString("%1%2").arg(LABEL_TEXT_COLOR).arg(LABEL_HIDE_BACKGROUND)

/**
 * @name    Spot(QWidget *parent, int id)
 * @details Spot构造函数。实现点测温的显示和功能
 * @param   parent  父窗口指针
 * @param   id  标示id
 * @author  lee
 * @date    2018-12-20
**/
Spot::Spot(QWidget *parent, int id) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    //    setAttribute(Qt::WA_TranslucentBackground, true);

    setFocusPolicy(Qt::StrongFocus);

    normalPix.load(":/pics/D300/cursor_1.png", nullptr,
                   Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    normalPix = normalPix.scaled(SPOT_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    focusPix.load(":/pics/D300/cursor_0.png", nullptr,
                  Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
    focusPix = focusPix.scaled(SPOT_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setFixedSize(normalPix.size());
    setMask(QBitmap(normalPix.mask()));

    m_id = id;
    isPressed = false;
    singleStep = 1;
    singleStepTemp = singleStep;
    initProperty();

    propertyWnd = new SpotPropertyWnd(this);

    longPressTimer = new QTimer(this);
    connect(longPressTimer, SIGNAL(timeout()), this, SLOT(longPressSlot()));

    updateTempTimer = new QTimer(this);
    connect(updateTempTimer, SIGNAL(timeout()), this, SLOT(updateTempSlot()));

    m_label = new QLabel(parent);
    m_label->setStyleSheet(LABEL_STYLESHEET);
//    m_label->setFont(QFont(font().family(), 11*width()/64));
    m_label->setScaledContents(true);
    m_label->setWindowFlags(Qt::FramelessWindowHint);
    m_label->setAttribute(Qt::WA_DeleteOnClose,true);

    //目前有八点测温点，以下为各点初始坐标
    const QPoint SpotPosBuf[MAXSPOTNUM] = {
        QPoint((SCREEN_WIDTH-width())/2, (SCREEN_HEIGHT-height())/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH*3/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT/6-height()/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT*3/6-height()/2),
        QPoint(SCREEN_WIDTH*5/6-width()/2, SCREEN_HEIGHT*3/6-height()/2),
        QPoint(SCREEN_WIDTH/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
        QPoint(SCREEN_WIDTH*3/6-width()/2, SCREEN_HEIGHT*5/6-height()/2),
    };

    move(SpotPosBuf[m_id]);
}

/**
 * @name    void mousePressEvent(QMouseEvent *event)
 * @details 鼠标点击事件。鼠标点击时记录点击位置，为拖动功能提供数据。
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::mousePressEvent(QMouseEvent *event)
{
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
 * @name    void mouseMoveEvent(QMouseEvent *event)
 * @details 鼠标移动事件。实现该Spot在鼠标拖动状态下跟随移动。
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::mouseMoveEvent(QMouseEvent *event)
{
    if(/*isPressed &&*/ event->buttons() & Qt::LeftButton)
    {
        QPoint position = event->globalPos()-dragPosition;
        move(position);
        event->accept();
    }
}

/**
 * @name    void mouseReleaseEvent(QMouseEvent *event)
 * @details 鼠标释放事件
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

/**
 * @name    void mouseDoubleClickEvent(QMouseEvent *event)
 * @details 鼠标双击事件。双击Spot唤出属性窗口
 * @param   event   鼠标事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::mouseDoubleClickEvent(QMouseEvent *event)
{
    //    QMessageBox::information(this, QString("Spot %1").arg(m_id), "I am Spot!", QMessageBox::Ok);
    propertyWnd->exec();
}

/**
 * @name    void paintEvent(QPaintEvent *event)
 * @details 绘图事件。根据是否获得焦点显示不同的Spot图标
 * @param   event   绘图事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(hasFocus())
        painter.drawPixmap(0, 0, normalPix);
    else
        painter.drawPixmap(0, 0, focusPix);

    QWidget::paintEvent(event);
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 按下按键事件。方向键移动Spot位置，回车键唤出属性窗口。长按时启动长按定时器，修改移动步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::keyPressEvent(QKeyEvent *event)
{
    QPoint position(pos());
    if(!isPressed )
    {
        isPressed = true;
        longPressTimer->start(LONGPRESSDURATION);
        singleStepTemp = singleStep;
    }
    if(event->key() == Qt::Key_Escape)
        event->ignore();
    if(event->key() == Qt::Key_Return)
        mouseDoubleClickEvent(0);
    //    else
    {
        if(event->key() == Qt::Key_Left)
        {
            position.setX(position.x()-singleStep);
        }
        else if(event->key() == Qt::Key_Right)
        {
            position.setX(position.x()+singleStep);
        }
        if(event->key() == Qt::Key_Up)
        {
            position.setY(position.y()-singleStep);
        }
        else if(event->key() == Qt::Key_Down)
        {
            position.setY(position.y()+singleStep);
        }
        move(position);
    }
}

/**
 * @name    void keyReleaseEvent(QKeyEvent *event)
 * @details 释放按键事件。停止长按定时器，并重置步进值
 * @param   event   按键事件指针
 * @author  lee
 * @date    2018-12-20
**/
void Spot::keyReleaseEvent(QKeyEvent *event)
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
 * @name    void move(int x, int y)
 * @details 重写move函数，限制x，y的值，并刷新温度
 * @param   x   横坐标
 * @param   y   纵坐标
 * @author  lee
 * @date    2018-12-20
**/
void Spot::move(int x, int y)
{
    x = (x < -width()/2 ? -width()/2 : x);
    x = (x > SCREEN_WIDTH-width()/2 ? SCREEN_WIDTH-width()/2 : x);
    y = (y < -height()/2 ? -height()/2 : y);
    y = (y > SCREEN_HEIGHT-height()/2 ? SCREEN_HEIGHT-height()/2 : y);

    QWidget::move(x, y);
    updateTempSlot();
}

/**
 * @name    inline void move(QPoint p)
 * @details 重写move函数，限制x，y的值
 * @param   p   移动点的坐标
 * @author  lee
 * @date    2018-12-20
**/
inline void Spot::move(QPoint p)
{
    move(p.x(), p.y());
}

/**
 * @name    void show()
 * @details 重写show函数，调用setDisplay
 * @author  lee
 * @date    2018-12-20
**/
void Spot::show()
{
    //    raise();
    setDisplay(1);
}

/**
 * @name    void hide()
 * @details 重写hide函数，调用setDisplay
 * @author  lee
 * @date    2018-12-20
**/
void Spot::hide()
{
    setDisplay(0);
}

/**
 * @name    void close()
 * @details 重写close函数，关闭Spot，也关闭温度显示label
 * @author  lee
 * @date    2018-12-20
**/
void Spot::close()
{
    m_label->close();

    QWidget::close();
}

/**
 * @name    float getTemp()
 * @details 返回Spot的温度
 * @return  Spot当前的温度值
 * @author  lee
 * @date    2018-12-20
**/
float Spot::getTemp()
{
    return m_curTemp;
}

/**
 * @name    int id()
 * @details 返回Spot的标示id
 * @return  Spot的标示id
 * @author  lee
 * @date    2018-12-20
**/
int Spot::id()
{
    return m_id;
}

/**
 * @name    void initProperty()
 * @details 初始化Spot的属性
 * @author  lee
 * @date    2018-12-20
**/
void Spot::initProperty()
{
    m_property.displayMode = 1;
    m_property.analysisMode = 0;
    m_property.posShowMode = 0;
    m_property.tempShowMode = 1;
    m_property.backgroundMode = 0;
    m_property.alarmMode = 0;
    m_property.alarmTempVal = 0.0;
    m_property_temp = m_property;
}

/**
 * @name    void setDisplay(int displayMode)
 * @details 根据displayMode的值，激活Spot，温度显示label和更新温度定时器
 * @param  displayMode 0:off 1:on
 * @date    2018-12-20
**/
void Spot::setDisplay(int displayMode)
{
    switch (displayMode) {
    case 0://hide
    {
        m_label->hide();
        QWidget::hide();
        updateTempTimer->stop();
        break;
    }
    case 1://show
    {
//        raise();
        setFocus();
        m_label->show();
        QWidget::show();
        updateTempTimer->start(1000);
        //更新Display属性
        m_property_temp = m_property;
        break;
    }
    default:
        break;
    }
    m_property.displayMode = displayMode;
}

/**
 * @name    void setMode(int mode)
 * @details 根据mode的值，改变Spot测温的方式
 * @param  mode 0:Manual 1:Max 2:min
 * @date    2018-12-20
**/
void Spot::setMode(int mode)
{
    switch (mode) {
    case 0://Manual
        qWarning("Set Manual Mode!");
        break;
    case 1://Max
        qWarning("Set Max Mode!");
        break;
    case 2://Min
        qWarning("Set Min Mode!");
        break;
    default:
        break;
    }
    m_property.analysisMode = mode;
}

/**
 * @name    void setPosShow(int posShow)
 * @details 根据posShow的值，设置是否显示坐标
 * @param  posShow 0:off 1:on
 * @date    2018-12-20
**/
void Spot::setPosShow(int posShow)
{
    switch (posShow) {
    case 0://Off
        qWarning("Pos Off!");
        break;
    case 1://On
        qWarning("Pos On!");
        break;
    default:
        break;
    }
    m_property.posShowMode = posShow;
}

/**
 * @name    void setTempShow(int tempShow)
 * @details 根据tempShow的值，设置是否显示温度
 * @param  tempShow 0:off 1:on
 * @date    2018-12-20
**/
void Spot::setTempShow(int tempShow)
{
    switch (tempShow) {
    case 0://Off
        qWarning("temp Off!");
        break;
    case 1://On
        qWarning("temp On!");
        break;
    default:
        break;
    }
    m_property.tempShowMode = tempShow;
}

/**
 * @name    void setBackground(int background)
 * @details 根据background的值，设置是否显示背景
 * @param  background 0:hide 1:show
 * @date    2018-12-20
**/
void Spot::setBackground(int background)
{
    switch (background) {
    case 0://hide
        m_label->setStyleSheet(LABEL_TEXT_COLOR+LABEL_HIDE_BACKGROUND);
        break;
    case 1://show
        m_label->setStyleSheet(LABEL_TEXT_COLOR+LABEL_SHOW_BACKGROUND);
        break;
    default:
        break;
    }
    m_property.backgroundMode = background;
}

/**
 * @name    void setAlarmMode(int alramMode)
 * @details 根据alramMode的值，设置温度报警的方式
 * @param  alramMode 0:off 1:Above 2:Below 3:Equal
 * @date    2018-12-20
**/
void Spot::setAlarmMode(int alramMode)
{
    switch (alramMode) {
    case 0://Off
        qWarning("alramMode Off!");
        break;
    case 1://Above
        qWarning("alramMode Above!");
        break;
    case 2://Below
        qWarning("alramMode Below!");
        break;
    case 3://Equal
        qWarning("alramMode Equal!");
        break;
    default:
        break;
    }
    m_property.alarmMode = alramMode;
}

/**
 * @name    void setAlarmTemp(float alarmTemp)
 * @details 设置报警的温度
 * @param   alarmTemp 报警温度
 * @date    2018-12-20
**/
void Spot::setAlarmTemp(float alarmTemp)
{
    m_property.alarmTempVal = alarmTemp;
}

/**
 * @name    void rollbackProperty()
 * @details 撤销属性更改，恢复更改前的状态

 * @date    2018-12-20
**/
void Spot::rollbackProperty()
{
    m_property = m_property_temp;
    _setProperty(m_property);
}

/**
 * @name    void commitProperty()
 * @details 确认更改属性

 * @date    2018-12-20
**/
void Spot::commitProperty()
{
    m_property_temp = m_property;
}

/**
 * @name    void _setProperty(SpotProperty property)
 * @details 设置属性值
 ×
 * @date    2018-12-20
**/
void Spot::_setProperty(SpotProperty property)
{
    setDisplay(property.displayMode);
    setMode(property.analysisMode);
    setPosShow(property.posShowMode);
    setTempShow(property.tempShowMode);
    setBackground(property.backgroundMode);
    setAlarmMode(property.alarmMode);
    setAlarmTemp(property.alarmTempVal);
    m_property = property;
}

//int Spot::getDisplay()
//{
//    return m_property.displayMode;
//}

//int Spot::getMode()
//{
//    return m_property.analysisMode;
//}

//int Spot::getPosShow()
//{
//    return m_property.posShowMode;
//}

//int Spot::getTempShow()
//{
//    return m_property.tempShowMode;
//}

//int Spot::getBackground()
//{
//    return m_property.backgroundMode;
//}

//int Spot::getAlarmMode()
//{
//    return m_property.alarmMode;
//}

//float Spot::getAlarmTemp()
//{
//    return m_property.alarmTempVal;
//}

/**
 * @name    SpotProperty _getProperty()
 * @details 读取Spot的属性
 * @return  Spot的属性值
 * @date    2018-12-20
**/
SpotProperty Spot::_getProperty()
{
    return m_property;
}

/**
 * @name    void adjustLabelPos()
 * @details 调整显示Label的位置
 * @date    2018-12-20
**/
void Spot::adjustLabelPos()
{
    QPoint labelPos = pos()+QPoint(width()/2, height()/2);
    int spacing = 3;
    if(labelPos.x() < SCREEN_WIDTH/2)
        labelPos.setX(labelPos.x()+spacing);
    else
        labelPos.setX(labelPos.x()-m_label->width()-spacing);
    if(labelPos.y() < SCREEN_HEIGHT/2)
        labelPos.setY(labelPos.y()+spacing);
    else
        labelPos.setY(labelPos.y()-m_label->height()-spacing);

    m_label->move(labelPos);
}

/**
 * @name    void moveEvent(QMoveEvent *event)
 * @details 重写移动事件，调整显示Label的位置
 * @param   event   移动事件
 * @date    2018-12-20
**/
void Spot::moveEvent(QMoveEvent *event)
{
    adjustLabelPos();
    QWidget::moveEvent(event);
}

/**
 * @name    void focusInEvent(QFocusEvent *event)
 * @details 获得焦点事件
 * @param   event   焦点事件指针
 * @date    2018-12-20
**/
void Spot::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
    //    this->raise();
}

/**
 * @name    void focusOutEvent(QFocusEvent *event)
 * @details 失去焦点事件
 * @param   event   焦点事件指针
 * @date    2018-12-20
**/
void Spot::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
    //    this->lower();
}

/**
 * @name    void updateText()
 * @details 更新显示Label
 * @date    2018-12-21
**/
void Spot::updateText()
{
    QString text = QString("%1:").arg(m_id);
    QString posText = QString("\n(%1, %2)").arg(pos().x()+SPOT_WIDTH/2).arg(pos().y()+SPOT_WIDTH/2);
#ifdef SHOWTEMP
    QString tempText =(!m_curTemp ? QString(">>>>>") :
                                    (QString::number(m_curTemp, 'f', 1)));
#else
    QString tempText =(!m_irtempstru.AD ? QString(">>>>>") :
                                    ("0x"+QString::number(m_irtempstru.AD, 16)));
#endif
    if(m_property.tempShowMode == 1)
        text += tempText;
    if(m_property.posShowMode == 1)
        text += posText;
    if(m_property.tempShowMode == 0
            && m_property.posShowMode == 0)
        text = QString::number(m_id);

    if(m_label->text() != text)
    {
        m_label->setText(text);
        m_label->adjustSize();
        adjustLabelPos();
    }
}

/**
 * @name    void longPressSlot()
 * @details 长按处理槽，改变移动的步进值
 * @date    2018-12-21
**/
void Spot::longPressSlot()
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

/**
 * @name    void updateTempSlot()
 * @details 刷新温度槽，从底层读取温度数据并刷新显示
 * @date    2018-12-21
**/
void Spot::updateTempSlot()
{
    QPoint position;
    position.setX(pos().x()+SPOT_WIDTH/2);
    position.setY(pos().y()+SPOT_WIDTH/2);

    if(GlobalParam::getFPGA()->getSpotTemp(m_id, position, m_irtempstru, 0) < 0)
    {
        //                qWarning("read spot temp failed");
        qsrand(QTime(m_id,m_id,m_id).secsTo(QTime::currentTime()));
        m_curTemp = qrand()%100+qrand()%10*0.1;
    }
    else
        m_curTemp = m_irtempstru.temp;
    updateText();
    updateAlarmWarning();
}

/**
 * @name    void updateAlarmWarning()
 * @details 根据报警温度和报警模式进行温度监测
 * @date    2018-12-21
**/
void Spot::updateAlarmWarning()
{
    switch (m_property.alarmMode) {
    case 1://Above
        if(m_curTemp > m_property.alarmTempVal)
        {
            qWarning("above temp!!!Beep!");
            return;
        }
        break;
    case 2://Below
        if(m_curTemp < m_property.alarmTempVal)
        {
            qWarning("below temp!!!Beep!");
            return;
        }
        break;
    case 3://Equal
        if(m_curTemp == m_property.alarmTempVal)
        {
            qWarning("equal temp!!!Beep!");
            return;
        }
        break;
    default:
        break;
    }
    //    if(isBeeping)
    //        qWarning("stop Beep!!");
}
