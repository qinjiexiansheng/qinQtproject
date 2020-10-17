#include "globalparamwidget.h"

//全局参数--左边列表面板
SatGlobalParamListWidget::SatGlobalParamListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    int nOpe;
    //辐射率--0  Emissivity
    nOpe = 0;
    SatButton *nEmissButton = new SatButton(SatButton::TextLeftButton,this);
    nEmissButton->setText(tr("Emissivity"));
    nEmissButton->installEventFilter(this);
    nLayout->addWidget(nEmissButton);
    nSignalMapper->setMapping(nEmissButton,nOpe);
    connect(nEmissButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nEmissButton);
    //距离--1  distance
    nOpe++;
    SatButton *nDistanceButton = new SatButton(SatButton::TextLeftButton,this);
    nDistanceButton->setText(tr("Distance"));
    nDistanceButton->installEventFilter(this);
    nLayout->addWidget(nDistanceButton);
    nSignalMapper->setMapping(nDistanceButton,nOpe);
    connect(nDistanceButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDistanceButton);
    //环境温度--2   The environment temperature
    nOpe++;
    SatButton *nEnvTempButton = new SatButton(SatButton::TextLeftButton,this);
    nEnvTempButton->setText(tr("Environment Temp"));
    nEnvTempButton->installEventFilter(this);
    nLayout->addWidget(nEnvTempButton);
    nSignalMapper->setMapping(nEnvTempButton,nOpe);
    connect(nEnvTempButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nEnvTempButton);
    //反射温度--3   Reflection temperature
    nOpe++;
    SatButton *nRefTempButton = new SatButton(SatButton::TextLeftButton,this);
    nRefTempButton->setText(tr("Reflection Temp"));
    nRefTempButton->installEventFilter(this);
    nLayout->addWidget(nRefTempButton);
    nSignalMapper->setMapping(nRefTempButton,nOpe);
    connect(nRefTempButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRefTempButton);
    //相对温度--4  Relative humidity
    nOpe++;
    SatButton *nRelHumButton = new SatButton(SatButton::TextLeftButton,this);
    nRelHumButton->setText(tr("Relative Humidity"));
    nRelHumButton->installEventFilter(this);
    nLayout->addWidget(nRelHumButton);
    nSignalMapper->setMapping(nRelHumButton,nOpe);
    connect(nRelHumButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRelHumButton);
    //修正温度--5  Correction temperature
    nOpe++;
    SatButton *nCorTempButton = new SatButton(SatButton::TextLeftButton,this);
    nCorTempButton->setText(tr("Correction Temp"));
    nCorTempButton->installEventFilter(this);
    nLayout->addWidget(nCorTempButton);
    nSignalMapper->setMapping(nCorTempButton,nOpe);
    connect(nCorTempButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCorTempButton);
    //重置--6 Reset
    nOpe++;
    SatButton *nResetButton = new SatButton(SatButton::TextLeftButton,this);
    nResetButton->setText(tr("Reset"));
    nResetButton->installEventFilter(this);
    nLayout->addWidget(nResetButton);
    nSignalMapper->setMapping(nResetButton,nOpe);
    connect(nResetButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nResetButton);
    //返回--7
    nOpe++;
    SatButton *nGoBackButton = new SatButton(SatButton::TextLeftButton,this);
    nGoBackButton->setText(tr("Quit"));
    nGoBackButton->installEventFilter(this);
    nLayout->addWidget(nGoBackButton);
    nSignalMapper->setMapping(nGoBackButton,nOpe);
    connect(nGoBackButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nGoBackButton);
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    //this->setFixedSize(430,90);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    //connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    connect(nSignalMapper,SIGNAL(mapped(int)),this,SLOT(handleContent(int)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类


}



bool SatGlobalParamListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatGlobalParamListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamListWidget::paintEvent(QPaintEvent *event){
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


void SatGlobalParamListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamListWidget::handleContent(int nOpe){
    if(nOpe == mList.size()-1){//返回按钮被点击
        emit goBackSignal();
    }else if(nOpe == mList.size()-2){
        QString nStr;
        nStr = tr("Function not implemented!");
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Reset_Param,NULL);//重置参数
        }
    }else{
        if(mIndex != nOpe){//当触摸点击时会发生这种情况
            mIndex = nOpe;
            emit indexChangeSignal(mIndex);
        }
        emit focusTransferSignal();//焦点转移，让右边面板获取焦点
    }
}





