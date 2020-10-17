#include "displayschema.h"

DisplaySchema::DisplaySchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
}

QString DisplaySchema::name(){
    return QString(tr("Display Setting"));
}

QString DisplaySchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("display_focus.png");
}

QString DisplaySchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("display_highlight.png");
}

QString DisplaySchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("display_normal.png");
}



int DisplaySchema::doLeftShort(){
#if 0
    if(mSatData->getInfoSign()){//窗口信息显示模式为真，则设为假
        return Global_Info_Hide;
    }else{
        return Global_Info_Show;
    }
#endif
#if 1
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Image_Thaw;//返回图像解冻操作
    }else{
        return Image_Free;//返回图像冻结操作
    }
#endif
}

int DisplaySchema::doLeftLong(){
#if 0
    if(mSatData->getInfoSign()){//窗口信息显示模式为真，则设为假
        return Global_Info_Hide;
    }else{
        return Global_Info_Show;
    }
#endif
#if 1
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Image_Thaw;//返回图像解冻操作
    }else{
        return Image_Free;//返回图像冻结操作
    }
#endif
}

int DisplaySchema::doRightShort(){
    if(mSatData->getPointSign()){//如果高低温点显示标记为真，则设为假
        return Global_Point_Hide;
    }else{
        return Global_Point_Show;
    }
}

int DisplaySchema::doRightLong(){//同上
    if(mSatData->getPointSign()){//如果高低温点显示标记为真，则设为假
        return Global_Point_Hide;
    }else{
        return Global_Point_Show;
    }
}

int DisplaySchema::doRightRelease(){
    return No_Operation;
}

int DisplaySchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}

int DisplaySchema::leaveMode(){
#if 1
    if(mSatData->getFrozenSign()){//如果冻结标记为真
        return Image_Thaw;//返回图像解冻操作
    }
#endif
    return No_Operation;
}
