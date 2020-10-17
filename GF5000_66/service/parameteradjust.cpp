#include "parameteradjust.h"

//设置FID,该业务只是修改底层的参数，并非数据类的参数，
//相反，该业务需要获取数据类的参数，所以调用该业务前先调整好数据类的参数
void AdjustParam::adjustFID(){
#ifdef _SAT_ARM_
#if 0
    int nFid = mSatData->getFid();//获取参数
    QString nStr = "echo setParam fid %1 > /tmp/eventFifo &";
    nStr = nStr.arg(nFid);
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setFID(mSatData->getFid());
#endif
#endif
}




//设置GSK
void AdjustParam::adjustGSK(){
#ifdef _SAT_ARM_
#if 0
    int nGsk = mSatData->getGsk();
    QString nStr = "echo setParam gsk %1 > /tmp/eventFifo &";
    nStr = nStr.arg(nGsk);
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setGSK(mSatData->getGsk());
#endif
#endif
}





//设置GAIN
void AdjustParam::adjustGAIN(){
#ifdef _SAT_ARM_
    int nGain = mSatData->getGain();
    nGain = nGain << 4;
    nGain = nGain | 3;
#if 0
    QString nStr = "echo setParam gain %1 > /tmp/eventFifo &";
    nStr = nStr.arg(nGain);
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setGAIN(nGain);
#endif
#endif
}




//设置INT
void AdjustParam::adjustINT(){
#ifdef _SAT_ARM_
#if 0
    int nInt = mSatData->getInt();
    QString nStr = "echo setParam tint %1 > /tmp/eventFifo &";
    nStr = nStr.arg(nInt);
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setTINT(mSatData->getInt());
#endif
#endif
}

void AdjustParam::adjustAutoInt(){
    int nAutoInt = autoInt();
    mSatData->setAutoInt(nAutoInt);
#ifdef _SAT_ARM_
    setTINT(nAutoInt);
#endif
}



int AdjustParam::autoInt(){
    int nAutoInt = mSatData->getDet();
    int nDelDet = 0;
    float nK = 1.0;
    if(mSatData->getGearMode() == SatData::GEARONE){
        nDelDet = DET_REFERENCE_ONE - mSatData->getDet();
        nK = C_FORMULA_ONE + A_FORMULA_ONE*nDelDet*nDelDet + B_FORMULA_ONE*nDelDet;
        nK /= 10000;
        nAutoInt = (INT_REFERENCE_ONE + B_CONSTANT_ONE)*nK - B_CONSTANT_ONE + 0.5;
    }else{
        nDelDet = DET_REFERENCE_TWO - mSatData->getDet();
        nK = C_FORMULA_TWO + A_FORMULA_TWO*nDelDet*nDelDet + B_FORMULA_TWO*nDelDet;
        nK /= 10000;
        nAutoInt = (INT_REFERENCE_TWO + B_CONSTANT_TWO)*nK - B_CONSTANT_TWO + 0.5;
    }
    nAutoInt = nAutoInt<MIN_INT?MIN_INT+1:nAutoInt;
    nAutoInt = nAutoInt>MAX_INT?MAX_INT:nAutoInt;
    return nAutoInt;
}
