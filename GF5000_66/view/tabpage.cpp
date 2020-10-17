#include "tabpage.h"
/*======================================

  标签页1 ： TabPageOne
  包含非均匀校正相关操作

  ======================================*/
TabPageOne::TabPageOne(QWidget *parent) : QWidget(parent){
    //加载样式
//    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
//    QFile nQss(nQssStr);
//    nQss.open(QFile::ReadOnly);
//    this->setStyleSheet(nQss.readAll());
//    nQss.close();
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    //this->setFixedSize(200,480);//窗口大小
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按钮排布，如果布局变化，则showEvent（）里也可能需要变化
    //开启、关闭非均匀校正按钮（用于加载不同的K值表）
    SatButton *nAdjustOpenButton = new SatButton(tr("Adjust"),SatButton::TextSwitchButton,this);
    nAdjustOpenButton->setOnPath(tr("On"));
    nAdjustOpenButton->setOffPath(tr("Off"));
    if(mSatData->getAdjustOpenSign()){
        nAdjustOpenButton->setOnState(true);
    }else{
        nAdjustOpenButton->setOffPath(false);
    }
    nAdjustOpenButton->installEventFilter(this);
    nLayout->addWidget(nAdjustOpenButton);
    nSignalMapper->setMapping(nAdjustOpenButton,"Adjust");
    connect(nAdjustOpenButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAdjustOpenButton);
    //清除当前档位的非均匀校正K值表
    SatButton *nClearAdjustButton = new SatButton(tr("Clear"),SatButton::ArrowButton,this);
    nClearAdjustButton->installEventFilter(this);
    nLayout->addWidget(nClearAdjustButton);
    nSignalMapper->setMapping(nClearAdjustButton,"Clear");
    connect(nClearAdjustButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nClearAdjustButton);
    //开启低温非均匀校正
    SatButton *nLowTempAdjustButton = new SatButton(tr("Low Temp Adjust"),SatButton::ArrowButton,this);
    nLowTempAdjustButton->installEventFilter(this);
    nLayout->addWidget(nLowTempAdjustButton);
    nSignalMapper->setMapping(nLowTempAdjustButton,"LowTempAdjust");
    connect(nLowTempAdjustButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLowTempAdjustButton);
    //开启高温非均匀校正
    SatButton *nHighTempAdjustButton = new SatButton(tr("High Temp Adjust"),SatButton::ArrowButton,this);
    nHighTempAdjustButton->installEventFilter(this);
    nLayout->addWidget(nHighTempAdjustButton);
    nSignalMapper->setMapping(nHighTempAdjustButton,"HighTempAdjust");
    connect(nHighTempAdjustButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nHighTempAdjustButton);
    //保存K值表
    SatButton *nSaveKTableButton = new SatButton(tr("Save K Table"),SatButton::ArrowButton,this);
    nSaveKTableButton->installEventFilter(this);
    nLayout->addWidget(nSaveKTableButton);
    nSignalMapper->setMapping(nSaveKTableButton,"SaveKTable");
    connect(nSaveKTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSaveKTableButton);
    //校坏点按钮
    SatButton *nCalBadPointButton = new SatButton(tr("Cal Bad Point"),SatButton::ArrowButton,this);
    nCalBadPointButton->installEventFilter(this);
    nLayout->addWidget(nCalBadPointButton);
    nSignalMapper->setMapping(nCalBadPointButton,"CalBadPoint");
    connect(nCalBadPointButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCalBadPointButton);
    //设置布局等
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}
bool TabPageOne::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){//重复按钮不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();//20号按键切换到下一拥有焦点的按钮
                return true;//返回真
                break;
            case KEY_19:
                focusPrevious();//切换上一按键
                return true;
                break;
            case KEY_18:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }
    return QWidget::eventFilter(obj,event);
}

void TabPageOne::showEvent(QShowEvent *se){//显示事件
    QWidget::showEvent(se);
    if(mSatData->getAdjustOpenSign()){//根据当前参数来初始化
        mList.at(0)->setOnState(true);
    }else{
        mList.at(0)->setOnState(false);
    }
    mList.at(mIndex)->setFocus();
}

