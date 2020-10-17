#include "satdata.h"

SatData* SatData::_SatData = NULL;
SatData* SatData::initance(){//静态方法，获取对象指针
    if(_SatData == NULL){
        _SatData = new SatData();
    }
    return _SatData;
}

bool SatData::attach(DataObserver* nObserver , QList<QString> nStrList){//注册观察者，多字段
    if(nObserver == NULL){//如果注册的观察者为空，返回假
        return false;
    }
    if(nStrList.isEmpty()){//如果注册的字段列表为空，返回假
        return false;
    }
    for(int i = 0 ; i < nStrList.size() ; i++){//对每一个字段调用单个字段注册函数
        attach(nObserver , nStrList[i]);
    }
    return true;
}

bool SatData::attach(DataObserver* nObserver,QString nStr){//注册观察者函数，单字段
    if(nObserver == NULL){//如果观察者为空，则返回假
        return false;
    }
    if(nStr.isEmpty()){//如果字段为空，则返回假
        return false;
    }
    if(mMap.contains(nStr)){//如果Map里存在该字段
        QList<DataObserver*> *nList = &mMap[nStr];//提取该字段的观察者列表
        int i = 0;
        for(; i < nList->size(); i++){
            if(nList->at(i) == nObserver){//遍历列表，查看列表是否已经存在该观察者
                break;
            }
        }
        if(i >= nList->size()){//如果不存在，则将该观察者加入到列表
            nList->append(nObserver);
        }
    }else{//如果Map不存在该字段，则在Map里新建该字段
        QList<DataObserver*> nList;
        nList.append(nObserver);
        mMap[nStr] = nList;
    }
    notifyObservers(nStr);
    return true;
}

bool SatData::unattach(DataObserver *nObserver){//删除观察者
    if(nObserver == NULL){//如果观察者为空，则返回假
        return false;
    }
    QMap<QString,QList<DataObserver*> >::iterator nMapIter;
    for(nMapIter = mMap.begin(); nMapIter != mMap.end(); nMapIter++){//遍历Map里的所有字段
        QList<DataObserver*> *nList = &nMapIter.value();//获取字段的观察者列表指针
        nList->removeOne(nObserver);//删除观察者
    }
    return true;
}

bool SatData::unattach(DataObserver *nObserver, QString nStr){//删除观察者的特殊字段
    if(nObserver == NULL){//如果观察者为空，则返回假
        return false;
    }
    if(nStr.isEmpty()){//如果字段为空，则返回假
        return false;
    }
    if(mMap.contains(nStr)){//如果Map里存在该字段
        QList<DataObserver*> *nList = &mMap[nStr];//得到字段的观察者列表指针
        nList->removeOne(nObserver);//删除
    }
    return true;
}


TEMP *SatData::getTemp(){
    if(mTemp == NULL){
        mTemp = new TEMP();
    }
    return mTemp;
}


