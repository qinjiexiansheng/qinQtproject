#include "mainwindow.h"
//add on 2018-04-16
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mSatData = SatData::initance();//获取数据类
    //按键(27号)定时器,用于判断长按或者短按
    mKeyTimer = new QTimer();
    mKeyTimer->setInterval(KEY_LONG_TIME);
    connect(mKeyTimer,SIGNAL(timeout()),this,SLOT(keyLongPress()));
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    //关机按键，判断长按或者短按
    mKeyTimer16 = new QTimer();
    mKeyTimer16->setInterval(ShutDownTime*1000);
    connect(mKeyTimer16,SIGNAL(timeout()),this,SLOT(powerOffSlot()));
    initWindow();//初始化窗口
}


void MainWindow::registerField(){

    QList<QString> nList;//窗口观察数据字段
    nList.append("Battery");//观察电量
    nList.append("AlarmSign");//观察报警标记
    nList.append("PlusSign");//观察+模式标记
    nList.append("LowSign");//观察低灵敏度标记
    nList.append("WindowDisplay");
    nList.append("CenterAd");
    nList.append("Sensor");
    nList.append("Det");
    nList.append("InfoShowSign");
    nList.append("PointInitialAD");
    nList.append("AreaIndicatorSign");
    nList.append("SchemaIndex");
    nList.append("Int");
    nList.append("AutoInt");
    nList.append("TipsString");
    nList.append("PointSign");
    nList.append("MaxPointX");
    nList.append("MaxPointY");
    nList.append("MinPointX");
    nList.append("MinPointY");
    nList.append("VideoSign");
    //nList.append("MaxTemp");
    //nList.append("MinTemp");
    nList.append("Dis");
    nList.append("Emiss");
    nList.append("EnvTemp");
    nList.append("RelHum");

    nList.append("TurnOffSign");
    nList.append("LengthUnit");
    nList.append("TempUnit");

    mSatData->attach(this,nList);//注册观察者及字段
}




void MainWindow::keyToEvent(int nKey, bool press, bool repeat){
    QWidget *nWidget = QApplication::focusWidget();
    if(nWidget != NULL){
        QKeyEvent *nKeyEvent = new QKeyEvent(press ? QKeyEvent::KeyPress : QKeyEvent::KeyRelease,
                                             nKey, Qt::NoModifier, "", repeat);
        QApplication::postEvent(nWidget,nKeyEvent);
#if 0
        QKeyEvent nKeyEvent(press ? QKeyEvent::KeyPress : QKeyEvent::KeyRelease,
                            nKey, Qt::NoModifier, "", repeat);
        QApplication::sendEvent(QApplication::focusWidget(),&nKeyEvent);
#endif
    }
}

void MainWindow::doUpdate(QString nUpStr){//观察的字段发生变化
    emit doUpdateSignal(nUpStr);
}

