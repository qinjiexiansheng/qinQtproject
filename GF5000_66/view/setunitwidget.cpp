#include "setunitwidget.h"

SatSetUnitListWidget::SatSetUnitListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Length Unit"));
    mStringList->append(tr("Temp Unit"));
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

void SatSetUnitListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    emit indexChangeSignal(mIndex);
}

void SatSetUnitListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSetUnitListWidget::paintEvent(QPaintEvent *event){
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

void SatSetUnitListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatSetUnitListWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatSetUnitListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSetUnitListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatSetUnitListWidget::proofreadIndex(){
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

void SatSetUnitListWidget::handleContent(const QString &nStr){
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











SatSetUnitPageOne::SatSetUnitPageOne(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Meter"));
    mStringList->append(tr("Foot"));
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


bool SatSetUnitPageOne::eventFilter(QObject *nObject, QEvent *event){
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
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatSetUnitPageOne::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatSetUnitPageOne::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageOne::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageOne::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageOne::queryMode(){
    //查询
    if(mSatData->getLengthUnit()){
        mList.at(0)->setSelect(true);
    }else{
        mList.at(1)->setSelect(true);
    }

}

void SatSetUnitPageOne::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("Meter")){
        emit operationSignal(Set_Length_Meter,NULL);
    }else if(nStr == tr("Foot")){
        emit operationSignal(Set_Length_Foot,NULL);
    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}





SatSetUnitPageTwo::SatSetUnitPageTwo(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Celsius"));
    mStringList->append(tr("Fahrenheit"));
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


bool SatSetUnitPageTwo::eventFilter(QObject *nObject, QEvent *event){
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
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatSetUnitPageTwo::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    queryMode();
}

void SatSetUnitPageTwo::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageTwo::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageTwo::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatSetUnitPageTwo::queryMode(){
    //查询
    if(mSatData->getTempUnit()){
        mList.at(0)->setSelect(true);
    }else{
        mList.at(1)->setSelect(true);
    }
}

void SatSetUnitPageTwo::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    mList.at(mIndex)->setSelect(true);
    if(nStr == tr("Celsius")){
        emit operationSignal(Set_Temp_Celsius,NULL);
    }else if(nStr == tr("Fahrenheit")){
        emit operationSignal(Set_Temp_Fahrenheit,NULL);
    }
    mList.at(mIndex)->setHighLight(false);
    emit focusTransferSignal();
}












SetUnitWidget::SetUnitWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Unit Setting"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatSetUnitListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
    SatSetUnitPageOne *nPageOne = new SatSetUnitPageOne(nTmpWidget);
    SatSetUnitPageTwo *nPageTwo = new SatSetUnitPageTwo(nTmpWidget);
    mRightWidget->addWidget(nPageOne);
    mRightWidget->addWidget(nPageTwo);
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

void SetUnitWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void SetUnitWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void SetUnitWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void SetUnitWidget::goBackSlot(){
    this->hide();
}
