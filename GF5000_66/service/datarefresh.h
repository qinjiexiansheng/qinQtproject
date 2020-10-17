#ifndef DATAREFRESH_H
#define DATAREFRESH_H
#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QDebug>
#include "lib/temp.h"
#include "lib/client.h"
#include "model/satdata.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <QByteArray>
#include "uitls/fileope.h"

#include "uitls/operationfield.h"



class TempADOperation : public QObject
{
public:
    TempADOperation(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void loadADTable();
    void saveADTable();
    void updateADTable();
    void countTempAD();
    void takeEffectADTable();
private:
    SatData *mSatData;
};

class KFileOperation : public QObject
{
public:
    KFileOperation(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
    }
    void saveKFile();
    void adjustKFile();
    void clearKFile();
    void queryKFile();
    void modifyKFile();
    void updateKFile();
    void highTempCal();
    void lowTempCal();
private:
    SatData *mSatData;
};

class DataOperation : public QObject
{
public:
    DataOperation(QObject *parent = 0) : QObject(parent){
        mSatData = SatData::initance();
        mTemp = mSatData->getTemp();
#ifdef _SAT_ARM_
        connect_server();//连接获取AD服务
#endif
    }
    void dataRefresh();
    void saveTestData();
    void manualPlay();
    void reference();
    void saveArg();
    void loadArg();

    void saveTestData2();//保存测试数据，中心

    void powerOff();//关机操作

    void savePreferences();
    void obtainPreferences();



    bool backupApp();//打包程序
    bool updateApp(QString nUpdateFile);//更新程序
    bool recoveryApp();//恢复程序



private:
    void backupDir(QString nDirStr);//保存目录信息
    void backupFile(QString nFileStr);//保存文件信息

    bool replaceFiles();//更换文件，将解压后的文件copy到对应的位置

    void fileEncode();//编码文件信息，将文件列表信息存储为二进制
    void fileDecode(QString nLine);//解码文件信息，根据传入的字符串提取文件信息

    bool generateKeyFile();//生成秘钥文件

    bool rebootSystem();//重启系统

    bool judgeState(int nState);//判读状态



private:
    QList<QFileInfo> mFileInfoList;
    SatData *mSatData;
    TEMP *mTemp;
};

#endif // DATAREFRESH_H
