#include "smallwidget.h"

SaveADWidget::SaveADWidget(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();//获取数据类
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    this->setFixedSize(250,220);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    mSatTitleBar = new SatTitleBar(tr("SetAD"),this);//标题栏
    QWidget *nWidget = new QWidget(this);
    QGridLayout *nWidgetLayout = new QGridLayout;
    //温度标签
    QLabel *nTempLabel = new QLabel(tr("Temp:"),nWidget);
    nWidgetLayout->addWidget(nTempLabel,0,0);
    mComboBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mComboBox,0,1);
    mComboBox->installEventFilter(this);
    mList.append(mComboBox);//加入焦点列表
    mEnum = mSatData->getGearMode();//获取当前档位
    //创建组合框里的项
    QList<QString> nStrList;
    if(mEnum == SatData::GEARONE){
        nStrList.append("0");
        nStrList.append("30");
        nStrList.append("70");
        nStrList.append("90");
        nStrList.append("100");
        nStrList.append("120");
        nStrList.append("140");
        nStrList.append("160");
        nStrList.append("180");
        nStrList.append("200");
        nStrList.append("250");
        nStrList.append("300");
    }else{
        nStrList.append("0");
        nStrList.append("30");
        nStrList.append("60");
        nStrList.append("180");
        nStrList.append("200");
        nStrList.append("250");
        nStrList.append("300");
        nStrList.append("400");
        nStrList.append("500");
        nStrList.append("600");
        nStrList.append("800");
        nStrList.append("1000");
        nStrList.append("1200");
    }
    mMaxIndex = nStrList.size();
    for(int i = 0; i < nStrList.size(); i++){
        mComboBox->addItem(nStrList.at(i));
    }
    mComboBox->setCurrentIndex(0);
    //标签
    QLabel *nADLabel = new QLabel(tr("AD:"),nWidget);
    nWidgetLayout->addWidget(nADLabel,1,0);
    //显示Ad值的标签
    mAdLabel = new QLabel(nWidget);
    mAdLabel->setText(QString("%1").arg(mSatData->getCenterAd(),4,16,QLatin1Char('0')));
    nWidgetLayout->addWidget(mAdLabel,1,1);
    //Save按钮
    QPushButton *nSaveButton = new QPushButton(tr("OK"),nWidget);
    nWidgetLayout->addWidget(nSaveButton,2,0);
    nSaveButton->installEventFilter(this);
    mList.append(nSaveButton);//加入焦点列表
    connect(nSaveButton,SIGNAL(clicked()),this,SLOT(saveSlot()));
    //OK按钮
    QPushButton *nOkButton = new QPushButton(tr("Cancel"),nWidget);
    nWidgetLayout->addWidget(nOkButton,2,1);
    nOkButton->installEventFilter(this);
    mList.append(nOkButton);//加入焦点列表
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(closeSlot()));
    //布局管理
    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;//垂直布局
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setRowStretch(2,1);
    this->setLayout(nMainLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

void SaveADWidget::registerField(){
    //注册监听字段，该窗口设置了关闭时销毁，在关闭时需要注销观察字段，或者在析构函数里注销
    mSatData->attach(this,"CenterAd");
}


void SaveADWidget::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}

void SaveADWidget::doUpdateSlot(QString nUpStr){
    if(nUpStr == "CenterAd"){//更新AD值
        mAdLabel->setText(QString("%1").arg(mSatData->getCenterAd(),4,16,QLatin1Char('0')));
    }
}



bool SaveADWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;//事件转为按键事件
        if(nKey->isAutoRepeat()){
            return true;//持续操作不处理
        }
        switch(nKey->key()){
            case KEY_20://下按键
                focusNext();
                break;
            case KEY_19://上按键
                focusPrevious();
                break;
            case KEY_26:
            case KEY_23:
                {
                    emit operationSignal(Manual_Play,NULL);//打档
                }
                break;
            case KEY_18:
                {
                    if(obj != mComboBox){
                        ((QPushButton*)obj)->click();//非组合框产生点击事件
                    }else{
                        saveSlot();
                    }
                }
                break;
            case KEY_25://返回按键
                closeSlot();
                break;
            case KEY_21:
                {
                    if(obj == mComboBox){//组合框切换
                        int nIndex = mComboBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = mMaxIndex - 1;
                        }
                        mComboBox->setCurrentIndex(nIndex);
                    }else{
                        focusPrevious();
                    }

                }
                break;
            case KEY_22:
                {
                    if(obj == mComboBox){//组合框切换
                        int nIndex = mComboBox->currentIndex();
                        nIndex++;
                        if(nIndex >= mMaxIndex){
                            nIndex = 0;
                        }
                        mComboBox->setCurrentIndex(nIndex);
                    }else{
                        focusNext();
                    }
                }
                break;
        }
        return true;//其他按键事件拦截
    }
    return QWidget::eventFilter(obj,event);
}


void SaveADWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SaveADWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SaveADWidget::closeSlot(){
    this->close();
}

void SaveADWidget::saveSlot(){
    QString nStr = mComboBox->currentText();//获取当前项的文本
    int nTemp = nStr.toInt();//转为数值
    QString nTempStr = mSatData->findTempKeyForValue(nTemp);//查找关键词，如temp1
    int nIndex = nTempStr.mid(4).toInt();
    if(nIndex > 0){
        nStr = QString("AD%1").arg(nIndex);
        mSatData->modifyAdList(nStr,mSatData->getCenterAd());
    }
    this->close();
}

void SaveADWidget::showEvent(QShowEvent *se){
    if(mEnum != mSatData->getGearMode()){
        mEnum = mSatData->getGearMode();
        //创建组合框里的项
        QList<QString> nStrList;
        if(mEnum == SatData::GEARONE){
            nStrList.append("0");
            nStrList.append("30");
            nStrList.append("70");
            nStrList.append("90");
            nStrList.append("100");
            nStrList.append("120");
            nStrList.append("140");
            nStrList.append("160");
            nStrList.append("180");
            nStrList.append("200");
            nStrList.append("250");
            nStrList.append("300");
        }else{
            nStrList.append("0");
            nStrList.append("30");
            nStrList.append("60");
            nStrList.append("180");
            nStrList.append("200");
            nStrList.append("250");
            nStrList.append("300");
            nStrList.append("400");
            nStrList.append("500");
            nStrList.append("600");
            nStrList.append("800");
            nStrList.append("1000");
            nStrList.append("1200");
        }
        mMaxIndex = nStrList.size();
        mComboBox->clear();
        for(int i = 0; i < nStrList.size(); i++){
            mComboBox->addItem(nStrList.at(i));
        }
        mComboBox->setCurrentIndex(0);
    }
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SaveADWidget::paintEvent(QPaintEvent *event){
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





/*============================================================================
 ============================================================================*/
SetGearWidget::SetGearWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(250,200);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    mSatData = SatData::initance();
    mSatTitleBar = new SatTitleBar(tr("SetGear"),this);
    QWidget *nWidget = new QWidget(this);

    QGridLayout *nWidgetLayout = new QGridLayout;
    QLabel *nTempLabel = new QLabel(tr("Range:"),nWidget);
    nWidgetLayout->addWidget(nTempLabel,0,0,1,1);
    mComboBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mComboBox,0,1,1,3);
    mComboBox->installEventFilter(this);
    mList.append(mComboBox);
    mComboBox->addItem(tr("1st -20~250°C"));//第一档
    mComboBox->addItem(tr("2st 200~1000°C"));//第二档
    mMaxIndex = 2;//组合框数量
    mOldGear = mSatData->getGearMode();
    if(mOldGear == SatData::GEARONE){
        mComboBox->setCurrentIndex(0);
    }else{
        mComboBox->setCurrentIndex(1);
    }
    QPushButton *nOkButton = new QPushButton(tr("OK"),nWidget);
    nWidgetLayout->addWidget(nOkButton,1,0,1,2);
    nOkButton->installEventFilter(this);
    mList.append(nOkButton);
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(okSlot()));//OK键连接关闭窗口槽

    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),nWidget);
    nWidgetLayout->addWidget(nCancelButton,1,2,1,2);
    nCancelButton->installEventFilter(this);
    mList.append(nCancelButton);
    connect(nCancelButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽

    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setRowStretch(1,10);
    this->setLayout(nMainLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

bool SetGearWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();//下一焦点
                break;
            case KEY_19:
                focusPrevious();//前一焦点
                break;
            case KEY_25:
                {
                    if(mSatData->getGearMode() != mOldGear){
                        if(mOldGear == SatData::GEARONE){
                            emit operationSignal(Gear_One,NULL);
                        }else if(mOldGear == SatData::GEARTWO){
                            emit operationSignal(Gear_Two,NULL);
                        }
                    }
                    closeSlot();//关闭窗口函数
                    break;
                }
            case KEY_18:
                {
                    if(obj != mComboBox){
                        ((QPushButton*)obj)->click();//非组合框，则产生点击事件
                    }else{
                        okSlot();
                    }
                }
                break;
            case KEY_21:
                {
                    if(obj == mComboBox){//事件对象为组合框，则显示前一个索引
                        int nIndex = mComboBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = mMaxIndex - 1;
                        }
                        mComboBox->setCurrentIndex(nIndex);
                        //切换档位操作
                        if(nIndex == 0){
                            emit operationSignal(Gear_One,NULL);
                        }else if(nIndex == 1){
                            emit operationSignal(Gear_Two,NULL);
                        }
                    }else{
                        focusPrevious();//前一焦点
                    }
                }
                break;
            case KEY_22:
                {
                    if(obj == mComboBox){//事件对象为组合框,显示下一索引
                        int nIndex = mComboBox->currentIndex();
                        nIndex++;
                        if(nIndex >= mMaxIndex){
                            nIndex = 0;
                        }
                        mComboBox->setCurrentIndex(nIndex);
                        //切换档位操作
                        if(nIndex == 0){
                            emit operationSignal(Gear_One,NULL);
                        }else if(nIndex == 1){
                            emit operationSignal(Gear_Two,NULL);
                        }
                    }else{
                        focusNext();//下一焦点
                    }
                }
                break;
            case KEY_23:
            case KEY_26:
                {
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
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
    this->close();//窗口关闭
}

void SetGearWidget::closeSlot(){
    if(mSatData->getGearMode() != mOldGear){
        if(mOldGear == SatData::GEARONE){
            emit operationSignal(Gear_One,NULL);
        }else if(mOldGear == SatData::GEARTWO){
            emit operationSignal(Gear_Two,NULL);
        }
    }
    this->close();
}

void SetGearWidget::showEvent(QShowEvent *se){
    mOldGear = mSatData->getGearMode();
    if(mOldGear == SatData::GEARONE){
        mComboBox->setCurrentIndex(0);
    }else{
        mComboBox->setCurrentIndex(1);
    }
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SetGearWidget::paintEvent(QPaintEvent *event){
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


/*============================================================================
 ============================================================================*/
AskDialog::AskDialog(QString nStr, QWidget *parent) : QDialog(parent){
    //样式加载
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    //样式加载结束
    this->setFixedSize(400,280);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时销毁

    QGridLayout *nWidgetLayout = new QGridLayout;
    QWidget *nWidget = new QWidget(this);
    mSatTitleBar = new SatTitleBar(tr("Warning"),this);
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(reject()));

    QLabel *nPicLabel = new QLabel(nWidget);
    QPixmap nPixmap;
    nPixmap.load(QString("%1%2").arg(IMG_DIR).arg("sigh1.png"));
    nPicLabel->setPixmap(nPixmap);
    nWidgetLayout->addWidget(nPicLabel,0,0,3,1,Qt::AlignCenter);

    //显示文本的标签
    QLabel *nAskLabel = new QLabel(nStr,nWidget);
    nAskLabel->setWordWrap(true);
    nWidgetLayout->addWidget(nAskLabel,0,1,3,2,Qt::AlignCenter);
    //NO按键
    QPushButton *nNoButton = new QPushButton(tr("NO"),nWidget);
    nNoButton->installEventFilter(this);
    nWidgetLayout->addWidget(nNoButton,3,0,1,2);
    mList.append(nNoButton);
    connect(nNoButton,SIGNAL(clicked()),this,SLOT(reject()));
    //YES按键
    QPushButton *nYesButton = new QPushButton(tr("Yes"),nWidget);
    nYesButton->installEventFilter(this);
    nWidgetLayout->addWidget(nYesButton,3,2,1,2);
    mList.append(nYesButton);
    connect(nYesButton,SIGNAL(clicked()),this,SLOT(accept()));
    mIndex = 0;
    mList.at(mIndex)->setFocus();

    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setColumnStretch(0,1);
    nWidgetLayout->setColumnStretch(1,1);
    nWidgetLayout->setColumnStretch(2,1);
    nWidgetLayout->setColumnStretch(3,1);
    nWidgetLayout->setRowStretch(0,10);
    this->setLayout(nMainLayout);
}
bool AskDialog::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_22:
            case KEY_27:
                focusNext();//下一焦点
                break;
            case KEY_21:
            case KEY_26:
                focusPrevious();//前一焦点
                break;
            case KEY_25:
                this->reject();
                break;
            case KEY_18:
            case KEY_16:
                {
                    mList.at(mIndex)->click();
                }
                break;
        }
        return true;
    }
    return QDialog::eventFilter(obj,event);
}