SatData::SatData(QObject *parent) : QObject(parent){//构造函数
    mTemp = NULL;
    mModel = new QStandardItemModel();//创建模型
    mModel->setColumnCount(2);//模型列数
    QStringList nHeader;
    nHeader<<tr("Key")<<tr("Value");
    mModel->setHorizontalHeaderLabels(nHeader);//设置模型的表头名称
    mMaxPointX = 100;//最大温度点x坐标
    mMaxPointY = 100;//最大温度点y坐标
    mMinPointX = 200;//最小温度点x坐标
    mMinPointY = 200;//最小温度点y坐标
    mCenterAd = 0x8000;//中心点AD值
    mCenterX = 320;//屏幕中心点的X坐标
    mCenterY = 240;//屏幕中心点的Y坐标
    mCollectDataItemX1 = 180;//第一个采集框的X坐标
    mCollectDataItemY1 = 190;//第一个采集框的Y坐标
    mCollectDataItemAD1 = 0x8000;//第一格采集框的AD值
    mCollectDataItemX2 = 400;//第二个采集框的X坐标
    mCollectDataItemY2 = 190;//第二个采集框的Y坐标
    mCollectDataItemAD2 = 0x8000;//第二个采集框的AD值
    mDet = 0x2000;//DET值,内部传感器的AD值
    mFid = DEFAULT_FID;//FID值,计算得到的范围[931-2792]
    mGsk = DEFAULT_GSK;//GSK值,计算得到的范围[1-3351]
    mInt = DEFAULT_INT;//INT值
    mGain = DEFAULT_GAIN;//GAIN值,范围[0-2],0代表3倍,1代表1.5倍,2代表1倍
    mTabNum = TEMP_AD_TABLE_TABNUM;//个数，主要是为了保存文本读出的数据，以下几个同理
    mTabBaseTemp = TEMP_AD_TABLE_TABBASETMP;//目前是整形
    mTabBegAD = 0;
    mTabMaxAD = 0;
    mTabMinAD = 0;
    mGlobalAD = 0x1000;//全局14位AD
    mPointInitialAD = 0x1200;//点的14位AD
    mAutoShutterTime = AUTO_SHUTTER_TIME;//自动打档时间
    mSerialNumber = 1;//序列号
    mOutFactoryYear = CURRENT_YEAR;//机器出厂年份
    mOutFactoryMonth = 1;//机器出厂月份
    mOutFactoryDay = 1;//机器出厂日期
    mCalBadPointItemX = 320;//校坏点的所在点的X坐标
    mCalBadPointItemY = 240;//校坏点的所在点的Y坐标
    mCalBadPointAD = 0x8000;//校坏点的所在点的AD值
    mInfraredMode = IRON;//红外模式
    mGearMode = GEARONE;//档位
    mDenoiseMode = DENOISEONE;//降噪模式
    mReference = INSIDE;//参考模式（内外参考）
    mWindowDisplay = NORMAL;//窗口显示模式
    mBattery = 1;//设备电量
    mAlarmTemp = ALARM_TEMP;//报警温度
    mRedTemp = RED_TEMP;//红色温度
    mOrangeTemp = ORANGE_TEMP;//橙色温度
    mSensor = 27.37;//SENSOR值,内部传感器温度
    mDiff30 = 0;
    mMaxTemp = 250;//最大温度
    mMinTemp = 0;//最小温度
    mCenterTemp = 30;//中心点温度
    mVideoSign = false;//视频正在拍摄标记(真:正在拍摄视频,假:不在拍摄状态)
    mFrozenSign = false;//图像冻结标记(真:图像已冻结,假:图像正在解冻状态)
    mInfoSign = false;//信息显示标记(真:显示,假:隐藏)
    mPointSign = false;//极点显示标记(真:显示,假:隐藏)
    mAlarmSign = false;//报警标记(真:温度报警,假:不报警)
    mPlusSign = false;//+模式标记(真:+模式,假:基本模式)
    mLowSign = false;//低灵敏度标记(真:低灵敏度,假:高灵敏度)

    mAdjustOpenSign = true;//非均匀校正开启标记，为真则使用校正过的K值表，为假则使用默认的K值表
    mInfoShowSign = false;//标定时，标定框旁信息显示标记
    mAutoShutterSign = true;//自动打档标记
    mCalBadPointState = false;//校坏点的所在点的状态（1为已校过的，0为未校过的）
    mTmpAdFile = QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
    mTmpAdNewFile = QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(1));
    mLogFile = "";
    mArgFile = "";
    mTestFile = "";
    mKFile = "";
    mDis = 0.5;//距离
    mEmiss = 1.00;//辐射率
    mEnvTemp = 25.0;//环境温度
    mRelHum = 0.5;//相对湿度
    mRefTemp = 25.0;
    mCorTemp = 0;
    mAreaIndicatorSign = true;
    mLaserSign = false;
    mCurrentSchemaIndex = 0;
    mAutoIntSign = true;//默认开启自动INT
    mAutoInt = INT_REFERENCE_ONE;
    mRecordArgSign = false;//记录数据标记(真:开启记录数据,假:关闭记录数据)

    mBatteryState = false;

    mLengthUnit = true;//长度单位，true为米，false为英尺
    mTempUnit = true;//温度单位，true为摄氏，false为华氏

    mAutoSavePictureTime = 30;
    mAutoSavePictureSign = false;

    mTurnOffSign = false;


}

void SatData::notifyObservers(QString nStr){//通知观察者
    if(mMap.contains(nStr)){//如果Map存在该字段
        QList<DataObserver*> nList = mMap[nStr];//获取字段观察者列表
        if(!nList.isEmpty()){
            for(int i = 0; i < nList.size(); i++){
                if(nList.at(i) != NULL){
                    nList.at(i)->doUpdate(nStr);//调用每个观察者的更新函数
                }
            }
        }
    }
}


//temp ad table operation ======begin======
QString SatData::findAdKeyForValue(int nValue){
    for(int i = 1; i <= mTabNum; i++){
        QString nKey = QString("AD%1").arg(i);
        if(findAdValueForKey(nKey) == nValue){
            return nKey;
        }
    }
    return NULL;
}