SatGlobalParamSmallWidget::SatGlobalParamSmallWidget(QWidget *parent) : QWidget(parent){
    //this->setFixedSize(640,60);
    this->setFixedHeight(60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //确认按钮
    SatPhotoButton *nConfirmButton = new SatPhotoButton(this);
    nConfirmButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nConfirmButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nConfirmButton->setTextStr(tr("Confirm"));
    nConfirmButton->setTextShowSign(false);
    nConfirmButton->installEventFilter(this);
    nLayout->addWidget(nConfirmButton);
    nSignalMapper->setMapping(nConfirmButton,"Confirm");
    connect(nConfirmButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nConfirmButton);
    //隐藏按钮
    SatPhotoButton *nHideButton = new SatPhotoButton(this);
    nHideButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_normal.png"));
    nHideButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_focus.png"));
    nHideButton->setTextStr(tr("Hide"));
    nHideButton->setTextShowSign(false);
    nHideButton->installEventFilter(this);
    nLayout->addWidget(nHideButton);
    nSignalMapper->setMapping(nHideButton,"Hide");
    connect(nHideButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nHideButton);
    //退出按钮
    SatPhotoButton *nQuitButton = new SatPhotoButton(this);
    nQuitButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_normal.png"));
    nQuitButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_focus.png"));
    nQuitButton->setTextStr(tr("Quit"));
    nQuitButton->setTextShowSign(false);
    nQuitButton->installEventFilter(this);
    nLayout->addWidget(nQuitButton);
    nSignalMapper->setMapping(nQuitButton,"Quit");
    connect(nQuitButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nQuitButton);
    //配置
    nLayout->addStretch();
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->setMargin(0);
    nLayout->setSpacing(10);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatGlobalParamSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatGlobalParamSmallWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_26:
                focusPrevious();
                break;
            case KEY_27:
                focusNext();
                break;
            case KEY_16:
                mList.at(mIndex)->click();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatGlobalParamSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatGlobalParamSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == tr("Confirm")){
        mIndex = 0;
    }else if(nOpeStr == tr("Hide")){
        this->hide();
    }else if(nOpeStr == tr("Quit")){
        this->hide();
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}






SatGlobalParamLabel::SatGlobalParamLabel(QWidget *parent) : QWidget(parent){
    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addStretch();
    mLabel = new QLabel(this);
    mLabel->installEventFilter(this);
    mLabel->setAlignment(Qt::AlignCenter);
    nLayout->addWidget(mLabel);
    mLineEdit = new QLineEdit(this);
    mLineEdit->installEventFilter(this);
    nLayout->addWidget(mLineEdit,0,Qt::AlignHCenter);
    nLayout->addStretch();
    nLayout->setSpacing(10);
    nLayout->setMargin(0);
    this->setLayout(nLayout);
}

QString SatGlobalParamLabel::getTextString(){
    return mTextString;
}

void SatGlobalParamLabel::setTextString(QString nTextString){
    if(mTextString != nTextString){
        mTextString = nTextString;
        mLineEdit->setText(mTextString);
        //update();
    }
}

QString SatGlobalParamLabel::getTitleString(){
    return mTitleString;
}

void SatGlobalParamLabel::setTitleString(QString nTitleString){
    if(mTitleString != nTitleString){
        mTitleString = nTitleString;
        mLabel->setText(mTitleString);
    }
}


void SatGlobalParamLabel::paintEvent(QPaintEvent *event){
#if 0
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawText(0,0,width(),height(),Qt::AlignCenter,mTextString);
#endif
    QWidget::paintEvent(event);
}


void SatGlobalParamLabel::focusInEvent(QFocusEvent *event){
    mLineEdit->setFocus();
    QWidget::focusInEvent(event);
}



//全局参数--右边面板--辐射率--Emiss
SatGlobalParamPage::SatGlobalParamPage(GlobalParamPageType nPageType,QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();
    mPageType = nPageType;
    //
    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addStretch();
    mLabel = new QLabel(this);
    mLabel->installEventFilter(this);
    mLabel->setAlignment(Qt::AlignCenter);
    nLayout->addWidget(mLabel);
    mLineEdit = new QLineEdit(this);
    mLineEdit->setAlignment(Qt::AlignCenter);
    mLineEdit->installEventFilter(this);
    nLayout->addWidget(mLineEdit,0,Qt::AlignHCenter);
    nLayout->addStretch();
    this->setLayout(nLayout);
    //操作小窗口
    mSmallWidget = new SatGlobalParamSmallWidget(this);
    //mSmallWidget->installEventFilter(this);
    mSmallWidget->hide();
    //总布局
    nLayout->addWidget(mSmallWidget);
    nLayout->setContentsMargins(0,0,0,0);
    nLayout->setSpacing(10);//设置内边框
    this->setLayout(nLayout);
    updateLabel();
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}


bool SatGlobalParamPage::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
            //return true;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                mSmallWidget->show();
                break;
            case KEY_27://左键
                addData();
                updateLabel();
                break;
            case KEY_26://右键
                subData();
                updateLabel();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatGlobalParamPage::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    updateData(true);
    updateLabel();
}

