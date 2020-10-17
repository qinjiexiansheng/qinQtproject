#include "controlpage.h"
#include "basewidget/optionslistwidget.h"
#include "basewidget/slidewidget.h"
#include "globalparam.h"
#include <QDebug>


ControlPage::ControlPage(QWidget *parent) : QDialog(parent)
{
    QStringList optionName, extraList;
    optionName<<"TV-Out Mode"<<"LED"<<"Laser"<<"USB Mode"<<"Multi-Func Key";
    extraList<<QString("%1 >").arg(GlobalParam::getTVOutMode())<<""<<""
            <<QString("%1 >").arg(GlobalParam::getUSBMode())
           <<QString("%1 >").arg(GlobalParam::getMultifuncKey());

    setFixedSize(260, 200);

    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    centralWidget= new OptionsListWidget(this, "Control", optionName.count());
//    centralWidget->setStyleSheet("QWidget#centralWidget{background-color: rgb(0, 155, 155)}");
    centralWidget->setStyleSheet("color: rgb(255, 255, 255);\
                     background-color: rgb(0, 155, 155)");
    centralWidget->setFixedSize(size());
    //设置选项
    for(int i=0; i<optionName.count();i++)
    {
        centralWidget->setOption(i, optionName[i]);
        centralWidget->setExtraText(i, extraList[i]);
    }
    centralWidget->setSwitch(1, GlobalParam::getLEDState());
    centralWidget->setSwitch(2, GlobalParam::getLaserState());

    connect(centralWidget, SIGNAL(optionsClickedSig(int)), this, SLOT(optionsClicked(int)));
}

void ControlPage::optionsClicked(int index)
{
    switch (index) {
    case 1:
        GlobalParam::setLEDState(centralWidget->getSwitchState());
        break;
    case 2:
        GlobalParam::setLaserState(centralWidget->getSwitchState());
        break;
    case 0:
    case 3:
    case 4:
    {
        QStringList list;
        GlobalParam::ValueType type;
        SlideWidget *w = new SlideWidget;

        if(index == 0)
        {
            w->setTitle("TVOut Format");
            list<<"PAL"<<"NTSC";
            w->addItems(&list);
            w->setCurrentText(GlobalParam::getTVOutMode());
            type = GlobalParam::ValueType::TVOUTMODE;
        }
        else if(index == 3)
        {
            w->setTitle("USB Mode");
            list<<"UDisk"<<"Trans.";
            w->addItems(&list);
            w->setCurrentText(GlobalParam::getUSBMode());
            type = GlobalParam::ValueType::USBMODE;
        }
        else
        {
            w->setTitle("Multi-Func Key");
            list<<"Shutter"<<"Freeze"<<"Snapshot"<<"Laser"<<"LaserDist"<<"LED";
            w->addItems(&list);
            w->setCurrentText(GlobalParam::getMultifuncKey());
            type = GlobalParam::ValueType::MULTIFUNCKEY;
        }
        w->setValueType(type);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
        w->exec();
        updateView();
        break;
    }
    default:
        break;
    }
}

void ControlPage::updateView()
{
    centralWidget->setExtraText(0, QString("%1 >").arg(GlobalParam::getTVOutMode()));
    centralWidget->setExtraText(3, QString("%1 >").arg(GlobalParam::getUSBMode()));
    centralWidget->setExtraText(4, QString("%1 >").arg(GlobalParam::getMultifuncKey()));
    centralWidget->setSwitch(1, GlobalParam::getLEDState());
    centralWidget->setSwitch(2, GlobalParam::getLaserState());
}