QString SatData::findTempKeyForValue(float nValue){
    for(int i = 1; i <= mTabNum; i++){
        QString nKey = QString("temp%1").arg(i);
        if(findTempValueForKey(nKey) == nValue){
            return nKey;
        }
    }
    return NULL;
}

QString SatData::findDiffKeyForValue(float nValue){
    for(int i = 1; i <= mTabNum; i++){
        QString nKey = QString("diff%1").arg(i);
        if(findDiffValueForKey(nKey) == nValue){
            return nKey;
        }
    }
    return NULL;
}

int SatData::findAdValueForKey(QString nKey){
    for(int i = 0; i < mAdList.size(); i++){
        if(mAdList.at(i)->getKey() == nKey){
            return mAdList.at(i)->getValue();
        }
    }
    return INT_MIN;
}

float SatData::findTempValueForKey(QString nKey){
    for(int i = 0; i < mTempList.size(); i++){
        if(mTempList.at(i)->getKey() == nKey){
            return mTempList.at(i)->getValue();
        }
    }
    return FLT_MIN;
}

float SatData::findDiffValueForKey(QString nKey){
    for(int i = 0; i < mDiffList.size(); i++){
        if(mDiffList.at(i)->getKey() == nKey){
            return mDiffList.at(i)->getValue();
        }
    }
    return FLT_MIN;
}

void SatData::appendAdList(IntPair *nAdPair){
    if(nAdPair != NULL){
        mAdList.append(nAdPair);
    }
}

void SatData::appendAdList(QString nKey,int nValue){
    if(!nKey.isEmpty()){
        IntPair *nIntPair = new IntPair(nKey,nValue);
        mAdList.append(nIntPair);
    }
}

void SatData::appendTempList(FloatPair *nTempPair){
    if(nTempPair != NULL){
        mTempList.append(nTempPair);
    }
}

void SatData::appendTempList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        FloatPair *nFloatPair = new FloatPair(nKey,nValue);
        mTempList.append(nFloatPair);
    }
}

void SatData::appendDiffList(FloatPair *nDiffPair){
    if(nDiffPair != NULL){
        mDiffList.append(nDiffPair);
    }
}

void SatData::appendDiffList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        FloatPair *nFloatPair = new FloatPair(nKey,nValue);
        mDiffList.append(nFloatPair);
    }
}

void SatData::modifyAdList(QString nKey,int nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mAdList.size(); i++){
            if(mAdList.at(i)->getKey() == nKey){
                mAdList.at(i)->setValue(nValue);
            }
        }
    }
}

void SatData::modifyTempList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mTempList.size(); i++){
            if(mTempList.at(i)->getKey() == nKey){
                mTempList.at(i)->setValue(nValue);
            }
        }
    }
}

void SatData::modifyDiffList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mDiffList.size(); i++){
            if(mDiffList.at(i)->getKey() == nKey){
                mDiffList.at(i)->setValue(nValue);
            }
        }
    }
}

QList<FloatPair *> *SatData::getTempList(){
    return &mTempList;
}

QList<FloatPair *> *SatData::getDiffList(){
    return &mDiffList;
}

QList<IntPair *> *SatData::getAdList(){
    return &mAdList;
}

void SatData::clearAdList(){
    mAdList.clear();
}

void SatData::clearTempList(){
    mTempList.clear();
}

void SatData::clearDiffList(){
    mDiffList.clear();
}

int SatData::getTabNum(){
    return mTabNum;
}

float SatData::getTabBaseTemp(){
    return mTabBaseTemp;
}

int SatData::getTabBegAD(){
    return mTabBegAD;
}

int SatData::getTabMaxAD(){
    return mTabMaxAD;
}

int SatData::getTabMinAD(){
    return mTabMinAD;
}
float SatData::getDiff30(){
    return mDiff30;
}

void SatData::setTabNum(int nTabNum){
    if(mTabNum != nTabNum){
        mTabNum = nTabNum;
    }
}

void SatData::setTabBaseTemp(float nTabBaseTemp){
    if(mTabBaseTemp != nTabBaseTemp){
        mTabBaseTemp = nTabBaseTemp;
    }
}

void SatData::setTabBegAD(int nTabBegAD){
    if(mTabBegAD != nTabBegAD){
        mTabBegAD = nTabBegAD;
    }
}

void SatData::setTabMaxAD(int nTabMaxAD){
    if(mTabMaxAD != nTabMaxAD){
        mTabMaxAD = nTabMaxAD;
    }
}

