#include "datetimewidget.h"

SatDateTimeListWidget::SatDateTimeListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Date"));
    mStringList->append(tr("Time"));
    mStringList->append(tr("Area"));
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
    //nLayout->setMargin(0);
    nLayout->setContentsMargins(0,0,1,0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatDateTimeListWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                for(int i=0; i<mStringList->size(); i++){
                    QString nTextStr = mStringList->value(i);
                    mList.at(i)->setText(nTextStr);
                }
            }
            break;
        default:
            break;
    }
}

void SatDateTimeListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatDateTimeListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatDateTimeListWidget::paintEvent(QPaintEvent *event){
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

void SatDateTimeListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatDateTimeListWidget::eventFilter(QObject *nObject, QEvent *event){
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
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatDateTimeListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatDateTimeListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    emit indexChangeSignal(mIndex);
    mList.at(mIndex)->setFocus();
}

void SatDateTimeListWidget::proofreadIndex(){
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

void SatDateTimeListWidget::handleContent(const QString &nStr){
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









SatDateTimePageOne::SatDateTimePageOne(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    //QVBoxLayout *nLayout = new QVBoxLayout;
    QGridLayout *nLayout = new QGridLayout;
    updateData();
    //
    mLabel = new QLabel(this);
    nLayout->addWidget(mLabel,0,0,1,2,Qt::AlignCenter);
    nLayout->setRowStretch(0,10);
    updatePanel();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Add Year"));
    mStringList->append(tr("Sub Year"));
    mStringList->append(tr("Add Month"));
    mStringList->append(tr("Sub Month"));
    mStringList->append(tr("Add Day"));
    mStringList->append(tr("Sub Day"));
    mStringList->append(tr("Confirm"));
    mStringList->append(tr("Cancel"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        QPushButton *nButton = new QPushButton(this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
        nLayout->addWidget(nButton,i/2+1,i%2);
    }
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //nLayout->setMargin(0);
    //nLayout->setContentsMargins(0,0,1,0);
    //nLayout->setSpacing(0);
    nLayout->setMargin(5);//外边距
    nLayout->setSpacing(5);//组件边距
    nLayout->setColumnStretch(1,1);
    nLayout->setColumnStretch(0,1);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}


void SatDateTimePageOne::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                for(int i=0; i<mStringList->size(); i++){
                    QString nTextStr = mStringList->value(i);
                    mList.at(i)->setText(nTextStr);
                }
            }
            break;
        default:
            break;
    }
}



void SatDateTimePageOne::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    updateData(true);
    updatePanel();
}

void SatDateTimePageOne::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageOne::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatDateTimePageOne::eventFilter(QObject *nObject, QEvent *event){
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

void SatDateTimePageOne::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageOne::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageOne::proofreadIndex(){
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

void SatDateTimePageOne::updateData(bool nIsGet){
    if(nIsGet){
        QDate nDate = QDate::currentDate();
        mYear = nDate.year();
        mMonth = nDate.month();
        mDay = nDate.day();
        if(mYear < 1970){
            mYear = 1970;
        }else if(mYear > 2100){
            mYear = 2100;
        }
        if(mMonth < 1){
            mMonth = 1;
        }else if(mMonth > 12){
            mMonth = 12;
        }
        if(mDay < 1){
            mDay = 1;
        }else if(mDay > numberDay(mYear,mMonth)){
            mDay = numberDay(mYear,mMonth);
        }
    }{
        //设置系统日期
    }
}

void SatDateTimePageOne::updatePanel(){
    QString nStr = QString("%1-%2-%3").arg(mYear,4,10,QLatin1Char('0'))
            .arg(mMonth,2,10,QLatin1Char('0'))
            .arg(mDay,2,10,QLatin1Char('0'));
    mLabel->setText(nStr);
}

void SatDateTimePageOne::modifyYear(bool nIsAdd){
    if(nIsAdd){
        mYear += 1;
        if(mYear > 2100){
            mYear = 2100;
        }
    }else{
        mYear -= 1;
        if(mYear < 1970){
            mYear = 1970;
        }
    }
}

void SatDateTimePageOne::modifyMonth(bool nIsAdd){
    if(nIsAdd){
        mMonth += 1;
        if(mMonth > 12){
            mMonth = 12;
        }
    }else{
        mMonth -= 1;
        if(mMonth < 1){
            mMonth = 1;
        }
    }
}

void SatDateTimePageOne::modifyDay(bool nIsAdd){
    if(nIsAdd){
        mDay += 1;
        int nMaxDay = numberDay(mYear,mMonth);
        if(mDay > nMaxDay){
            mDay = nMaxDay;
        }
    }else{
        mDay -= 1;
        if(mDay < 1){
            mDay = 1;
        }
    }
}

int SatDateTimePageOne::numberDay(int nYear, int nMonth){
    if(nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7
            || nMonth == 8 || nMonth == 10 || nMonth == 12){
        return 31;
    }
    if(nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11){
        return 30;
    }
    if(nMonth == 2 && QDate::isLeapYear(nYear)){
        return 29;
    }else if(nMonth == 2 && !QDate::isLeapYear(nYear)){
        return 28;
    }
    return 0;
}

void SatDateTimePageOne::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    if(nStr == tr("Add Year")){
        modifyYear(true);
    }else if(nStr == tr("Sub Year")){
        modifyYear(false);
    }else if(nStr == tr("Add Month")){
        modifyMonth(true);
    }else if(nStr == tr("Sub Month")){
        modifyMonth(false);
    }else if(nStr == tr("Add Day")){
        modifyDay(true);
    }else if(nStr == tr("Sub Day")){
        modifyDay(false);
    }else if(nStr == tr("Confirm")){
        updateData(false);
        return;
    }else if(nStr == tr("Cancel")){
        emit focusTransferSignal();
        return;
    }
}










SatDateTimePageTwo::SatDateTimePageTwo(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    //QVBoxLayout *nLayout = new QVBoxLayout;
    QGridLayout *nLayout = new QGridLayout;
    updateData();
    //
    mLabel = new QLabel(this);
    nLayout->addWidget(mLabel,0,0,1,2,Qt::AlignCenter);
    nLayout->setRowStretch(0,10);
    updatePanel();
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Add Hour"));
    mStringList->append(tr("Sub Hour"));
    mStringList->append(tr("Add Minute"));
    mStringList->append(tr("Sub Minute"));
    mStringList->append(tr("Add Second"));
    mStringList->append(tr("Sub Second"));
    mStringList->append(tr("Confirm"));
    mStringList->append(tr("Cancel"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        QPushButton *nButton = new QPushButton(this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
        nLayout->addWidget(nButton,i/2+1,i%2);
    }
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //nLayout->setMargin(0);
    //nLayout->setContentsMargins(0,0,1,0);
    //nLayout->setSpacing(0);
    nLayout->setMargin(5);//外边距
    nLayout->setSpacing(5);//组件边距
    nLayout->setColumnStretch(1,1);
    nLayout->setColumnStretch(0,1);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}


void SatDateTimePageTwo::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                for(int i=0; i<mStringList->size(); i++){
                    QString nTextStr = mStringList->value(i);
                    mList.at(i)->setText(nTextStr);
                }
            }
            break;
        default:
            break;
    }
}


void SatDateTimePageTwo::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    updateData(true);
    updatePanel();
}

