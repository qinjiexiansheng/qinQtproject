#include "satdata.h"

satData::satData(QObject *parent) : QObject(parent)
{

}

satData *satData::initance(){

}

QString satData::getTmpAdFile(){
    return mTmpAdFile;
}

QString satData::getTmpAdNewFile(){
    return mTmpAdNewFile;
}

//temp ad table operation ======begin======
QString satData::findAdKeyForValue(int nValue){
    for(int i = 0; i < mAdList.size(); i++){
        QString nKey = QString("AD%1").arg(i);
        if(mAdList.at(i)->getValue() == nValue){
            return nKey;
        }
    }
    return NULL;
}

QString satData::findTempKeyForValue(float nValue){
    for(int i = 0; i < mTempList.size(); i++){
        QString nKey = QString("temp%1").arg(i);
        if(mTempList.at(i)->getValue() == nValue){
            return nKey;
        }
    }
    return NULL;
}

QString satData::findDiffKeyForValue(float nValue){
    for(int i = 0; i < mDiffList.size(); i++){
        QString nKey = QString("diff%1").arg(i);
        if(mDiffList.at(i)->getValue() == nValue){
            return nKey;
        }
    }
    return NULL;
}

int satData::findAdValueForKey(QString nKey){
    for(int i = 0; i < mAdList.size(); i++){
        if(mAdList.at(i)->getKey() == nKey){
            return mAdList.at(i)->getValue();
        }
    }
    return INT_MIN;
}

float satData::findTempValueForKey(QString nKey){
    for(int i = 0; i < mTempList.size(); i++){
        if(mTempList.at(i)->getKey() == nKey){
            return mTempList.at(i)->getValue();
        }
    }
    return FLT_MIN;
}

float satData::findDiffValueForKey(QString nKey){
    for(int i = 0; i < mDiffList.size(); i++){
        if(mDiffList.at(i)->getKey() == nKey){
            return mDiffList.at(i)->getValue();
        }
    }
    return FLT_MIN;
}

void satData::appendAdList(IntPair *nAdPair){
    if(nAdPair != NULL){
        mAdList.append(nAdPair);
    }
}

void satData::appendAdList(QString nKey,int nValue){
    if(!nKey.isEmpty()){
        IntPair *nIntPair = new IntPair(nKey,nValue);
        mAdList.append(nIntPair);
    }
}

void satData::appendTempList(FloatPair *nTempPair){
    if(nTempPair != NULL){
        mTempList.append(nTempPair);
    }
}

void satData::appendTempList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        FloatPair *nFloatPair = new FloatPair(nKey,nValue);
        mTempList.append(nFloatPair);
    }
}

void satData::appendDiffList(FloatPair *nDiffPair){
    if(nDiffPair != NULL){
        mDiffList.append(nDiffPair);
    }
}

void satData::appendDiffList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        FloatPair *nFloatPair = new FloatPair(nKey,nValue);
        mDiffList.append(nFloatPair);
    }
}

void satData::modifyAdList(QString nKey,int nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mAdList.size(); i++){
            if(mAdList.at(i)->getKey() == nKey){
                mAdList.at(i)->setValue(nValue);
            }
        }
    }
}

void satData::modifyTempList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mTempList.size(); i++){
            if(mTempList.at(i)->getKey() == nKey){
                mTempList.at(i)->setValue(nValue);
            }
        }
    }
}

void satData::modifyDiffList(QString nKey,float nValue){
    if(!nKey.isEmpty()){
        for(int i = 0; i < mDiffList.size(); i++){
            if(mDiffList.at(i)->getKey() == nKey){
                mDiffList.at(i)->setValue(nValue);
            }
        }
    }
}

QList<FloatPair *> *satData::getTempList(){
    return &mTempList;
}

QList<FloatPair *> *satData::getDiffList(){
    return &mDiffList;
}

QList<IntPair *> *satData::getAdList(){
    return &mAdList;
}

void satData::clearAdList(){
    mAdList.clear();
}

void satData::clearTempList(){
    mTempList.clear();
}

void satData::clearDiffList(){
    mDiffList.clear();
}

int satData::getTabNum(){
    return mTabNum;
}

float satData::getTabBaseTemp(){
    return mTabBaseTemp;
}

int satData::getTabBegAD(){
    return mTabBegAD;
}

int satData::getTabMaxAD(){
    return mTabMaxAD;
}

int satData::getTabMinAD(){
    return mTabMinAD;
}
float satData::getDiff30(){
    return mDiff30;
}

void satData::setTabNum(int nTabNum){
    if(mTabNum != nTabNum){
        mTabNum = nTabNum;
    }
}

void satData::setTabBaseTemp(float nTabBaseTemp){
    if(mTabBaseTemp != nTabBaseTemp){
        mTabBaseTemp = nTabBaseTemp;
    }
}

void satData::setTabBegAD(int nTabBegAD){
    if(mTabBegAD != nTabBegAD){
        mTabBegAD = nTabBegAD;
    }
}

void satData::setTabMaxAD(int nTabMaxAD){
    if(mTabMaxAD != nTabMaxAD){
        mTabMaxAD = nTabMaxAD;
    }
}

void satData::setTabMinAD(int nTabMinAD){
    if(mTabMinAD != nTabMinAD){
        mTabMinAD = nTabMinAD;
    }
}


void satData::setDiff30(float nDiff30){
    if(mDiff30 != nDiff30){
        mDiff30 = nDiff30;
    }
}



//temp ad table operation ======end======
