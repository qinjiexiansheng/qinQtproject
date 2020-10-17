#include "systemcontrolwidget.h"

SatSysControlListWidget::SatSysControlListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
#if 0
    mStringList->append(tr("Video Output"));
#endif
    mStringList->append(tr("Laser"));
#if 0
    mStringList->append(tr("USB Model"));
#endif
#if 0
    mStringList->append(tr("Screen saver"));//屏保设置
    mStringList->append(tr("Timing shutdown"));//定时关机
#endif


    mStringList->append(tr("Cancel"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::TextLeftButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setContentsMargins(0,0,1,0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatSysControlListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    emit indexChangeSignal(mIndex);
}

void SatSysControlListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSysControlListWidget::paintEvent(QPaintEvent *event){
#if 1
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
#endif
    QWidget::paintEvent(event);
}

void SatSysControlListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatSysControlListWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            //return false;
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
            case KEY_18:
            case KEY_22:
                mList.at(mIndex)->click();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_19:
                focusPrevious();
                break;
        }
#endif
        return true;
    }else if(event->type() == QEvent::KeyRelease){
#if 0
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            //return false;
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
            case KEY_18:
            case KEY_22:
                mList.at(mIndex)->click();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_19:
                focusPrevious();
                break;
        }
#endif
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatSysControlListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSysControlListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSysControlListWidget::proofreadIndex(){
    QWidget *nFocusWidget = focusWidget();
    if(nFocusWidget != mList.at(mIndex)){
        int nIndex = mIndex;
        for(int i=0; i<mList.size(); i++){
            if(mList.at(i) == nFocusWidget){
                nIndex = i;
                break;
            }
        }
        mIndex = nIndex;
    }
}

void SatSysControlListWidget::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    if(nStr == tr("Cancel")){
        emit goBackSignal();
    }else{
        emit focusTransferSignal();
    }
}




#if 0
SatSysControlPageOne::SatSysControlPageOne(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("MP4"));
    mStringList->append(tr("MP3"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::RadioTickButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    queryMode();//查询当前模式
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    //nLayout->setContentsMargins(0,0,1,0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}


bool SatSysControlPageOne::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysControlPageOne::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatSysControlPageOne::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageOne::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageOne::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageOne::queryMode(){
    //查询
    int nCurrentModeIndex = 0;
    mList.at(nCurrentModeIndex)->setSelect(true);

}

void SatSysControlPageOne::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("MP4")){
        //发操作命令
    }else if(nStr == tr("MP3")){
        //发操作命令
    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}
#endif






SatSysControlPageTwo::SatSysControlPageTwo(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("On"));
    mStringList->append(tr("Off"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::RadioTickButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    queryMode();//查询当前模式
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));

    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类

}


bool SatSysControlPageTwo::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysControlPageTwo::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatSysControlPageTwo::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageTwo::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageTwo::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageTwo::queryMode(){
    //查询
    bool nLaserSign = mSatData->getLaserSign();
    if(nLaserSign){
        mList.at(0)->setSelect(true);
    }else{
        mList.at(1)->setSelect(true);
    }
}

void SatSysControlPageTwo::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("On")){
        if(!mSatData->getLaserSign()){
            emit operationSignal(Laser_On,NULL);
        }
    }else if(nStr == tr("Off")){
        if(mSatData->getLaserSign()){
            emit operationSignal(Laser_Off,NULL);
        }
    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}