void SatDateTimePageTwo::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageTwo::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatDateTimePageTwo::eventFilter(QObject *nObject, QEvent *event){
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

void SatDateTimePageTwo::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageTwo::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageTwo::proofreadIndex(){
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

void SatDateTimePageTwo::updateData(bool nIsGet){
    if(nIsGet){
        QTime nTime = QTime::currentTime();
        mHour = nTime.hour();
        mMinute = nTime.minute();
        mSecond = nTime.second();
        if(mHour < 0){
            mHour = 0;
        }else if(mHour > 23){
            mHour = 23;
        }
        if(mMinute < 0){
            mMinute = 0;
        }else if(mMinute > 59){
            mMinute = 59;
        }
        if(mSecond < 0){
            mSecond = 0;
        }else if(mSecond > 59){
            mSecond = 59;
        }
    }{
        //设置系统日期
    }
}

void SatDateTimePageTwo::updatePanel(){
    QString nStr = QString("%1:%2:%3").arg(mHour,2,10,QLatin1Char('0'))
            .arg(mMinute,2,10,QLatin1Char('0'))
            .arg(mSecond,2,10,QLatin1Char('0'));
    mLabel->setText(nStr);
}

void SatDateTimePageTwo::modifyHour(bool nIsAdd){
    if(nIsAdd){
        mHour += 1;
        if(mHour > 23){
            mHour = 23;
        }
    }else{
        mHour -= 1;
        if(mHour < 0){
            mHour = 0;
        }
    }
}

void SatDateTimePageTwo::modifyMinute(bool nIsAdd){
    if(nIsAdd){
        mMinute += 1;
        if(mMinute > 59){
            mMinute = 59;
        }
    }else{
        mMinute -= 1;
        if(mMinute < 0){
            mMinute = 0;
        }
    }
}

void SatDateTimePageTwo::modifySecond(bool nIsAdd){
    if(nIsAdd){
        mSecond += 1;
        if(mSecond >  59){
            mSecond = 59;
        }
    }else{
        mSecond -= 1;
        if(mSecond < 0){
            mSecond = 0;
        }
    }
}

void SatDateTimePageTwo::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    if(nStr == tr("Add Hour")){
        modifyHour(true);
    }else if(nStr == tr("Sub Hour")){
        modifyHour(false);
    }else if(nStr == tr("Add Minute")){
        modifyMinute(true);
    }else if(nStr == tr("Sub Minute")){
        modifyMinute(false);
    }else if(nStr == tr("Add Second")){
        modifySecond(true);
    }else if(nStr == tr("Sub Second")){
        modifySecond(false);
    }else if(nStr == tr("Confirm")){
        updateData(false);
        return;
    }else if(nStr == tr("Cancel")){
        emit focusTransferSignal();
        return;
    }
}







SatDateTimePageThreeListWidget::SatDateTimePageThreeListWidget(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("BeiJing"));
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
    //nLayout->setMargin(0);
    nLayout->setContentsMargins(0,0,0,1);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

QString SatDateTimePageThreeListWidget::getSelectTimeZone(){
    return mStringList->at(mIndex);
}


void SatDateTimePageThreeListWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                for(int i=0; i<mStringList->size(); i++){
                    QString nTextStr = mStringList->value(i);
                    mList.at(i)->setText(nTextStr);
                }
            }
            break;
        default:
            break;
    }
}



void SatDateTimePageThreeListWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    //将目前的时区设置高亮，时区不在列表，则显示北京时区
    mIndex = 1;
    mList.at(mIndex)->setHighLight(true);
}

void SatDateTimePageThreeListWidget::focusInEvent(QFocusEvent *event){
    //qDebug("[D]Lin >> SatDateTimePageThreeListWidget--focusInEvent()--");
    QWidget::focusInEvent(event);
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThreeListWidget::paintEvent(QPaintEvent *event){
#if 0
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
#endif
    QWidget::paintEvent(event);
}

void SatDateTimePageThreeListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatDateTimePageThreeListWidget::eventFilter(QObject *nObject, QEvent *event){
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
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatDateTimePageThreeListWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThreeListWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThreeListWidget::proofreadIndex(){
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

void SatDateTimePageThreeListWidget::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    emit focusTransferSignal();
}











SatDateTimePageThree::SatDateTimePageThree(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    //QVBoxLayout *nLayout = new QVBoxLayout;
    QGridLayout *nLayout = new QGridLayout;
    //
    mScrollArea = new SatScrollArea(this);
    mListWidget = new SatDateTimePageThreeListWidget(mScrollArea);
    mScrollArea->setWidget(mListWidget);
    mScrollArea->setAlignment(Qt::AlignCenter);
    mScrollArea->setWidgetResizable(true);
    nLayout->addWidget(mScrollArea,0,0,1,3);
    nLayout->setRowStretch(0,10);
    //mListWidget->installEventFilter(mScrollArea);
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
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
        nLayout->addWidget(nButton,i/3+1,i%3);
    }
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //nLayout->setContentsMargins(0,0,0,0);
    //nLayout->setSpacing(0);
    nLayout->setMargin(5);//外边距
    nLayout->setSpacing(5);//组件边距
    nLayout->setColumnStretch(1,1);
    nLayout->setColumnStretch(0,1);
    nLayout->setColumnStretch(2,1);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    connect(mListWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusUpToDownSlot()));
}