void SatGlobalParamPage::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mLineEdit->setFocus();
}

void SatGlobalParamPage::updateLabel(){
    QString nTitleStr;
    QString nDataStr;
    if(mPageType == Emiss_Page){
        nTitleStr = tr("Emissivity:");
        nDataStr = QString("%1").arg(QString::number(mData, 'f', 2));
    }else if(mPageType == Dis_Page){
        nTitleStr = tr("Distance:");
        if(mSatData->getLengthUnit()){
            nDataStr = QString("%1 m").arg(QString::number(mData, 'f', 1));
        }else{
            nDataStr = QString("%1 ft").arg(QString::number(mData/0.3048,'f',1));
        }
    }else if(mPageType == EnvTemp_Page){
        nTitleStr = tr("Environment Temp:");
        if(mSatData->getTempUnit()){
            nDataStr = QString("%1 °C").arg(QString::number(mData, 'f', 1));
        }else{
            nDataStr = QString("%1 °F").arg(QString::number((mData*1.8 + 32),'f',1));
            qDebug("%s",nDataStr.toStdString().c_str());
        }
    }else if(mPageType == RefTemp_Page){
        nTitleStr = tr("Reflection Temp:");
        nDataStr = QString("%1°C").arg(QString::number(mData, 'f', 1));
        if(mSatData->getTempUnit()){
            nDataStr = QString("%1 °C").arg(QString::number(mData, 'f', 1));
        }else{
            nDataStr = QString("%1 °F").arg(QString::number((mData*1.8 + 32),'f',1));
        }
    }else if(mPageType == RelHum_Page){
        nTitleStr = tr("Relative Humidity:");
        nDataStr = QString("%1%").arg((int)(mData*100));
    }else if(mPageType == CorTemp_Page){
        nTitleStr = tr("Correction Temp:");
        nDataStr = QString("%1°C").arg(QString::number(mData, 'f', 1));
        if(mSatData->getTempUnit()){
            nDataStr = QString("%1 °C").arg(QString::number(mData, 'f', 1));
        }else{
            nDataStr = QString("%1 °F").arg(QString::number((mData*1.8 + 32),'f',1));
        }
    }else{
    }
    mLabel->setText(nTitleStr);
    mLineEdit->setText(nDataStr);
    mLineEdit->setAlignment(Qt::AlignCenter);
}

void SatGlobalParamPage::updateData(bool nIsGet){
    if(nIsGet){
        if(mPageType == Emiss_Page){
            mData = mSatData->getEmiss();
            mGrowth = 0.01;
        }else if(mPageType == Dis_Page){
            mData = mSatData->getDis();
            mGrowth = 0.5;
        }else if(mPageType == EnvTemp_Page){
            mData = mSatData->getEnvTemp();
            mGrowth = 0.1;
        }else if(mPageType == RefTemp_Page){
            mData = mSatData->getRefTemp();
            mGrowth = 0.1;
        }else if(mPageType == RelHum_Page){
            mData = mSatData->getRelHum();
            mGrowth = 0.01;
        }else if(mPageType == CorTemp_Page){
            mData = mSatData->getCorTemp();
            mGrowth = 0.1;
        }else{
        }
    }else{
        if(mPageType == Emiss_Page){
            emit operationSignal(Set_Emiss,QString("Emiss=%1").arg(mData));
        }else if(mPageType == Dis_Page){
            emit operationSignal(Set_Dis,QString("Dis=%1").arg(mData));
        }else if(mPageType == EnvTemp_Page){
            emit operationSignal(Set_EnvTemp,QString("EnvTemp=%1").arg(mData));
        }else if(mPageType == RefTemp_Page){
            emit operationSignal(Set_RefTemp,QString("RefTemp=%1").arg(mData));
        }else if(mPageType == RelHum_Page){
            emit operationSignal(Set_RelHum,QString("RelHum=%1").arg(mData));
        }else if(mPageType == CorTemp_Page){
            emit operationSignal(Set_CorTemp,QString("CorTemp=%1").arg(mData));
        }else{
        }
    }
}


