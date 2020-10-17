#include "gearadjust.h"

//设置为第一档,数据类里的档位枚举变量已经先被设置为该档位，即操作中不需要再设置档位枚举变量,其实也可以设置
//第一档为高灵敏度，-20到250
void GearMode::gearOne(){
    mSatData->setLowSign(false);//灵敏度标记设置为假
    //设置当前档位的文件
    mSatData->setKFile(QString("%1%2").arg(COF_DIR).arg(QString(K_FILE).arg(1)));
    mSatData->setArgFile(QString("%1%2").arg(COF_DIR).arg(QString(ARG_FILE).arg(1)));
    mSatData->setTmpAdFile(QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1)));
    mSatData->setTmpAdNewFile(QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(1)));
    mTempADOpe->loadADTable();//加载档位的温度AD表
    mTempADOpe->saveADTable();//保存为临时文件
    mTempADOpe->takeEffectADTable();//生效温度AD表
    mDataOpe->loadArg();//加载参数文件
    int nMs = 20;
    mAdjustOpe->adjustFID();
    msDelay(nMs);
    if(mSatData->getAutoIntSign()){
        mAdjustOpe->adjustAutoInt();
    }else{
        mAdjustOpe->adjustINT();
    }
    msDelay(nMs);
    mAdjustOpe->adjustGAIN();
    msDelay(nMs);
    mKFileOpe->adjustKFile();
    msDelay(nMs);
    mAdjustOpe->adjustGSK();
    mOtherOpe->loadModelData();
    mSatData->getTemp()->setGear(0);

    mDataOpe->manualPlay();
}





//设置为第二档,数据类里的档位枚举变量已经先被设置为该档位，即操作中不需要再设置档位枚举变量
//第二档为低灵敏度，200以上原理同上
void GearMode::gearTwo(){
    mSatData->setLowSign(true);
    mSatData->setKFile(QString("%1%2").arg(COF_DIR).arg(QString(K_FILE).arg(2)));
    mSatData->setArgFile(QString("%1%2").arg(COF_DIR).arg(QString(ARG_FILE).arg(2)));
    mSatData->setTmpAdFile(QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(2)));
    mSatData->setTmpAdNewFile(QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(2)));
    mTempADOpe->loadADTable();
    mTempADOpe->saveADTable();
    mTempADOpe->takeEffectADTable();
    mDataOpe->loadArg();
    int nMs = 20;
    mAdjustOpe->adjustFID();
    msDelay(nMs);
    if(mSatData->getAutoIntSign()){
        mAdjustOpe->adjustAutoInt();
    }else{
        mAdjustOpe->adjustINT();
    }

    msDelay(nMs);
    mAdjustOpe->adjustGAIN();
    msDelay(nMs);
    mKFileOpe->adjustKFile();
    msDelay(nMs);
    mAdjustOpe->adjustGSK();
    mOtherOpe->loadModelData();
    mSatData->getTemp()->setGear(1);
    mDataOpe->manualPlay();
}


//线程休眠函数
void GearMode::msDelay(int nMs){
    usleep(nMs*1000);
}
