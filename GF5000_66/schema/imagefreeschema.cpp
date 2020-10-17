#include "imagefreeschema.h"

ImageFreeSchema::ImageFreeSchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
}

QString ImageFreeSchema::name(){
    return QString(tr("Image Free"));
}

QString ImageFreeSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("image_focus.png");
}

QString ImageFreeSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("image_highlight.png");
}

QString ImageFreeSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("image_normal.png");
}



int ImageFreeSchema::doLeftShort(){
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Photo_Graph;//返回拍照操作
    }else{
        return Manual_Play;//标记为假时返回打档操作
    }
}
int ImageFreeSchema::doLeftLong(){
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Photo_Graph;//返回拍照操作
    }else{
        return Manual_Play;//标记为假时返回打档操作
    }
}

int ImageFreeSchema::doRightShort(){
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Image_Thaw;//返回图像解冻操作
    }else{
        return Image_Free;//返回图像冻结操作
    }
}

int ImageFreeSchema::doRightLong(){//同上
    if(mSatData->getFrozenSign()){
        return Image_Thaw;
    }else{
        return Image_Free;
    }
}

int ImageFreeSchema::doRightRelease(){
    return No_Operation;
}

int ImageFreeSchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}
int ImageFreeSchema::leaveMode(){
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Image_Thaw;//返回图像解冻操作
    }
    return No_Operation;
}