void TabPageOne::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageOne::focusPrevious(){//上一焦点
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageOne::handleContent(const QString &nStr){
    if(nStr == "Adjust"){
        if(mSatData->getAdjustOpenSign()){//如果校正标记为真，则设为假
            emit operationSignal(Adjust_Off,NULL);
            //mList.at(0)->setOnState(true);
        }else{
            emit operationSignal(Adjust_On,NULL);
            //mList.at(0)->setOnState(false);
        }
        mIndex = 0;
    }else if(nStr == "Clear"){//清除K值文件表
        QString nStr;
        if(mSatData->getGearMode() == SatData::GEARONE){
            nStr = QString("The file(%1%2) will be cleared.Are you sure?")
                    .arg(COF_DIR).arg(QString(K_FILE).arg(1));
        }else{
            nStr = QString("The file(%1%2) will be cleared.Are you sure?")
                    .arg(COF_DIR).arg(QString(K_FILE).arg(2));
        }
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Clear_KTable,NULL);//发送清除K值表操作
        }
        mIndex = 1;
    }else if(nStr == "LowTempAdjust"){
        QString nStr;
        nStr = "The low temperature adjust will begin.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Adjust_LowTemp,NULL);//发送低温校正操作
        }
        mIndex = 2;
    }else if(nStr == "HighTempAdjust"){
        QString nStr;
        nStr = "The high temperature adjust will begin.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Adjust_HighTemp,NULL);
        }
        mIndex = 3;
    }else if(nStr == "SaveKTable"){
        QString nStr;
        nStr = "The K value table will be saved.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Save_KTable,NULL);
        }
        mIndex = 4;
    }else if(nStr == "CalBadPoint"){
        QString nStr;
        nStr = "The bad point adjust will begin.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Set_Window_BadPoint,NULL);
        }
        mIndex = 5;
    }
}

/*======================================

  标签页2 ： TabPageTwo
  包含与标定相关的操作

  ======================================*/
TabPageTwo::TabPageTwo(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //自动打档设置按钮
    SatButton *nAutoShutterButton = new SatButton(tr("Auto Shutter"),SatButton::TextArrowButton,this);
    nAutoShutterButton->setOnPath("On");
    nAutoShutterButton->installEventFilter(this);
    nLayout->addWidget(nAutoShutterButton);
    nSignalMapper->setMapping(nAutoShutterButton,"AutoShutter");
    connect(nAutoShutterButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAutoShutterButton);
    //内、外参考切换按键
    SatButton *nReferenceButton = new SatButton(tr("Shutter"),SatButton::TextSwitchButton,this);
    nReferenceButton->setOnPath(tr("Out"));
    nReferenceButton->setOffPath(tr("In"));
    if(mSatData->getReference() == SatData::OUTSIDE){
        nReferenceButton->setOnState(true);
    }else{
        nReferenceButton->setOnState(false);
    }
    nReferenceButton->installEventFilter(this);
    nLayout->addWidget(nReferenceButton);
    nSignalMapper->setMapping(nReferenceButton,"Reference");
    connect(nReferenceButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nReferenceButton);
    //窗口信息显示（Sensor温度，AD等）
    SatButton *nIndicatorButton = new SatButton(tr("Indicator"),SatButton::TextSwitchButton,this);
    nIndicatorButton->setOnPath(tr("Area"));
    nIndicatorButton->setOffPath(tr("Spot"));
    nIndicatorButton->setOnState(mSatData->getAreaIndicatorSign());
    nIndicatorButton->installEventFilter(this);
    nLayout->addWidget(nIndicatorButton);
    nSignalMapper->setMapping(nIndicatorButton,"Indicator");
    connect(nIndicatorButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nIndicatorButton);
    //窗口信息显示（Sensor温度，AD等）
    SatButton *nShowInfoButton = new SatButton(tr("Info"),SatButton::TextSwitchButton,this);
    nShowInfoButton->setOnPath(tr("Show"));
    nShowInfoButton->setOffPath(tr("Hide"));
    nShowInfoButton->setOnState(mSatData->getInfoShowSign());
    nShowInfoButton->installEventFilter(this);
    nLayout->addWidget(nShowInfoButton);
    nSignalMapper->setMapping(nShowInfoButton,"Info");
    connect(nShowInfoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nShowInfoButton);
    //设置档位按钮
    SatButton *nSetRangeButton = new SatButton(tr("Set Range"),SatButton::TextArrowButton,this);
    nSetRangeButton->setOnPath(tr("one"));
    nSetRangeButton->installEventFilter(this);
    nLayout->addWidget(nSetRangeButton);
    nSignalMapper->setMapping(nSetRangeButton,"Range");
    connect(nSetRangeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSetRangeButton);
    //设置参数按钮
    SatButton *nSetParamButton = new SatButton(tr("Set Param"),SatButton::ArrowButton,this);
    nSetParamButton->installEventFilter(this);
    nLayout->addWidget(nSetParamButton);
    nSignalMapper->setMapping(nSetParamButton,"Param");
    connect(nSetParamButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSetParamButton);
    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    //设置参数窗口
    mSetParamWidget = new SetParamWidget(this);
    mSetParamWidget->move(0,0);
    mSetParamWidget->registerField();
    //设置档位窗口
    mSetGearWidget = new SetGearWidget(this);
    mSetGearWidget->move(100,70);
    //自动打档设置窗口
    mSetAutoShutterWidget = new SetAutoShutterWidget(this);
    mSetAutoShutterWidget->move(100,150);
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool TabPageTwo::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();
                return true;
                break;
            case KEY_19:
                focusPrevious();
                return true;
                break;
            case KEY_18:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);
}

