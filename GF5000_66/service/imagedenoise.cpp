#include "imagedenoise.h"

//设置为无降噪,数据类里的降噪枚举已经先被设置，该业务不需要重新设置
void DenoiseMode::denoiseNot(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam denoise 0 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setDenoise(0);

#endif
#endif
    mSatData->setTipsString(tr("Noise reduction has been shut down"));
}





//设置为降噪算法1,数据类里的降噪枚举已经先被设置，该业务不需要重新设置
void DenoiseMode::denoiseOne(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam denoise 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setDenoise(1);

#endif
#endif
    mSatData->setTipsString(tr("Noise reduction has been started"));
}

