#include "languagewidget.h"

//语言列表窗口
SatLanguageListWidget::SatLanguageListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("English"));
    mStringList->append(tr("Chinese"));
    //按键生成
    for(int i=0; i<mStringList->size(); i++){
        QString nLanguageStr = mStringList->value(i);
        SatButton *nLanguageButton = new SatButton(SatButton::TextLeftButton,this);
        nLanguageButton->setText(nLanguageStr);
        nLanguageButton->installEventFilter(this);
        nLayout->addWidget(nLanguageButton);
        nSignalMapper->setMapping(nLanguageButton,nLanguageStr);//映射
        connect(nLanguageButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));//连接信号槽
        mList.append(nLanguageButton);
    }
    //布局配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();//布局中增加弹簧，占据布局的下半空间
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

//获取当前选择的语言
QString SatLanguageListWidget::getLanguage(){
    if(mIndex < 0 || mIndex >= mStringList->size()){
        return NULL;
    }
    return mStringList->value(mIndex);
}

//窗口显示事件，将第一个设为焦点
void SatLanguageListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

//焦点进入事件，设置焦点
void SatLanguageListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

//绘制事件，绘制右边的线
void SatLanguageListWidget::paintEvent(QPaintEvent *event){
#if 1
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
//    painter.drawLine(0,0,0,height());//画左边线
//    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
//    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
#endif
    QWidget::paintEvent(event);
}

//鼠标释放事件，校准焦点
void SatLanguageListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

//事件过滤
bool SatLanguageListWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){//在按键按下事件中处理
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
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
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}

//焦点移到上一个组件
void SatLanguageListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){//循环焦点
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

//焦点移到下一组件
void SatLanguageListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatLanguageListWidget::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){//当触摸点击时，需要校准索引
        mIndex = nIndex;
    }
    if(nStr == tr("English")){
    }
    emit focusTransferSignal();//发送焦点转移信号，上层窗口会将焦点移到另一个窗口
}

//索引校准，由于触摸滑动可能导致拥有焦点的项并不是当前索引的项
void SatLanguageListWidget::proofreadIndex(){
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
    }else{
    }
}


//语言设置窗口--右边列表面板
SatLanguagePage::SatLanguagePage(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Load"));
    mStringList->append(tr("Cancel"));
    mStringList->append(tr("Close"));
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
#if 0
    //装载
    SatButton *nLoadButton = new SatButton(SatButton::TextLeftButton,this);
    nLoadButton->setText(tr("Load"));
    nLoadButton->installEventFilter(this);
    nLayout->addWidget(nLoadButton);
    nSignalMapper->setMapping(nLoadButton,"Load");
    connect(nLoadButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLoadButton);
    //返回
    SatButton *nCancelButton = new SatButton(SatButton::TextLeftButton,this);
    nCancelButton->setText(tr("Cancel"));
    nCancelButton->installEventFilter(this);
    nLayout->addWidget(nCancelButton);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCancelButton);
    //关闭
    SatButton *nCloseButton = new SatButton(SatButton::TextLeftButton,this);
    nCloseButton->setText(tr("Close"));
    nCloseButton->installEventFilter(this);
    nLayout->addWidget(nCloseButton);
    nSignalMapper->setMapping(nCloseButton,"Close");
    connect(nCloseButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCloseButton);
#endif
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatLanguagePage::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void SatLanguagePage::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

bool SatLanguagePage::eventFilter(QObject *nObject, QEvent *event){
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
            case KEY_18:
                mList.at(mIndex)->click();
                break;
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_25:
                return false;
            case KEY_21:
                emit focusTransferSignal();
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
            case KEY_18:
                mList.at(mIndex)->click();
                break;
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_25:
                return false;
            case KEY_21:
                emit focusTransferSignal();
                break;
        }
#endif
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatLanguagePage::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatLanguagePage::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatLanguagePage::handleContent(const QString &nStr){
    //点击时，改变索引
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){//触摸点击可能会造成焦点和索引不一致
        mIndex = nIndex;
    }
    //操作判断
    if(nStr == tr("Load")){
        QString nStr;
        nStr = tr("Load the language?");
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit loadLanguageSignal();//发送加载该语言操作
        }
    }else if(nStr == tr("Cancel")){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }else if(nStr == tr("Close")){
        emit goBackSignal();
    }
}