void MainWindow::doUpdateSlot(QString nUpStr){
    if(nUpStr == "Battery"){//电量的字段发生变化
        showBattery();
    }else if(nUpStr == "AlarmSign"){//报警标记发生变化
        showWarning();
    }else if(nUpStr == "PlusSign"){//+模式标记发生变化
        showPlus();
    }else if(nUpStr == "LowSign"){//低灵敏标记发生变化
        showLow();
    }else if(nUpStr == "WindowDisplay"){
        showBattery();
        showWarning();
        showPlus();
        showLow();
        showText();
        showCenterItem();
        showCorrectItem();
        if(mSatData->getWindowDisplay() == SatData::CALBADPOINT){//切换到校坏点模式
            mSolidBar->hide();//隐藏伪彩条
            mCollectData1Item->hide();//隐藏采集数据框1
            mCollectData2Item->hide();//隐藏采集数据框2
            if(mTabWidget != NULL){
                mTabWidget->hide();//隐藏标定窗口
            }
            mBadPointCalItem->show();
            mBadPointCalItem->setFocus();//校坏点项设置焦点
            mSchemaItem->hide();
        }else if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
            mBadPointCalItem->hide();
            mSolidBar->show();
            mCollectData1Item->show();
            mCollectData2Item->show();
            mSchemaItem->show();
        }else{//正常模式
            mSolidBar->show();
            mCollectData1Item->hide();
            mCollectData2Item->hide();
            mBadPointCalItem->hide();
            mSchemaItem->show();
        }
    }else if(nUpStr == "CenterAd" || nUpStr == "Sensor" || nUpStr == "Det" ||
             nUpStr == "PointInitialAD" || nUpStr == "Int" || nUpStr == "AutoInt"){
        int nInt;
        if(mSatData->getAutoIntSign()){
            nInt = mSatData->getAutoInt();
        }else{
            nInt = mSatData->getInt();
        }
        QString nTextStr = QString("AD:%1\nT:%2\nDet:%3\nAD(ini):%4\nInt:%5")
                .arg(mSatData->getCenterAd(),4,16,QLatin1Char('0'))
                .arg(mSatData->getSensor())
                .arg(mSatData->getDet(),4,16,QLatin1Char('0'))
                .arg(mSatData->getPointInitialAD(),4,16,QLatin1Char('0'))
                .arg(nInt);
        mTextItem->setPlainText(nTextStr);
    }else if(nUpStr == "InfoShowSign"){
        showText();
    }else if(nUpStr == "AreaIndicatorSign"){
        showCenterItem();
    }else if(nUpStr == "SchemaIndex"){
        //暂时留着,因为模式改变导致主界面中的模式图标改变，已经由图标项监听
    }else if(nUpStr == "TipsString"){
        if(!mSatData->getTipsString().isEmpty()){
            mTipsItem->setPlainText(mSatData->getTipsString());
            mTipsItem->show();
            mTipsTimer->start();
        }
    }else if(nUpStr == "PointSign" || nUpStr == "MaxPointX" || nUpStr == "MaxPointY" || nUpStr == "MinPointX" || nUpStr == "MinPointY"){
        showPole();
    }else if(nUpStr == "VideoSign"){
        showVideo();
    }else if(nUpStr == "MaxTemp" || nUpStr == "MinTemp"){

    }else if(nUpStr == "Dis" || nUpStr == "LengthUnit"){
        if(mSatData->getLengthUnit()){//单位：米
            QString nItemStr = QString("D:%1m").arg(QString::number(mSatData->getDis(),'f',1));
            mDisTextItem->setPlainText(nItemStr);
        }else{//单位：英尺
            float nDis = mSatData->getDis();
            nDis = nDis/0.3048;
            QString nItemStr = QString("D:%1ft").arg(QString::number(nDis,'f',1));
            mDisTextItem->setPlainText(nItemStr);
        }
    }else if(nUpStr == "TurnOffSign"){
        if(mSatData->getTurnOffSign()){
            if(mShutDownWidget == NULL){
                mShutDownWidget = new ShutDownWidget(this);
                mShutDownWidget->setGeometry(0,0,640,480);
                mShutDownWidget->setTextString(tr("Shutting Down!"));
            }
            mShutDownWidget->show();
        }
    }else if(nUpStr == "Emiss"){
        QString nItemStr = QString("E:%1").arg(QString::number(mSatData->getEmiss(),'f',1));
        mEmissTextItem->setPlainText(nItemStr);
    }else if(nUpStr == "EnvTemp" || nUpStr == "TempUnit"){
        if(mSatData->getTempUnit()){
            QString nItemStr = QString("T:%1°C").arg(QString::number(mSatData->getEnvTemp(),'f',1));
            mEnvTmpTextItem->setPlainText(nItemStr);
        }else{
            float nEnvTemp = mSatData->getEnvTemp();
            nEnvTemp = nEnvTemp*1.8 + 32;
            QString nItemStr = QString("T:%1°F").arg(QString::number(nEnvTemp,'f',1));
            mEnvTmpTextItem->setPlainText(nItemStr);
        }
    }else if(nUpStr == "RelHum"){
        int nRelHum = mSatData->getRelHum()*100;
        QString nItemStr = QString("H:%1%").arg(nRelHum);
        mRelHumTextItem->setPlainText(nItemStr);
    }
}


