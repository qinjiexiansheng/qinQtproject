#include "satcontrol.h"

SatControl::SatControl(QObject *parent) :QObject(parent){
    mSatData = SatData::initance();

    mSatData->addSchema(new BasicSchema(this));//基本模式
    mSatData->addSchema(new GearSchema(this));//档位选择模式
    mSatData->addSchema(new DisplaySchema(this));//显示模式
    mSatData->addSchema(new InfraredSchema(this));//红外选择模式
    mSatData->addSchema(new DenoiseSchema(this));//降噪选择模式
    //mSatData->addSchema(new ImageFreeSchema(this));//图像冻结模式
    //mSatData->addSchema(new CorrectSchema(this));//修正模式
    mSatData->setCurrentSchemaIndex(0);
    init();
}

void SatControl::setTranslator(QTranslator *nTranslator){
    mTranslator = nTranslator;
}

void SatControl::changeLanguage(QString nLanguage){
    if(mSatData->getLanguage() == nLanguage){
        return;
    }else{
        if(nLanguage == "English"){
            mTranslator->load(QString("en.qm"));
        }else if(nLanguage == "Chinese"){
            mTranslator->load(QString("ch.qm"));
        }
    }
}


void SatControl::init(){
    //业务创建
    mCameraOpe = new Camera(this);
    mTempADOpe = new TempADOperation(this);
    mKFileOpe = new KFileOperation(this);
    mDataOpe = new DataOperation(this);
    mDenoiseOpe = new DenoiseMode(this);
    mInfraredOpe = new InfraredMode(this);
    mOtherOpe = new OtherBus(this);
    mAdjustOpe = new AdjustParam(this);
    mGearOpe = new GearMode(this);
    //读取参数文件
    mDataOpe->obtainPreferences();
    mSatData->getTemp()->setDistance(mSatData->getDis());
    mSatData->getTemp()->setEmiss(mSatData->getEmiss());
    mSatData->getTemp()->setEnvTemp(mSatData->getEnvTemp());
    mSatData->getTemp()->setRefTemp(mSatData->getRefTemp());
    mSatData->getTemp()->setRelHum(mSatData->getRelHum());
    mSatData->getTemp()->setCorTemp(mSatData->getCorTemp());
    //根据档位加载一次文件或者参数
    if(mSatData->getGearMode() == SatData::GEARONE){
        mGearOpe->gearOne();
    }else{
        mGearOpe->gearTwo();
    }
    mOtherOpe->loadModelData();
    QString nLogStr = FileOpe::numberFile(LOG_DIR,LOG_FILE);
    mSatData->setLogFile(nLogStr);
    mKFileOpe->queryKFile();
    //每次程序启动时打开文件写入一段话
    QString nTestStr = FileOpe::numberFile(LOG_DIR,DATA_FILE);
    mSatData->setTestFile(nTestStr);
    QFile nFile(nTestStr);
    if(!nFile.open(QIODevice::ReadOnly)){//如果文件打不开，即文件不存在，则新建一个并加入一行
        nFile.open(QIODevice::ReadWrite);
        QTextStream out(&nFile);
        out<<"-----[Date and Time,Fid,Gsk,Gain,Int,Det,Sensor,AD1,AD2,AD14]-----\n";
        nFile.close();
    }else{//文件可以打开，则加入一行分割
        nFile.close();
        nFile.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&nFile);
        out<<"=====================================================\n";
        nFile.close();
    }
    //
    QString nNTestStr = FileOpe::numberFile(LOG_DIR,DATA_FILE_TWO);
    mSatData->setNTestFile(nNTestStr);
    QFile nNFile(nNTestStr);
    if(!nNFile.open(QIODevice::ReadOnly)){//如果文件打不开，即文件不存在，则新建一个并加入一行
        nNFile.open(QIODevice::ReadWrite);
        QTextStream out(&nNFile);
        out<<"-----[Date and Time,Fid,Gsk,Gain,Int,Det,Sensor,AD1,AD2,AD14,ADCenter,ADTemp]-----\n";
        nNFile.close();
    }else{//文件可以打开，则加入一行分割
        nNFile.close();
        nNFile.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream out(&nNFile);
        out<<"=============================================================\n";
        nNFile.close();
    }

    //做一次数据刷新
    mDataOpe->dataRefresh();
    if(mSatData->getAutoIntSign()){
        mAdjustOpe->adjustAutoInt();
    }
    //qDebug("[D]Lin >> SatControl End");
    //更新定时器启动
    mDUTimer = new QTimer(this);
    mDUTimer->setInterval(UPDATA_TIME);
    connect(mDUTimer,SIGNAL(timeout()),this,SLOT(doDataUpdate()));//连接信号槽，更新时间到了做一次数据刷新
    mDUTimer->start();
    //自动打档定时器
    mAMTimer = new QTimer(this);
    mAMTimer->setInterval(mSatData->getAutoShutterTime()*1000);
    connect(mAMTimer,SIGNAL(timeout()),this,SLOT(doAutoManual()));//定时打档
    if(mSatData->getAutoShutterSign()){
        mAMTimer->start();
    }
    //自动保存图片定时器
    mASTimer = new QTimer(this);
    mASTimer->setInterval(mSatData->getAutoSavePictureTime()*1000);
    connect(mASTimer,SIGNAL(timeout()),this,SLOT(doAutoSavePhoto()));
    if(mSatData->getAutoSavePictureSign()){
        mASTimer->start();
    }
}