//语言列表滑动区域
SatLanguageScrollArea::SatLanguageScrollArea(QWidget *parent) : QScrollArea(parent) , mOldPoint(QPoint(0,0)){
    mIsStartMove = false;
    mIsContinueMove = false;
}

void SatLanguageScrollArea::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        if(mIsStartMove){
            QPoint nNewPoint = event->globalPos();
            int nOffsetX = nNewPoint.x() - mOldPoint.x();
            int nOffsetY = nNewPoint.y() - mOldPoint.y();
            if(!mIsContinueMove && (nOffsetX > -10 && nOffsetX < 10) && (nOffsetY > -10 && nOffsetY < 10)){
                return;
            }
            mIsContinueMove = true;
            QScrollBar *nScrollBarX = this->horizontalScrollBar();
            QScrollBar *nScrollBarY = this->verticalScrollBar();
            nScrollBarX->setValue(nScrollBarX->value() - nOffsetX);
            nScrollBarY->setValue(nScrollBarY->value() - nOffsetY);
            mOldPoint = nNewPoint;
        }else{
            mIsStartMove = true;
            mIsContinueMove = false;
            mOldPoint = event->globalPos();
        }
    }
    QScrollArea::mouseMoveEvent(event);
}

void SatLanguageScrollArea::mouseReleaseEvent(QMouseEvent *event){
    mIsStartMove = false;
    mIsContinueMove = false;
    QScrollArea::mouseReleaseEvent(event);
}

void SatLanguageScrollArea::keyPressEvent(QKeyEvent *event){
    if(!this->widget()->hasFocus()){
        this->widget()->setFocus();
    }
    QScrollArea::keyPressEvent(event);
}

void SatLanguageScrollArea::keyReleaseEvent(QKeyEvent *event){
    calcRoll();
    QScrollArea::keyReleaseEvent(event);
}


void SatLanguageScrollArea::calcRoll(){
    QWidget *nFocusWidget = this->focusWidget();
    if(nFocusWidget){
        int nScrollBarValue = this->verticalScrollBar()->value();
        int nWidgetY = nFocusWidget->pos().y();
        int nWidgetH = nFocusWidget->height();
        int nAreaY = this->pos().y();
        int nAreaH = this->height();
        int nDeltaValue = 0;
        if(nWidgetY < (nAreaY + nScrollBarValue)){
            nDeltaValue = (nAreaY + nScrollBarValue) - nWidgetY;
        }else if((nWidgetY + nWidgetH) > (nAreaH + nScrollBarValue)){
            nDeltaValue = (nAreaH + nScrollBarValue) - (nWidgetY + nWidgetH);
        }else{
            return;
        }
        this->verticalScrollBar()->setValue(nScrollBarValue - nDeltaValue);
    }
}


//语言设置窗口
LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);
    //创建标题栏
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Language Setting"));
    //子窗口创建
    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatLanguageScrollArea(nTmpWidget);
    mRightWidget = new SatLanguagePage(nTmpWidget);
    SatLanguageListWidget *nListWidget = new SatLanguageListWidget(mLeftWidget);
    mLeftWidget->setWidget(nListWidget);
    mLeftWidget->setAlignment(Qt::AlignTop);
    mLeftWidget->setWidgetResizable(true);
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
    //信号槽连接
    connect(nListWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusLeftToRightSlot()));
    connect(mRightWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(mRightWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mRightWidget,SIGNAL(loadLanguageSignal()),this,SLOT(loadLanguageSlot()));
}

void LanguageWidget::focusLeftToRightSlot(){
    mRightWidget->setFocus();
}

void LanguageWidget::focusRightToLeftSlot(){
    mLeftWidget->widget()->setFocus();
}

void LanguageWidget::goBackSlot(){
    this->hide();
}

void LanguageWidget::loadLanguageSlot(){

}

void LanguageWidget::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == KEY_25){//返回键
        goBackSlot();
    }
    QWidget::keyReleaseEvent(event);
}

