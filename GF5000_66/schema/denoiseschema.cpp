#include "denoiseschema.h"

DenoiseSchema::DenoiseSchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
    mList.append(SatData::NOTDENOISE);//将降噪枚举加入循环列表，顺序为枚举顺序
    mList.append(SatData::DENOISEONE);
    if(mSatData->getDenoiseMode() == SatData::NOTDENOISE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
}

QString DenoiseSchema::name(){
    return QString(tr("Image Denoise"));
}

QString DenoiseSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("noise_focus.png");
}

QString DenoiseSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("noise_highlight.png");
}

QString DenoiseSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("noise_normal.png");
}


int DenoiseSchema::doLeftShort(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;//循环切换
    }
    if(mList.at(mIndex) == SatData::NOTDENOISE){
        //mSatData->setTipsString(tr("Noise reduction has been shut down"));
        return Denoise_Not;
    }else if(mList.at(mIndex) == SatData::DENOISEONE){
        //mSatData->setTipsString("Noise reduction has been started");
        return Denoise_One;
    }
    return No_Operation;
}

int DenoiseSchema::doLeftLong(){//操作同上
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size()-1;
    }
    if(mList.at(mIndex) == SatData::NOTDENOISE){
        //mSatData->setTipsString(tr("Noise reduction has been shut down"));
        return Denoise_Not;
    }else if(mList.at(mIndex) == SatData::DENOISEONE){
        //mSatData->setTipsString("Noise reduction has been started");
        return Denoise_One;
    }
    return No_Operation;
}

int DenoiseSchema::doRightShort(){//操作同上
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::NOTDENOISE){
        //mSatData->setTipsString(tr("Noise reduction has been shut down"));
        return Denoise_Not;
    }else if(mList.at(mIndex) == SatData::DENOISEONE){
        //mSatData->setTipsString("Noise reduction has been started");
        return Denoise_One;
    }
    return No_Operation;
}

int DenoiseSchema::doRightLong(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::NOTDENOISE){
        //mSatData->setTipsString(tr("Noise reduction has been shut down"));
        return Denoise_Not;
    }else if(mList.at(mIndex) == SatData::DENOISEONE){
        //mSatData->setTipsString("Noise reduction has been started");
        return Denoise_One;
    }
    return No_Operation;
}

int DenoiseSchema::doRightRelease(){
    return No_Operation;
}

int DenoiseSchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}

int DenoiseSchema::leaveMode(){
    return No_Operation;
}


