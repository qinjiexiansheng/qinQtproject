#include "analysissettingpage.h"
#include <QDebug>
#include <QMessageBox>
#include "basewidget/optionslistwidget.h"
#include "globalparampage.h"
#include "temprangepage.h"
#include "emisstablepage.h"
#include "comptemppage.h"
#include "globalparam.h"
#include <QDebug>

/**
 * @name    AnalysisSettingPage(QWidget *parent) : QDialog(parent)
 * @details Analysis Setting界面显示,并实现响应功能
 * @author  lee
 * @date    2018-11-15
**/
AnalysisSettingPage::AnalysisSettingPage(QWidget *parent) : QDialog(parent)
{
    QStringList optionsList, extraList;
    optionsList<<"Global Param."<<"Reset"<<"Temp.Range"<<"Emiss Table"<<"Comp.Temp."<<"Lens";
    extraList<<">"<<""<<QString("%1 ~ %2 >").arg(GlobalParam::getLowerLimit()).arg(GlobalParam::getUpperLimit())<<
               ">"<<QString("%1 >").arg(GlobalParam::getcompSwitchState() ? "On" : "Off")
            <<QString("%1°").arg(GlobalParam::getLens());

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);

    //设置选项
    centralWidget= new OptionsListWidget(this, "Analysis Setting", optionsList.count());
    centralWidget->setStyleSheet("color: rgb(255, 255, 255);\
                     background-color: rgb(0, 155, 155)");                            
    centralWidget->setFixedSize(size());
    for(int i=0; i<optionsList.count(); i++)
    {
        centralWidget->setOption(i, optionsList[i]);
        centralWidget->setExtraText(i, extraList[i]);
    }

    connect(centralWidget, SIGNAL(optionsClickedSig(int)), this, SLOT(optionsClicked(int)));
}

/**
 * @name   void optionsClicked(int index)
 * @details 响应选项点击事件
 * @author  lee
 * @date    2018-11-15
**/
void AnalysisSettingPage::optionsClicked(int index)
{
    switch (index) {
    case 0:
    {
        //打开GlobalParam界面
        GlobalParamPage *w = new GlobalParamPage();
        w->move(this->pos());
        if(w->exec() == QDialog::Accepted)
            qWarning("LGlobalParamPage:Ok");
        else
            qWarning("LGlobalParamPage:Cancel");
        break;
    }
    case 1:
    {
        //打开ResrtParam对话框
        if(QMessageBox::warning(this, "Reset",
                                tr("Are you sure to reset\n all param ?"),
                                QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
        {
            GlobalParam::loadDefault();
            centralWidget->setExtraText(2, QString("%1 ~ %2 >")
                                   .arg(GlobalParam::getLowerLimit()).arg(GlobalParam::getUpperLimit()));
            centralWidget->setExtraText(4, QString("%1 >")
                                   .arg(GlobalParam::getcompSwitchState() ? "On" : "Off"));
        }

        break;
    }
    case 2:
    {
        //打开温度档位设置界面
        TempRangePage *w = new TempRangePage;
        w->setFocus();
        w->setCurrentIndex(GlobalParam::getTempRangeLevel());
        w->move(this->pos().x()+((width()-w->width())/2), this->pos().y()+(height()-w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            centralWidget->setExtraText(2, QString("%1 ~ %2 >")
                                   .arg(GlobalParam::getLowerLimit())
                                   .arg(GlobalParam::getUpperLimit()));
        }
        else
            qWarning("LTempRangePage:Cancel");
        break;
    }
    case 3:
    {
        //打开辐射率表界面
        EmissTablePage *w = new EmissTablePage;
        w->move(this->pos());
        w->exec();
        break;
    }
    case 4:
    {
        //打开比较温度界面
        CompTempPage *w = new CompTempPage;
        w->move(this->pos());
        if(w->exec() == QDialog::Rejected)
        {
            qWarning("CompTempPage:Cancel");
            centralWidget->setExtraText(4, QString("%1 >")
                                   .arg(GlobalParam::getcompSwitchState() ? "On" : "Off"));
        }
        //qDebug()<<"CompTempPage exit";
        break;
    }
    case 5:
    {
        break;
    }
    default:
        QMessageBox::information(this, "Option Selected",
                                 tr("Option %1 is selected!").arg(index));
        break;
    }
}