void TabPageTwo::showEvent(QShowEvent *se){//显示事件
    QWidget::showEvent(se);
    if(mSatData->getReference() == SatData::OUTSIDE){
        mList.at(1)->setOnState(true);
    }else{
        mList.at(1)->setOnState(false);
    }
    mList.at(2)->setOnState(mSatData->getAreaIndicatorSign());
    mList.at(3)->setOnState(mSatData->getInfoShowSign());
    mList.at(mIndex)->setFocus();
}

void TabPageTwo::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageTwo::focusPrevious(){//上一焦点
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}


void TabPageTwo::handleContent(const QString &nStr){
    if(nStr == "Reference"){
        if(mSatData->getReference() == SatData::OUTSIDE){
            emit operationSignal(Shutter_Inside,NULL);
        }else{
            emit operationSignal(Shutter_Outside,NULL);
        }
    }else if(nStr == "Info"){
        if(mSatData->getInfoShowSign()){
            emit operationSignal(Center_Info_Hide,NULL);
        }else{
            emit operationSignal(Center_Info_Show,NULL);
        }
    }else if(nStr == "Range"){
        mSetGearWidget->show();
    }else if(nStr == "Param"){
        //设置参数
        mSetParamWidget->show();
    }else if(nStr == "AutoShutter"){
        //自动打档设置
        mSetAutoShutterWidget->show();
        mList.at(mIndex)->setFocus();
    }else if(nStr == "Indicator"){
        if(mSatData->getAreaIndicatorSign()){
            emit operationSignal(Area_Indicator_Off,NULL);
        }else{
            emit operationSignal(Area_Indicator_On,NULL);
        }
    }
}

/*======================================

  标签页3 ： TabPageThree
  其他的一些操作

  ======================================*/
