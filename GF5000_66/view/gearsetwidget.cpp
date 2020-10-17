#include "gearsetwidget.h"

//设置档位--左边列表窗口
SatGearSetListWidget::SatGearSetListWidget(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    int nOpe;
    //第一档--0
    nOpe = 0;
    SatButton *nGearOneButton = new SatButton(SatButton::TextLeftButton,this);
    nGearOneButton->setText(tr("Gear One"));
    nGearOneButton->installEventFilter(this);
    nLayout->addWidget(nGearOneButton);
    nSignalMapper->setMapping(nGearOneButton,nOpe);
    connect(nGearOneButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nGearOneButton);
    //第二档--1
    nOpe++;
    SatButton *nGearTwoButton = new SatButton(SatButton::TextLeftButton,this);
    nGearTwoButton->setText(tr("Gear Two"));
    nGearTwoButton->installEventFilter(this);
    nLayout->addWidget(nGearTwoButton);
    nSignalMapper->setMapping(nGearTwoButton,nOpe);
    connect(nGearTwoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nGearTwoButton);
    //配置
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    //this->setFixedSize(430,90);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    //connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    connect(nSignalMapper,SIGNAL(mapped(int)),this,SLOT(handleContent(int)));
    SatControl *nSatControl = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSatControl,SLOT(doService(int,QString)));
}

void SatGearSetListWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                mList.at(0)->setText(tr("Gear One"));
                mList.at(1)->setText(tr("Gear Two"));
            }
            break;
        default:
            break;
    }
}



bool SatGearSetListWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                mList.at(mIndex)->click();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
            default:
                return true;
        }
#endif
        return true;
    }else if(event->type() == QEvent::KeyRelease){
#if 0
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                mList.at(mIndex)->click();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
        }
#endif
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatGearSetListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mList.at(mIndex)->setFocus();
    emit indexChangeSignal(mIndex);
}

void SatGearSetListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatGearSetListWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
//    painter.drawLine(0,0,0,height());//画左边线
//    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
//    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}


void SatGearSetListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatGearSetListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatGearSetListWidget::handleContent(int nOpe){
    if(mIndex != nOpe){//当触摸点击时会发生这种情况
        mIndex = nOpe;
        emit indexChangeSignal(mIndex);
    }
    if(mSatData->getGearMode() == SatData::GEARONE && mIndex == 1){
        //qDebug("000");
        emit operationSignal(Gear_Two,NULL);
    }else if(mSatData->getGearMode() == SatData::GEARTWO && mIndex == 0){
        //qDebug("111");
        emit operationSignal(Gear_One,NULL);
    }else{
        //qDebug("%d---%d",mIndex,nOpe);
    }

    emit goBackSignal();
}









SatGearSetPage::SatGearSetPage(GearSetPageType nPageType, QWidget *parent) : QWidget(parent){
    QString nStr;
    mPageType = nPageType;
    if(mPageType == GearOne_Page){
        nStr = QString(tr("  The first gear\n\n\n  Measuring range:\n\n\n\t-20°C~250°C\n\n\n\n"));
    }else if(mPageType == GearTwo_Page){
        nStr = QString(tr("  The second gear\n\n\n  Measuring range:\n\n\n\t200°C~1000°C\n\n\n\n"));
    }
    QVBoxLayout *nLayout = new QVBoxLayout;
    mLabel = new QLabel(this);
    mLabel->setText(nStr);
    nLayout->addWidget(mLabel);
    nLayout->setSpacing(0);
    nLayout->setMargin(0);
    this->setLayout(nLayout);
}

void SatGearSetPage::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                QString nStr;
                if(mPageType == GearOne_Page){
                    nStr = QString(tr("  The first gear\n\n\n  Measuring range:\n\n\n\t-20°C~250°C\n\n\n\n"));
                }else if(mPageType == GearTwo_Page){
                    nStr = QString(tr("  The second gear\n\n\n  Measuring range:\n\n\n\t200°C~1000°C\n\n\n\n"));
                }
                mLabel->setText(nStr);
            }
            break;
        default:
            break;
    }
}





GearSetWidget::GearSetWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Gear Setting"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatGearSetListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
    SatGearSetPage *nPageOne = new SatGearSetPage(SatGearSetPage::GearOne_Page,nTmpWidget);
    SatGearSetPage *nPageTwo = new SatGearSetPage(SatGearSetPage::GearTwo_Page,nTmpWidget);
    mRightWidget->addWidget(nPageOne);
    mRightWidget->addWidget(nPageTwo);

    QHBoxLayout *nHLayout = new QHBoxLayout;
    nHLayout->addWidget(mLeftWidget,2);
    nHLayout->addWidget(mRightWidget,3);
    nHLayout->setSpacing(0);
    nHLayout->setMargin(0);
    nTmpWidget->setLayout(nHLayout);

    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar);
    nVLayout->addWidget(nTmpWidget);
    nVLayout->setMargin(0);//设置外边框
    nVLayout->setSpacing(0);//设置内边框
    this->setLayout(nVLayout);
    connect(mLeftWidget,SIGNAL(indexChangeSignal(int)),this,SLOT(itemChangeSlot(int)));
    connect(mLeftWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
}


void GearSetWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                mSatTitleBar->setTitle(tr("Gear Setting"));
            }
            break;
        default:
            break;
    }
}

void GearSetWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void GearSetWidget::goBackSlot(){
    this->hide();
}