void SatData::setTabMinAD(int nTabMinAD){
    if(mTabMinAD != nTabMinAD){
        mTabMinAD = nTabMinAD;
    }
}


void SatData::setDiff30(float nDiff30){
    if(mDiff30 != nDiff30){
        mDiff30 = nDiff30;
    }
}



//temp ad table operation ======end======









/*======================================
  获取函数
 ======================================*/
int SatData::getMaxPointX(){
    return mMaxPointX;
}

int SatData::getMaxPointY(){
    return mMaxPointY;
}

int SatData::getMinPointX(){
    return mMinPointX;
}

int SatData::getMinPointY(){
    return mMinPointY;
}

float SatData::getMaxTemp(){
    return mMaxTemp;
}

float SatData::getMinTemp(){
    return mMinTemp;
}

float SatData::getCenterTemp(){
    return mCenterTemp;
}

int SatData::getCenterAd(){
    return mCenterAd;
}

int SatData::getDet(){
    return mDet;
}

float SatData::getSensor(){
    return mSensor;
}

int SatData::getFid(){
    return mFid;
}

int SatData::getGsk(){
    return mGsk;
}

int SatData::getInt(){
    return mInt;
}

int SatData::getGain(){
    return mGain;
}

float SatData::getBattery(){
    return mBattery;
}

float SatData::getAlarmTemp(){
    return mAlarmTemp;
}

float SatData::getRedTemp(){
    return mRedTemp;
}

float SatData::getOrangeTemp(){
    return mOrangeTemp;
}
SatData::InfraredEnum SatData::getInfraredMode(){
    return mInfraredMode;
}

SatData::GearEnum SatData::getGearMode(){
    return mGearMode;
}

SatData::DenoiseEnum SatData::getDenoiseMode(){
    return mDenoiseMode;
}

bool  SatData::getVideoSign(){
    return mVideoSign;
}

bool SatData::getFrozenSign(){
    return mFrozenSign;
}
bool SatData::getInfoSign(){
    return mInfoSign;
}
bool SatData::getPointSign(){
    return mPointSign;
}

bool SatData::getAlarmSign(){
    return mAlarmSign;
}

bool SatData::getPlusSign(){
    return mPlusSign;
}

bool SatData::getLowSign(){
    return mLowSign;
}



SatData::ReferenceEnum SatData::getReference(){
    return mReference;
}

bool SatData::getAdjustOpenSign(){
    return mAdjustOpenSign;
}


bool SatData::getInfoShowSign(){
    return mInfoShowSign;
}

bool SatData::getAutoShutterSign(){
    return mAutoShutterSign;
}

int SatData::getAutoShutterTime(){
    return mAutoShutterTime;
}

int SatData::getSerialNumber(){
    return mSerialNumber;
}

int SatData::getOutFactoryYear(){
    return mOutFactoryYear;
}

int SatData::getOutFactoryMonth(){
    return mOutFactoryMonth;
}

int SatData::getOutFactoryDay(){
    return mOutFactoryDay;
}

SatData::WindowDisplayEnum SatData::getWindowDisplay(){
    return mWindowDisplay;
}

int SatData::getCalBadPointItemX(){
    return mCalBadPointItemX;
}
int SatData::getCalBadPointItemY(){
    return mCalBadPointItemY;
}
int SatData::getCalBadPointAD(){
    return mCalBadPointAD;
}
bool SatData::getCalBadPointState(){
    return mCalBadPointState;
}

int SatData::getCollectDataItemX1(){
    return mCollectDataItemX1;
}
int SatData::getCollectDataItemY1(){
    return mCollectDataItemY1;
}
int SatData::getCollectDataItemAD1(){
    return mCollectDataItemAD1;
}
int SatData::getCollectDataItemX2(){
    return mCollectDataItemX2;
}
int SatData::getCollectDataItemY2(){
    return mCollectDataItemY2;
}
int SatData::getCollectDataItemAD2(){
    return mCollectDataItemAD2;
}


int SatData::getCenterX(){
    return mCenterX;
}

int SatData::getCenterY(){
    return mCenterY;
}

int SatData::getGlobalAD(){
    return mGlobalAD;
}

int SatData::getPointInitialAD(){
    return mPointInitialAD;
}

QStandardItemModel *SatData::getModel(){
    return mModel;
}


QString SatData::getTmpAdFile(){
    return mTmpAdFile;
}

QString SatData::getTmpAdNewFile(){
    return mTmpAdNewFile;
}

QString SatData::getLogFile(){
    return mLogFile;
}

