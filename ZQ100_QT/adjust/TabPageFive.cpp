#include "TabPageFive.h"

TabPageFive::TabPageFive(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
//    mSatData = SatData::initance();
    nSignalMapper = new QSignalMapper(this);//信号映射
    nVBoxLayout = new QVBoxLayout(this);
    //自动调节Int开关按钮
    nAutoIntButton = new SatButton(tr("AutoInt"), this);
//    nAutoIntButton->setOnPath(tr("On"));
//    nAutoIntButton->setOffPath(tr("Off"));
////    if(mSatData->getAutoIntSign())
//    {
//        nAutoIntButton->setOnState(true);
//    }
//    else{
//        nAutoIntButton->setOnState(false);
//    }
    nAutoIntButton->installEventFilter(this);
    nVBoxLayout->addWidget(nAutoIntButton);
    nSignalMapper->setMapping(nAutoIntButton,"AutoInt");
    connect(nAutoIntButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAutoIntButton);
    //
    nRecordArgButton = new SatButton(tr("RecordArg"), this);
//    nRecordArgButton->setOnPath(tr("On"));
//    nRecordArgButton->setOffPath(tr("Off"));
//    if(mSatData->getRecordArgSign()){
//        nRecordArgButton->setOnState(true);

    nRecordArgButton->installEventFilter(this);
    nVBoxLayout->addWidget(nRecordArgButton);
    nSignalMapper->setMapping(nRecordArgButton,"RecordArg");
    connect(nRecordArgButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRecordArgButton);
    //
    nDistanceButton = new SatButton(tr("Distance"), this);
    nDistanceButton->installEventFilter(this);
    nVBoxLayout->addWidget(nDistanceButton);
    nSignalMapper->setMapping(nDistanceButton,"Distance");
    connect(nDistanceButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDistanceButton);

    nVBoxLayout->addStretch();
    nVBoxLayout->setMargin(0);//设置外边距
    nVBoxLayout->setSpacing(0);//设置内边距
    this->setLayout(nVBoxLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
//    SatControl *nSat = SatControl::initance();
//    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类


//    mSetDisWidget = NULL;
}


bool TabPageFive::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case UP:
                focusPrevious();
                return true;
                break;
            case DOWN:
                focusNext();
                return true;
                break;
            case ENTER:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
    }//这里不能返回真，因为上层需要左右按键事件来切换标签页
    return QWidget::eventFilter(obj,event);
}

void TabPageFive::showEvent(QShowEvent *se) //显示事件
{
//    QWidget::showEvent(se);
//    if(mSatData->getAutoIntSign()){
//        mList.at(0)->setOnState(true);
//    }else{
//        mList.at(0)->setOnState(false);
//    }
//    mList.at(1)->setOnState(mSatData->getRecordArgSign());
    mList.at(mIndex)->setFocus();
}

void TabPageFive::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFive::focusPrevious() //上一焦点
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFive::handleContent(const QString &nStr)
{
    if(nStr == "AutoInt"){
        if(mIndex != 0){
            mIndex = 0;
        }
//        if(mSatData->getAutoIntSign()){
//            emit operationSignal(AutoInt_Off,NULL);
//        }else{
//            emit operationSignal(AutoInt_On,NULL);
//        }
    }else if(nStr == "RecordArg"){
        if(mIndex != 1){
            mIndex = 1;
        }
//        if(mSatData->getRecordArgSign()){
//            emit operationSignal(Set_RecordArg_Off,NULL);
//        }else{
//            emit operationSignal(Set_RecordArg_On,NULL);
//        }
    }else if(nStr == "Distance"){
        if(mIndex != 2){
            mIndex = 2;
        }
//        if(mSetDisWidget == NULL){
//            mSetDisWidget = new SetDisWidget(this);
//        }
//        mSetDisWidget->move(100,250);
//        mSetDisWidget->show();
    }
}