SatControl* SatControl::_SatControl = NULL;
SatControl* SatControl::initance(){//使用饱汉式单例模式，非线程安全
    if(_SatControl == NULL){
        _SatControl = new SatControl();
    }
    return _SatControl;
}



//定时拍照
void SatControl::doAutoSavePhoto(){
    mCameraOpe->photograph();
}


void SatControl::doDataUpdate(){//数据刷新槽
    if(!mSatData->getFrozenSign()){
        mDataOpe->dataRefresh();//数据刷新
    }
    //qDebug("[D]Lin >> SatControl End");
}

void SatControl::doAutoManual(){//自动打档槽
    if(mSatData->getAutoShutterSign() == true){//如果标记为真，才自动打档
        if(mSatData->getAutoIntSign()){
            mAdjustOpe->adjustAutoInt();
        }
        mDataOpe->manualPlay();
#if 1
        QDateTime nCurrentTime = QDateTime::currentDateTime();//获取当前时间
        QString nDate = nCurrentTime.toString("yyyy-MM-dd");
        QString nTime = nCurrentTime.toString("hh:mm:ss");//格式化时分秒
        int nFid        = mSatData->getFid();
        int nGsk        = mSatData->getGsk();
        int nGain       = mSatData->getGain();
        int nInt;
        if(mSatData->getAutoIntSign()){
            nInt = mSatData->getAutoInt();
        }else{
            nInt = mSatData->getInt();
        }
        int nDet        = mSatData->getDet();
        float nSensor  = mSatData->getSensor();
        int nAD1      = mSatData->getCollectDataItemAD1();
        int nAD2     = mSatData->getCollectDataItemAD2();
        int nAD14 = mSatData->getGlobalAD();
        int nADCenter = mSatData->getCenterAd();
        float nTemp = mSatData->getCenterTemp();
        QString nStr = "%1-%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13\n";
        nStr =  nStr.arg(nDate)
                .arg(nTime)
                .arg(nFid)
                .arg(nGsk)
                .arg(nGain)
                .arg(nInt)
                .arg(nDet,4,16,QLatin1Char('0'))
                .arg(QString::number(nSensor,'f',2))
                .arg(nAD1,4,16,QLatin1Char('0'))
                .arg(nAD2,4,16,QLatin1Char('0'))
                .arg(nAD14,4,16,QLatin1Char('0'))
                .arg(nADCenter,4,16,QLatin1Char('0'))
                .arg(QString::number(nTemp,'f',1));
        qDebug("[D] >> %s",nStr.toStdString().c_str());
#endif
        if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){
            mDataOpe->saveTestData();
        }
        if(mSatData->getRecordArgSign()){
            mDataOpe->saveTestData2();
        }
    }
}