void SatGlobalParamPage::addData(){
    mData = mData + mGrowth;
    if(mPageType == Emiss_Page){
        if(mData > Emiss_Max){
            mData = Emiss_Max;
        }
    }else if(mPageType == Dis_Page){
        if(mData > Dis_Max){
            mData = Dis_Max;
        }
    }else if(mPageType == EnvTemp_Page){
        if(mData > EnvTemp_Max){
            mData = EnvTemp_Max;
        }
    }else if(mPageType == RefTemp_Page){
        if(mData > RefTemp_Max){
            mData = RefTemp_Max;
        }
    }else if(mPageType == RelHum_Page){
        if(mData > RelHum_Max){
            mData = RelHum_Max;
        }
    }else if(mPageType == CorTemp_Page){
        if(mData > CorTemp_Max){
            mData = CorTemp_Max;
        }
    }else{
    }
}

void SatGlobalParamPage::subData(){
    mData = mData - mGrowth;
    if(mPageType == Emiss_Page){
        if(mData < Emiss_Min){
            mData = Emiss_Min;
        }
    }else if(mPageType == Dis_Page){
        if(mData < Dis_Min){
            mData = Dis_Min;
        }
    }else if(mPageType == EnvTemp_Page){
        if(mData < EnvTemp_Min){
            mData = EnvTemp_Min;
        }
    }else if(mPageType == RefTemp_Page){
        if(mData < RefTemp_Min){
            mData = RefTemp_Min;
        }
    }else if(mPageType == RelHum_Page){
        if(mData < RelHum_Min){
            mData = RelHum_Min;
        }
    }else if(mPageType == CorTemp_Page){
        if(mData < CorTemp_Min){
            mData = CorTemp_Min;
        }
    }else{
    }
}


void SatGlobalParamPage::operationSlot(const QString &nStr){
    if(nStr == tr("Confirm")){
        updateData(false);
        mSmallWidget->hide();
        mLineEdit->setFocus();
        emit focusTransferSignal();
    }else if(nStr == tr("Quit")){
        updateData(true);
        updateLabel();
        mSmallWidget->hide();
        mLineEdit->setFocus();
        emit focusTransferSignal();
    }else if(nStr == tr("Hide")){
        mLineEdit->setFocus();
    }
}

void SatGlobalParamPage::goBackSlot(){
    updateData(true);
    updateLabel();
    mSmallWidget->hide();
    mLineEdit->setFocus();
    emit focusTransferSignal();
}









GlobalParamWidget::GlobalParamWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Global Param Setting"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatGlobalParamListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
    SatGlobalParamPage *nPageOne = new SatGlobalParamPage(SatGlobalParamPage::Emiss_Page,nTmpWidget);
    SatGlobalParamPage *nPageTwo = new SatGlobalParamPage(SatGlobalParamPage::Dis_Page,nTmpWidget);
    SatGlobalParamPage *nPageThree = new SatGlobalParamPage(SatGlobalParamPage::EnvTemp_Page,nTmpWidget);
    SatGlobalParamPage *nPageFour = new SatGlobalParamPage(SatGlobalParamPage::RefTemp_Page,nTmpWidget);
    SatGlobalParamPage *nPageFive = new SatGlobalParamPage(SatGlobalParamPage::RelHum_Page,nTmpWidget);
    SatGlobalParamPage *nPageSix = new SatGlobalParamPage(SatGlobalParamPage::CorTemp_Page,nTmpWidget);
    mRightWidget->addWidget(nPageOne);
    mRightWidget->addWidget(nPageTwo);
    mRightWidget->addWidget(nPageThree);
    mRightWidget->addWidget(nPageFour);
    mRightWidget->addWidget(nPageFive);
    mRightWidget->addWidget(nPageSix);

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
    connect(mLeftWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusLeftToRightSlot()));
    connect(mLeftWidget,SIGNAL(indexChangeSignal(int)),this,SLOT(itemChangeSlot(int)));
    connect(mLeftWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(nPageOne,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageTwo,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageThree,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageFour,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageFive,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageSix,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
}

void GlobalParamWidget::showEvent(QShowEvent *event){
    mRightWidget->setCurrentIndex(0);
    QWidget::showEvent(event);
}

void GlobalParamWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void GlobalParamWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void GlobalParamWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void GlobalParamWidget::goBackSlot(){
    this->hide();
}
