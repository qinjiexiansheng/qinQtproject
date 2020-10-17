#include "tabpagetwo.h"
#include "globalclass.h"
#include "AskDialog.h"

TabPageTwo::TabPageTwo(QWidget *parent): QWidget(parent)
{ 
    QVBoxLayout *nLayout = new QVBoxLayout(this);
    nSignalMapper = new QSignalMapper(this);

    standerd = NULL;

 // this->setFixedSize(100,200);//窗口大小

    qDebug("TabPageOne::TabPageOne(QWidget *parent): QWidget(parent)");
//
    nSettingButton = new SatButton(tr("Setting"),this);
    nSettingButton->installEventFilter(this);
    mList.append(nSettingButton);
    nSignalMapper->setMapping(nSettingButton, "Setting");
    connect(nSettingButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
    nLayout->addWidget(nSettingButton);
//
    nSettingButton2 = new SatButton(tr("Setting2"),this);
    nSettingButton2->installEventFilter(this);
    nLayout->addWidget(nSettingButton2);
    nSignalMapper->setMapping(nSettingButton2, "Setting2");
    mList.append(nSettingButton2);
    connect(nSettingButton2, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
//
    //设置档位按钮
    nSetRangeButton = new SatButton(tr("Set Range"), this);
//    nSetRangeButton->setOnPath(tr("one"));
    nSetRangeButton->installEventFilter(this);
    nLayout->addWidget(nSetRangeButton);
    nSignalMapper->setMapping(nSetRangeButton, "Range");
    connect(nSetRangeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSetRangeButton);

    nSetGearWidget = new SetGearWidget(this);
    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(5);//设置内边距
    this->setLayout(nLayout);

    mIndex = 0;
    mList.at(mIndex)->setFocus();

    connect(nSignalMapper, SIGNAL(mapped(QString)), this, SLOT(handleContent(QString)) );

    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类


}

bool TabPageTwo::eventFilter(QObject *obj, QEvent *event)
{

  //  qDebug("bool TabPageTwo::eventFilter(QObject *obj, QEvent *event)");

    if(event->type() == QEvent::KeyPress){

   //   qDebug("bool TabPageTwo::eventFilter(QObject *obj, QEvent *event)");

        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        qDebug("nKey->key() =0x%x ",nKey->key());

        switch(nKey->key()){
            case UP:
                qDebug("TabPageTwo eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("TabPageTwo eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case ENTER:
                 qDebug("TabPageTwo eventFilter case ENTER");
                 mList.at(mIndex)->click();
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);
}
/*
void TabPageTwo::keyReleaseEvent(QKeyEvent *event)
{


}
*/

void TabPageTwo::showEvent(QShowEvent *se)
{
    qDebug("void TabPageTwo::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void TabPageTwo::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageTwo::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageTwo::handleContent(const QString &nStr)
{

    qDebug("TabPageTwo::handleContent");

    if(nStr == "Setting"){
       // qDebug(" nstr Setting");
       globalClass::getStandardparam()->show();

    }else if(nStr == "Setting2"){
        qDebug(" nstr Adjust2");
        emit operationSignal(NULL, NULL);
    }else if(nStr == "Range"){
        qDebug(" Range ");
        nSetGearWidget->show();
    }
}

TabPageTwo::~TabPageTwo()
{

}
