#include "powermanagerpage.h"
#include "basewidget/titlebar.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QGridLayout>
#include "basewidget/slidewidget.h"

PowerManagerPage::PowerManagerPage(QWidget *parent) : QDialog(parent)
{
    initView();
}

void PowerManagerPage::initView()
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    m_titleBar = new TitleBar(this, GlobalParam::TitleBarStyle::SINGLE_BUTTON, 40, SCREEN_WIDTH);
    m_titleBar->setText("Power Manager", "Back");
    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)),
            this,SLOT(on_titleBarClicked(GlobalParam::ButtonType,bool)));

    centralWidget = new QWidget;
    centralWidget->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT-m_titleBar->height());

    m_screenSaverLabel = new QLabel;
    m_powerOffLabel = new QLabel;

    m_screenSaverLabel->setAlignment(Qt::AlignCenter);
    m_powerOffLabel->setAlignment(Qt::AlignCenter);

    m_screenSaverLabel->setFrameStyle(QFrame::Panel);
    m_powerOffLabel->setFrameStyle(QFrame::Panel);

    updateLabels();

    QPushButton *screenSaverBtn = new QPushButton("Set Screen Saver");
    QPushButton *powerOffBtn = new QPushButton("Set Power Off");

    QButtonGroup *btnGroup = new QButtonGroup;
    btnGroup->addButton(screenSaverBtn, 0);
    btnGroup->addButton(powerOffBtn, 1);

    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(showSettingPage(int)));

    QGridLayout *widgetLayout = new QGridLayout(centralWidget);
    widgetLayout->addWidget(m_screenSaverLabel, 0, 0);
    widgetLayout->addWidget(screenSaverBtn, 0, 1);
    widgetLayout->addWidget(m_powerOffLabel, 1, 0);
    widgetLayout->addWidget(powerOffBtn, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(centralWidget);
}

void PowerManagerPage::updateLabels()
{
    m_screenSaverLabel->setText(GlobalParam::getScreenSaver());
    m_powerOffLabel->setText(GlobalParam::getPowerOff());
}

/**
 * @name    void showSettingPage(int btnId)
 * @details 根据按键唤出对应的设置界面
 * @author  lee
 * @date    2018-11-21
**/
void PowerManagerPage::showSettingPage(int btnId)
{
    QStringList list;
    switch (btnId) {
    case 0:
    {
        SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::SCREENSAVER);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        w->setTitle("Screensaver Setting");

        list<<"Off"<<"30 Seconds"<<"1 minute"<<"2 minutes"<<"3 minutes"
           <<"5 minutes"<<"10 minutes"<<"20 minutes"<<"30 minutes";
        w->addItems(&list);

        w->setCurrentText(GlobalParam::getScreenSaver());

        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            //        m_timezoneLabel->setText(w->getCurrentText());
            qWarning("Image Mode: Ok");
        }
        break;
    }
    case 1:
    {
        SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::POWEROFF);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        w->setTitle("Poweroff Setting");

        list<<"Off"<<"1 minute"<<"3 minutes"<<"5 minutes"<<"10 minutes"<<"20 minutes"
           <<"30 minutes"<<"45 minutes"<<"60 minutes"<<"90 minutes"<<"120 minutes"
             <<"180 minutes"<<"240 minutes";
        w->addItems(&list);

        w->setCurrentText(GlobalParam::getPowerOff());

        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            //        m_timezoneLabel->setText(w->getCurrentText());
            qWarning("Image Mode: Ok");
        }
        break;
    }
    }
    updateLabels();
}

/**
 * @name    void on_titleBarClicked(GlobalParam::ButtonType id, bool status)()
 * @details 处理标题栏信号的槽函数
 * @param   id  响应的按键类型
 * @param   status  响应的按键状态,默认为false,BUTTON_SWITCH时为实际的checked状态
 * @author  lee
 * @date    2018-11-19
**/
void PowerManagerPage::on_titleBarClicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
    {
        //关闭
        close();
    }
}