QString SatData::getArgFile(){
    return mArgFile;
}

QString SatData::getTestFile(){
    return mTestFile;
}
QString SatData::getKFile(){
    return mKFile;
}
float SatData::getDis(){
    return mDis;
}
float SatData::getEmiss(){
    return mEmiss;
}
float SatData::getEnvTemp(){
    return mEnvTemp;
}
float SatData::getRelHum(){
    return mRelHum;
}

bool SatData::getAreaIndicatorSign(){
    return mAreaIndicatorSign;
}

bool SatData::getLaserSign(){
    return mLaserSign;
}

bool SatData::getBatteryState(){
    return mBatteryState;
}


float SatData::getRefTemp(){
    return mRefTemp;
}

float SatData::getCorTemp(){
    return mCorTemp;
}
bool SatData::getAutoIntSign(){
    return mAutoIntSign;
}

int SatData::getAutoInt(){
    return mAutoInt;
}





bool SatData::getRecordArgSign(){
    return mRecordArgSign;
}


QString SatData::getNTestFile(){
    return mNTestFile;
}

QString SatData::getTipsString(){
    return mTipsString;
}

bool SatData::getLengthUnit(){
    return mLengthUnit;
}

bool SatData::getTempUnit(){
    return mTempUnit;
}

bool SatData::getAutoSavePictureSign(){
    return mAutoSavePictureSign;
}

int SatData::getAutoSavePictureTime(){
    return mAutoSavePictureTime;
}

bool SatData::getTurnOffSign(){
    return mTurnOffSign;
}

int SatData::getUpdateAppState(){
    return mUpdateAppState;
}

QString SatData::getLanguage(){
    return mLanguage;
}



/*======================================
  设置函数
 ======================================*/
void SatData::setMaxPointX(int nMaxPointX){
    if(mMaxPointX != nMaxPointX){
        mMaxPointX = nMaxPointX;
        notifyObservers("MaxPointX");
    }
}

void SatData::setMaxPointY(int nMaxPointY){
    if(mMaxPointY != nMaxPointY){
        mMaxPointY = nMaxPointY;
        notifyObservers("MaxPointY");
    }
}

void SatData::setMinPointX(int nMinPointX){
    if(mMinPointX != nMinPointX){
        mMinPointX = nMinPointX;
        notifyObservers("MinPointX");
    }
}

void SatData::setMinPointY(int nMinPointY){
    if(mMinPointY != nMinPointY){
        mMinPointY = nMinPointY;
        notifyObservers("MinPointY");
    }
}

void SatData::setMaxTemp(float nMaxTemp){
    if(mMaxTemp != nMaxTemp){
        mMaxTemp = nMaxTemp;
        notifyObservers("MaxTemp");
    }
}

void SatData::setMinTemp(float nMinTemp){
    if(mMinTemp != nMinTemp){
        mMinTemp = nMinTemp;
        notifyObservers("MinTemp");
    }
}

void SatData::setCenterTemp(float nCenterTemp){
    if(mCenterTemp != nCenterTemp){
        mCenterTemp = nCenterTemp;
        notifyObservers("CenterTemp");
    }
}

void SatData::setCenterAd(int nCenterAd){
    if(mCenterAd != nCenterAd){
        mCenterAd = nCenterAd;
        notifyObservers("CenterAd");
    }
}

void SatData::setDet(int nDet){
    if(mDet != nDet){
        mDet = nDet;
        notifyObservers("Det");
    }
}

void SatData::setSensor(float nSensor){
    if(mSensor != nSensor){
        mSensor = nSensor;
        notifyObservers("Sensor");
    }
}

void SatData::setFid(int nFid){
    if(mFid != nFid){
        mFid = nFid;
        notifyObservers("Fid");
    }
}

void SatData::setGsk(int nGsk){
    if(mGsk != nGsk){
        mGsk = nGsk;
        notifyObservers("Gsk");
    }
}

void SatData::setInt(int nInt){
    if(mInt != nInt){
        mInt = nInt;
        notifyObservers("Int");
    }
}

void SatData::setGain(int nGain){
    if(mGain != nGain){
        mGain = nGain;
        notifyObservers("Gain");
    }
}

void SatData::setBattery(float nBattery){
    if(mBattery != nBattery){
        mBattery = nBattery;
        notifyObservers("Battery");
    }
}


void SatData::setAlarmTemp(float nAlarmTemp){
    if(mAlarmTemp != nAlarmTemp){
        mAlarmTemp = nAlarmTemp;
        notifyObservers("AlarmTemp");
    }
}

