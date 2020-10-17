#include "systemwidget.h"

SatSysListWidget::SatSysListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    int nOpe;
    //参数设置--0
    nOpe = 0;
    SatButton *nParamSetButton = new SatButton(SatButton::TextLeftButton,this);
    nParamSetButton->setText(tr("Param Setting"));
    nParamSetButton->installEventFilter(this);
    nLayout->addWidget(nParamSetButton);
    nSignalMapper->setMapping(nParamSetButton,nOpe);
    connect(nParamSetButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nParamSetButton);
    //系统设置--1
    nOpe++;
    SatButton *nSystemSetButton = new SatButton(SatButton::TextLeftButton,this);
    nSystemSetButton->setText(tr("System Setting"));
    nSystemSetButton->installEventFilter(this);
    nLayout->addWidget(nSystemSetButton);
    nSignalMapper->setMapping(nSystemSetButton,nOpe);
    connect(nSystemSetButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSystemSetButton);
    //图像设置--2
    nOpe++;
    SatButton *nImageSetButton = new SatButton(SatButton::TextLeftButton,this);
    nImageSetButton->setText(tr("Image Setting"));
    nImageSetButton->installEventFilter(this);
    nLayout->addWidget(nImageSetButton);
    nSignalMapper->setMapping(nImageSetButton,nOpe);
    connect(nImageSetButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nImageSetButton);
    //系统信息--3
    nOpe++;
    SatButton *nSystemInfoButton = new SatButton(SatButton::TextLeftButton,this);
    nSystemInfoButton->setText(tr("System Info"));
    nSystemInfoButton->installEventFilter(this);
    nLayout->addWidget(nSystemInfoButton);
    nSignalMapper->setMapping(nSystemInfoButton,nOpe);
    connect(nSystemInfoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSystemInfoButton);
    //返回按钮
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
}

bool SatSysListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatSysListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSysListWidget::paintEvent(QPaintEvent *event){
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


void SatSysListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSysListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSysListWidget::handleContent(int nOpe){
    if(nOpe == mList.size()-1){//返回按钮被点击
        emit goBackSignal();
    }else{
        if(mIndex != nOpe){//当触摸点击时会发生这种情况
            mIndex = nOpe;
            emit indexChangeSignal(mIndex);
        }
        emit focusTransferSignal();//焦点转移，让右边面板获取焦点
    }
}



//系统界面--右边面板--参数设置面板-------
SatSysStackPageOne::SatSysStackPageOne(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //全局参数
    SatButton *nGlobalParamButton = new SatButton(SatButton::ArrowButton,this);
    nGlobalParamButton->setText(tr("Global Param"));
    nGlobalParamButton->installEventFilter(this);
    nLayout->addWidget(nGlobalParamButton);
    nSignalMapper->setMapping(nGlobalParamButton,"GlobalParam");
    connect(nGlobalParamButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nGlobalParamButton);
    //档位
    SatButton *nGearButton = new SatButton(SatButton::ArrowButton,this);
    nGearButton->setText(tr("Gear"));
    nGearButton->installEventFilter(this);
    nLayout->addWidget(nGearButton);
    nSignalMapper->setMapping(nGearButton,"Gear");
    connect(nGearButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nGearButton);
    //辐射率表
    SatButton *nEmissTableButton = new SatButton(SatButton::ArrowButton,this);
    nEmissTableButton->setText(tr("Emiss Table"));
    nEmissTableButton->installEventFilter(this);
    nLayout->addWidget(nEmissTableButton);
    nSignalMapper->setMapping(nEmissTableButton,"Emiss");
    connect(nEmissTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nEmissTableButton);
    //返回按钮
    SatButton *nCancelButton = new SatButton(SatButton::TextLeftButton,this);
    nCancelButton->setText(tr("Cancel"));
    nCancelButton->installEventFilter(this);
    nLayout->addWidget(nCancelButton);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCancelButton);
    //配置
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    //=========
    mGlobalParamWidget = NULL;
    mGearSetWidget = NULL;
    mEmissTableWidget = NULL;
}


bool SatSysStackPageOne::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysStackPageOne::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void SatSysStackPageOne::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    if(mIndex >= mList.size() - 1){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageOne::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}
void SatSysStackPageOne::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageOne::handleContent(const QString &nStr){
    if(nStr == "GlobalParam"){
        if(mGlobalParamWidget == NULL){
            mGlobalParamWidget = new GlobalParamWidget(this);
        }
        mGlobalParamWidget->show();
    }else if(nStr == "Gear"){
        if(mGearSetWidget == NULL){
            mGearSetWidget = new GearSetWidget(this);
        }
        mGearSetWidget->show();
    }else if(nStr == "Emiss"){
        if(mEmissTableWidget == NULL){
            mEmissTableWidget = new EmissivityTableWidget(this);
        }
        mEmissTableWidget->show();
    }else if(nStr == "Cancel"){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }
}



