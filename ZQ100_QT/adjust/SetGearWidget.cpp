#include "SetGearWidget.h"

SetGearWidget::SetGearWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(220,90);//窗口大小
    this->setGeometry(100, 100, 220, 90);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
//    mSatData = SatData::initance();

 //   QWidget *this = new QWidget(this);
    nGridLayout = new QGridLayout;
    QLabel *nTempLabel = new QLabel(tr("Range:"),this);
    nGridLayout->addWidget(nTempLabel,0,0);//,0,1);

    mComboBox = new QComboBox(this);
    nGridLayout->addWidget(mComboBox,0,1);//,0,3);
    mComboBox->installEventFilter(this);
    mList.append(mComboBox);
    mComboBox->addItem(tr("1st -20~250°C"));//第一档
    mComboBox->addItem(tr("2st 200~1000°C"));//第二档
    mMaxIndex = 2;//组合框数量
//    mOldGear = mSatData->getGearMode();
//    if(mOldGear == SatData::GEARONE){
//        mComboBox->setCurrentIndex(0);
//    }else{
//        mComboBox->setCurrentIndex(1);
//    }
    nOkButton = new QPushButton(tr("OK"),this);
    nGridLayout->addWidget(nOkButton,1,0);//,2,2);
    nOkButton->installEventFilter(this);
    mList.append(nOkButton);
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(okSlot()));//OK键连接关闭窗口槽

    nCancelButton = new QPushButton(tr("Cancel"),this);
    nGridLayout->addWidget(nCancelButton,1,1);//,2,2);
    nCancelButton->installEventFilter(this);
    mList.append(nCancelButton);
    connect(nCancelButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽

  //  nGridLayout->setMargin(5);
 //   nGridLayout->setSpacing(10);
//    nGridLayout->setRowStretch(1,10);
    mIndex = 0;
    mList.at(mIndex)->setFocus();

    this->setLayout(nGridLayout);
    //连接业务操作
//    SatControl *nSat = SatControl::initance();
//    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

bool SetGearWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case UP:
                focusPrevious();//前一焦点
                break;
            case DOWN:
                focusNext();//下一焦点
                break;
            case LEFT:
                {
                    if(obj == mComboBox){//事件对象为组合框，则显示前一个索引
                        int nIndex = mComboBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = mMaxIndex - 1;
                        }
                        mComboBox->setCurrentIndex(nIndex);
//                        //切换档位操作
//                        if(nIndex == 0){
//                            emit operationSignal(Gear_One,NULL);
//                        }else if(nIndex == 1){
//                            emit operationSignal(Gear_Two,NULL);
//                        }
                    }
                }
                break;
            case RIGHT:
                {
                    if(obj == mComboBox){//事件对象为组合框,显示下一索引
                        int nIndex = mComboBox->currentIndex();
                        nIndex++;
                        if(nIndex >= mMaxIndex){
                            nIndex = 0;
                        }
                        mComboBox->setCurrentIndex(nIndex);
//                        //切换档位操作
//                        if(nIndex == 0){
//                            emit operationSignal(Gear_One,NULL);
//                        }else if(nIndex == 1){
//                            emit operationSignal(Gear_Two,NULL);
//                        }
                    }
                }
                break;
            case ENTER:
                    if(obj != mComboBox){
                        ((QPushButton*)obj)->click();//非组合框，则产生点击事件
                    }
                break;
            case ESC:
                    closeSlot();//关闭窗口函数
                break;
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetGearWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetGearWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetGearWidget::okSlot(){
   // this->close();//窗口关闭
}

void SetGearWidget::closeSlot(){
//    if(mSatData->getGearMode() != mOldGear){
//        if(mOldGear == SatData::GEARONE){
//            emit operationSignal(Gear_One,NULL);
//        }else if(mOldGear == SatData::GEARTWO){
//            emit operationSignal(Gear_Two,NULL);
//        }
//    }
    this->close();
}

void SetGearWidget::showEvent(QShowEvent *se){
//    mOldGear = mSatData->getGearMode();
//    if(mOldGear == SatData::GEARONE){
//        mComboBox->setCurrentIndex(0);
//    }else{
//        mComboBox->setCurrentIndex(1);
//    }
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}