void SatData::setRedTemp(float nRedTemp){
    if(mRedTemp != nRedTemp){
        mRedTemp = nRedTemp;
        notifyObservers("RedTemp");
    }
}

void SatData::setOrangeTemp(float nOrangeTemp){
    if(mOrangeTemp != nOrangeTemp){
        mOrangeTemp = nOrangeTemp;
        notifyObservers("OrangeTemp");
    }
}

void SatData::setInfraredMode(InfraredEnum nInfraredMode){
    if(mInfraredMode != nInfraredMode){
        mInfraredMode = nInfraredMode;
        notifyObservers("InfraredMode");
    }
}

void SatData::setGearMode(GearEnum nGearMode){
    if(mGearMode != nGearMode){
        mGearMode = nGearMode;
        notifyObservers("SensitiveMode");
    }
}

void SatData::setDenoiseMode(DenoiseEnum nDenoiseMode){
    if(mDenoiseMode != nDenoiseMode){
        mDenoiseMode = nDenoiseMode;
        notifyObservers("DenoiseMode");
    }
}

void SatData::setVideoSign(bool nVideoSign){
    if(mVideoSign != nVideoSign){
        mVideoSign = nVideoSign;
        notifyObservers("VideoSign");
    }
}

void SatData::setFrozenSign(bool nFrozenSign){
    if(mFrozenSign != nFrozenSign){
        mFrozenSign = nFrozenSign;
        notifyObservers("FrozenSign");
    }
}

void SatData::setInfoSign(bool nInfoSign){
    if(mInfoSign != nInfoSign){
        mInfoSign = nInfoSign;
        notifyObservers("InfoSign");
    }
}

void SatData::setPointSign(bool nPointSign){
    if(mPointSign != nPointSign){
        mPointSign = nPointSign;
        notifyObservers("PointSign");
    }
}


void SatData::setAlarmSign(bool nAlarmSign){
    if(mAlarmSign != nAlarmSign){
        mAlarmSign = nAlarmSign;
        notifyObservers("AlarmSign");
    }
}


void SatData::setPlusSign(bool nPlusSign){
    if(mPlusSign != nPlusSign){
        mPlusSign = nPlusSign;
        notifyObservers("PlusSign");
    }
}


void SatData::setLowSign(bool nLowSign){
    if(mLowSign != nLowSign){
        mLowSign = nLowSign;
        notifyObservers("LowSign");
    }
}



void SatData::setReference(ReferenceEnum nReference){
    if(mReference != nReference){
        mReference = nReference;
    }
}
void SatData::setAdjustOpenSign(bool nAdjustOpenSign){
    if(mAdjustOpenSign != nAdjustOpenSign){
        mAdjustOpenSign = nAdjustOpenSign;
    }
}

void SatData::setInfoShowSign(bool nInfoShowSign){
    if(mInfoShowSign != nInfoShowSign){
        mInfoShowSign = nInfoShowSign;
        notifyObservers("InfoShowSign");
    }
}

void SatData::setAutoShutterSign(bool nAutoShutterSign){
    if(mAutoShutterSign != nAutoShutterSign){
        mAutoShutterSign = nAutoShutterSign;
        notifyObservers("AutoShutterSign");
    }
}

void SatData::setAutoShutterTime(int nAutoShutterTime){
    if(mAutoShutterTime != nAutoShutterTime){
        mAutoShutterTime = nAutoShutterTime;
        notifyObservers("AutoShutterTime");
    }
}
void SatData::setSerialNumber(int nSerialNumber){
    if(mSerialNumber != nSerialNumber){
        mSerialNumber = nSerialNumber;
    }
}

void SatData::setOutFactoryYear(int nOutFactoryYear){
    if(mOutFactoryYear != nOutFactoryYear){
        mOutFactoryYear = nOutFactoryYear;
    }
}

void SatData::setOutFactoryMonth(int nOutFactoryMonth){
    if(mOutFactoryMonth != nOutFactoryMonth){
        mOutFactoryMonth = nOutFactoryMonth;
    }
}

void SatData::setOutFactoryDay(int nOutFactoryDay){
    if(mOutFactoryDay != nOutFactoryDay){
        mOutFactoryDay = nOutFactoryDay;
    }
}

void SatData::setWindowDisplay(WindowDisplayEnum nWindowDisplay){
    if(mWindowDisplay != nWindowDisplay){
        mWindowDisplay = nWindowDisplay;
        notifyObservers("WindowDisplay");
    }
}