TabPageThree::TabPageThree(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //保存AD值按钮
    SatButton *nSaveADButton = new SatButton(tr("Save AD"),SatButton::ArrowButton,this);
    nSaveADButton->installEventFilter(this);
    nLayout->addWidget(nSaveADButton);
    nSignalMapper->setMapping(nSaveADButton,"SaveAD");
    connect(nSaveADButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSaveADButton);
    //更新温度AD表按钮（将当前暂时的AD表替换永久的AD表）
    SatButton *nUpdateTableButton = new SatButton(tr("Update Table"),SatButton::ArrowButton,this);
    nUpdateTableButton->installEventFilter(this);
    nLayout->addWidget(nUpdateTableButton);
    nSignalMapper->setMapping(nUpdateTableButton,"UpdateTable");
    connect(nUpdateTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nUpdateTableButton);
    //重新加载温度AD表（将重新加载一次永久AD表，并保存为临时AD表，主要是为了在不用切换档位也可以加载表）
    SatButton *nReloadTableButton = new SatButton(tr("Take Effect Table"),SatButton::ArrowButton,this);
    nReloadTableButton->installEventFilter(this);
    nLayout->addWidget(nReloadTableButton);
    nSignalMapper->setMapping(nReloadTableButton,"TakeEffectTable");
    connect(nReloadTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nReloadTableButton);
    //修改温度AD表
    SatButton *nModifyTableButton = new SatButton(tr("Modify Table"),SatButton::ArrowButton,this);
    nModifyTableButton->installEventFilter(this);
    nLayout->addWidget(nModifyTableButton);
    nSignalMapper->setMapping(nModifyTableButton,"ModifyTable");
    connect(nModifyTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nModifyTableButton);
    //显示温度AD表
    SatButton *nShowTableButton = new SatButton(tr("Show Table"),SatButton::ArrowButton,this);
    nShowTableButton->installEventFilter(this);
    nLayout->addWidget(nShowTableButton);
    nSignalMapper->setMapping(nShowTableButton,"ShowTable");
    connect(nShowTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nShowTableButton);
    //布局调整
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    //保存AD窗口
    mSaveAdWidget = new SaveADWidget(this);
    mSaveAdWidget->move(40,140);
    mSaveAdWidget->registerField();
    //修改标定表窗口
    mModifyAdWidget = new ModifyAdTableWidget(this);
    mModifyAdWidget->move(0,0);
    //显示标定表窗口
    mShowAdWidget = new ShowAdTableWidget(this);
    mShowAdWidget->move(0,0);
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool TabPageThree::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();
                return true;
                break;
            case KEY_19:
                focusPrevious();
                return true;
                break;
            case KEY_18:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
    }//这里不能返回真，因为上层需要左右按键事件来切换标签页
    return QWidget::eventFilter(obj,event);
}

