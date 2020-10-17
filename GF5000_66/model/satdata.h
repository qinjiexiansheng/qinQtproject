#ifndef SATDATA_H
#define SATDATA_H

#include <QObject>
#include <QMap>
#include <QHash>
#include <QList>
#include <QDebug>
#include <QPair>
#include <float.h>
#include <limits.h>
#include <QThread>
#include <QStandardItemModel>
#include "uitls/interface.h"
#include "uitls/macrodefine.h"
#include "lib/temp.h"




/*======================================

  数据类 ： SatData
  保存程序中需要用到的数据，应用观察者模式，
  数据变化时，可以通知注册的观察者

  ======================================*/
class SatData : public QObject
{
    Q_OBJECT
public:
    /*======================================
      红外图像模式 InfraredEnum
      IRON     ：铁红
      IRONINV  ：反铁红
      RAINBOW  ：彩虹
      FEATHER  ：羽红
      GREYINV  ：黑热
      GREY     ：白热
     ======================================*/
    enum InfraredEnum{IRON,IRONINV,RAINBOW,FEATHER,GREY,GREYINV};
    /*======================================
      档位枚举 GearEnum
      GEARONE  ：第一档位，高灵敏度
      GEARTWO  ：第二档位，低灵敏度
     ======================================*/
    enum GearEnum{GEARONE,GEARTWO};
    /*======================================
      红外图像模式 DenoiseEnum
      NOTDENOISE ：无降噪
      DENOISEONE ：降噪1算法
     ======================================*/
    enum DenoiseEnum{NOTDENOISE,DENOISEONE};
    enum ReferenceEnum{INSIDE,OUTSIDE};//内外参考枚举
    enum WindowDisplayEnum{NORMAL,COLLECTDATA,CALBADPOINT};//主窗口显示模式（正常、采集数据、校坏点）

    /*======================================
      静态方法，获取该类的实例，使用饿汉单例模式
     ======================================*/
    static SatData* initance();

    /*======================================
      注册和移除观察者函数
     ======================================*/
    bool attach(DataObserver *nObserver,QList<QString> nStrList);
    bool attach(DataObserver *nObserver,QString nStr);
    bool unattach(DataObserver *nObserver);
    bool unattach(DataObserver *nObserver,QString nStr);

    TEMP* getTemp();

    //temp ad table operation ======begin======
    QString findAdKeyForValue(int nValue);
    QString findTempKeyForValue(float nValue);
    QString findDiffKeyForValue(float nValue);
    int findAdValueForKey(QString nKey);
    float findTempValueForKey(QString nKey);
    float findDiffValueForKey(QString nKey);
    void appendAdList(IntPair *nAdPair);
    void appendAdList(QString nKey,int nValue = 0);
    void appendTempList(FloatPair *nTempPair);
    void appendTempList(QString nKey,float nValue = 0);
    void appendDiffList(FloatPair *nDiffPair);
    void appendDiffList(QString nKey,float nValue = 0);
    void modifyAdList(QString nKey,int nValue = 0);
    void modifyTempList(QString nKey,float nValue = 0);
    void modifyDiffList(QString nKey,float nValue = 0);
    QList<FloatPair *> *getTempList();
    QList<FloatPair *> *getDiffList();
    QList<IntPair *> *getAdList();
    void clearAdList();
    void clearTempList();
    void clearDiffList();
    int getTabNum();
    float getTabBaseTemp();
    int getTabBegAD();
    int getTabMaxAD();
    int getTabMinAD();
    float getDiff30();
    void setTabNum(int nTabNum);
    void setTabBaseTemp(float nTabBaseTemp);
    void setTabBegAD(int nTabBegAD);
    void setTabMaxAD(int nTabMaxAD);
    void setTabMinAD(int nTabMinAD);
    void setDiff30(float nDiff30);
    //temp ad table operation ======end======

