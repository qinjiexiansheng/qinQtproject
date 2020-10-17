#include "infraredmode.h"

//设置红外图像为铁红,数据类里的枚举变量已经先被设置，该业务不需要再设置
//伪彩色: 0.铁红; 1.反铁红; 2.彩虹; 3. 羽红; 5.黑热; 4.白热
void InfraredMode::iron(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 0 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(0);

#endif
#endif
    mSatData->setTipsString(tr("Switched to iron red"));
}





//设置红外图像为反铁红 ： IronInv
void InfraredMode::ironInv(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(1);

#endif
#endif
    mSatData->setTipsString(tr("Switched to anti iron red"));
}




//设置红外图像为白热 ： Grey
void InfraredMode::grey(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 4 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(4);

#endif
#endif
    mSatData->setTipsString(tr("Switched to white hot"));
}




//设置红外图像为黑热 ： GreyInv
void InfraredMode::greyInv(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 5 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(5);

#endif
#endif
    mSatData->setTipsString(tr("Switched to black fever"));
}





//设置红外图像为羽红 ： Feather
void InfraredMode::feather(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 3 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(3);
#endif
#endif
    mSatData->setTipsString(tr("Switched to feather red"));
}





//设置红外图像为彩虹 ： RainBow
void InfraredMode::rainBow(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam irmode 2 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    setIrmode(2);
#endif
#endif
    mSatData->setTipsString(tr("Switched to rainbow"));
}
