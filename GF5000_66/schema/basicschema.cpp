#include "basicschema.h"

BasicSchema::BasicSchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
}

QString BasicSchema::name(){
    return QString(tr("BasicSchema"));
}

QString BasicSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("base_focus.png");
}

QString BasicSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("base_normal.png");
}

QString BasicSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("base_highlight.png");
}

int BasicSchema::doLeftShort(){//基本模式的左短按操作，返回打档字段
    return Manual_Play;
}

int BasicSchema::doLeftLong(){//基本模式的左长按操作，返回打档字段
    return Manual_Play;
}

int BasicSchema::doRightShort(){//基本模式的右短按操作
    if(mSatData->getVideoSign()){//如果视频拍摄标记为真
        return Video_Stop;//返回停止视频拍摄操作
    }
    return Photo_Graph;//其他返回拍照操作
}

int BasicSchema::doRightLong(){//基本模式的右长按操作
    if(!mSatData->getVideoSign()){//如果视频拍摄为假
        return Video_Start;//返回开启视频拍摄操作
    }else{//视频拍摄标记为真，即正在视频拍摄
        return Video_Stop;//返回停止视频拍摄操作
    }
    return Photo_Graph;
}

int BasicSchema::doRightRelease(){//基本模式的右释放操作
    return No_Operation;
}

int BasicSchema::entryMode(){//基本模式的进入该模式的函数
    if(mSatData->getPlusSign()){
        return Set_Plus_False;
    }
    return No_Operation;
}

int BasicSchema::leaveMode(){//基本模式的离开该模式的函数
    if(mSatData->getVideoSign()){//视频拍摄标记为真
        return Video_Stop;//返回停止视频拍摄操作
    }
    return No_Operation;
}