//系统界面--右边面板--参数设置面板-------
SatSysStackPageTwo::SatSysStackPageTwo(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //语言
    SatButton *nLanguageButton = new SatButton(SatButton::ArrowButton,this);
    nLanguageButton->setText(tr("Language"));
    nLanguageButton->installEventFilter(this);
    nLayout->addWidget(nLanguageButton);
    nSignalMapper->setMapping(nLanguageButton,"Language");
    connect(nLanguageButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLanguageButton);
    //更新
    SatButton *nUpdateButton = new SatButton(SatButton::ArrowButton,this);
    nUpdateButton->setText(tr("Update"));
    nUpdateButton->installEventFilter(this);
    nLayout->addWidget(nUpdateButton);
    nSignalMapper->setMapping(nUpdateButton,"Update");
    connect(nUpdateButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nUpdateButton);
#if 0
    //日期时间
    SatButton *nDateTimeButton = new SatButton(SatButton::ArrowButton,this);
    nDateTimeButton->setText(tr("DateTime"));
    nDateTimeButton->installEventFilter(this);
    nLayout->addWidget(nDateTimeButton);
    nSignalMapper->setMapping(nDateTimeButton,"DateTime");
    connect(nDateTimeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDateTimeButton);
#endif
    //控制
    SatButton *nControlButton = new SatButton(SatButton::ArrowButton,this);
    nControlButton->setText(tr("Control"));
    nControlButton->installEventFilter(this);
    nLayout->addWidget(nControlButton);
    nSignalMapper->setMapping(nControlButton,"Control");
    connect(nControlButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nControlButton);

    //单位设置
    SatButton *nUnitSetButton = new SatButton(SatButton::ArrowButton,this);
    nUnitSetButton->setText(tr("Unit Setting"));
    nUnitSetButton->installEventFilter(this);
    nLayout->addWidget(nUnitSetButton);
    nSignalMapper->setMapping(nUnitSetButton,"Unit");
    connect(nUnitSetButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nUnitSetButton);
#if 0
    //电源管理
    SatButton *nPowerManageButton = new SatButton(SatButton::ArrowButton,this);
    nPowerManageButton->setText(tr("Power Manage"));
    nPowerManageButton->installEventFilter(this);
    nLayout->addWidget(nPowerManageButton);
    nSignalMapper->setMapping(nPowerManageButton,"Power");
    connect(nPowerManageButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nPowerManageButton);
#endif
    //返回按钮
    SatButton *nCancelButton = new SatButton(SatButton::TextLeftButton,this);
    nCancelButton->setText(tr("Cancel"));
    nCancelButton->installEventFilter(this);
    nLayout->addWidget(nCancelButton);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCancelButton);
    //配置
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));


    mLanguageWidget = NULL;
    mUpdateProgramWidget = NULL;
    mDateTimeWidget = NULL;
    mSystemControlWidget = NULL;
    mSetUnitWidget = NULL;
    mPowerManageWidget = NULL;

}


bool SatSysStackPageTwo::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysStackPageTwo::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void SatSysStackPageTwo::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    if(mIndex >= mList.size() - 1){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageTwo::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}
void SatSysStackPageTwo::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageTwo::handleContent(const QString &nStr){
    if(nStr == "Language"){
        if(mLanguageWidget == NULL){
            mLanguageWidget = new LanguageWidget(this);
        }
        mLanguageWidget->show();
    }else if(nStr == "Update"){
        if(mUpdateProgramWidget == NULL){
            mUpdateProgramWidget = new UpdateProgramWidget(this);
            mUpdateProgramWidget->registerField();
        }
        mUpdateProgramWidget->show();
    }else if(nStr == "DateTime"){
        if(mDateTimeWidget == NULL){
            mDateTimeWidget = new DateTimeWidget(this);
        }
        mDateTimeWidget->show();
    }else if(nStr == "Control"){
        if(mSystemControlWidget == NULL){
            mSystemControlWidget = new SystemControlWidget(this);
        }
        mSystemControlWidget->show();
    }else if(nStr == "Unit"){
        if(mSetUnitWidget == NULL){
            mSetUnitWidget = new SetUnitWidget(this);
        }
        mSetUnitWidget->show();
    }else if(nStr == "Power"){
        if(mPowerManageWidget == NULL){
            mPowerManageWidget = new PowerManageWidget(this);
        }
        mPowerManageWidget->show();
    }else if(nStr == "Cancel"){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }
}