    /*======================================
      获取函数
     ======================================*/
    int getMaxPointX();
    int getMaxPointY();
    int getMinPointX();
    int getMinPointY();
    float getMaxTemp();
    float getMinTemp();
    float getCenterTemp();
    int getCenterAd();
    int getDet();
    float getSensor();
    int getFid();
    int getGsk();
    int getInt();
    int getGain();
    float getBattery();
    float getAlarmTemp();
    float getRedTemp();
    float getOrangeTemp();
    InfraredEnum getInfraredMode();
    GearEnum getGearMode();
    DenoiseEnum getDenoiseMode();
    ReferenceEnum getReference();
    WindowDisplayEnum getWindowDisplay();
    bool   getVideoSign();
    bool   getFrozenSign();
    bool   getInfoSign();
    bool   getPointSign();
    bool   getAlarmSign();
    bool   getPlusSign();
    bool   getLowSign();

    int    getAutoSenCount();
    bool getAdjustOpenSign();
    bool getInfoShowSign();
    bool getAutoShutterSign();
    int getAutoShutterTime();
    int getSerialNumber();
    int getOutFactoryYear();
    int getOutFactoryMonth();
    int getOutFactoryDay();
    int getCalBadPointItemX();
    int getCalBadPointItemY();
    int getCalBadPointAD();
    bool getCalBadPointState();
    int getCollectDataItemX1();
    int getCollectDataItemY1();
    int getCollectDataItemAD1();
    int getCollectDataItemX2();
    int getCollectDataItemY2();
    int getCollectDataItemAD2();
    int getCenterX();
    int getCenterY();
    int getGlobalAD();
    int getPointInitialAD();
    QStandardItemModel *getModel();
    QString getTmpAdFile();
    QString getTmpAdNewFile();
    QString getLogFile();
    QString getTestFile();
    QString getArgFile();
    QString getKFile();
    float getDis();
    float getEmiss();
    float getEnvTemp();
    float getRelHum();
    float getRefTemp();
    float getCorTemp();


    bool getAreaIndicatorSign();
    bool getLaserSign();
    bool getBatteryState();

    bool getAutoIntSign();
    int getAutoInt();



    bool   getRecordArgSign();
    QString getNTestFile();



    QString getTipsString();

    bool getLengthUnit();
    bool getTempUnit();

    int getAutoSavePictureTime();
    bool getAutoSavePictureSign();


    bool getTurnOffSign();
    int getUpdateAppState();


    QString getLanguage();




    /*======================================
      设置函数
     ======================================*/
    void setMaxPointX(int nMaxPointX);
    void setMaxPointY(int nMaxPointY);
    void setMinPointX(int nMinPointX);
    void setMinPointY(int nMinPointY);
    void setMaxTemp(float nMaxTemp);
    void setMinTemp(float nMinTemp);
    void setCenterTemp(float nCenterTemp);
    void setCenterAd(int nCenterAd);
    void setDet(int nDet);
    void setFid(int nFid);
    void setGsk(int nGsk);
    void setInt(int nInt);
    void setGain(int nGain);
    void setSensor(float nSensor);
    void setBattery(float nBattery);
    void setAlarmTemp(float nAlarmTemp);
    void setRedTemp(float nRedTemp);
    void setOrangeTemp(float nOrangeTemp);
    void setInfraredMode(InfraredEnum nInfraredMode);
    void setGearMode(GearEnum nGearMode);
    void setDenoiseMode(DenoiseEnum nDenoiseMode);
    void setReference(ReferenceEnum nReference);
    void setWindowDisplay(WindowDisplayEnum nWindowDisplay);
    void setVideoSign(bool nVideoSign);
    void setFrozenSign(bool nFrozenSign);
    void setInfoSign(bool nInfoSign);
    void setPointSign(bool nPointSign);
    void setAlarmSign(bool nAlarmSign);
    void setPlusSign(bool nPlusSign);
    void setLowSign(bool nLowSign);
    void setAutoSenCount(int nAutoSenCount);
    void setAdjustOpenSign(bool nAdjustOpenSign);
    void setInfoShowSign(bool nInfoShowSign);
    void setAutoShutterSign(bool nAutoShutterSign);
    void setAutoShutterTime(int nAutoShutterTime);
    void setSerialNumber(int nSerialNumber);
    void setOutFactoryYear(int nOutFactoryYear);
    void setOutFactoryMonth(int nOutFactoryMonth);
    void setOutFactoryDay(int nOutFactoryDay);
    void setCalBadPointItemX(int nCalBadPointItemX);
    void setCalBadPointItemY(int nCalBadPointItemY);
    void setCalBadPointAD(int nCalBadPointAD);
    void setCalBadPointState(bool nCalBadPointState);
    void setCollectDataItemX1(int nCollectDataItemX1);
    void setCollectDataItemY1(int nCollectDataItemY1);
    void setCollectDataItemAD1(int nCollectDataItemAD1);
    void setCollectDataItemX2(int nCollectDataItemX2);
    void setCollectDataItemY2(int nCollectDataItemY2);
    void setCollectDataItemAD2(int nCollectDataItemAD2);
    void setCenterX(int nCenterX);
    void setCenterY(int nCenterY);
    void setGlobalAD(int nGlobalAD);
    void setPointInitialAD(int nPointInitialAD);
    void setTmpAdFile(QString nTmpAdFile);
    void setTmpAdNewFile(QString nTmpAdNewFile);
    void setLogFile(QString nLogFile);
    void setTestFile(QString nTestFile);
    void setArgFile(QString nArgFile);
    void setKFile(QString nKFile);
    void setDis(float nDis);
    void setEmiss(float nEmiss);
    void setEnvTemp(float nEnvTemp);
    void setRelHum(float nRelHum);
    void setRefTemp(float nRefTemp);
    void setCorTemp(float nCorTemp);