void AskDialog::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void AskDialog::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void AskDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QDialog::paintEvent(event);
}







/*============================================================================
 ============================================================================*/
SetAutoShutterWidget::SetAutoShutterWidget(QWidget *parent) : QWidget(parent)
{
    mSatData = SatData::initance();
    this->setFixedSize(250,240);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    mSatTitleBar = new SatTitleBar(tr("AutoShutter"),this);
    QWidget *nWidget = new QWidget(this);
    QGridLayout *nWidgetLayout = new QGridLayout;
    //自动打档显示标签
    QLabel *nAutoLabel = new QLabel(tr("Auto Shutter:"),nWidget);
    nWidgetLayout->addWidget(nAutoLabel,0,0);
    //自动打档切换按钮
    mAutoBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mAutoBox,0,1);
    mAutoBox->installEventFilter(this);
    mList.append(mAutoBox);
    mAutoBox->addItem(tr("ON"));
    mAutoBox->addItem(tr("OFF"));
    mAutoBoxMaxIndex = 2;//组合框数量
    mOldAutoSign = mSatData->getAutoShutterSign();
    if(mOldAutoSign){
        mAutoBox->setCurrentIndex(0);
    }else{
        mAutoBox->setCurrentIndex(1);
    }
    //时间标签
    QLabel *nTimeLabel = new QLabel(tr("Time(s):"),nWidget);
    nWidgetLayout->addWidget(nTimeLabel,1,0);
    //时间输入
    mTimeEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mTimeEdit,1,1);
    mTimeEdit->installEventFilter(this);
    mOldAutoTime = mSatData->getAutoShutterTime();
    mAutoTime = mOldAutoTime;
    mTimeEdit->setText(QString("%1").arg(mAutoTime));
    mList.append(mTimeEdit);
    //关闭按钮
    QPushButton *nOkButton = new QPushButton(tr("Close"),nWidget);
    nWidgetLayout->addWidget(nOkButton,2,0,1,2);//加入布局
    nOkButton->installEventFilter(this);//注册过滤
    mList.append(nOkButton);//加入焦点列表
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽
    nWidget->setLayout(nWidgetLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();

    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    this->setLayout(nMainLayout);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setRowStretch(2,10);

    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

bool SetAutoShutterWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;

        switch(nKey->key()){
            case KEY_20:
                if(nKey->isAutoRepeat()){//按键持续操作不处理
                    return true;
                }
                focusNext();//下一焦点
                break;
            case KEY_19:
                if(nKey->isAutoRepeat()){//按键持续操作不处理
                    return true;
                }
                focusPrevious();//前一焦点
                break;
            case KEY_23:
            case KEY_26:
                {
                    if(nKey->isAutoRepeat()){//按键持续操作不处理
                        return true;
                    }
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
            case KEY_25:
                {
                    if(nKey->isAutoRepeat()){//按键持续操作不处理
                        return true;
                    }
                    if(mOldAutoSign != mSatData->getAutoShutterSign()){
                        if(mOldAutoSign){
                            emit operationSignal(Auto_Shutter_On,NULL);
                        }else{
                            emit operationSignal(Auto_Shutter_Off,NULL);
                        }
                    }
                    if(mOldAutoTime != mSatData->getAutoShutterTime()){
                        emit operationSignal(Auto_Shutter_Time,QString("Time=%1").arg(mOldAutoTime));
                    }
                    closeSlot();//关闭窗口函数
                    break;
                }
            case KEY_18:
                {
                    if(nKey->isAutoRepeat()){//按键持续操作不处理
                        return true;
                    }
                    if(obj == mAutoBox){
                        this->closeSlot();
                    }else if(obj == mTimeEdit){
                        this->closeSlot();
                    }else{
                        ((QPushButton*)obj)->click();//非组合框，则产生点击事件
                    }
                }
                break;
            case KEY_21:
                {
                    if(obj == mAutoBox){//事件对象为组合框，则显示前一个索引
                        if(nKey->isAutoRepeat()){//按键持续操作不处理
                            return true;
                        }
                        int nIndex = mAutoBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = mAutoBoxMaxIndex - 1;
                        }
                        mAutoBox->setCurrentIndex(nIndex);
                        if(nIndex == 0){
                            emit operationSignal(Auto_Shutter_On,NULL);
                        }else{
                            emit operationSignal(Auto_Shutter_Off,NULL);
                        }
                    }else if(obj == mTimeEdit){
                        mAutoTime--;
                        if(mAutoTime < AUTO_SHUTTER_MIN_TIME){
                            mAutoTime = AUTO_SHUTTER_MIN_TIME;
                        }
                        mTimeEdit->setText(QString("%1").arg(mAutoTime));
                    }else{
                        if(nKey->isAutoRepeat()){//按键持续操作不处理
                            return true;
                        }
                        focusPrevious();//前一焦点
                    }
                }
                break;
            case KEY_22:
                {
                    if(obj == mAutoBox){//事件对象为组合框,显示下一索引
                        if(nKey->isAutoRepeat()){//按键持续操作不处理
                            return true;
                        }
                        int nIndex = mAutoBox->currentIndex();
                        nIndex++;
                        if(nIndex >= mAutoBoxMaxIndex){
                            nIndex = 0;
                        }
                        mAutoBox->setCurrentIndex(nIndex);
                        if(nIndex == 0){
                            emit operationSignal(Auto_Shutter_On,NULL);
                        }else{
                            emit operationSignal(Auto_Shutter_Off,NULL);
                        }
                    }else if(obj == mTimeEdit){
                        mAutoTime++;
                        mTimeEdit->setText(QString("%1").arg(mAutoTime));
                    }else{
                        if(nKey->isAutoRepeat()){//按键持续操作不处理
                            return true;
                        }
                        focusNext();//下一焦点
                    }
                }
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_21:
            case KEY_22:
                {
                    if(obj == mTimeEdit){
                        emit operationSignal(Auto_Shutter_Time,QString("Time=%1").arg(mAutoTime));
                    }
                }
                break;
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetAutoShutterWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetAutoShutterWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetAutoShutterWidget::closeSlot(){
    this->close();//窗口关闭
}

void SetAutoShutterWidget::showEvent(QShowEvent *se){
    mOldAutoSign = mSatData->getAutoShutterSign();
    if(mOldAutoSign){
        mAutoBox->setCurrentIndex(0);
    }else{
        mAutoBox->setCurrentIndex(1);
    }
    mOldAutoTime = mSatData->getAutoShutterTime();
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SetAutoShutterWidget::paintEvent(QPaintEvent *event){
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
















/*============================================================================
 ============================================================================*/
SetSerialNumberWidget::SetSerialNumberWidget(QWidget *parent) : QWidget(parent)
{
    mSatData = SatData::initance();
    this->setFixedSize(250,180);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    mSatTitleBar = new SatTitleBar(tr("SerialNumber"),this);
    QWidget *nWidget = new QWidget(this);


    QGridLayout *nWidgetLayout = new QGridLayout;
    //序列号显示标签
    QLabel *nSerialNumberLabel = new QLabel(tr("Serial Number:"),nWidget);
    nWidgetLayout->addWidget(nSerialNumberLabel,0,0);
    //序列号输入
    mSerialEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mSerialEdit,0,1);
    mSerialEdit->installEventFilter(this);
    mOldSerialNumber = mSatData->getSerialNumber();
    mSerialNumber = mOldSerialNumber;
    mSerialEdit->setText(QString("%1").arg(mSerialNumber));
    mList.append(mSerialEdit);
    //关闭按钮
    QPushButton *nOkButton = new QPushButton(tr("Close"),nWidget);
    nWidgetLayout->addWidget(nOkButton,1,0,1,2);//加入布局
    nOkButton->installEventFilter(this);//注册过滤
    mList.append(nOkButton);//加入焦点列表
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽
    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    this->setLayout(nMainLayout);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setRowStretch(1,10);

    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

bool SetSerialNumberWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();//下一焦点
                break;
            case KEY_19:
                focusPrevious();//前一焦点
                break;
            case KEY_23:
            case KEY_26:
                {
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
            case KEY_25:
                {
                    if(mOldSerialNumber != mSatData->getSerialNumber()){
                        emit operationSignal(Serial_Number,QString("Num=%1").arg(mOldSerialNumber));
                    }
                    closeSlot();//关闭窗口函数
                    break;
                }
            case KEY_18:
                {
                    if(obj == mSerialEdit){
                        QString nStr = QString("%1").arg(mSerialNumber);//获取当前项的数据
                        DigitKeyboard* nDialog = new DigitKeyboard(nStr);//打开十六进制键盘
                        if(nDialog->exec()){
                            if(nStr.isEmpty()){
                                nStr = "0";
                            }
                            mSerialNumber = nStr.toInt();
                            mSerialEdit->setText(QString("%1").arg(mSerialNumber));
                            emit operationSignal(Serial_Number,QString("Num=%1").arg(mSerialNumber));
                        }
                    }else{
                        ((QPushButton*)obj)->click();//产生点击事件
                    }
                }
                break;
            case KEY_21:
                {
                    if(obj == mSerialEdit){
                        mSerialNumber--;
                        if(mSerialNumber < 1){
                            mSerialNumber = 1;
                        }
                        mSerialEdit->setText(QString("%1").arg(mSerialNumber));
                    }else{
                        focusPrevious();//前一焦点
                    }
                }
                break;
            case KEY_22:
                {
                    if(obj == mSerialEdit){
                        mSerialNumber++;
                        mSerialEdit->setText(QString("%1").arg(mSerialNumber));
                    }else{
                        focusNext();//下一焦点
                    }
                }
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_21:
            case KEY_22:
                {
                    if(obj == mSerialEdit){
                        emit operationSignal(Serial_Number,QString("Num=%1").arg(mSerialNumber));
                    }
                }
                break;
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetSerialNumberWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetSerialNumberWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetSerialNumberWidget::closeSlot(){
    this->close();//窗口关闭
}

void SetSerialNumberWidget::showEvent(QShowEvent *se){
    mOldSerialNumber = mSatData->getSerialNumber();
    QWidget::showEvent(se);
}

void SetSerialNumberWidget::paintEvent(QPaintEvent *event){
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



/*============================================================================
 ============================================================================*/
SetDateWidget::SetDateWidget(QWidget *parent) : QWidget(parent)
{
    mSatData = SatData::initance();
    this->setFixedSize(250,480);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    mSatTitleBar = new SatTitleBar(tr("Data"),this);
    QWidget *nWidget = new QWidget(this);

    QGridLayout *nWidgetLayout = new QGridLayout;
    QString nStr;
    int nIndex;
    //年份显示标签
    QLabel *nYearLabel = new QLabel(tr("Year:"),nWidget);
    nWidgetLayout->addWidget(nYearLabel,0,0);
    //年份输入
    mYearBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mYearBox,0,1);
    mYearBox->installEventFilter(this);
    mOldYear = mSatData->getOutFactoryYear();
    mYear = mOldYear;
    mList.append(mYearBox);
    for(int i = 0; i < YEAR_MAX_COUNT; i++){
        nStr = QString("%1").arg(CURRENT_YEAR + i);
        mYearBox->addItem(nStr);
    }
    nStr = QString("%1").arg(mYear);
    nIndex = mYearBox->findText(nStr);
    mYearBox->setCurrentIndex(nIndex);
    //月份显示标签
    QLabel *nMonthLabel = new QLabel(tr("Month:"),nWidget);
    nWidgetLayout->addWidget(nMonthLabel,1,0);
    mMonthBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mMonthBox,1,1);
    mMonthBox->installEventFilter(this);
    mOldMonth = mSatData->getOutFactoryMonth();
    mMonth = mOldMonth;
    mList.append(mMonthBox);
    for(int i = 1; i <= MONTH_MAX_COUNT; i++){
        nStr = QString("%1").arg(i);
        mMonthBox->addItem(nStr);
    }
    nStr = QString("%1").arg(mMonth);
    nIndex = mMonthBox->findText(nStr);
    mMonthBox->setCurrentIndex(nIndex);
    //日期显示标签
    QLabel *nDayLabel = new QLabel(tr("Day:"),nWidget);
    nWidgetLayout->addWidget(nDayLabel,2,0);
    mDayBox = new QComboBox(nWidget);
    nWidgetLayout->addWidget(mDayBox,2,1);
    mDayBox->installEventFilter(this);
    mOldDay = mSatData->getOutFactoryDay();
    mDay = mOldDay;
    mList.append(mDayBox);
    for(int i = 1; i <= DAY_MAX_COUNT; i++){
        nStr = QString("%1").arg(i);
        mDayBox->addItem(nStr);
    }
    nStr = QString("%1").arg(mDay);
    nIndex = mDayBox->findText(nStr);
    mDayBox->setCurrentIndex(nIndex);

    QLabel *nInfoLabel = new QLabel(nWidget);
    nWidgetLayout->addWidget(nInfoLabel,3,0,3,2);
    nStr = QString("XXX:\nXXX:\nXXX:\n");
    nInfoLabel->setText(nStr);






    //关闭按钮
    QPushButton *nOkButton = new QPushButton(tr("OK"),nWidget);
    nWidgetLayout->addWidget(nOkButton,6,0,1,1);//加入布局
    nOkButton->installEventFilter(this);//注册过滤
    mList.append(nOkButton);//加入焦点列表
    connect(nOkButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽

    //关闭按钮
    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),nWidget);
    nWidgetLayout->addWidget(nCancelButton,6,1,1,1);//加入布局
    nCancelButton->installEventFilter(this);//注册过滤
    mList.append(nCancelButton);//加入焦点列表
    connect(nCancelButton,SIGNAL(clicked()),this,SLOT(closeSlot()));//OK键连接关闭窗口槽




    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    nWidgetLayout->setMargin(10);
    nWidgetLayout->setSpacing(10);
    nWidgetLayout->setRowStretch(6,10);
    this->setLayout(nMainLayout);




    mIndex = 0;
    mList.at(mIndex)->setFocus();
    //连接业务操作
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类的业务操作槽
}

bool SetDateWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//按键持续操作不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();//下一焦点
                break;
            case KEY_19:
                focusPrevious();//前一焦点
                break;
            case KEY_23:
            case KEY_26:
                {
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
            case KEY_25:
                {
                    if(mOldYear != mSatData->getOutFactoryYear()){
                        emit operationSignal(Set_Fac_Year,QString("Year=%1").arg(mOldYear));
                    }
                    if(mOldMonth != mSatData->getOutFactoryMonth()){
                        emit operationSignal(Set_Fac_Month,QString("Month=%1").arg(mOldMonth));
                    }
                    if(mOldDay != mSatData->getOutFactoryDay()){
                        emit operationSignal(Set_Fac_Day,QString("Day=%1").arg(mOldDay));
                    }
                    closeSlot();//关闭窗口函数
                    break;
                }
            case KEY_18:
                {
                    if(obj->inherits("QComboBox")){
                        closeSlot();
                    }else{
                        ((QPushButton*)obj)->click();//产生点击事件
                    }
                }
                break;
            case KEY_21:
                {
                    if(obj == mYearBox){
                        int nIndex = mYearBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = YEAR_MAX_COUNT - 1;
                        }
                        mYearBox->setCurrentIndex(nIndex);
                        mYear = mYearBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Year,QString("Year=%1").arg(mYear));
                    }else if(obj == mMonthBox){
                        int nIndex = mMonthBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = MONTH_MAX_COUNT - 1;
                        }
                        mMonthBox->setCurrentIndex(nIndex);
                        mMonth = mMonthBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Month,QString("Month=%1").arg(mMonth));
                    }else if(obj == mDayBox){
                        int nIndex = mDayBox->currentIndex();
                        nIndex--;
                        if(nIndex < 0){
                            nIndex = DAY_MAX_COUNT - 1;
                        }
                        mDayBox->setCurrentIndex(nIndex);
                        mDay = mDayBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Day,QString("Day=%1").arg(mDay));
                    }else{
                        focusPrevious();
                    }
                }
                break;
            case KEY_22:
                {
                    if(obj == mYearBox){
                        int nIndex = mYearBox->currentIndex();
                        nIndex++;
                        if(nIndex > YEAR_MAX_COUNT - 1){
                            nIndex = 0;
                        }
                        mYearBox->setCurrentIndex(nIndex);
                        mYear = mYearBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Year,QString("Year=%1").arg(mYear));
                    }else if(obj == mMonthBox){
                        int nIndex = mMonthBox->currentIndex();
                        nIndex++;
                        if(nIndex > MONTH_MAX_COUNT - 1){
                            nIndex = 0;
                        }
                        mMonthBox->setCurrentIndex(nIndex);
                        mMonth = mMonthBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Month,QString("Month=%1").arg(mMonth));
                    }else if(obj == mDayBox){
                        int nIndex = mDayBox->currentIndex();
                        nIndex++;
                        if(nIndex > DAY_MAX_COUNT - 1){
                            nIndex = 0;
                        }
                        mDayBox->setCurrentIndex(nIndex);
                        mDay = mDayBox->currentText().toInt();
                        emit operationSignal(Set_Fac_Day,QString("Day=%1").arg(mDay));
                    }else{
                        focusNext();
                    }
                }
                break;
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetDateWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetDateWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环焦点
    }
    mList.at(mIndex)->setFocus();
}

