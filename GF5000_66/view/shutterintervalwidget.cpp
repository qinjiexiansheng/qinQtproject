#include "shutterintervalwidget.h"
#if 0
SatShutterIntervalListWidget::SatShutterIntervalListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("close"));
    mStringList->append(tr("30 seconds"));
    mStringList->append(tr("1 minutes"));
    mStringList->append(tr("5 minutes"));
    mStringList->append(tr("10 minutes"));
    mStringList->append(tr("30 minutes"));
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


bool SatShutterIntervalListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatShutterIntervalListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalListWidget::queryMode(){
    //查询
    int nIndex = 0;
    mList.at(nIndex)->setSelect(true);
}

void SatShutterIntervalListWidget::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("close")){

    }else if(nStr == tr("30 seconds")){
        //发操作命令
    }else if(nStr == tr("1 minutes")){

    }else if(nStr == tr("5 minutes")){
        //发操作命令
    }else if(nStr == tr("10 minutes")){

    }else if(nStr == tr("30 minutes")){

    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}












SatShutterIntervalPage::SatShutterIntervalPage(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Confirm"));
    mStringList->append(tr("Reelect"));
    mStringList->append(tr("Cancel"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        QPushButton *nButton = new QPushButton(this);
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
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatShutterIntervalPage::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void SatShutterIntervalPage::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

bool SatShutterIntervalPage::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            return false;
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

void SatShutterIntervalPage::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalPage::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalPage::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    if(nStr == tr("Cancel")){
        emit goBackSignal();
    }else if(nStr == tr("Confirm")){
        emit goBackSignal();
    }else if(nStr == tr("Reelect")){
        emit focusTransferSignal();
    }
}






















ShutterIntervalWidget::ShutterIntervalWidget(QWidget *parent) : QWidget(parent){
    //this->setWindowFlags(Qt::Window);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setGeometry(195,90,250,300);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Shutter Interval"));

    SatScrollArea *nScrollArea = new SatScrollArea(this);
    mLeftWidget = new SatShutterIntervalListWidget(nScrollArea);
    nScrollArea->setWidget(mLeftWidget);
    nScrollArea->setAlignment(Qt::AlignCenter);
    nScrollArea->setWidgetResizable(true);

    mRightWidget = new SatShutterIntervalPage(this);
    //总布局
    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addWidget(mSatTitleBar);
    nLayout->addWidget(nScrollArea);
    nLayout->addWidget(mRightWidget);
    nLayout->setMargin(1);//设置外边框
    nLayout->setSpacing(0);//设置内边框
    this->setLayout(nLayout);

    connect(mLeftWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusLeftToRightSlot()));
    connect(mRightWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mRightWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
}

void ShutterIntervalWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}

void ShutterIntervalWidget::focusLeftToRightSlot(){
    mRightWidget->setFocus();
}

void ShutterIntervalWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void ShutterIntervalWidget::goBackSlot(){
    this->hide();
}
#endif











#if 1

SatShutterIntervalSmallWidget::SatShutterIntervalSmallWidget(QWidget *parent) : QWidget(parent){
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

void SatShutterIntervalSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatShutterIntervalSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatShutterIntervalSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatShutterIntervalSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == tr("Confirm")){
        mIndex = 0;
    }else if(nOpeStr == tr("Hide")){
        this->hide();
        return;
    }else if(nOpeStr == tr("Quit")){
        this->hide();
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}






//自动保存图片面板
SatShutterIntervalPage::SatShutterIntervalPage(QWidget *parent) : QLabel(parent){
    mData = 0;
}

int SatShutterIntervalPage::getData(){
    return mData;
}

void SatShutterIntervalPage::setData(int nData){
    if(mData != nData){
        mData = nData;
        update();
    }
}


void SatShutterIntervalPage::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    QString nText;
    if(mData <= 60){
        nText = tr("%1 Seconds").arg(mData);
    }else if(mData <= 3600){
        if(mData % 60 == 0){
            if(mData/60 <= 1){
                nText = tr("%1 Minute").arg(mData/60);
            }else{
                nText = tr("%1 Minutes").arg(mData/60);
            }
        }else{
            if(mData/60 <= 1){
                nText = tr("%1 Minute %2 Seconds").arg(mData/60).arg(mData%60);
            }else{
                nText = tr("%1 Minutes %2 Seconds").arg(mData/60).arg(mData%60);
            }
        }
    }
    painter.drawText(0,0,width(),height(),Qt::AlignCenter,nText);
    QLabel::paintEvent(event);
}



ShutterIntervalWidget::ShutterIntervalWidget(QWidget *parent) : QWidget(parent){
    //this->setWindowFlags(Qt::Window);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setGeometry(195,140,250,200);
    mSatData = SatData::initance();
    queryData();
    //标题
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Auto Shutter"));
    mSatTitleBar->installEventFilter(this);
    //
    mPage = new SatShutterIntervalPage(this);
    mPage->setData(mData);
    //操作小窗口
    mSmallWidget = new SatShutterIntervalSmallWidget(this);
    mSmallWidget->hide();
    //总布局
    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar,0,Qt::AlignTop);
    nVLayout->addWidget(mPage);
    nVLayout->addWidget(mSmallWidget,0,Qt::AlignBottom);
    nVLayout->setContentsMargins(1,1,1,1);
    nVLayout->setSpacing(0);//设置内边框
    nVLayout->setStretchFactor(mPage,10);
    this->setLayout(nVLayout);
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool ShutterIntervalWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
#if 0
        if(nKey->isAutoRepeat()){
            return true;
        }
#endif
        switch(nKey->key()){
            case KEY_16:
                mSmallWidget->show();
                break;
            case KEY_26:
                subData();
                break;
            case KEY_27:
                addData();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void ShutterIntervalWidget::showEvent(QShowEvent *event){
    queryData();
    QWidget::showEvent(event);
}

void ShutterIntervalWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}

void ShutterIntervalWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == tr("Confirm")){
        emit operationSignal(Auto_Shutter_Time,QString("Time=%1").arg(mData));
        mSmallWidget->hide();
        this->hide();
    }
}

void ShutterIntervalWidget::goBackSlot(){
    this->hide();
}

void ShutterIntervalWidget::addData(){
    mData++;
    if(mData < 30){
        mData = 30;
    }
    if(mData > 3600){
        mData = 3600;
    }
    mPage->setData(mData);
}

void ShutterIntervalWidget::subData(){
    mData--;
    if(mData < 30){
        mData = 30;
    }
    if(mData > 3600){
        mData = 3600;
    }
    mPage->setData(mData);
}

void ShutterIntervalWidget::queryData(){
    mData = mSatData->getAutoShutterTime();
}
#endif