void TabPageThree::showEvent(QShowEvent *se){//显示事件
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void TabPageThree::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageThree::focusPrevious(){//上一焦点
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageThree::handleContent(const QString &nStr){
    if(nStr == "TakeEffectTable"){
        //重新加载温度AD表
        QString nStr;
        if(mSatData->getGearMode() == SatData::GEARONE){
            nStr = QString("The file(%1%2) will take effect.Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
        }else{
            nStr = QString("The file(%1%2) will take effect.Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(2));
        }
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Effect_TempAd_Table,NULL);
        }
    }else if(nStr == "ModifyTable"){
        mModifyAdWidget->show();
    }else if(nStr == "ShowTable"){
        mShowAdWidget->show();
    }else if(nStr == "SaveAD"){
        mSaveAdWidget->show();
    }else if(nStr == "UpdateTable"){
        QString nStr;
        if(mSatData->getGearMode() == SatData::GEARONE){
            nStr = QString("The file(%1%2) will replace the file(%3%4).Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(1))
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
        }else{
            nStr = QString("The file(%1%2) will replace the file(%3%4).Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(2))
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(2));
        }
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Update_TempAd_Table,NULL);
        }
    }
}



/*======================================

  标签页3 ： TabPageFour
  其他的一些操作

  ======================================*/
TabPageFour::TabPageFour(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //显示采集数据框
    SatButton *nCollectDataButton = new SatButton(tr("Box"),SatButton::TextSwitchButton,this);
    nCollectDataButton->setOnPath(tr("Show"));
    nCollectDataButton->setOffPath(tr("Hide"));
    if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
        nCollectDataButton->setOnState(true);
    }else{
        nCollectDataButton->setOnState(false);
    }
    nCollectDataButton->installEventFilter(this);
    nLayout->addWidget(nCollectDataButton);
    nSignalMapper->setMapping(nCollectDataButton,"CollectData");
    connect(nCollectDataButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCollectDataButton);
    //显示采集数据框
    SatButton *nLaserButton = new SatButton(tr("Laser"),SatButton::TextSwitchButton,this);
    nLaserButton->setOnPath(tr("On"));
    nLaserButton->setOffPath(tr("Off"));
    nLaserButton->setOnState(mSatData->getLaserSign());
    nLaserButton->installEventFilter(this);
    nLayout->addWidget(nLaserButton);
    nSignalMapper->setMapping(nLaserButton,"Laser");
    connect(nLaserButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLaserButton);
    //设置机器序列号按钮
    SatButton *nSerialNumberButton = new SatButton(tr("Serial Number"),SatButton::TextArrowButton,this);
    nSerialNumberButton->setOnPath(QString(mSatData->getSerialNumber()));
    nSerialNumberButton->installEventFilter(this);
    nLayout->addWidget(nSerialNumberButton);
    nSignalMapper->setMapping(nSerialNumberButton,"SerialNumber");
    connect(nSerialNumberButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSerialNumberButton);
    //设置出厂日期按钮
    SatButton *nSetFactoryDateButton = new SatButton(tr("Set Factory Date"),SatButton::TextArrowButton,this);
    nSetFactoryDateButton->installEventFilter(this);
    nLayout->addWidget(nSetFactoryDateButton);
    nSignalMapper->setMapping(nSetFactoryDateButton,"Date");
    connect(nSetFactoryDateButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSetFactoryDateButton);
    //备份文件
    SatButton *nTableToSDButton = new SatButton(tr("Table To SD"),SatButton::ArrowButton,this);
    nTableToSDButton->installEventFilter(this);
    nLayout->addWidget(nTableToSDButton);
    nSignalMapper->setMapping(nTableToSDButton,"TableToSD");
    connect(nTableToSDButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nTableToSDButton);
    //恢复文件
    SatButton *nSDToTableButton = new SatButton(tr("SDToTable"),SatButton::ArrowButton,this);
    nSDToTableButton->installEventFilter(this);
    nLayout->addWidget(nSDToTableButton);
    nSignalMapper->setMapping(nSDToTableButton,"SDToTable");
    connect(nSDToTableButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSDToTableButton);
    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    //设置序列号窗口
    mSetSerialWidget = new SetSerialNumberWidget(this);
    mSetSerialWidget->move(100,230);
    //设置日期窗口
    mSetDateWidget = new SetDateWidget(this);
    mSetDateWidget->move(0,0);
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool TabPageFour::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();
                return true;
                break;
            case KEY_19:
                focusPrevious();
                return true;
                break;
            case KEY_18:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
    }//这里不能返回真，因为上层需要左右按键事件来切换标签页
    return QWidget::eventFilter(obj,event);
}

void TabPageFour::showEvent(QShowEvent *se){//显示事件
    QWidget::showEvent(se);
    if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
        mList.at(0)->setOnState(true);
    }else{
        mList.at(0)->setOnState(false);
    }
    mList.at(1)->setOnState(mSatData->getLaserSign());
    mList.at(mIndex)->setFocus();
}

void TabPageFour::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFour::focusPrevious(){//上一焦点
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFour::handleContent(const QString &nStr){
    if(nStr == "CollectData"){
        if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
            emit operationSignal(Set_Window_Normal,NULL);
        }else{
            emit operationSignal(Set_Window_Collect,NULL);
        }
    }else if(nStr == "SerialNumber"){
        //设置机器序列号
        mSetSerialWidget->show();
        mList.at(mIndex)->setFocus();
    }else if(nStr == "Date"){
        //设置出厂日期
        mSetDateWidget->show();
        mList.at(mIndex)->setFocus();
    }else if(nStr == "TableToSD"){
        QString nStr;
        nStr = "This will be backed up to the SD card.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(Table_To_SD,NULL);
        }
        mList.at(mIndex)->setFocus();
    }else if(nStr == "SDToTable"){
        QString nStr;
        nStr = "This will restore the file from the SD card.Are you sure?";
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            emit operationSignal(SD_To_Table,NULL);
        }
        mList.at(mIndex)->setFocus();
    }else if(nStr == "Laser"){
        if(mSatData->getLaserSign()){
            emit operationSignal(Laser_Off,NULL);
        }else{
            emit operationSignal(Laser_On,NULL);
        }
    }
}