void MainWindow::alarmFlashSlot(){//报警闪烁
    if(mWarningItem->isVisible()){//如果报警图标在显示状态，则隐藏
        mWarningItem->hide();
    }else{//反之，则显示报警图标
        mWarningItem->show();
    }
}

void MainWindow::batFlashSlot(){//低电量闪烁，在0格电和1格电中切换
    if(mBatteryItem[BATTERY_ZERO]->isVisible()){//如果0格电的图标显示，则隐藏并显示1格电的图标
        mBatteryItem[BATTERY_ZERO]->hide();
        mBatteryItem[BATTERY_ONE]->show();
    }else{//反之同理
        mBatteryItem[BATTERY_ONE]->hide();
        mBatteryItem[BATTERY_ZERO]->show();
    }
}

void MainWindow::tipsHideSlot(){
    if(mTipsTimer->isActive()){
        mTipsTimer->stop();
    }
    mTipsItem->hide();
}


void MainWindow::powerOffSlot(){
    if(mPowerSignal){
        mPowerSignal = false;
    }
    if(mKeyTimer16->isActive()){
        mKeyTimer16->stop();
    }
    QString nStr = tr("Does it shut down?");
    AskDialog *nDialog = new AskDialog(nStr,this);
    nDialog->move((640-nDialog->width())/2,(480-nDialog->height())/2);
    if(nDialog->exec()){
        emit operationSignal(ShutDown,NULL);
    }
}



void MainWindow::keyPressEvent(QKeyEvent *ke){
    if(ke->key() == KEY_16 && !ke->isAutoRepeat()){ //16号按键
        //在Release事件里做操作，原因：16号作关机键
        mPowerSignal = true;
        if(!mKeyTimer16->isActive()){
            mKeyTimer16->start();
        }
    }else if(ke->key() == KEY_26 && !ke->isAutoRepeat()){ //26号按键
        int nOpeStr = mSatData->getCurrentSchema()->doLeftShort();
        operationSelf(nOpeStr);//调用操作过滤方法
    }else if(ke->key() == KEY_27 && !ke->isAutoRepeat()){ //27号按键
        if(!mKeyTimer->isActive()){//如果定时器没有开启
            mKeyTimer->start(KEY_LONG_TIME);//开启按键定时器
        }
//        if(mPictureBrowingWidget == NULL){
//            mPictureBrowingWidget = new PictureBrowingWidget(QString(PICTURE_DIR),this);
//        }
//        mPictureBrowingWidget->show();
//        if(mPictureViewWidget == NULL){
//            mPictureViewWidget = new PictureViewWidget(QString("%1%2").arg(PICTURE_DIR).arg("ir.jpg"),this);
//        }
//        mPictureViewWidget->show();
    }else if(ke->key() == KEY_18){//18号按键，标定窗口显示
        if(mTabWidget == NULL){
            mTabWidget = new TabDialog(this);
        }
        mTabWidget->show();
    }else if(ke->key() == KEY_24){
        if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
            if(mCollectData1Item->hasFocus()){
                mCollectData1Item->clearFocus();
                mCollectData2Item->setFocus();
            }else{
                mCollectData2Item->clearFocus();
                mCollectData1Item->setFocus();
            }
        }
    }else if(ke->key() == KEY_23){
        emit operationSignal(Manual_Play,NULL);
    }else if(ke->key() == KEY_25){
        if(mSatData->getWindowDisplay() != SatData::NORMAL){
            //mSatData->setWindowDisplay(SatData::NORMAL);
            emit operationSignal(Set_Window_Normal,NULL);
        }
    }else if(ke->key() == Qt::Key_O){
//        if(mSystemWidget == NULL){
//            mSystemWidget = new SystemWidget(this);
//        }
//        mSystemWidget->show();
    }else if(ke->key() == Qt::Key_I){
//        if(mPictureBrowingWidget == NULL){
//            mPictureBrowingWidget = new PictureBrowingWidget(QString(PICTURE_DIR),this);
//        }
//        mPictureBrowingWidget->show();
    }



    QMainWindow::keyPressEvent(ke);
}