void SetDateWidget::closeSlot(){
    this->close();//窗口关闭
}

void SetDateWidget::showEvent(QShowEvent *se){
    mOldYear = mSatData->getOutFactoryYear();
    mOldMonth = mSatData->getOutFactoryMonth();
    mOldDay = mSatData->getOutFactoryDay();
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}
void SetDateWidget::paintEvent(QPaintEvent *event){
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

















SetDisWidget::SetDisWidget(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();//获取数据类
    mDistance = mSatData->getDis();
    this->setFixedSize(250,200);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    mSatTitleBar = new SatTitleBar(tr("Set Distance"),this);
    QWidget *nWidget = new QWidget(this);
    QGridLayout *nWidgetLayout = new QGridLayout;
    int nItemNum = 0;
    //距离显示
    QLabel *nDisLabel = new QLabel(tr("Dis:"),nWidget);
    nWidgetLayout->addWidget(nDisLabel,nItemNum,0,Qt::AlignLeft);
    mDisLineEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mDisLineEdit,nItemNum,1,Qt::AlignLeft);
    mDisLineEdit->installEventFilter(this);
    mDisLineEdit->setText(QString("%1m").arg(QString::number(mDistance, 'f', 1)));
    nItemNum++;
    //关闭按钮
    mCloseButton = new QPushButton(tr("Close"),nWidget);
    nWidgetLayout->addWidget(mCloseButton,nItemNum,0);
    mCloseButton->installEventFilter(this);
    connect(mCloseButton,SIGNAL(clicked()),this,SLOT(closeSlot()));
    //ok按钮
    mOkButton = new QPushButton(tr("Save"),nWidget);
    nWidgetLayout->addWidget(mOkButton,nItemNum,1);
    mOkButton->installEventFilter(this);
    connect(mOkButton,SIGNAL(clicked()),this,SLOT(okSlot()));
    nItemNum++;
    nWidgetLayout->setRowStretch(nItemNum-1,1);
    nItemNum++;
    nWidgetLayout->setMargin(10);//外边距
    nWidgetLayout->setSpacing(10);//组件边距
    nWidgetLayout->setColumnStretch(1,1);
    nWidgetLayout->setColumnStretch(0,1);
    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);

    this->setLayout(nMainLayout);
    //将有焦点的组件放入列表
    mList.append(mDisLineEdit);
    mList.append(mCloseButton);
    mList.append(mOkButton);
    mIndex = 0;//当前焦点索引
    mList.at(mIndex)->setFocus();
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool SetDisWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        switch (nKey->key()){
            case KEY_19:
                {
                    if(!nKey->isAutoRepeat()){//重复的不处理
                        focusPrevious();
                    }
                    break;
                }
            case KEY_20:
                {
                    if(!nKey->isAutoRepeat()){
                        focusNext();
                    }
                    break;
                }
            case KEY_23:
            case KEY_26:
                {
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
            case KEY_25://关闭窗口
                closeSlot();
                break;
            case KEY_21://左按键
                {
                    if(obj == mDisLineEdit){
                        mDistance -= 0.1;
                        if(mDistance < 0){
                            mDistance = 0;
                        }
                        mDisLineEdit->setText(QString("%1m").arg(QString::number(mDistance, 'f', 1)));
                    }else if(obj == mCloseButton || obj == mOkButton){
                        focusPrevious();
                    }
                }
                break;
            case KEY_22://右按键
                {
                    if(obj == mDisLineEdit){
                        mDistance += 0.1;
                        if(mDistance > 12){
                            mDistance = 12;
                        }
                        mDisLineEdit->setText(QString("%1m").arg(QString::number(mDistance, 'f', 1)));
                    }else if(obj == mCloseButton || obj == mOkButton){
                        focusNext();
                    }
                }
                break;
            case KEY_18://中间键
                {
                    if(!nKey->isAutoRepeat()){
                        if(obj == mCloseButton){
                            mCloseButton->click();
                        }else if(obj == mOkButton){
                            mOkButton->click();
                        }else{
                            okSlot();
                        }
                    }
                }
                break;
            default:
                break;
           }
        return true;
    }else if(event->type() == QEvent::KeyRelease){//按键释放事件
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetDisWidget::showEvent(QShowEvent *se){//显示事件，主要是重新显示时，调好窗口焦点
    mDistance = mSatData->getDis();
    mDisLineEdit->setText(QString("%1m").arg(QString::number(mDistance, 'f', 1)));
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SetDisWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SetDisWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SetDisWidget::closeSlot(){//close按键槽，如果窗口设置了关闭时销毁，则需要注销观察字段
    this->hide();
}

void SetDisWidget::okSlot(){//ok按键槽，需要保存档位参数（到文件），如果窗口是关闭销毁，则需要注销观察字段
    emit operationSignal(Set_Dis,QString("Dis=%1").arg(mDistance));
    this->hide();
}


void SetDisWidget::paintEvent(QPaintEvent *event){
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












//===========================================

ShutDownWidget::ShutDownWidget(QWidget *parent) : QWidget(parent){
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

QString ShutDownWidget::getTextString(){
    return mTextString;
}

void ShutDownWidget::setTextString(QString nTextString){
    if(mTextString != nTextString){
        mTextString = nTextString;
        update();
    }
}

void ShutDownWidget::paintEvent(QPaintEvent *event){
    if(!mTextString.isEmpty()){
        QPainter painter(this);
        QPen nPen;
        nPen.setColor(QColor("#3485FB"));
        nPen.setWidth(1);
        painter.setPen(nPen);
        painter.setBrush(QColor("#3485FB"));
        painter.drawRect(0,0,width(),height());

        nPen.setColor(QColor("#FFFFFF"));
        painter.setPen(nPen);
        painter.drawText(0,0,width(),height(),Qt::AlignCenter,mTextString);
    }
    QWidget::paintEvent(event);
}









