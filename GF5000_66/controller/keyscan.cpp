#include "keyscan.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

KeyScan::KeyScan(QObject *parent) : QObject(parent){
    //qDebug()<<"[D]Lin >> The KeyScan::KeyScan() ThreadID:"<<QThread::currentThreadId();
    init();
    //qDebug()<<QString("[D]Lin >> [%1,%2] ThreadID:%3").arg(__FILE__).arg(__LINE__).arg(QThread::currentThreadId());
}

void KeyScan::init(){
    SatKey *nKey16 = new SatKey(QString("/dev/gpio50"),KEY_16);
    mKeyList.append(nKey16);
    SatKey *nKey27 = new SatKey(QString("/dev/gpio27"),KEY_27);
    mKeyList.append(nKey27);
    SatKey *nKey26 = new SatKey(QString("/dev/gpio26"),KEY_26);
    mKeyList.append(nKey26);
    SatKey *nKey18 = new SatKey(QString("/dev/gpio18"),KEY_18);
    mKeyList.append(nKey18);
    SatKey *nKey19 = new SatKey(QString("/dev/gpio19"),KEY_19);
    mKeyList.append(nKey19);
    SatKey *nKey20 = new SatKey(QString("/dev/gpio20"),KEY_20);
    mKeyList.append(nKey20);
    SatKey *nKey21 = new SatKey(QString("/dev/gpio21"),KEY_21);
    mKeyList.append(nKey21);
    SatKey *nKey22 = new SatKey(QString("/dev/gpio22"),KEY_22);
    mKeyList.append(nKey22);
    SatKey *nKey23 = new SatKey(QString("/dev/gpio23"),KEY_23);
    mKeyList.append(nKey23);
    SatKey *nKey25 = new SatKey(QString("/dev/gpio25"),KEY_25);
    mKeyList.append(nKey25);
    SatKey *nKey24 = new SatKey(QString("/dev/gpio24"),KEY_24);
    mKeyList.append(nKey24);
#if 1
    for(int i = 0;i < mKeyList.size(); i++){
        setGpio(mKeyList.at(i)->getDevFile(),1);
    }
#endif
    //qDebug()<<"[D]Lin >> The KeyScan::init() ThreadID:"<<QThread::currentThreadId();
    //qDebug()<<QString("[D]Lin >> [%1,%2] ThreadID:%3").arg(__FILE__).arg(__LINE__).arg(QThread::currentThreadId());
    mScanTimer = new QTimer();//定时器
    mScanTimer->setInterval(KEYSCAN_TIME);
    connect(mScanTimer,SIGNAL(timeout()),this,SLOT(startScan()));//连接信号槽
    mScanTimer->start();//开启定时器
}

void KeyScan::startScan(){
    //qDebug()<<"[D]Lin >> The KeyScan::startScan() ThreadID:"<<QThread::currentThreadId();
    //qDebug()<<QString("[D]Lin >> [%1,%2] ThreadID:%3").arg(__FILE__).arg(__LINE__).arg(QThread::currentThreadId());
    for(int i = 0; i < mKeyList.size(); i++){
        bool nState;
        int nValue = getGpio(mKeyList.at(i)->getDevFile());
        //printf("[D]Lin >> Key[%s,%d] Value:%d\n",mKeyList.at(i)->getDevFile().toStdString().c_str(),mKeyList.at(i)->getKey(),nValue);
        if(nValue == 0){
            nState = true;
        }else{
            nState = false;
        }
        //qDebug("[D]Lin >> [%s,%d] Just Debug",__FILE__,__LINE__);
        if(nState != mKeyList.at(i)->getState()){
            mKeyList.at(i)->setState(nState);
            printf("[D]Lin >> Key[%s,%d] is %s--[F]\n",mKeyList.at(i)->getDevFile().toStdString().c_str(),
                   mKeyList.at(i)->getKey(),mKeyList.at(i)->getState()?"PRESS":"RELEASE");
            emit keyChangeSignal(mKeyList.at(i)->getKey(),mKeyList.at(i)->getState(),false);
        }else if(mKeyList.at(i)->getState() == true){
            printf("[D]Lin >> Key[%s,%d] is %s--[T]\n",mKeyList.at(i)->getDevFile().toStdString().c_str(),
                   mKeyList.at(i)->getKey(),mKeyList.at(i)->getState()?"PRESS":"RELEASE");
            emit keyChangeSignal(mKeyList.at(i)->getKey(),mKeyList.at(i)->getState(),true);
        }
    }
}


int KeyScan::getGpio(QString nDevFile){
    const char *nFileName = nDevFile.toStdString().c_str();
    int fd = open(nFileName, O_RDWR);
    if(fd<0){
        return -1;
    }
    unsigned char value =0;
    read(fd, &value, 1);
    //printf ( "===[%s, %d] %s===value:%d\n", __FILE__, __LINE__, nFileName , value);
    close(fd);
    //return atoi((char *)&value);//返回该字符的整数
    return ((int)value - 0x30);
}



void KeyScan::setGpioDir(QString nDevFile, int nDir){
    const char *nFileName = nDevFile.toStdString().c_str();
    int fd = open(nFileName, O_RDWR);
    if(fd<0){
        //qDebug("[E]Lin >> [%s,%d] Open gpio error:%s",__FILE__,__LINE__,nFileName);
        return;
    }
    if(nDir == 0){
        write(fd, "O", 1);
    }else{
        write(fd, "I", 1);
    }
    close(fd);
}



void KeyScan::setGpio(QString nDevFile, int nLevel){
    setGpioDir(nDevFile,0);
    const char *nFileName = nDevFile.toStdString().c_str();
    int fd = open(nFileName, O_RDWR);
    if(fd<0){
        //qDebug("[E]Lin >> [%s,%d] Open gpio error:%s",__FILE__,__LINE__,nFileName);
        return;
    }
    if(nLevel){
        write(fd, "O1", 2);
    }
    else{
        write(fd, "O0", 2);
    }
    close(fd);
    setGpioDir(nDevFile,1);
}