void MainWindow::keyReleaseEvent(QKeyEvent *ke){
    if(ke->key() == KEY_16 && !ke->isAutoRepeat()){//16号按键释放
        //===============
        //显示模式选择窗口
        //===============
        //qDebug("[D]Lin >> Schema select widget open!");
        //mSchemaWidget->show();
        if(mPowerSignal){
            mPowerSignal = false;
            if(mKeyTimer16->isActive()){
                mKeyTimer16->stop();
                mMainSmallWidget->show();
            }
        }
    }else if(ke->key() == KEY_27){ //27号按键释放
        if(mKeyTimer->isActive()){ //如果定时器还在运行,则做模式的右短按操作
            mKeyTimer->stop();//停止定时器
            int nOpeStr = mSatData->getCurrentSchema()->doRightShort();
            operationSelf(nOpeStr);//过滤操作
        }
    }
    QMainWindow::keyReleaseEvent(ke);
}



void MainWindow::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            //重新设置窗口字符串
            break;
        default:
            break;
    }
}




void MainWindow::keyLongPress(){//按键长按槽
    mKeyTimer->stop();//停止，防止定时器重复触发
    int nOpeStr = mSatData->getCurrentSchema()->doRightLong();
    operationSelf(nOpeStr);
}

void MainWindow::operationSelf(int nOpeStr){//过滤操作方法
    if(nOpeStr == No_Operation){//NULL的不处理
        return ;
    }else if(nOpeStr == Open_Correct_Widget){//打开修正窗口操作
//        if(mSystemWidget == NULL){
//            mSystemWidget = new SystemWidget(this);
//        }
//        mSystemWidget->show();
    }else{
        emit operationSignal(nOpeStr,NULL);
    }
}


