#include "powermanagewidget.h"

SatPowerManageListWidget::SatPowerManageListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Screen Saver"));
    mStringList->append(tr("Timing Shutdown"));
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

void SatPowerManageListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    emit indexChangeSignal(mIndex);
}

void SatPowerManageListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatPowerManageListWidget::paintEvent(QPaintEvent *event){
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

void SatPowerManageListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatPowerManageListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatPowerManageListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatPowerManageListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatPowerManageListWidget::proofreadIndex(){
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

void SatPowerManageListWidget::handleContent(const QString &nStr){
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







SatPowerManagePageOneListWidget::SatPowerManagePageOneListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
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
}


bool SatPowerManagePageOneListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatPowerManagePageOneListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatPowerManagePageOneListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOneListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOneListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageOneListWidget::queryMode(){
    //查询
    int nIndex = 0;
    mList.at(nIndex)->setSelect(true);
}

void SatPowerManagePageOneListWidget::handleContent(const QString &nStr){
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


















SatPowerManagePageTwoListWidget::SatPowerManagePageTwoListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
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
}


bool SatPowerManagePageTwoListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatPowerManagePageTwoListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatPowerManagePageTwoListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwoListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwoListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPowerManagePageTwoListWidget::queryMode(){
    //查询
    int nIndex = 0;
    mList.at(nIndex)->setSelect(true);
}

void SatPowerManagePageTwoListWidget::handleContent(const QString &nStr){
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











PowerManageWidget::PowerManageWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Power Manage"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatPowerManageListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);

    SatScrollArea *nScrollAreaOne = new SatScrollArea(nTmpWidget);
    SatPowerManagePageOneListWidget *nPageOne = new SatPowerManagePageOneListWidget(nScrollAreaOne);
    nScrollAreaOne->setWidget(nPageOne);
    nScrollAreaOne->setAlignment(Qt::AlignCenter);
    nScrollAreaOne->setWidgetResizable(true);

    SatScrollArea *nScrollAreaTwo = new SatScrollArea(nTmpWidget);
    SatPowerManagePageTwoListWidget *nPageTwo = new SatPowerManagePageTwoListWidget(nScrollAreaTwo);
    nScrollAreaTwo->setWidget(nPageTwo);
    nScrollAreaTwo->setAlignment(Qt::AlignCenter);
    nScrollAreaTwo->setWidgetResizable(true);


    mRightWidget->addWidget(nScrollAreaOne);
    mRightWidget->addWidget(nScrollAreaTwo);
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
    connect(nPageOne,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(nPageTwo,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
}

void PowerManageWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void PowerManageWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void PowerManageWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void PowerManageWidget::goBackSlot(){
    this->hide();
}