/*======================================

  标签页5 ： TabPageFive
  其他的一些操作

  ======================================*/
TabPageFive::TabPageFive(QWidget *parent) : QWidget(parent){
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //自动调节Int开关按钮
    SatButton *nAutoIntButton = new SatButton(tr("AutoInt"),SatButton::TextSwitchButton,this);
    nAutoIntButton->setOnPath(tr("On"));
    nAutoIntButton->setOffPath(tr("Off"));
    if(mSatData->getAutoIntSign()){
        nAutoIntButton->setOnState(true);
    }else{
        nAutoIntButton->setOnState(false);
    }
    nAutoIntButton->installEventFilter(this);
    nLayout->addWidget(nAutoIntButton);
    nSignalMapper->setMapping(nAutoIntButton,"AutoInt");
    connect(nAutoIntButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nAutoIntButton);
    //
    SatButton *nRecordArgButton = new SatButton(tr("RecordArg"),SatButton::TextSwitchButton,this);
    nRecordArgButton->setOnPath(tr("On"));
    nRecordArgButton->setOffPath(tr("Off"));
    if(mSatData->getRecordArgSign()){
        nRecordArgButton->setOnState(true);
    }else{
        nRecordArgButton->setOnState(false);
    }
    nRecordArgButton->installEventFilter(this);
    nLayout->addWidget(nRecordArgButton);
    nSignalMapper->setMapping(nRecordArgButton,"RecordArg");
    connect(nRecordArgButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRecordArgButton);
    //
    SatButton *nDistanceButton = new SatButton(tr("Distance"),SatButton::ArrowButton,this);
    nDistanceButton->installEventFilter(this);
    nLayout->addWidget(nDistanceButton);
    nSignalMapper->setMapping(nDistanceButton,"Distance");
    connect(nDistanceButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDistanceButton);



    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类


    mSetDisWidget = NULL;

}

bool TabPageFive::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_20:
                focusNext();
                return true;
                break;
            case KEY_19:
                focusPrevious();
                return true;
                break;
            case KEY_18:
                {
                    mList.at(mIndex)->click();
                }
                return true;
                break;
        }
    }//这里不能返回真，因为上层需要左右按键事件来切换标签页
    return QWidget::eventFilter(obj,event);
}

void TabPageFive::showEvent(QShowEvent *se){//显示事件
    QWidget::showEvent(se);
    if(mSatData->getAutoIntSign()){
        mList.at(0)->setOnState(true);
    }else{
        mList.at(0)->setOnState(false);
    }
    mList.at(1)->setOnState(mSatData->getRecordArgSign());
    mList.at(mIndex)->setFocus();
}

void TabPageFive::focusNext(){//下一焦点
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFive::focusPrevious(){//上一焦点
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFive::handleContent(const QString &nStr){
    if(nStr == "AutoInt"){
        if(mIndex != 0){
            mIndex = 0;
        }
        if(mSatData->getAutoIntSign()){
            emit operationSignal(AutoInt_Off,NULL);
        }else{
            emit operationSignal(AutoInt_On,NULL);
        }
    }else if(nStr == "RecordArg"){
        if(mIndex != 1){
            mIndex = 1;
        }
        if(mSatData->getRecordArgSign()){
            emit operationSignal(Set_RecordArg_Off,NULL);
        }else{
            emit operationSignal(Set_RecordArg_On,NULL);
        }
    }else if(nStr == "Distance"){
        if(mIndex != 2){
            mIndex = 2;
        }
        if(mSetDisWidget == NULL){
            mSetDisWidget = new SetDisWidget(this);
        }
        mSetDisWidget->move(100,250);
        mSetDisWidget->show();
    }
}