//系统界面--右边面板--图像设置面板-------
SatSysStackPageThree::SatSysStackPageThree(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //打档时间manualPlay
    SatButton *nManualPlaySignButton = new SatButton(SatButton::TextSwitchButton,this);
    nManualPlaySignButton->setText(tr("Auto Shutter"));
    nManualPlaySignButton->setOnPath(tr("On"));
    nManualPlaySignButton->setOffPath(tr("Off"));
    nManualPlaySignButton->setOnState(mSatData->getAutoShutterSign());
    nManualPlaySignButton->installEventFilter(this);
    nLayout->addWidget(nManualPlaySignButton);
    nSignalMapper->setMapping(nManualPlaySignButton,"ManualPlaySign");
    connect(nManualPlaySignButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nManualPlaySignButton);
    //打档时间manualPlay
    SatButton *nManualPlayTimeButton = new SatButton(SatButton::TextArrowButton,this);
    nManualPlayTimeButton->setText(tr("Auto Shutter Time"));
    nManualPlayTimeButton->installEventFilter(this);
    nLayout->addWidget(nManualPlayTimeButton);
    nSignalMapper->setMapping(nManualPlayTimeButton,"ManualPlayTime");
    connect(nManualPlayTimeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nManualPlayTimeButton);
    if(mSatData->getAutoShutterSign() == false){
        nManualPlayTimeButton->hide();
    }


    //自动保存图片
    SatButton *nAutoSaveSignButton = new SatButton(SatButton::TextSwitchButton,this);
    nAutoSaveSignButton->setText(tr("Save Photo"));
    nAutoSaveSignButton->setOnPath(tr("On"));
    nAutoSaveSignButton->setOffPath(tr("Off"));
    nAutoSaveSignButton->setOnState(mSatData->getAutoSavePictureSign());
    nAutoSaveSignButton->installEventFilter(this);
    nLayout->addWidget(nAutoSaveSignButton);
    nSignalMapper->setMapping(nAutoSaveSignButton,"SavePhotoSign");
    connect(nAutoSaveSignButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAutoSaveSignButton);
    //自动保存图片
    SatButton *nAutoSaveTimeButton = new SatButton(SatButton::TextArrowButton,this);
    nAutoSaveTimeButton->setText(tr("Save Photo Time"));
    nAutoSaveTimeButton->installEventFilter(this);
    nLayout->addWidget(nAutoSaveTimeButton);
    nSignalMapper->setMapping(nAutoSaveTimeButton,"SavePhotoTime");
    connect(nAutoSaveTimeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAutoSaveTimeButton);
    if(mSatData->getAutoSavePictureSign() == false){
        nAutoSaveTimeButton->hide();
    }
    //返回按钮
    SatButton *nCancelButton = new SatButton(SatButton::TextLeftButton,this);
    nCancelButton->setText("Cancel");
    nCancelButton->installEventFilter(this);
    nLayout->addWidget(nCancelButton);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCancelButton);
    //配置
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类

    mShutterIntervalWidget = NULL;
    mAutoSavePictureWidget = NULL;


}

void SatSysStackPageThree::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}

void SatSysStackPageThree::doUpdateSlot(QString nOpeStr){
    if(nOpeStr == "AutoShutterSign" || nOpeStr == "AutoShutterTime"){
        if(mSatData->getAutoShutterSign()){
            mList.at(0)->setOnPath(QString("%1").arg(mSatData->getAutoShutterTime()));
        }else{
            mList.at(0)->setOnPath(tr("Off"));
        }
    }
}

void SatSysStackPageThree::registerField(){
#if 0
    QList<QString> nList;
    nList.append("AutoShutterSign");
    nList.append("AutoShutterTime");
    nList.append("AutoSavePictureSign");
    nList.append("AutoSavePictureTime");
    mSatData->attach(this,nList);
#endif

}


bool SatSysStackPageThree::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysStackPageThree::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mList.at(0)->setOnState(mSatData->getAutoShutterSign());
    if(mSatData->getAutoShutterSign()){
        mList.at(1)->show();
    }else{
        mList.at(1)->hide();
    }
    mList.at(2)->setOnState(mSatData->getAutoSavePictureSign());
    if(mSatData->getAutoSavePictureSign()){
        mList.at(3)->show();
    }else{
        mList.at(3)->hide();
    }
}

