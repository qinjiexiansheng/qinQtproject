#include "correctschema.h"

CorrectSchema::CorrectSchema(QObject *parent) : QObject(parent){
    mSatData = SatData::initance();
}

QString CorrectSchema::name(){
    return QString(tr("CorrectModel"));
}

QString CorrectSchema::imageFocus(){
    return QString("%1%2").arg(IMG_DIR).arg("correct_focus.png");
}
QString CorrectSchema::imageLight(){
    return QString("%1%2").arg(IMG_DIR).arg("correct_highlight.png");
}
QString CorrectSchema::imageNormal(){
    return QString("%1%2").arg(IMG_DIR).arg("correct_normal.png");
}

int CorrectSchema::doLeftShort(){
    return Manual_Play;
}

int CorrectSchema::doLeftLong(){
    return Manual_Play;
}

int CorrectSchema::doRightShort(){
    return Open_Correct_Widget;
}

int CorrectSchema::doRightLong(){
    return Open_Correct_Widget;
}

int CorrectSchema::doRightRelease(){
    return No_Operation;
}

int CorrectSchema::entryMode(){
    if(!mSatData->getPlusSign()){
        return Set_Plus_True;
    }
    return No_Operation;
}

int CorrectSchema::leaveMode(){
    return No_Operation;
}