    void setAreaIndicatorSign(bool nAreaIndicatorSign);
    void setLaserSign(bool nLaserSign);
    void setBatteryState(bool nBatteryState);


    void setTurnOffSign(bool nTurnOffSign);

    //=====begin
    AbstractSchema* getCurrentSchema();
    int getCurrentSchemaIndex();
    AbstractSchema* getSchema(int nIndex);
    void setCurrentSchemaIndex(int nIndex);
    int getSchemaListSize();
    void addSchema(AbstractSchema* nSchema);
    //=====end


    void setAutoIntSign(bool nAutoIntSign);
    void setAutoInt(int nAutoInt);


    void setRecordArgSign(bool nRecordArgSign);
    void setNTestFile(QString nNTestFile);


    void setTipsString(QString nTipsString);

    void setLengthUnit(bool nLengthUnit);
    void setTempUnit(bool nTempUnit);

    void setAutoSavePictureTime(int nAutoSavePictureTime);
    void setAutoSavePictureSign(bool nAutoSavePictureSign);

    void setUpdateAppState(int nUpdateAppState);


    void setLanguage(QString nLanguage);


protected:
    SatData(QObject *parent = 0);

private:
    void notifyObservers(QString nStr);//通知函数，根据字段来通知注册了该字段的观察者
    static SatData*  _SatData;//单例静态变量
    QMap<QString,QList<DataObserver*> >  mMap;//字段-观察者
    QList<FloatPair*> mTempList;//温度AD表中的temp项
    QList<FloatPair*> mDiffList;//温度AD表中的diff项
    QList<IntPair*> mAdList;//温度AD表中的AD项


    QList<AbstractSchema*> mSchemaList;//模式列表
    int mCurrentSchemaIndex;//当前模式索引

    TEMP *mTemp;
    QStandardItemModel *mModel;//模型
    QString mTmpAdFile;//当前标定表文件
    QString mTmpAdNewFile;//当前标定表临时文件
    QString mLogFile;//当前日志文件
    QString mTestFile;//当前保存测试的文件