void SatSysStackPageThree::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    if(mIndex >= mList.size() - 1){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageThree::focusNext(){
    while(1){
        mIndex++;
        if(mIndex >= mList.size()){
            mIndex = 0;
        }
        if(!mList.at(mIndex)->isHidden()){
            break;
        }
    }
    mList.at(mIndex)->setFocus();
}
void SatSysStackPageThree::focusPrevious(){
    while(1){
        mIndex--;
        if(mIndex < 0){
            mIndex = mList.size() - 1;
        }
        if(!mList.at(mIndex)->isHidden()){
            break;
        }
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageThree::handleContent(const QString &nStr){
    if(nStr == "ManualPlaySign"){
        if(mSatData->getAutoShutterSign()){
            emit operationSignal(Auto_Shutter_Off,NULL);
            mList.at(1)->hide();
        }else{
            emit operationSignal(Auto_Shutter_On,NULL);
            mList.at(1)->show();
        }
    }else if(nStr == "ManualPlayTime"){
        if(mShutterIntervalWidget == NULL){
            mShutterIntervalWidget = new ShutterIntervalWidget(this);
        }
        mShutterIntervalWidget->show();
    }else if(nStr == "SavePhotoSign"){
        if(mSatData->getAutoSavePictureSign()){
            emit operationSignal(Set_SavePhotoSign_Off,NULL);
            mList.at(3)->hide();
        }else{
            emit operationSignal(Set_SavePhotoSign_On,NULL);
            mList.at(3)->show();
        }
    }else if(nStr == "SavePhotoTime"){
        if(mAutoSavePictureWidget == NULL){
            mAutoSavePictureWidget = new AutoSavePictureWidget(this);
        }
        mAutoSavePictureWidget->show();
    }else if(nStr == "Cancel"){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }
}




//系统界面--右边面板--系统信息面板-------
SatSysStackPageFour::SatSysStackPageFour(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //系统信息显示
    QLabel *nSystemInfoLabel = new QLabel(this);
    QString nSystemInfoStr = "\n\n\n  SATER..\n\n\thttps:http://www.sat.com.cn/\n\n\n\n";
    nSystemInfoLabel->setText(nSystemInfoStr);
    nLayout->addWidget(nSystemInfoLabel);
    //
    nLayout->addStretch();
    //恢复出厂设置Restore factory settings
    SatButton *nRestoreFactorySettingButton = new SatButton(SatButton::ArrowButton,this);
    nRestoreFactorySettingButton->setText(tr("Restore Factory Settings"));
    nRestoreFactorySettingButton->installEventFilter(this);
    nLayout->addWidget(nRestoreFactorySettingButton);
    nSignalMapper->setMapping(nRestoreFactorySettingButton,"Restore");
    connect(nRestoreFactorySettingButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRestoreFactorySettingButton);
    //返回按钮
    SatButton *nCancelButton = new SatButton(SatButton::TextLeftButton,this);
    nCancelButton->setText(tr("Cancel"));
    nCancelButton->installEventFilter(this);
    nLayout->addWidget(nCancelButton);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCancelButton);
    //配置

    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}


bool SatSysStackPageFour::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysStackPageFour::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    //更新面板中显示信息
}

void SatSysStackPageFour::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    if(mIndex >= mList.size() - 1){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageFour::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}
void SatSysStackPageFour::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysStackPageFour::handleContent(const QString &nStr){
    if(nStr == "Restore"){
        //恢复出厂设置
        QString nStr;
        nStr = tr("Function not implemented!");
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            //恢复出厂设置
        }
    }else if(nStr == "Cancel"){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }
}
























SystemWidget::SystemWidget(QWidget *parent) : QWidget(parent){
    //加载样式
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);




    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("System"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatSysListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
    SatSysStackPageOne *nPageOne = new SatSysStackPageOne(nTmpWidget);
    SatSysStackPageTwo *nPageTwo = new SatSysStackPageTwo(nTmpWidget);
    SatSysStackPageThree *nPageThree = new SatSysStackPageThree(nTmpWidget);
    SatSysStackPageFour *nPageFour = new SatSysStackPageFour(nTmpWidget);
    mRightWidget->addWidget(nPageOne);
    mRightWidget->addWidget(nPageTwo);
    mRightWidget->addWidget(nPageThree);
    mRightWidget->addWidget(nPageFour);

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





}


void SystemWidget::showEvent(QShowEvent *event){
    mRightWidget->setCurrentIndex(0);
    QWidget::showEvent(event);
}



void SystemWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void SystemWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void SystemWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void SystemWidget::goBackSlot(){
    this->hide();
}