void SatControl::doService(int nOpeStr, QString nParStr){//业务处理槽
    if(nParStr.isEmpty()){
        nParStr = "";
    }
    qDebug("[D]Lin >> The Operation ID is:%d--%s",nOpeStr,nParStr.toStdString().c_str());
    if(0){
        return ;
    }
    if(nOpeStr == No_Operation){
        return;
    }else if(nOpeStr == Set_Schema){
        int nSchema = nParStr.split('=').at(1).toInt();
        mSatData->setCurrentSchemaIndex(nSchema);
    }else if(nOpeStr == Gear_One){
        mSatData->setGearMode(SatData::GEARONE);
        mGearOpe->gearOne();
    }else if(nOpeStr == Gear_Two){
        mSatData->setGearMode(SatData::GEARTWO);
        mGearOpe->gearTwo();
    }else if(nOpeStr == Video_Start){
        mCameraOpe->videoStart();
        mSatData->setVideoSign(true);
    }else if(nOpeStr == Video_Stop){
        mCameraOpe->videoStop();
        mSatData->setVideoSign(false);
    }else if(nOpeStr == Manual_Play){
        if(mSatData->getAutoIntSign()){
            mAdjustOpe->adjustAutoInt();
        }
        mDataOpe->manualPlay();
    }else if(nOpeStr == Photo_Graph){
        mCameraOpe->photograph();
    }else if(nOpeStr == Set_Plus_True){
        mSatData->setPlusSign(true);
    }else if(nOpeStr == Set_Plus_False){
        mSatData->setPlusSign(false);
    }else if(nOpeStr == Denoise_Not){
        mDenoiseOpe->denoiseNot();
        mSatData->setDenoiseMode(SatData::NOTDENOISE);
    }else if(nOpeStr == Denoise_One){
        mDenoiseOpe->denoiseOne();
        mSatData->setDenoiseMode(SatData::DENOISEONE);
    }else if(nOpeStr == Global_Info_Hide){
        mSatData->setInfoSign(false);
    }else if(nOpeStr == Global_Info_Show){
        mSatData->setInfoSign(true);
    }else if(nOpeStr == Global_Point_Hide){
        mSatData->setPointSign(false);
    }else if(nOpeStr == Global_Point_Show){
        mSatData->setPointSign(true);
    }else if(nOpeStr == Image_Thaw){
        mCameraOpe->imageThaw();
        mSatData->setFrozenSign(false);
    }else if(nOpeStr == Image_Free){
        mCameraOpe->imageFreeze();
        mSatData->setFrozenSign(true);
    }else if(nOpeStr == Infrared_Iron){
        mInfraredOpe->iron();
        mSatData->setInfraredMode(SatData::IRON);
    }else if(nOpeStr == Infrared_Ironinv){
        mInfraredOpe->ironInv();
        mSatData->setInfraredMode(SatData::IRONINV);
    }else if(nOpeStr == Infrared_Rainbow){
        mInfraredOpe->rainBow();
        mSatData->setInfraredMode(SatData::RAINBOW);
    }else if(nOpeStr == Infrared_Feather){
        mInfraredOpe->feather();
        mSatData->setInfraredMode(SatData::FEATHER);
    }else if(nOpeStr == Infrared_Greyinv){
        mInfraredOpe->greyInv();
        mSatData->setInfraredMode(SatData::GREYINV);
    }else if(nOpeStr == Infrared_Grey){
        mInfraredOpe->grey();
        mSatData->setInfraredMode(SatData::GREY);
    }else if(nOpeStr == Save_Model_Data){
        mOtherOpe->saveModelData();
    }else if(nOpeStr == Set_Fid){
        int nFid = nParStr.split('=').at(1).toInt();
        mSatData->setFid(nFid);
        mAdjustOpe->adjustFID();
    }else if(nOpeStr == Set_Gsk){
        int nGsk = nParStr.split('=').at(1).toInt();
        mSatData->setGsk(nGsk);
        mAdjustOpe->adjustGSK();
    }else if(nOpeStr == Set_Gain){
        int nGain = nParStr.split('=').at(1).toInt();
        mSatData->setGain(nGain);
        mAdjustOpe->adjustGAIN();
    }else if(nOpeStr == Set_Int){
        int nInt = nParStr.split('=').at(1).toInt();
        mSatData->setInt(nInt);
        mAdjustOpe->adjustINT();
    }else if(nOpeStr == Save_Arg){
        mDataOpe->saveArg();
    }else if(nOpeStr == Auto_Shutter_On){
        mSatData->setAutoShutterSign(true);
        if(mAMTimer != NULL && !mAMTimer->isActive()){
            mAMTimer->start();
        }
    }else if(nOpeStr == Auto_Shutter_Off){
        mSatData->setAutoShutterSign(false);
        mAMTimer->stop();
    }else if(nOpeStr == Auto_Shutter_Time){
        int nTime = nParStr.split('=').at(1).toInt();
        mSatData->setAutoShutterTime(nTime);
        mAMTimer->setInterval(nTime*1000);
    }else if(nOpeStr == Serial_Number){
        int nNum = nParStr.split('=').at(1).toInt();
        mSatData->setSerialNumber(nNum);
    }else if(nOpeStr == Set_Fac_Year){
        int nYear = nParStr.split('=').at(1).toInt();
        mSatData->setOutFactoryYear(nYear);
    }else if(nOpeStr == Set_Fac_Month){
        int nMonth = nParStr.split('=').at(1).toInt();
        mSatData->setOutFactoryMonth(nMonth);
    }else if(nOpeStr == Set_Fac_Day){
        int nDay = nParStr.split('=').at(1).toInt();
        mSatData->setOutFactoryDay(nDay);
    }else if(nOpeStr == BadPoint_Query){
        mKFileOpe->queryKFile();
    }else if(nOpeStr == BadPoint_SetPos){
        QStringList nList = nParStr.split(';');
        int nX = nList.at(0).split('=').at(1).toInt();
        int nY = nList.at(1).split('=').at(1).toInt();
        mSatData->setCalBadPointItemX(nX);
        mSatData->setCalBadPointItemY(nY);
        mKFileOpe->queryKFile();
    }else if(nOpeStr == BadPoint_Cal){
        mKFileOpe->modifyKFile();
    }else if(nOpeStr == Save_KTable){
        mKFileOpe->saveKFile();
    }else if(nOpeStr == Set_Window_Normal){
        mSatData->setWindowDisplay(SatData::NORMAL);
    }else if(nOpeStr == Set_Window_BadPoint){
        mSatData->setWindowDisplay(SatData::CALBADPOINT);
    }else if(nOpeStr == Set_Window_Collect){
        mSatData->setWindowDisplay(SatData::COLLECTDATA);
    }else if(nOpeStr == Collect1_SetPos){
        QStringList nList = nParStr.split(';');
        int nX = nList.at(0).split('=').at(1).toInt();
        int nY = nList.at(1).split('=').at(1).toInt();
        mSatData->setCollectDataItemX1(nX);
        mSatData->setCollectDataItemY1(nY);
    }else if(nOpeStr == Collect2_SetPos){
        QStringList nList = nParStr.split(';');
        int nX = nList.at(0).split('=').at(1).toInt();
        int nY = nList.at(1).split('=').at(1).toInt();
        mSatData->setCollectDataItemX2(nX);
        mSatData->setCollectDataItemY2(nY);
    }else if(nOpeStr == Adjust_On){
        mSatData->setAdjustOpenSign(true);
        mKFileOpe->adjustKFile();
    }else if(nOpeStr == Adjust_Off){
        mSatData->setAdjustOpenSign(false);
        mKFileOpe->adjustKFile();
    }else if(nOpeStr == Clear_KTable){
        mKFileOpe->clearKFile();
    }else if(nOpeStr == Adjust_LowTemp){
        mKFileOpe->lowTempCal();
    }else if(nOpeStr == Adjust_HighTemp){
        mKFileOpe->highTempCal();
    }else if(nOpeStr == Shutter_Inside){
        mSatData->setReference(SatData::INSIDE);
        mDataOpe->reference();
    }else if(nOpeStr == Shutter_Outside){
        mSatData->setReference(SatData::OUTSIDE);
        mDataOpe->reference();
    }else if(nOpeStr == Center_Info_Hide){
        mSatData->setInfoShowSign(false);
    }else if(nOpeStr == Center_Info_Show){
        mSatData->setInfoShowSign(true);
    }else if(nOpeStr == Update_TempAd_Table){
        mTempADOpe->updateADTable();
        mOtherOpe->loadModelData();
    }else if(nOpeStr == Effect_TempAd_Table){
        mTempADOpe->takeEffectADTable();
    }else if(nOpeStr == Table_To_SD){
        mOtherOpe->tableToSD();
    }else if(nOpeStr == SD_To_Table){
        mOtherOpe->SDToTable();
    }else if(nOpeStr == Area_Indicator_Off){
        mSatData->setAreaIndicatorSign(false);
    }else if(nOpeStr == Area_Indicator_On){
        mSatData->setAreaIndicatorSign(true);
    }else if(nOpeStr == Laser_Off){
        mSatData->setLaserSign(false);
        mOtherOpe->stopLaser();
    }else if(nOpeStr == Laser_On){
        mSatData->setLaserSign(true);
        mOtherOpe->openLaser();
    }else if(nOpeStr == AutoInt_Off){
        mSatData->setAutoIntSign(false);
        mAdjustOpe->adjustINT();
    }else if(nOpeStr == AutoInt_On){
        mSatData->setAutoIntSign(true);
        mAdjustOpe->adjustAutoInt();
    }else if(nOpeStr == Set_RecordArg_On){
        mSatData->setRecordArgSign(true);
    }else if(nOpeStr == Set_RecordArg_Off){
        mSatData->setRecordArgSign(false);
    }else if(nOpeStr == Set_Dis){
        float nDistance = nParStr.split('=').at(1).toFloat();
        mSatData->setDis(nDistance);
        mSatData->getTemp()->setDistance(mSatData->getDis());
    }else if(nOpeStr == Set_Emiss){
        float nEmiss = nParStr.split('=').at(1).toFloat();
        mSatData->setEmiss(nEmiss);
        mSatData->getTemp()->setEmiss(nEmiss);
    }else if(nOpeStr == Set_EnvTemp){
        float nEnvTemp = nParStr.split('=').at(1).toFloat();
        mSatData->setEnvTemp(nEnvTemp);
        mSatData->getTemp()->setEnvTemp(nEnvTemp);
    }else if(nOpeStr == Set_RelHum){
        float nRelHum = nParStr.split('=').at(1).toFloat();
        mSatData->setRelHum(nRelHum);
        mSatData->getTemp()->setRelHum(nRelHum);
    }else if(nOpeStr == Set_RefTemp){
        float nRefTemp = nParStr.split('=').at(1).toFloat();
        mSatData->setRefTemp(nRefTemp);
        mSatData->getTemp()->setRefTemp(nRefTemp);
    }else if(nOpeStr == Set_CorTemp){
        float nCorTemp = nParStr.split('=').at(1).toFloat();
        mSatData->setCorTemp(nCorTemp);
        mSatData->getTemp()->setCorTemp(nCorTemp);
    }else if(nOpeStr == Reset_Param){
        //重置测温参数
        mSatData->setDis(0.5);
        mSatData->setEmiss(1.0);
        mSatData->setEnvTemp(25);
        mSatData->setRelHum(0.5);
        mSatData->setRefTemp(25);
        mSatData->setCorTemp(0);
    }else if(nOpeStr == Set_Length_Foot){//设置长度单位为英尺
        mSatData->setLengthUnit(false);
    }else if(nOpeStr == Set_Length_Meter){//设置长度单位为米
        mSatData->setLengthUnit(true);
    }else if(nOpeStr == Set_Temp_Celsius){//设置温度单位为摄氏温度
        mSatData->setTempUnit(true);
    }else if(nOpeStr == Set_Temp_Fahrenheit){//设置温度单位为华氏温度
        mSatData->setTempUnit(false);
    }else if(nOpeStr == Set_SavePhotoSign_On){
        mSatData->setAutoSavePictureSign(true);
        if(mASTimer != NULL && !mASTimer->isActive()){
            mASTimer->start();
        }
    }else if(nOpeStr == Set_SavePhotoSign_Off){
        mSatData->setAutoSavePictureSign(false);
        if(mASTimer != NULL){
            mASTimer->stop();
        }
    }else if(nOpeStr == Set_SavePhotoTime){//设置自动保存图片间隔
        int nTime = nParStr.split('=').at(1).toInt();
        mSatData->setAutoSavePictureTime(nTime);
        mASTimer->setInterval(nTime*1000);
    }else if(nOpeStr == ShutDown){//关机操作
        mSatData->setTurnOffSign(true);
        mDataOpe->savePreferences();
        mDataOpe->powerOff();
    }else if(nOpeStr == Save_Param){//保存参数
        mDataOpe->savePreferences();
    }else if(nOpeStr == Read_Param){//读取参数。。。。。。
        mDataOpe->obtainPreferences();
    }else if(nOpeStr == Backup_App){
        if(mDataOpe->backupApp()){
            qDebug("BackupApp---success");
        }else{
            qDebug("BackupApp---failure");
        }
    }else if(nOpeStr == Update_App){
        if(mDataOpe->updateApp(nParStr)){
            qDebug("UpdateApp---success");
        }else{
            qDebug("UpdateApp---failure");
        }
    }else if(nOpeStr == Recovery_App){
        if(mDataOpe->recoveryApp()){
            qDebug("RecoveryApp---success");
        }else{
            qDebug("RecoveryApp---failure");
        }
    }else if(nOpeStr == Set_UpdateAppState){//设置更新app的状态
        int nState = nParStr.split('=').at(1).toInt();
        mSatData->setUpdateAppState(nState);
    }
}
