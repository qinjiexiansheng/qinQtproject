#include "timesettingpage.h"
#include "basewidget/titlebar.h"
#include "basewidget/slidewidget.h"
#include "basewidget/dateeditor.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTime>
#include <QDate>
#include <QTimeZone>
#include <QDebug>
#include <QDateTime>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QButtonGroup>

/**
 * @name    TimeSettingPage(QWidget *parent)
 * @details 时间设置界面
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-11-19
**/
TimeSettingPage::TimeSettingPage(QWidget *parent) : QDialog(parent)
{
    initView();

    QTimer *updateTimer = new QTimer(this);

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    updateTimer->start(1000);

}

/**
 * @name    void initView()
 * @details 初始化设置时间界面的显示和相关槽函数的链接
 * @author  lee
 * @date    2018-11-19
**/
void TimeSettingPage::initView()
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    m_titleBar = new TitleBar(this, GlobalParam::TitleBarStyle::SINGLE_BUTTON, 40, SCREEN_WIDTH);
    m_titleBar->setText("Date & Time", "Back");
    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)),
            this,SLOT(on_titleBarClicked(GlobalParam::ButtonType,bool)));

    centralWidget = new QWidget;
    centralWidget->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT-m_titleBar->height());

    m_dateLabel = new QLabel;
    m_timeLabel = new QLabel;
    m_timezoneLabel= new QLabel;

    m_dateLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timezoneLabel->setAlignment(Qt::AlignCenter);

    m_dateLabel->setFrameStyle(QFrame::Panel);
    m_timeLabel->setFrameStyle(QFrame::Panel);
    m_timezoneLabel->setFrameStyle(QFrame::Panel);

    updateTime();

    QPushButton *dateBtn = new QPushButton("Set Date");
    QPushButton *timeBtn = new QPushButton("Set time");
    QPushButton *timezoneBtn = new QPushButton("Set timezone");

    QButtonGroup *btnGroup = new QButtonGroup;
    btnGroup->addButton(dateBtn, 0);
    btnGroup->addButton(timeBtn, 1);
    btnGroup->addButton(timezoneBtn, 2);

    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(showSettingPage(int)));

    QGridLayout *widgetLayout = new QGridLayout(centralWidget);
    widgetLayout->addWidget(m_dateLabel, 0, 0);
    widgetLayout->addWidget(dateBtn, 0, 1);
    widgetLayout->addWidget(m_timeLabel, 1, 0);
    widgetLayout->addWidget(timeBtn, 1, 1);
    widgetLayout->addWidget(m_timezoneLabel, 2, 0);
    widgetLayout->addWidget(timezoneBtn, 2, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(centralWidget);
}

/**
 * @name    void on_titleBarClicked(GlobalParam::ButtonType id, bool status)()
 * @details 处理标题栏信号的槽函数
 * @param   id  响应的按键类型
 * @param   status  响应的按键状态,默认为false,BUTTON_SWITCH时为实际的checked状态
 * @author  lee
 * @date    2018-11-19
**/
void TimeSettingPage::on_titleBarClicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
    {
        //关闭
        close();
    }
}

/**
 * @name    void updateTime()
 * @details 刷新当前时间、日期和时区
 * @author  lee
 * @date    2018-11-21
**/
void TimeSettingPage::updateTime()
{
    m_dateLabel->setText(QDate::currentDate().toString("yyyy-MM-dd"));

    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if(m_showColon)
    {
        text[2]=':';
        m_showColon=false;
    }
    else
    {
        text[2]=' ';
        m_showColon=true;
    }

    m_timeLabel->setText(text);

    m_timezoneLabel->setText(QString(QTimeZone::systemTimeZoneId()));
}

/**
 * @name    void showSettingPage(int btnId)
 * @details 根据按键唤出对应的设置界面
 * @author  lee
 * @date    2018-11-21
**/
void TimeSettingPage::showSettingPage(int btnId)
{
    QStringList list;

    switch (btnId) {
    case 0:
    {
        DateEditor *w = new DateEditor;
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
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
        SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::TIME);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setLButton("Cancel");
        w->setRButton("Ok");

        w->setTitle("Time Setting");
        for(int i=0; i<24;i++)
            list<<QString::number(i);
        w->addItems(&list);
        list.clear();
        for(int i=0; i<60;i++)
            list<<QString("%1").arg(i, 2, 10, QChar('0'));
        w->addItems(&list, 1);
        w->setCurrentText(QTime::currentTime().hour());
        w->setCurrentText(QTime::currentTime().minute(), 1);
        w->setSeparatorText(":");

        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            //        m_timezoneLabel->setText(w->getCurrentText());
            qWarning("Image Mode: Ok");
        }
        break;
    }
    case 2:
    {
        SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::TIMEZONE);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        w->setTitle("TimeZone Setting");
        list<<"Europe/London"<<"Europe/Berlin"<<"Europe/Athens"
           <<"Europe/Oslo"<<"America/New_York"<<"America/Los_Angeles"<<"Asia/Shanghai"<<"Asia/Hong_Kong"
          <<"Asia/Tokyo"<<"Australia/Brisbane";
        w->addItems(&list);
        w->setCurrentText(GlobalParam::getTimeZoneTemp());
        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            //        m_timezoneLabel->setText(w->getCurrentText());
            qWarning("Image Mode: Ok");
        }
        break;
    }
    }

    updateTime();
}