void SatData::setCalBadPointItemX(int nCalBadPointItemX){
    if(mCalBadPointItemX != nCalBadPointItemX){
        mCalBadPointItemX = nCalBadPointItemX;
        notifyObservers("CalBadPointItemX");
    }
}
void SatData::setCalBadPointItemY(int nCalBadPointItemY){
    if(mCalBadPointItemY != nCalBadPointItemY){
        mCalBadPointItemY = nCalBadPointItemY;
        notifyObservers("CalBadPointItemY");
    }
}
void SatData::setCalBadPointAD(int nCalBadPointAD){
    if(mCalBadPointAD != nCalBadPointAD){
        mCalBadPointAD = nCalBadPointAD;
        notifyObservers("CalBadPointAD");
    }
}
void SatData::setCalBadPointState(bool nCalBadPointState){
    if(mCalBadPointState != nCalBadPointState){
        mCalBadPointState = nCalBadPointState;
        notifyObservers("CalBadPointState");
    }
}

void SatData::setCollectDataItemX1(int nCollectDataItemX1){
    if(mCollectDataItemX1 != nCollectDataItemX1){
        mCollectDataItemX1 = nCollectDataItemX1;
    }
}
void SatData::setCollectDataItemY1(int nCollectDataItemY1){
    if(mCollectDataItemY1 != nCollectDataItemY1){
        mCollectDataItemY1 = nCollectDataItemY1;
    }
}
void SatData::setCollectDataItemAD1(int nCollectDataItemAD1){
    if(mCollectDataItemAD1 != nCollectDataItemAD1){
        mCollectDataItemAD1 = nCollectDataItemAD1;
        notifyObservers("CollectDataItemAD1");
    }
}
void SatData::setCollectDataItemX2(int nCollectDataItemX2){
    if(mCollectDataItemX2 != nCollectDataItemX2){
        mCollectDataItemX2 = nCollectDataItemX2;
    }
}
void SatData::setCollectDataItemY2(int nCollectDataItemY2){
    if(mCollectDataItemY2 != nCollectDataItemY2){
        mCollectDataItemY2 = nCollectDataItemY2;
    }
}
void SatData::setCollectDataItemAD2(int nCollectDataItemAD2){
    if(mCollectDataItemAD2 != nCollectDataItemAD2){
        mCollectDataItemAD2 = nCollectDataItemAD2;
        notifyObservers("CollectDataItemAD2");
    }
}


void SatData::setCenterX(int nCenterX){
    if(mCenterX != nCenterX){
        mCenterX = nCenterX;
    }
}

void SatData::setCenterY(int nCenterY){
    if(mCenterY != nCenterY){
        mCenterY = nCenterY;
    }
}
void SatData::setGlobalAD(int nGlobalAD){
    if(mGlobalAD != nGlobalAD){
        mGlobalAD = nGlobalAD;
        notifyObservers("GlobalAD");
    }
}
void SatData::setPointInitialAD(int nPointInitialAD){
    if(mPointInitialAD != nPointInitialAD){
        mPointInitialAD = nPointInitialAD;
        notifyObservers("PointInitialAD");
    }
}


void SatData::setTmpAdFile(QString nTmpAdFile){
    mTmpAdFile = nTmpAdFile;
}

void SatData::setTmpAdNewFile(QString nTmpAdNewFile){
    mTmpAdNewFile = nTmpAdNewFile;
}

void SatData::setArgFile(QString nArgFile){
    mArgFile = nArgFile;
}

void SatData::setLogFile(QString nLogFile){
    mLogFile = nLogFile;
}

void SatData::setTestFile(QString nTestFile){
    mTestFile = nTestFile;
}

void SatData::setKFile(QString nKFile){
    mKFile = nKFile;
}

void SatData::setDis(float nDis){
    if(mDis != nDis){
        mDis = nDis;
        notifyObservers("Dis");
    }
}
void SatData::setEmiss(float nEmiss){
    if(mEmiss != nEmiss){
        mEmiss = nEmiss;
        notifyObservers("Emiss");
    }
}
void SatData::setEnvTemp(float nEnvTemp){
    if(mEnvTemp != nEnvTemp){
        mEnvTemp = nEnvTemp;
        notifyObservers("EnvTemp");
    }
}

void SatData::setRelHum(float nRelHum){
    if(mRelHum != nRelHum){
        mRelHum = nRelHum;
        notifyObservers("RelHum");
    }
}