void SatDateTimePageThree::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                for(int i=0; i<mStringList->size(); i++){
                    QString nTextStr = mStringList->value(i);
                    mList.at(i)->setText(nTextStr);
                }
            }
            break;
        default:
            break;
    }
}


void SatDateTimePageThree::focusInEvent(QFocusEvent *event){
    qDebug("[D]Lin >> SatDateTimePageThree--focusInEvent()--");
    QWidget::focusInEvent(event);
    mListWidget->setFocus();
    mScrollArea->calcRoll();
}

void SatDateTimePageThree::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatDateTimePageThree::eventFilter(QObject *nObject, QEvent *event){
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
                mList.at(mIndex)->click();
                break;
            case KEY_20:
            case KEY_22:
                focusNext();
                break;
            case KEY_19:
            case KEY_21:
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
                mList.at(mIndex)->click();
                break;
            case KEY_20:
            case KEY_22:
                focusNext();
                break;
            case KEY_19:
            case KEY_21:
                focusPrevious();
                break;
        }
#endif
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatDateTimePageThree::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThree::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThree::proofreadIndex(){
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

void SatDateTimePageThree::focusUpToDownSlot(){
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatDateTimePageThree::handleContent(const QString &nStr){
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    if(nStr == tr("Confirm")){
        //设置时区
    }else if(nStr == tr("Reelect")){
        mListWidget->setFocus();
    }else if(nStr == tr("Cancel")){
        emit focusTransferSignal();
    }
}













DateTimeWidget::DateTimeWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("DateTime"));

    QWidget *nTmpWidget = new QWidget(this);
    mLeftWidget = new SatDateTimeListWidget(nTmpWidget);
    mRightWidget = new QStackedWidget(nTmpWidget);
    SatDateTimePageOne *nPageOne = new SatDateTimePageOne(nTmpWidget);
    SatDateTimePageTwo *nPageTwo = new SatDateTimePageTwo(nTmpWidget);
    SatDateTimePageThree *nPageThree = new SatDateTimePageThree(nTmpWidget);
    mRightWidget->addWidget(nPageOne);
    mRightWidget->addWidget(nPageTwo);
    mRightWidget->addWidget(nPageThree);

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
}

void DateTimeWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            {
                mSatTitleBar->setTitle(tr("DateTime"));
            }
            break;
        default:
            break;
    }
}


void DateTimeWidget::focusLeftToRightSlot(){
    mRightWidget->currentWidget()->setFocus();
}

void DateTimeWidget::focusRightToLeftSlot(){
    mLeftWidget->setFocus();
}

void DateTimeWidget::itemChangeSlot(int nIndex){
    if(nIndex >= 0 && nIndex < mRightWidget->count()){
        mRightWidget->setCurrentIndex(nIndex);
    }
}

void DateTimeWidget::goBackSlot(){
    this->hide();
}

