#include "infraredschema.h"

InfraredSchema::InfraredSchema(QObject *parent) : QObject(parent)
{
    mSatData = SatData::initance();
    mList.append(SatData::IRON);//将红外图像模式枚举加入切换列表，加入顺序为枚举定义的顺序
    mList.append(SatData::IRONINV);
    mList.append(SatData::RAINBOW);
    mList.append(SatData::FEATHER);
    mList.append(SatData::GREYINV);
    mList.append(SatData::GREY);
    SatData::InfraredEnum nEnum = mSatData->getInfraredMode();
    if(nEnum == SatData::IRON){
        mIndex = 0;
    }else if(nEnum == SatData::IRONINV){
        mIndex = 1;
    }else if(nEnum == SatData::RAINBOW){
        mIndex = 2;
    }else if(nEnum == SatData::FEATHER){
        mIndex = 3;
    }else if(nEnum == SatData::GREYINV){
        mIndex = 4;
    }else{
        mIndex = 5;
    }
}

QString InfraredSchema::name(){
    return QString(tr("Infrared Setting"));
}

QString InfraredSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("ir_focus.png");
}

QString InfraredSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("ir_highlight.png");
}

QString InfraredSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("ir_normal.png");
}


int InfraredSchema::doLeftShort(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    if(mList.at(mIndex) == SatData::IRON){
        return Infrared_Iron;
    }else if(mList.at(mIndex) == SatData::IRONINV){
        return Infrared_Ironinv;
    }else if(mList.at(mIndex) == SatData::RAINBOW){
        return Infrared_Rainbow;
    }else if(mList.at(mIndex) == SatData::FEATHER){
        return Infrared_Feather;
    }else if(mList.at(mIndex) == SatData::GREYINV){
        return Infrared_Greyinv;
    }else if(mList.at(mIndex) == SatData::GREY){
        return Infrared_Grey;
    }
    return No_Operation;
}

int InfraredSchema::doLeftLong(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    if(mList.at(mIndex) == SatData::IRON){
        return Infrared_Iron;
    }else if(mList.at(mIndex) == SatData::IRONINV){
        return Infrared_Ironinv;
    }else if(mList.at(mIndex) == SatData::RAINBOW){
        return Infrared_Rainbow;
    }else if(mList.at(mIndex) == SatData::FEATHER){
        return Infrared_Feather;
    }else if(mList.at(mIndex) == SatData::GREYINV){
        return Infrared_Greyinv;
    }else if(mList.at(mIndex) == SatData::GREY){
        return Infrared_Grey;
    }
    return No_Operation;
}

int InfraredSchema::doRightShort(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::IRON){
        return Infrared_Iron;
    }else if(mList.at(mIndex) == SatData::IRONINV){
        return Infrared_Ironinv;
    }else if(mList.at(mIndex) == SatData::RAINBOW){
        return Infrared_Rainbow;
    }else if(mList.at(mIndex) == SatData::FEATHER){
        return Infrared_Feather;
    }else if(mList.at(mIndex) == SatData::GREYINV){
        return Infrared_Greyinv;
    }else if(mList.at(mIndex) == SatData::GREY){
        return Infrared_Grey;
    }
    return No_Operation;
}

int InfraredSchema::doRightLong(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::IRON){
        return Infrared_Iron;
    }else if(mList.at(mIndex) == SatData::IRONINV){
        return Infrared_Ironinv;
    }else if(mList.at(mIndex) == SatData::RAINBOW){
        return Infrared_Rainbow;
    }else if(mList.at(mIndex) == SatData::FEATHER){
        return Infrared_Feather;
    }else if(mList.at(mIndex) == SatData::GREYINV){
        return Infrared_Greyinv;
    }else if(mList.at(mIndex) == SatData::GREY){
        return Infrared_Grey;
    }
    return No_Operation;
}

int InfraredSchema::doRightRelease(){
    return No_Operation;
}

int InfraredSchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}

int InfraredSchema::leaveMode(){
    return No_Operation;
}