    QString mArgFile;//当前档位参数文件
    QString mKFile;//当前K值表文件
    int mMaxPointX;//最大温度点x坐标
    int mMaxPointY;//最大温度点y坐标
    int mMinPointX;//最小温度点x坐标
    int mMinPointY;//最小温度点y坐标
    int mCenterAd;//中心点AD值
    int mCenterX;//屏幕中心点的X坐标
    int mCenterY;//屏幕中心点的Y坐标
    int mCollectDataItemX1;//第一个采集框的X坐标
    int mCollectDataItemY1;//第一个采集框的Y坐标
    int mCollectDataItemAD1;//第一格采集框的AD值
    int mCollectDataItemX2;//第二个采集框的X坐标
    int mCollectDataItemY2;//第二个采集框的Y坐标
    int mCollectDataItemAD2;//第二个采集框的AD值
    int mDet;//DET值,内部传感器的AD值
    int mFid;//FID值,计算得到的范围[931-2792]
    int mGsk;//GSK值,计算得到的范围[1-3351]
    int mInt;//INT值
    int mGain;//GAIN值,范围[0-2],0代表3倍,1代表1.5倍,2代表1倍
    int mTabNum;//个数，主要是为了保存文本读出的数据，以下几个同理
    int mTabBegAD;
    int mTabMaxAD;
    int mTabMinAD;
    int mGlobalAD;//全局14位AD
    int mPointInitialAD;//点的14位AD
    int mAutoShutterTime;//自动打档时间
    int mSerialNumber;//序列号
    int mOutFactoryYear;//机器出厂年份
    int mOutFactoryMonth;//机器出厂月份
    int mOutFactoryDay;//机器出厂日期
    int mCalBadPointItemX;//校坏点的所在点的X坐标
    int mCalBadPointItemY;//校坏点的所在点的Y坐标
    int mCalBadPointAD;//校坏点的所在点的AD值
    InfraredEnum mInfraredMode;//红外模式
    GearEnum mGearMode;//档位
    DenoiseEnum mDenoiseMode;//降噪模式
    ReferenceEnum mReference;//参考模式（内外参考）
    WindowDisplayEnum mWindowDisplay;//窗口显示模式
    float mTabBaseTemp;//目前是整形
    float mBattery;//设备电量
    float mAlarmTemp;//报警温度
    float mRedTemp;//红色温度
    float mOrangeTemp;//橙色温度
    float mSensor;//SENSOR值,内部传感器温度
    float mDiff30;
    float mMaxTemp;//最大温度
    float mMinTemp;//最小温度
    float mCenterTemp;//中心点温度


    float mDis;//距离
    float mEmiss;//辐射率
    float mEnvTemp;//环境温度
    float mRelHum;//相对湿度
    float mRefTemp;//反射温度
    float mCorTemp;//修正温度





    bool mVideoSign;//视频正在拍摄标记(真:正在拍摄视频,假:不在拍摄状态)
    bool mFrozenSign;//图像冻结标记(真:图像已冻结,假:图像正在解冻状态)
    bool mInfoSign;//信息显示标记(真:显示,假:隐藏)
    bool mPointSign;//极点显示标记(真:显示,假:隐藏)
    bool mAlarmSign;//报警标记(真:温度报警,假:不报警)
    bool mPlusSign;//+模式标记(真:+模式,假:基本模式)
    bool mLowSign;//低灵敏度标记(真:低灵敏度,假:高灵敏度)
    bool mAdjustOpenSign;//非均匀校正开启标记，为真则使用校正过的K值表，为假则使用默认的K值表
    bool mInfoShowSign;//标定时，标定框旁信息显示标记
    bool mAutoShutterSign;//自动打档标记
    bool mCalBadPointState;//校坏点的所在点的状态（1为已校过的，0为未校过的）
    bool mAreaIndicatorSign;//中心区域，面积或点显示标记
    bool mLaserSign;//激光标记
    bool mBatteryState;//充电状态

    bool mAutoIntSign;//自动调节INT标记
    int mAutoInt;//自动INT数值


    QString mAppCompileDate;//APP版本
    QString mKernelCompileDate;//内核版本
    QString mFpgaCompileDate;//fpga版本



    bool mRecordArgSign;//记录数据标记(真:开启记录数据,假:关闭记录数据),在正常模式下记录参数
    QString mNTestFile;//在正常模式下记录参数的文件名


    QString mTipsString;//提示字符串


    bool mLengthUnit;//长度单位，true为米，false为英尺
    bool mTempUnit;//温度单位，true为摄氏，false为华氏

    int mAutoSavePictureTime;//自动保存图片时间间隔
    bool mAutoSavePictureSign;//自动保存图片开启标记


    bool mTurnOffSign;//关机标记


    int mUpdateAppState;//程序更新状态

    QString mLanguage;



};

#endif // SATDATA_H
