#include "gearschema.h"


GearSchema::GearSchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
    mList.append(SatData::GEARONE);//将档位枚举加入列表，加入顺序为枚举顺序
    mList.append(SatData::GEARTWO);
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
}

QString GearSchema::name(){
    return QString(tr("Gear Setting"));
}

QString GearSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("gear_focus.png");
}

QString GearSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("gear_highlight.png");
}

QString GearSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("gear_normal.png");
}




int GearSchema::doLeftShort(){
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size()-1;
    }
    if(mList.at(mIndex) == SatData::GEARONE){
        return Gear_One;
    }else if(mList.at(mIndex) == SatData::GEARTWO){
        return Gear_Two;
    }
    return No_Operation;
}

int GearSchema::doLeftLong(){
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size()-1;
    }
    if(mList.at(mIndex) == SatData::GEARONE){
        return Gear_One;
    }else if(mList.at(mIndex) == SatData::GEARTWO){
        return Gear_Two;
    }
    return No_Operation;
}

int GearSchema::doRightShort(){
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::GEARONE){
        return Gear_One;
    }else if(mList.at(mIndex) == SatData::GEARTWO){
        return Gear_Two;
    }
    return No_Operation;
}


int GearSchema::doRightLong(){
    if(mSatData->getGearMode() == SatData::GEARONE){
        mIndex = 0;
    }else{
        mIndex = 1;
    }
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mList.at(mIndex) == SatData::GEARONE){
        return Gear_One;
    }else if(mList.at(mIndex) == SatData::GEARTWO){
        return Gear_Two;
    }
    return No_Operation;
}

int GearSchema::doRightRelease(){
    return No_Operation;
}

int GearSchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}

int GearSchema::leaveMode(){
    return No_Operation;
}