void SatData::setAreaIndicatorSign(bool nAreaIndicatorSign){
    if(mAreaIndicatorSign != nAreaIndicatorSign){
        mAreaIndicatorSign = nAreaIndicatorSign;
        notifyObservers("AreaIndicatorSign");
    }
}

void SatData::setLaserSign(bool nLaserSign){
    if(mLaserSign != nLaserSign){
        mLaserSign = nLaserSign;
        notifyObservers("LaserSign");
    }
}


void SatData::setBatteryState(bool nBatteryState){
    if(mBatteryState != nBatteryState){
        mBatteryState = nBatteryState;
        notifyObservers("BatteryState");
    }
}


AbstractSchema* SatData::getCurrentSchema(){
    return mSchemaList.at(mCurrentSchemaIndex);
}

int SatData::getCurrentSchemaIndex(){
    return mCurrentSchemaIndex;
}

AbstractSchema* SatData::getSchema(int nIndex){
    if(nIndex < 0 ){
        nIndex = 0;
    }else if(nIndex >= mSchemaList.size()){
        nIndex = mSchemaList.size()-1;
    }
    return mSchemaList.at(nIndex);
}

void SatData::setCurrentSchemaIndex(int nIndex){
    if(nIndex < 0 ){
        nIndex = 0;
    }else if(nIndex >= mSchemaList.size()){
        nIndex = mSchemaList.size()-1;
    }
    if(mCurrentSchemaIndex != nIndex){
        mCurrentSchemaIndex = nIndex;
        notifyObservers("SchemaIndex");
    }
}

int SatData::getSchemaListSize(){
    return mSchemaList.size();
}

void SatData::addSchema(AbstractSchema *nSchema){
    mSchemaList.append(nSchema);
}


void SatData::setAutoIntSign(bool nAutoIntSign){
    if(mAutoIntSign != nAutoIntSign){
        mAutoIntSign = nAutoIntSign;
        notifyObservers("AutoIntSign");
    }
}

void SatData::setAutoInt(int nAutoInt){
    if(mAutoInt != nAutoInt){
        mAutoInt = nAutoInt;
        notifyObservers("AutoInt");
    }
}

void SatData::setRecordArgSign(bool nRecordArgSign){
    if(mRecordArgSign != nRecordArgSign){
        mRecordArgSign = nRecordArgSign;
        notifyObservers("RecordArgSign");
    }
}



void SatData::setRefTemp(float nRefTemp){
    if(mRefTemp != nRefTemp){
        mRefTemp = nRefTemp;
        notifyObservers("RefTemp");
    }
}

void SatData::setCorTemp(float nCorTemp){
    if(mCorTemp != nCorTemp){
        mCorTemp = nCorTemp;
        notifyObservers("CorTemp");
    }
}

void SatData::setNTestFile(QString nNTestFile){
    if(mNTestFile != nNTestFile){
        mNTestFile = nNTestFile;
    }
}



void SatData::setTipsString(QString nTipsString){
    if(mTipsString != nTipsString){
        mTipsString = nTipsString;
        notifyObservers("TipsString");
    }
}

void SatData::setLengthUnit(bool nLengthUnit){
    if(mLengthUnit != nLengthUnit){
        mLengthUnit = nLengthUnit;
        notifyObservers("LengthUnit");
    }
}

void SatData::setTempUnit(bool nTempUnit){
    if(mTempUnit != nTempUnit){
        mTempUnit = nTempUnit;
        notifyObservers("TempUnit");
    }
}

void SatData::setAutoSavePictureTime(int nAutoSavePictureTime){
    if(mAutoSavePictureTime != nAutoSavePictureTime){
        mAutoSavePictureTime = nAutoSavePictureTime;
        notifyObservers("AutoSavePictureTime");
    }
}

void SatData::setAutoSavePictureSign(bool nAutoSavePictureSign){
    if(mAutoSavePictureSign != nAutoSavePictureSign){
        mAutoSavePictureSign = nAutoSavePictureSign;
        notifyObservers("AutoSavePictureSign");
    }
}

void SatData::setTurnOffSign(bool nTurnOffSign){
    if(mTurnOffSign != nTurnOffSign){
        mTurnOffSign = nTurnOffSign;
        notifyObservers("TurnOffSign");
    }
}

void SatData::setUpdateAppState(int nUpdateAppState){
    if(mUpdateAppState != nUpdateAppState){
        mUpdateAppState = nUpdateAppState;
        notifyObservers("UpdateAppState");
    }
}

void SatData::setLanguage(QString nLanguage){
    if(mLanguage != nLanguage){
        mLanguage = nLanguage;
        notifyObservers("Language");
    }
}





