#include "systemsettingpage.h"
#include "basewidget/optionslistwidget.h"
#include "basewidget/slidewidget.h"
#include "updatepage.h"
#include "timesettingpage.h"
#include "wifimanagerpage.h"
#include "powermanagerpage.h"
#include "unitsettingpage.h"
#include "controlpage.h"
/**
 * @name    SystemSettingPage(QWidget *parent)
 * @details StstemSetting界面,实现了界面显示和控制功能
 * @param   parent  父窗口指针

 * @date    2018-11-15
**/
SystemSettingPage::SystemSettingPage(QWidget *parent) : QDialog(parent)
{
    QStringList optionsName;
    optionsName<<"Language"<<"Update"<<"Date & Time"<<"Control"<<"Unit Setting"<<"Wifi Manager"<<"Power Manager";

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    centralWidget= new OptionsListWidget(this, "System Setting", optionsName.count());
    centralWidget->setStyleSheet("color: rgb(255, 255, 255);\
                     background-color: rgb(0, 155, 155)");
    centralWidget->setFixedSize(size());
    //设置选项
    for(int i=0; i<optionsName.count(); i++)
    {
        centralWidget->setOption(i, optionsName[i]);
        centralWidget->setExtraText(i, ">");
    }

    connect(centralWidget, SIGNAL(optionsClickedSig(int)), this, SLOT(optionsClicked(int)));
}

/**
 * @name   void optionsClicked(int index)
 * @details 响应选项点击事件

 * @date    2018-11-15
**/
void SystemSettingPage::optionsClicked(int index)
{
    switch (index) {
    case 0:
    {
        //打开语言选择窗口
        SlideWidget *w = new SlideWidget(0, 40, 40);
        w->setStyleSheet(CHILDPAGE_STYLESHEET);
        w->setTitle("Language Setting");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        QStringList list;
        list.clear();
        list<<"English"<<"Chinese"<<"Janpan"<<"Japanese"<<"Spanish"<<"Russian";
        w->addItems(&list);
//        w->setCurrentIndex(2);
        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(size().height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
            qWarning("Language Setting: Ok");
        else
            qWarning("Language Setting: Cancel");
        break;
    }
    case 1:
    {
        //打开更新界面
        UpdatePage *w = new UpdatePage;
        w->setStyleSheet("background-color: rgb(0, 155, 155); color: white;");
        w->move(this->pos());
        if(w->exec() == QDialog::Accepted)
            qWarning("UpdatePage:Ok");
        else
            qWarning("UpdatePage:Cancel");
        break;
    }
    case 2:
    {
        //打开事件设置界面
        TimeSettingPage *w = new TimeSettingPage;
        w->setStyleSheet("background-color: rgb(0, 155, 155); color: white;");
        w->move(this->pos());
        if(w->exec() == QDialog::Accepted)
            qWarning("UpdatePage:Ok");
        else
            qWarning("UpdatePage:Cancel");
        break;
    }
    case 3:
    {
        //打开System Setting界面
        ControlPage *w = new ControlPage;
        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
            qWarning("ControlPage:Ok");
        else
            qWarning("ControlPage:Cancel");
        break;

        break;
    }
    case 4:
    {
        //打开单位设置界面
        UnitSettingPage *w = new UnitSettingPage;
        w->setFixedSize(200, 180);
        w->setStyleSheet("background-color: rgb(0, 155, 155); color: white;");
        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
            qWarning("UpdatePage:Ok");
        else
            qWarning("UpdatePage:Cancel");
        break;
    }
    case 5:
    {
        //打开WIFI管理界面
        WifiManagerPage *w = new WifiManagerPage;
        w->setStyleSheet("background-color: rgb(0, 155, 155); color: white;");
        w->move(this->pos());
        if(w->exec() == QDialog::Accepted)
            qWarning("UpdatePage:Ok");
        else
            qWarning("UpdatePage:Cancel");
        break;
    }
    case 6:
    {
        //打开电管管理界面
        PowerManagerPage *w = new PowerManagerPage;
        w->setStyleSheet("background-color: rgb(0, 155, 155); color: white;");
        w->move(this->pos());
        if(w->exec() == QDialog::Accepted)
            qWarning("UpdatePage:Ok");
        else
            qWarning("UpdatePage:Cancel");
        break;
    }
    default:
        QMessageBox::information(this, "Option Selected",
                                 tr("Option %1 is selected!").arg(index));
        break;
    }
}
