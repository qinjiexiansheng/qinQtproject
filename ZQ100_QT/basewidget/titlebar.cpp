#include "titlebar.h"

/**
 * @name    TitleBar(QWidget *parent, GlobalParam::TitleBarStyle type, int height, int width)
 * @details 自定义标题栏
 * @param   parent  父窗口
 * @param   type    标题栏样式,单按钮,双按钮,开关样式
 * @param   height  标题高度
 * @param   width   标题宽度

 * @date    2018-11-15
**/
TitleBar::TitleBar(QWidget *parent, GlobalParam::TitleBarStyle type, int height, int width)
    : QWidget(parent)
{
    m_title = NULL;
    m_button1 = NULL;
    m_button2 = NULL;
    m_switch = NULL;

    initView(type, width, height);

}

/**
 * @name    void initView(GlobalParam::TitleBarStyle type, int width, int height)
 * @details 初始化显示
 * @param   type    标题栏样式,单按钮,双按钮,开关样式
 * @param   height  标题高度
 * @param   width   标题宽度

 * @date    2018-11-15
**/
void TitleBar::initView(GlobalParam::TitleBarStyle type, int width, int height)
{
    setWindowFlags(Qt::FramelessWindowHint);

    QFont fontStyle(font().family(), -1, QFont::Bold);

    m_title = new QLabel("UNTITLED");
    m_title->setFont(fontStyle);
    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFocusPolicy(Qt::NoFocus);
    m_title->setFixedSize(width/10.0*6.0, height);

    m_button1 = new QPushButton("BACK");
    m_button1->setFont(fontStyle);
    m_button1->setObjectName("BUTTON1");
    m_button1->setFocusPolicy(Qt::NoFocus);
    m_button1->setFixedSize(width/10.0*2.0, height-2);
    connect(m_button1, SIGNAL(clicked(bool)), this, SLOT(on_clicked(bool)));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_button1);
    mainLayout->addWidget(m_title);

    //根据type设置标题栏样式
    switch (type) {
    case  GlobalParam::TitleBarStyle::DOUBLE_BUTTON:
    {
        m_button2 = new QPushButton("Save");
        m_button2->setObjectName("BUTTON2");
        m_button2->setFont(fontStyle);
        m_button2->setFocusPolicy(Qt::NoFocus);
        m_button2->setFixedSize(m_button1->size());
        connect(m_button2, SIGNAL(clicked(bool)), this, SLOT(on_clicked(bool)));
        mainLayout->addWidget(m_button2);
        break;
    }
    case  GlobalParam::TitleBarStyle::SWITCH_BUTTON:
    {
        QString qss=tr("QPushButton {\
                       border:0px;\
                        border-image: url(%1);\
                        outline: none;  \
                            }\
                        QPushButton:checked {\
                                    border-image: url(%2);\
                                }").arg(":/pics/D300/switch_off.png").arg(":/pics/D300/switch_on.png");
        m_switch = new QPushButton;
        m_switch->setObjectName("SWITCH");
        m_switch->setStyleSheet(qss);
        m_switch->setCheckable(true);
        m_switch->setFocusPolicy(Qt::NoFocus);
        m_switch->setFixedSize(m_button1->size());
        connect(m_switch, SIGNAL(toggled(bool)), this, SLOT(on_clicked(bool)));
        mainLayout->addWidget(m_switch);
        break;
    }
        default:
            break;
    }

    setFixedSize(mainLayout->sizeHint());
}

/**
 * @name    void setText(QString title, QString button1, QString button2)
 * @details 设置显示的文本
 * @param   title    标题文本
 * @param   button1  左按键文本
 * @param   button2  右按键的文本

 * @date    2018-11-15
**/
void TitleBar::setText(QString title, QString button1, QString button2)
{
    m_title->setText(title);
    m_button1->setText(button1);
    if(m_button2)
        m_button2->setText(button2);
}

/**
 * @name    void setSwitchState(bool val)
 * @details 设置开关状态
 * @param   val 开关状态

 * @date    2018-11-15
**/
void TitleBar::setSwitchState(bool val)
{
    if(m_switch)
    {
        m_switch->setChecked(val);
    }
}

/**
 * @name    bool getSwitchState()
 * @details 获取开关状态
 * @param   val 开关状态

 * @date    2018-11-15
**/
bool TitleBar::getSwitchState()
{
    if(m_switch)
        return m_switch->isChecked();
    return false;
}

/**
 * @name    void setSwitchEnable(bool val)
 * @details 设置开关有效状态
 * @param   val 有效状态

 * @date    2018-11-15
**/
void TitleBar::setSwitchEnable(bool val)
{
    m_switch->setEnabled(val);
}

/**
 * @name    bool switchIsEnable(
 * @details 获取开关有效状态
 * @return  开关有效状态

 * @date    2018-11-15
**/
bool TitleBar::switchIsEnable()
{
    return m_switch->isEnabled();
}

/**
 * @name    void on_clicked(bool status)
 * @details 按键点击信号的槽函数
 * @param   status  checked状态,默认为false,当BUTTON_SWITCH时为实际的checked状态

 * @date    2018-11-15
**/
void TitleBar::on_clicked(bool status)
{
    QString objName = sender()->objectName();
    GlobalParam::ButtonType id;

    if(objName == "BUTTON1")
        id = GlobalParam::ButtonType::BUTTON_LEFT;
    else if(objName == "BUTTON2")
        id = GlobalParam::ButtonType::BUTTON_RIGHT;
    else if(objName == "SWITCH")
        id = GlobalParam::ButtonType::BUTTON_SWITCH;
    else
        id = GlobalParam::ButtonType::NONE_BUTTON;
    //发送点击信号
    emit clicked(id, status);
}
