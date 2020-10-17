#include "camera.h"

//拍照
void Camera::photograph(){
#ifdef _SAT_ARM_
#if 0
    //FIFO形式通信
    QString nStr = "echo setParam camera 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    //socket通信
    //setCamera(1);
    char *nFilename = setCamera(1);
    //int nLen = strlen(nFilename);
    //nLen = 9;
    //printf("[D]Lin >> The photo len:%d\n",nLen);
    //qDebug("[D]Lin >> The photo len:%d",nLen);
    qDebug("[D]Lin >> The photo's name:%s",nFilename);
    mSatData->setTipsString(tr("The picture has been saved as %1").arg(nFilename));
#endif
#endif
#ifdef _SAT_XNJ_
    FileOpe::writeInfoToPhoto("NULL");
    mSatData->setTipsString(tr("The picture has been saved as %1").arg("nFilename"));
    qDebug("Take the photo!!!!");
#endif
}


//开启视频拍摄
void Camera::videoStart(){
#ifdef _SAT_ARM_
#if 0
    //FIFO
    QString nStr = "echo setParam video 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    //Socket
    SetVideo(1);
#endif
#endif
}



//关闭视频拍摄
void Camera::videoStop(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam video 0 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    SetVideo(0);
#endif
#endif
}



//图像冻结
void Camera::imageFreeze(){
#ifdef _SAT_ARM_
#if 0
    //FIFO
    QString nStr = "echo setParam freeze 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    //Socket
    setImageFreeze(1);
#endif
#endif
}



//图像解冻
void Camera::imageThaw(){
#ifdef _SAT_ARM_
#if 0
    //FIFO
    QString nStr = "echo setParam freeze 0 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    //Socket
    setImageFreeze(0);
#endif
#endif
}