void MainWindow::initWindow(){//初始化窗口
    QGraphicsView* nView = new QGraphicsView(); //创建视图
    this->setCentralWidget(nView);//设置视图为中心窗口
    QGraphicsScene* nScene = new QGraphicsScene();//创建场景
    nView->setScene(nScene);//设置场景
    nView->setSceneRect(0,0,640,480); //视图大小
    nView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //关闭垂直滑条
    nView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //关闭水平滑条
    this->setStyleSheet("padding:0px;border:0px");//设置主窗口为无边框
    this->setGeometry(0,0,640,480);//设置主窗口的大小
    //this->setWindowFlags(Qt::FramelessWindowHint);
    nView->setBackgroundBrush(QBrush(QColor(32,176,80)));//设置背景色32,176,80,255
    int x,y,margin = 20; //离边界像素点
    QPixmap nPixmap;
    QString nPixStr;
    //设置plus指示项
    nPixStr = QString("%1plus.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    mPlusItem = nScene->addPixmap(nPixmap);
    mPlusItem->setPos(margin,height()-margin-nPixmap.height());
    showPlus();//根据窗口模式和标记来决定隐藏
    //设置报警指示项
    nPixStr = QString("%1alarm.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    mWarningItem = nScene->addPixmap(nPixmap);
    x = (width()-nPixmap.width())/2;
    y = margin;
    mWarningItem->setPos(x,y);
    mWarningItem->hide();//默认关闭
    //报警闪烁定时器
    mAlarmFlashTimer = new QTimer();
    mAlarmFlashTimer->setInterval(ALARM_FLASH_TIME);
    connect(mAlarmFlashTimer,SIGNAL(timeout()),this,SLOT(alarmFlashSlot()));
    showWarning();
    //设置取景框指示框cursor_0.png
    nPixStr = QString("%1cursor_0.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    nPixmap = nPixmap.scaled(50,50);
    x = (width()-nPixmap.width())/2;
    y = (height()-nPixmap.height())/2;
    mSpotCenterItem = nScene->addPixmap(nPixmap);
    mSpotCenterItem->setPos(x,y);

    nPixStr = QString("%1mid1-2px.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    x = (width()-nPixmap.width())/2;
    y = (height()-nPixmap.height())/2;
    mAreaCenterItem = nScene->addPixmap(nPixmap);
    mAreaCenterItem->setPos(x,y);
    showCenterItem();
    //中心框旁显示信息
    QFont nFont;
    nFont.setPointSize(16); //字体大小
    mTextItem = new QGraphicsTextItem();
    nScene->addItem(mTextItem);
    int nInt;
    if(mSatData->getAutoIntSign()){
        nInt = mSatData->getAutoInt();
    }else{
        nInt = mSatData->getInt();
    }
    QString nTextStr = QString("AD:%1\nT:%2\nDet:%3\nAD(ini):%4\nInt:%5")
            .arg(mSatData->getCenterAd(),4,16,QLatin1Char('0'))
            .arg(QString::number(mSatData->getSensor()),'f',2)
            .arg(mSatData->getDet(),4,16,QLatin1Char('0'))
            .arg(mSatData->getPointInitialAD(),4,16,QLatin1Char('0'))
            .arg(nInt);
    mTextItem->setFont(nFont);
    mTextItem->setPlainText(nTextStr);
    mTextItem->setDefaultTextColor(QColor(255,255,255));
    mTextItem->setPos(x+nPixmap.width(),y+nPixmap.height());
    if(!mSatData->getInfoShowSign()){
        mTextItem->hide();
    }
    //设置电量指示项(全部加载并隐藏)
    for(int i = 1 ; i <= 5 ; i++){
        nPixStr = QString("%1battery0%2.png").arg(IMG_DIR).arg(i);
        nPixmap.load(nPixStr);
        mBatteryItem[i-1] = nScene->addPixmap(nPixmap);
        x = (width()-nPixmap.width())/2-5;//计算x坐标
        y = height()-nPixmap.height()-margin;//计算y坐标
        mBatteryItem[i-1]->setPos(x,y);
        mBatteryItem[i-1]->hide();
    }
    //充电图标
    nPixStr = QString("%1charge.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    mBatteryItem[5] = nScene->addPixmap(nPixmap);
    x = (width()-nPixmap.width())/2-5;//计算x坐标
    y = height()-nPixmap.height()-margin;//计算y坐标
    mBatteryItem[5]->setPos(x,y);
    mBatteryItem[5]->hide();
    //电源闪烁定时器
    mBatFlashTimer = new QTimer();
    mBatFlashTimer->setInterval(BAT_FLASH_TIME);
    connect(mBatFlashTimer,SIGNAL(timeout()),this,SLOT(batFlashSlot()));
    showBattery();
    //设置温度指示项
    mSolidBar = new SolidBar(this);
    nScene->addItem(mSolidBar);
    x = width()-mSolidBar->width()-margin;//计算x坐标
    y = height()-mSolidBar->height()-margin;//计算y坐标
    mSolidBar->setPos(x,y);
    mSolidBar->registerField();
    //设置低灵敏度指示项
    nPixStr = QString("%1low.png").arg(IMG_DIR);
    nPixmap.load(nPixStr);
    mLowItem = nScene->addPixmap(nPixmap);
    mLowItem->setPos(margin,margin);
    if(!mSatData->getLowSign()){
        mLowItem->hide();
    }
    //校坏点指示项
    mBadPointCalItem = new BadPointCalItem(this);
    nScene->addItem(mBadPointCalItem);
    x = mSatData->getCalBadPointItemX();
    y = mSatData->getCalBadPointItemY();
    mBadPointCalItem->setItemPos(x,y);
    //mBadPointCalItem->setPos(x,y);
    mBadPointCalItem->hide();
    mBadPointCalItem->registerField();
    //采集数据指示项1
    mCollectData1Item = new CollectDataItem(1,this);
    nScene->addItem(mCollectData1Item);
    x = mSatData->getCollectDataItemX1();
    y = mSatData->getCollectDataItemY1();
    mCollectData1Item->setItemPos(x,y);
    //mCollectData1Item->setPos(x,y);
    mCollectData1Item->hide();
    mCollectData1Item->registerField();
    //采集数据指示项2
    mCollectData2Item = new CollectDataItem(2,this);
    nScene->addItem(mCollectData2Item);
    x = mSatData->getCollectDataItemX2();
    y = mSatData->getCollectDataItemY2();
    mCollectData2Item->setItemPos(x,y);
    //mCollectData2Item->setPos(x,y);
    mCollectData2Item->hide();
    mCollectData2Item->registerField();
//    mTabWidget = new TabDialog(this);//创建标定窗口
//    mTabWidget->hide();
    mTabWidget = NULL;
//    mSchemaWidget = new SatSchemaWidget(this);
//    x = this->pos().x() + (width() - mSchemaWidget->width())/2;
//    y = this->pos().y() + height() - mSchemaWidget->height() - 5;
//    mSchemaWidget->move(x,y);
//    mSchemaWidget->hide();


    QString nItemStr;
    nFont.setPointSize(16);
    x = 110;
    y = height() - 50;
    mDisTextItem = new QGraphicsTextItem();
    nScene->addItem(mDisTextItem);
    if(mSatData->getLengthUnit()){
        nItemStr = QString("D:%1m").arg(QString::number(mSatData->getDis(),'f',1));
    }else{
        float nDis = mSatData->getDis();
        nDis = nDis/0.3048;
        nItemStr = QString("D:%1ft").arg(QString::number(nDis,'f',1));
    }
    mDisTextItem->setFont(nFont);
    mDisTextItem->setPlainText(nItemStr);
    mDisTextItem->setDefaultTextColor(QColor(255,255,255));
    mDisTextItem->setPos(x,y);

    x += 90;
    mEmissTextItem = new QGraphicsTextItem();
    nScene->addItem(mEmissTextItem);
    nItemStr = QString("E:%1").arg(QString::number(mSatData->getEmiss(),'f',1));
    mEmissTextItem->setFont(nFont);
    mEmissTextItem->setPlainText(nItemStr);
    mEmissTextItem->setDefaultTextColor(QColor(255,255,255));
    mEmissTextItem->setPos(x,y);

    x = 380;
    mEnvTmpTextItem = new QGraphicsTextItem();
    nScene->addItem(mEnvTmpTextItem);
    if(mSatData->getTempUnit()){
        nItemStr = QString("T:%1°C").arg(QString::number(mSatData->getEnvTemp(),'f',1));
    }else{
        float nEnvTemp = mSatData->getEnvTemp();
        nEnvTemp = nEnvTemp*1.8 + 32;
        nItemStr = QString("T:%1°F").arg(QString::number(nEnvTemp,'f',1));
    }
    mEnvTmpTextItem->setFont(nFont);
    mEnvTmpTextItem->setPlainText(nItemStr);
    mEnvTmpTextItem->setDefaultTextColor(QColor(255,255,255));
    mEnvTmpTextItem->setPos(x,y);

    x += 80;
    mRelHumTextItem = new QGraphicsTextItem();
    nScene->addItem(mRelHumTextItem);
    int nRelHum = mSatData->getRelHum()*100;
    nItemStr = QString("H:%1%").arg(nRelHum);
    mRelHumTextItem->setFont(nFont);
    mRelHumTextItem->setPlainText(nItemStr);
    mRelHumTextItem->setDefaultTextColor(QColor(255,255,255));
    mRelHumTextItem->setPos(x,y);

    showCorrectItem();


    mSchemaItem = new SchemaItem(mPlusItem->boundingRect().width(),mPlusItem->boundingRect().height());
    mSchemaItem->registerField();
    nScene->addItem(mSchemaItem);
    x = mPlusItem->pos().x() + 10 + mPlusItem->boundingRect().width();
    y = mPlusItem->pos().y();
    mSchemaItem->setPos(x,y);

    mMainSmallWidget = new SatMainSmallWidget(this);
    mMainSmallWidget->move(0,85);
    mMainSmallWidget->hide();
    //操作提示项
    mTipsItem = new QGraphicsTextItem();
    nScene->addItem(mTipsItem);
    mTipsItem->setFont(nFont);
    mTipsItem->setDefaultTextColor(QColor(255,255,255));
    x = mPlusItem->pos().x();
    y = mPlusItem->pos().y() - 30;
    mTipsItem->setPos(x,y);
    mTipsItem->hide();
    //提示隐藏定时器
    mTipsTimer = new QTimer();
    mTipsTimer->setInterval(Tips_Hide_Time);
    connect(mTipsTimer,SIGNAL(timeout()),this,SLOT(tipsHideSlot()));

    mVideoItem = new SatPhotoItem(250,60,this);
    mVideoItem->setPhotoWidth(50);
    mVideoItem->setPhotoHeight(30);
    mVideoItem->setTextString(tr("Video is filming!"));
    mVideoItem->setPhotoFilename(QString("%1%2").arg(IMG_DIR).arg("video_rec.png"));
    mVideoItem->setTextShowSign(true);
    nScene->addItem(mVideoItem);
    x = (width()-mVideoItem->getWidth())/2;
    y = 5;
    mVideoItem->setPos(x,y);
    showVideo();
    //极点
    mMaxPoleItem = new SatPoleItem(SatPoleItem::MaxPole,this);
    nScene->addItem(mMaxPoleItem);
    mMinPoleItem = new SatPoleItem(SatPoleItem::MinPole,this);
    nScene->addItem(mMinPoleItem);



    mMaxTempItem = new QGraphicsTextItem();
    nScene->addItem(mMaxTempItem);
    QString nMaxTempString = QString("%1°C").arg(QString::number(mSatData->getMaxTemp(),'f',1));
    nFont.setPointSize(16);
    mMaxTempItem->setFont(nFont);
    mMaxTempItem->setPlainText(nMaxTempString);
    mMaxTempItem->setDefaultTextColor(QColor(255,0,0));
    x = this->width() - 120;
    y = 10;
    mMaxTempItem->setPos(x,y);


    mMinTempItem = new QGraphicsTextItem();
    nScene->addItem(mMinTempItem);
    QString nMinTempString = QString("%1°C").arg(QString::number(mSatData->getMinTemp(),'f',1));
    nFont.setPointSize(16);
    mMinTempItem->setFont(nFont);
    mMinTempItem->setPlainText(nMinTempString);
    mMinTempItem->setDefaultTextColor(QColor(52,133,251));
    x = this->width() - 120;
    y = 30;
    mMinTempItem->setPos(x,y);

    showPole();


    mShutDownWidget = NULL;

}

void MainWindow::showVideo(){
    if(mSatData->getVideoSign()){
        mVideoItem->show();
    }else{
        mVideoItem->hide();
    }
}


void MainWindow::showPole(){
    if(mSatData->getPointSign()){
        mMaxPoleItem->setPos(mSatData->getMaxPointX(),mSatData->getMaxPointY());
        mMinPoleItem->setPos(mSatData->getMinPointX(),mSatData->getMinPointY());
        mMaxPoleItem->show();
        mMinPoleItem->show();
        float nMaxTemp = mSatData->getMaxTemp();
        //qDebug("[D]Lin >> MaxTemp:%f",nMaxTemp);
        QString nMaxTempString = QString("%1°C").arg(QString::number(nMaxTemp,'f',1));
        mMaxTempItem->setPlainText(nMaxTempString);



        float nMinTemp = mSatData->getMinTemp();
        //qDebug("[D]Lin >> MinTemp:%f",nMinTemp);
        QString nMinTempString = QString("%1°C").arg(QString::number(nMinTemp,'f',1));
        mMinTempItem->setPlainText(nMinTempString);

        mMaxTempItem->show();
        mMinTempItem->show();
    }else{
        mMaxPoleItem->hide();
        mMinPoleItem->hide();
        mMaxTempItem->hide();
        mMinTempItem->hide();
    }
}



void MainWindow::showLow(){
    if(mSatData->getWindowDisplay() != SatData::CALBADPOINT){
        if(mSatData->getLowSign()){
            mLowItem->show();
        }else{
            mLowItem->hide();
        }
    }
}

void MainWindow::showPlus(){//+模式项的显示
    if(mSatData->getWindowDisplay() != SatData::CALBADPOINT){//非校坏点模式
        if(mSatData->getPlusSign()){//获取数据类的+模式标记，为真则项显示
            mPlusItem->show();
        }else{
            mPlusItem->hide();
        }
    }else{//如果是校坏点模式，则隐藏
        mPlusItem->hide();
    }
}

void MainWindow::showWarning(){//报警项的显示与隐藏
    if(mSatData->getWindowDisplay() != SatData::CALBADPOINT){//非校坏点模式
        bool nSign = mSatData->getAlarmSign();
        if(nSign && !mAlarmFlashTimer->isActive()){//如果标记为真，并且报警闪烁定时器没有在工作状态
            mAlarmFlashTimer->start();
        }else if(!nSign){//如果标记为假
            if(mAlarmFlashTimer->isActive()){//如果定时器处于工作状态，则停止
                mAlarmFlashTimer->stop();
            }
            mWarningItem->hide();//报警图标隐藏
        }
    }else{//校坏点模式
        if(mAlarmFlashTimer->isActive()){//如果定时器处于工作状态，则停止
            mAlarmFlashTimer->stop();
        }
        mWarningItem->hide();//报警图标隐藏
    }
}

void MainWindow::showBattery(){//电量显示与隐藏
    if(mSatData->getWindowDisplay() != SatData::CALBADPOINT){//如果窗口显示模式不为校坏点模式时，显示电量项
        if(mSatData->getBatteryState()){
            mBatFlashTimer->stop();
            for(int i = 0; i < 6; i++){
                mBatteryItem[i]->hide();//先全部隐藏
            }
            mBatteryItem[5]->show();
        }else{
            int nBat = mapBattery(mSatData->getBattery());//映射电量
            if(nBat == BATTERY_ZERO && !mBatFlashTimer->isActive()){//如果电量为低电量枚举，并且低电量闪烁定时器没有在工作，则开启
                for(int i = 0; i < 6; i++){
                    mBatteryItem[i]->hide();//先全部隐藏
                }
                mBatteryItem[nBat]->show();//低电量的图标显示
                mBatFlashTimer->start();//定时器开启
            }else if(nBat != BATTERY_ZERO){//如果电量非低电量
                if(mBatFlashTimer->isActive()){//定时器活动则关闭
                    mBatFlashTimer->stop();
                }
                for(int i = 0; i < 6; i++){
                    mBatteryItem[i]->hide();//全部电量项隐藏
                }
                mBatteryItem[nBat]->show();//显示电量项
            }
        }
    }else{//校坏点模式
        mBatFlashTimer->stop();
        for(int i = 0; i < 6; i++){
            mBatteryItem[i]->hide();//先全部隐藏
        }
    }
}

void MainWindow::showText(){//显示中心框的文本
    if(mSatData->getWindowDisplay() == SatData::NORMAL){//正常模式，则根据标记来决定显示或隐藏
        if(mSatData->getInfoShowSign()){//根据标记
            mTextItem->show();
        }else{
            mTextItem->hide();
        }
    }else{//非正常模式，隐藏文本项
        mTextItem->hide();
    }
}


void MainWindow::showCenterItem(){
    if(mSatData->getWindowDisplay() == SatData::NORMAL){
        if(mSatData->getAreaIndicatorSign()){
            mAreaCenterItem->show();
            mSpotCenterItem->hide();
        }else{
            mAreaCenterItem->hide();
            mSpotCenterItem->show();
        }
    }else{
        mAreaCenterItem->hide();
        mSpotCenterItem->hide();
    }
}


void MainWindow::showCorrectItem(){
    if(mSatData->getWindowDisplay() == SatData::CALBADPOINT){
        mDisTextItem->hide();
        mEmissTextItem->hide();
        mEnvTmpTextItem->hide();
        mRelHumTextItem->hide();
    }else{
        mDisTextItem->show();
        mEmissTextItem->show();
        mEnvTmpTextItem->show();
        mRelHumTextItem->show();
    }
}





int MainWindow::mapBattery(float nBattery){//电量映射
    if(nBattery >= BATTERY_FOUR_MIN){//如果电量大于等于4格电的最低值，则返回4格电
        return BATTERY_FOUR;
    }else if(nBattery >= BATTERY_THREE_MIN){
        return BATTERY_THREE;
    }else if(nBattery >= BATTERY_TWO_MIN){
        return BATTERY_TWO;
    }else if(nBattery >= BATTERY_ONE_MIN){
        return BATTERY_ONE;
    }else{
        return BATTERY_ZERO;
    }
}

