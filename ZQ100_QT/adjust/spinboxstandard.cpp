#include "spinboxstandard.h"
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QEvent>
#include <QTimer>

#define DEF_INTERVAL 3000

/**
 * @name    SpinBoxStandard(QWidget *parent, GlobalParam::Orientation orientation)
 * @details 继承自QLineEdit类,实现了自定义的SpinBoxStandard功能
 * @param   parent  父窗口指针
 * @param   orientation 方向
 * @author  lee
 * @date    2018-11-15
**/
SpinBoxStandard::SpinBoxStandard(QWidget *parent, GlobalParam::Orientation orientation) : QLineEdit(parent)
{
    m_prefix = "";
    m_suffix = "";
    m_decimals = 2;
    m_minimum = 0.00;
    m_maximum = 99.99;
    m_singleStep = 0.1;
    m_value = 0.00;
    m_curOrientation = orientation;
    m_isPressed = false;
    m_longPressInterval = DEF_INTERVAL;

    //添加自定义的加/减按钮
    m_reduceBtn = new QPushButton("-", this);
    m_reduceBtn->setStyleSheet("QPushButton:!enabled{background-color: gray;}");
    m_reduceBtn->setObjectName("reduceBtn");
    m_reduceBtn->setFocusPolicy(Qt::NoFocus);

    m_addBtn = new QPushButton("+",this);
    m_addBtn->setStyleSheet(m_reduceBtn->styleSheet());
    m_addBtn->setObjectName("addBtn");
    m_addBtn->setFocusPolicy(Qt::NoFocus);

    //开启一个定时器判断按键长按事件
    m_longPressTimer = new QTimer(this);

    setReadOnly(true);

    //显示文本数据
    showValue();

    adjustLayout();

    connect(m_reduceBtn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    connect(m_addBtn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    connect(m_longPressTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

/**
 * @name    void adjustLayout()
 * @details 调整各个空间的大小和位置
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::adjustLayout()
{
    //根据该变量实现水平分布和垂直分布
    if(m_curOrientation == GlobalParam::Orientation::HORIZONTAL)
    {
        m_reduceBtn->resize(width()/7.0, height());
        m_addBtn->resize(m_reduceBtn->size());

        m_addBtn->move(width()-m_addBtn->width(), 0);

        setTextMargins(m_addBtn->width(), 0, m_addBtn->width(), 0);
    }
    else
    {
        m_reduceBtn->resize(width(), height()/7.0);
        m_addBtn->resize(m_reduceBtn->size());

        m_addBtn->move(0, 0);
        m_reduceBtn->move(0, height()-m_reduceBtn->height());

        setTextMargins(0, m_addBtn->height(), 0, m_addBtn->height());
    }
}

/**
 * @name    void resizeEvent(QResizeEvent *e)
 * @details 大小变化事件,同事调整布局
 * @param   e   重构大小事件指针
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    setMinimumSize(size());
    setMaximumSize(size());

    adjustLayout();
}

void SpinBoxStandard::focusInEvent(QFocusEvent *e)
{
    selectAll();
    QLineEdit::focusInEvent(e);
}

void SpinBoxStandard::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
}


/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 按键事件,实现按键加减数值和切换焦点, 以及长按判断
 * @param   e   按键事件
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::keyPressEvent(QKeyEvent *e)
{
#if 0
    Qt::Key focusNextKey = Qt::Key_Down;
    Qt::Key focusPreviousKey = Qt::Key_Up;
 #else
    Qt::Key addKey = KEY_PRESS_RIGHT;
    Qt::Key reduceKey = KEY_PRESS_LEFT;

#endif
    Qt::Key focusNextKey = Qt::Key_Down;
    Qt::Key focusPreviousKey = Qt::Key_Up;

    if(m_curOrientation == GlobalParam::Orientation::VERTICAL)
    {
       addKey = Qt::Key_Up;
       reduceKey = Qt::Key_Down;
       focusNextKey = Qt::Key_Right;
       focusPreviousKey = Qt::Key_Left;
    }

    if(e->key() == addKey)
        m_addBtn->click();
    else if(e->key() == reduceKey)
        m_reduceBtn->click();
   // else if(e->key() == focusPreviousKey);
    //    focusPreviousChild();
   // else if(e->key() == focusNextKey);
     //   focusNextChild();
    else if(e->key() == Qt::Key_Return)
        emit clicked(this);
    else
        e->ignore();

    if(!e->isAutoRepeat() && !m_isPressed
            && (e->key() == addKey || e->key() == reduceKey))
    {
        m_isPressed = true;
        m_singleStepTemp = m_singleStep;
        m_longPressTimer->start(m_longPressInterval);
    }
}

/**
 * @name    void keyReleaseEvent(QKeyEvent *e)
 * @details 按键释放事件,
 * @param   e   按键释放事件
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::keyReleaseEvent(QKeyEvent *e)
{
    bool btnRelease = false;
    if(m_curOrientation == GlobalParam::Orientation::HORIZONTAL)
        btnRelease = (e->key() == KEY_PRESS_RIGHT || e->key() == KEY_PRESS_LEFT);
    else
        btnRelease = (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down);

    if(!e->isAutoRepeat() && m_isPressed
            && btnRelease)
    {
        m_isPressed = false;
        m_singleStep = m_singleStepTemp;
        m_longPressTimer->stop();
    }

    QLineEdit::keyReleaseEvent(e);
}

/**
 * @name    void buttonClicked()
 * @details 响应按钮点击信号的槽函数
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::buttonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    //以步进值增减数值
    if(btn->objectName() == "reduceBtn")
        setValue(value()-singleStep());
    else
        setValue(value()+singleStep());
    setFocus();
    selectAll();
}

/**
 * @name    void onTimeout()
 * @details 响应长按定时器超时信号的槽函数
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::onTimeout()
{
    //长按时不断倍增步进值
    if(m_isPressed)
        m_singleStep = m_singleStep*10;
}

/**
 * @name    void showValue()
 * @details 显示数值
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::showValue()
{
    m_addBtn->setEnabled(m_value < m_maximum);
    m_reduceBtn->setEnabled(m_value > m_minimum);

    m_value = m_value > m_maximum ? m_maximum : m_value;
    m_value = m_value < m_minimum ? m_minimum : m_value;

    QString text;
    QString val = QString::number(m_value, 'f', m_decimals);
    text = QString(m_prefix+val+m_suffix);
    setText(text);
}

/**
 * @name    void setValue(double val)
 * @details 设置数值
 * @param   val 数值
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setValue(double val)
{
    m_value = val;

    showValue();
}

/**
 * @name    void setPrefix(const QString &prefix)
 * @details 设置前缀符号
 * @param   prefix 前缀符号
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setPrefix(const QString &prefix)
{
    m_prefix = prefix;

    showValue();
}

/**
 * @name    void setSuffix(const QString &suffix)
 * @details 设置后缀符号
 * @param   suffix 缀符号
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setSuffix(const QString &suffix)
{
    m_suffix = suffix;

    showValue();
}

/**
 * @name    void setSingleStep(double val)
 * @details 设置步进值
 * @param   val 步进值
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setSingleStep(double val)
{
    m_singleStep = val;
}

/**
 * @name    void setMinimum(double min)
 * @details 设置最小值
 * @param   min 最小值
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setMinimum(double min)
{
    m_minimum = min;

    showValue();
}

/**
 * @name    void setMaximum(double max)
 * @details 设置最大值
 * @param   max 最大值
 * @author  lee
 * @date    2018-11-15
**/
void SpinBoxStandard::setMaximum(double max)
{
    m_maximum = max;

    showValue();
}

/**
* @name    void SpinBoxStandard::setRange(double min, double max)
* @details 设置取值范围
* @param   min 最小值
* @param   max 最大值
* @author  lee
* @date    2018-11-15
**/
void SpinBoxStandard::setRange(double min, double max)
{
    m_minimum = min;
    m_maximum = max;

    showValue();
}

/**
* @name    void setDecimals(int prec)
* @details 设置小数位数
* @param   prec 小数位数
* @author  lee
* @date    2018-11-15
**/
void SpinBoxStandard::setDecimals(int prec)
{
    m_decimals = prec;

    showValue();
}

/**
* @name    void setLongPressInterval(int msec)
* @details 设置长按时间
* @param   msec 长按时间,毫秒
* @author  lee
* @date    2018-11-15
**/
void SpinBoxStandard::setLongPressInterval(int msec)
{
    m_longPressInterval = msec;
}

void SpinBoxStandard::moveEvent(QMoveEvent *e)
{
    QLineEdit::moveEvent(e);
    //    adjustLayout();
}

/**
* @name    void mouseDoubleClickEvent(QMouseEvent *e)
* @details 鼠标双击事件,双击时放松点击信号
* @param   e 鼠标事件
* @author  lee
* @date    2018-11-15
**/
void SpinBoxStandard::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        emit clicked(this);
    else
        e->accept();
}