#if 0
SatSysControlPageThree::SatSysControlPageThree(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("USB1"));
    mStringList->append(tr("USB2"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::RadioTickButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    queryMode();//查询当前模式
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}


bool SatSysControlPageThree::eventFilter(QObject *nObject, QEvent *event){
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

void SatSysControlPageThree::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatSysControlPageThree::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageThree::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageThree::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSysControlPageThree::queryMode(){
    //查询
    bool nUsbSign = true;
    if(nUsbSign){
        mList.at(0)->setSelect(true);
    }else{
        mList.at(1)->setSelect(true);
    }
}

void SatSysControlPageThree::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("USB1")){
        //发操作命令
    }else if(nStr == tr("USB2")){
        //发操作命令
    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}
#endif



#if 0
//屏保设置
SatPowerManagePageOne::SatPowerManagePageOne(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("close"));
    mStringList->append(tr("1 minutes"));
    mStringList->append(tr("5 minutes"));
    mStringList->append(tr("10 minutes"));
    mStringList->append(tr("30 minutes"));
    mStringList->append(tr("1 hours"));
    mStringList->append(tr("2 hours"));
    mStringList->append(tr("3 hours"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::RadioTickButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    queryMode();//查询当前模式
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}


bool SatPowerManagePageOne::eventFilter(QObject *nObject, QEvent *event){
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
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatPowerManagePageOne::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatPowerManagePageOne::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOne::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOne::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOne::queryMode(){
    //查询
    int nIndex = 0;
    mList.at(nIndex)->setSelect(true);
}

void SatPowerManagePageOne::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("close")){

    }else if(nStr == tr("1 minutes")){
        //发操作命令
    }else if(nStr == tr("5 minutes")){
        //发操作命令
    }else if(nStr == tr("10 minutes")){

    }else if(nStr == tr("30 minutes")){

    }else if(nStr == tr("1 hours")){

    }else if(nStr == tr("2 hours")){

    }else if(nStr == tr("3 hours")){

    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}

















//定时关机
SatPowerManagePageTwo::SatPowerManagePageTwo(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("close"));
    mStringList->append(tr("1 minutes"));
    mStringList->append(tr("5 minutes"));
    mStringList->append(tr("10 minutes"));
    mStringList->append(tr("30 minutes"));
    mStringList->append(tr("1 hours"));
    mStringList->append(tr("2 hours"));
    mStringList->append(tr("3 hours"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::RadioTickButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    queryMode();//查询当前模式
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}


bool SatPowerManagePageTwo::eventFilter(QObject *nObject, QEvent *event){
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
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatPowerManagePageTwo::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatPowerManagePageTwo::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwo::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwo::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwo::queryMode(){
    //查询
    int nIndex = 0;
    mList.at(nIndex)->setSelect(true);
}

void SatPowerManagePageTwo::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("close")){
    }else if(nStr == tr("1 minutes")){
    }else if(nStr == tr("5 minutes")){
        //发操作命令
    }else if(nStr == tr("10 minutes")){

    }else if(nStr == tr("30 minutes")){

    }else if(nStr == tr("1 hours")){

    }else if(nStr == tr("2 hours")){

    }else if(nStr == tr("3 hours")){

    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}

#endif




















SystemControlWidget::SystemControlWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Control"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatSysControlListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
#if 0
    SatSysControlPageOne *nPageOne = new SatSysControlPageOne(nTmpWidget);
#endif
    SatSysControlPageTwo *nPageTwo = new SatSysControlPageTwo(nTmpWidget);
#if 0
    SatSysControlPageThree *nPageThree = new SatSysControlPageThree(nTmpWidget);
    mRightWidget->addWidget(nPageOne);
#endif

#if 0
    SatScrollArea *nScrollAreaOne = new SatScrollArea(nTmpWidget);
    SatPowerManagePageOne *nPowerManageOne = new SatPowerManagePageOne(nScrollAreaOne);
    nScrollAreaOne->setWidget(nPowerManageOne);
    nScrollAreaOne->setAlignment(Qt::AlignCenter);
    nScrollAreaOne->setWidgetResizable(true);
    SatScrollArea *nScrollAreaTwo = new SatScrollArea(nTmpWidget);
    SatPowerManagePageTwo *nPowerManageTwo = new SatPowerManagePageTwo(nScrollAreaTwo);
    nScrollAreaTwo->setWidget(nPowerManageTwo);
    nScrollAreaTwo->setAlignment(Qt::AlignCenter);
    nScrollAreaTwo->setWidgetResizable(true);
#endif



    mRightWidget->addWidget(nPageTwo);
#if 0
    mRightWidget->addWidget(nPageThree);
#endif

#if 0
    mRightWidget->addWidget(nScrollAreaOne);
    mRightWidget->addWidget(nScrollAreaTwo);
    connect(nPowerManageOne,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPowerManageTwo,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
#endif


    //内布局
    QHBoxLayout *nHLayout = new QHBoxLayout;
    nHLayout->addWidget(mLeftWidget,2);
    nHLayout->addWidget(mRightWidget,3);
    nHLayout->setSpacing(0);
    nHLayout->setMargin(0);
    nTmpWidget->setLayout(nHLayout);
    //总布局
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
#if 0
    connect(nPageOne,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
#endif
    connect(nPageTwo,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
#if 0
    connect(nPageThree,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
#endif
}

void SystemControlWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void SystemControlWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void SystemControlWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void SystemControlWidget::goBackSlot(){
    this->hide();
}
