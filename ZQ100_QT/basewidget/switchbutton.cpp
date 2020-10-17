#include "switchbutton.h"

/**
 * @name    SwitchButton(QWidget *parent, QString text0, QString text1)
 * @details SwitchButton的构造函数，初始化显示及功能
 * @param   parent  父窗口指针
 * @param   text0   开关的左侧文字
 * @param   text1   开关的右侧文字
 * @author  lee
 * @date    2018-12-21
**/
SwitchButton::SwitchButton(QWidget *parent, QString text0, QString text1) : QWidget(parent)
{
    m_leftBtn = new QPushButton(text0);
    m_rightBtn = new QPushButton(text1);

    m_leftBtn->installEventFilter(this);
    m_rightBtn->installEventFilter(this);

    m_leftBtn->setCheckable(true);
    m_rightBtn->setCheckable(true);

    m_leftBtn->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127);}\
                               QPushButton:checked{background-color: rgb(0, 100, 200);}");
    m_rightBtn->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127);}\
                               QPushButton:checked{background-color: rgb(0, 100, 200);}");
    setState(false);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_leftBtn);
    mainLayout->addWidget(m_rightBtn);

    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(m_leftBtn, 0);
    btnGroup->addButton(m_rightBtn, 1);

    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));
}

/**
 * @name    void setState(bool state)
 * @details 设置开关的状态
 * @param   state  0:off 1:on
 * @author  lee
 * @date    2018-12-21
**/
void SwitchButton::setState(bool state)
{
    m_state = state;
    m_leftBtn->setChecked(!state);
    m_rightBtn->setChecked(state);
}

/**
 * @name    bool getState()
 * @details 获取开关的状态
 * @return   开关的状态  0:off 1:on
 * @author  lee
 * @date    2018-12-21
**/
bool SwitchButton::getState()
{
    return m_state;
}

/**
 * @name    bool eventFilter(QObject *watched, QEvent *event)
 * @details 事件过滤器，自定义按键的功能
 * @param   watched 检测的对象
 * @param   event 检测的事件
 * @author  lee
 * @date    2018-12-21
**/
bool SwitchButton::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (watched == m_leftBtn || watched == m_rightBtn) {
            if(keyEvent->key() == Qt::Key_Up)
                focusPreviousChild();
            else if(keyEvent->key() == Qt::Key_Down)
                focusNextChild();
            else if(keyEvent->key() == Qt::Key_Left)
                setState(false);
            else if(keyEvent->key() == Qt::Key_Right)
                setState(true);
            else
                keyEvent->ignore();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @name    void buttonClicked(int id)
 * @details 点击时，切换开关
 * @param   id buttonid
 * @author  lee
 * @date    2018-12-21
**/
void SwitchButton::buttonClicked(int id)
{
    setState(id);
}

