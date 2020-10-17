#include "unitsettingpage.h"
#include "basewidget/switchbutton.h"
#include "tmainpage.h"

/**
 * @name    UnitSettingPage(QWidget *parent)
 * @details 单位设置窗口，用于修改温度和长度的单位
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-12-21
**/
UnitSettingPage::UnitSettingPage(QWidget *parent) : QDialog(parent)
{
    initView();
}

/**
 * @name    void initView()
 * @details 初始化单位设置窗口的显示和功能
 * @author  lee
 * @date    2018-12-21
**/
void UnitSettingPage::initView()
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    QLabel *title = new QLabel("Unit Setting");
    title->setFont(QFont(font().family(), -1, QFont::Bold));
    title->setAlignment(Qt::AlignCenter);
    title->setFocusPolicy(Qt::NoFocus);
    title->setFixedHeight(30);

    QWidget *centralWidget = new QWidget;

    m_lengthSwitch = new SwitchButton(0, "Meter", "Foot");
    m_tempSwitch = new SwitchButton(0, "°C", "°F");

    m_lengthSwitch->setFocus();

    updateLabels();

    QGridLayout *widgetLayout = new QGridLayout(centralWidget);
    widgetLayout->addWidget(new QLabel("Length: "), 0, 0);
    widgetLayout->addWidget(m_lengthSwitch, 0, 1);
    widgetLayout->addWidget(new QLabel("Temp: "), 1, 0);
    widgetLayout->addWidget(m_tempSwitch, 1, 1);

    QPushButton *btn1 = new QPushButton("Cancel");
    QPushButton *btn2 = new QPushButton("Ok");

    btn1->setFocusPolicy(Qt::NoFocus);
    btn2->setFocusPolicy(Qt::NoFocus);
    btn1->setFixedHeight(30);
    btn2->setFixedHeight(btn1->height());


    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(0);
    bottomLayout->addWidget(btn1);
    bottomLayout->addWidget(btn2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(title);
    mainLayout->addWidget(centralWidget);
    mainLayout->addLayout(bottomLayout);

    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

/**
 * @name    void updateLabels()
 * @details 更新当前的单位显示
 * @author  lee
 * @date    2018-12-21
**/
void UnitSettingPage::updateLabels()
{
//    //qDebug()<<GlobalParam::getLengthUnit();
//    //qDebug()<<GlobalParam::getTempUnit();

    m_lengthSwitch->setState(GlobalParam::getLengthUnit());
    m_tempSwitch->setState(GlobalParam::getTempUnit());
}

/**
 * @name    void accept()
 * @details 保存当前的单位设置，并更新主界面的单位显示
 * @author  lee
 * @date    2018-12-21
**/
void UnitSettingPage::accept()
{
    GlobalParam::setLengthUnit(m_lengthSwitch->getState()?1:0);
    GlobalParam::setTempUnit(m_tempSwitch->getState()?1:0);

//    //qDebug()<<m_lengthSwitch->getState()<<","<<GlobalParam::getLengthUnit();
//    //qDebug()<<m_tempSwitch->getState()<<","<<GlobalParam::getTempUnit();

    GlobalParam::getParentWidget()->updateLabels();

    QDialog::accept();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义回车和Esc键的功能
 * @param   e  按键事件

 * @date    2018-11-21
**/
void UnitSettingPage::keyPressEvent(QKeyEvent *e)
{
    qWarning("UnitSettingPage");
    if(e->key() == Qt::Key_Escape)
        reject();
    else if(e->key() == Qt::Key_Return)
        accept();
    else
        e->accept();
}
