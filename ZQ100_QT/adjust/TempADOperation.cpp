#include "TempADOperation.h"
#include "FileOpe.h"

TempADOperation::TempADOperation(QObject *parent) : QObject(parent)
{

}
//加载温度AD表,将温度AD表加入内存，保存在QMap里
void TempADOperation::loadADTable(){
    QString nFileStr = mSatData->getTmpAdFile();//获取当前档位的tmpad文件
    QFile nFile(nFileStr);
    mSatData->clearAdList();//清除Ad列表
    mSatData->clearDiffList();//清除Diff列表
    mSatData->clearTempList();//清除temp列表
    if(!nFile.open(QIODevice::ReadOnly | QIODevice::Text)){//如果文件不存在，或者打开出错，则初始化程序数据
        QString nStr;
        mSatData->setTabBaseTemp(TEMP_AD_TABLE_TABBASETMP);
        mSatData->setTabNum(TEMP_AD_TABLE_TABNUM);
        for(int i = 1; i <= TEMP_AD_TABLE_TABNUM; i++){//初始化数据
            nStr = QString("temp%1").arg(i);
            mSatData->appendTempList(nStr); //can dui temp list jinxing fuzhi quding wen du biao
            nStr = QString("AD%1").arg(i);
            mSatData->appendAdList(nStr);
            nStr = QString("diff%1").arg(i);
            mSatData->appendDiffList(nStr);
        }
        qDebug("[W]Lin >> Init temp ad table finish!");
        return ;
    }
    QTextStream in(&nFile);
    QString nLineStr = in.readLine();//读入首行
    if(nLineStr != "[TempADTable]"){//第一行
        qDebug("[W]Lin >> The ad table is not correct!");
    }
    while(!in.atEnd()){
        nLineStr = in.readLine();
        nLineStr = nLineStr.simplified();//去掉重复的空格
        QStringList nStrList = nLineStr.split(' ');//根据空格来分割
        if(nStrList.size() == 3){
            if(nStrList.at(0).startsWith("temp")){//Temp开头，则保存在TempMap里
                mSatData->appendTempList(nStrList.at(0),nStrList.at(2).toFloat());
            }else if(nStrList.at(0).startsWith("diff30")){
                mSatData->setDiff30(nStrList.at(2).toFloat());
            }else if(nStrList.at(0).startsWith("AD")){//AD开头
                mSatData->appendAdList(nStrList.at(0),nStrList.at(2).toInt(0,16));
            }else if(nStrList.at(0).startsWith("diff")){
                mSatData->appendDiffList(nStrList.at(0),nStrList.at(2).toFloat());
            }else if(nStrList.at(0).startsWith("TabNum")){//TabNum开头
                mSatData->setTabNum(nStrList.at(2).toInt());
            }else if(nStrList.at(0).startsWith("TabBaseTmp")){//TabBaseTemp开头
                mSatData->setTabBaseTemp(nStrList.at(2).toFloat());
            }else if(nStrList.at(0).startsWith("TabBegAD")){
                mSatData->setTabBegAD(nStrList.at(2).toInt(0,16));
            }else if(nStrList.at(0).startsWith("TabMaxAD")){
                mSatData->setTabMaxAD(nStrList.at(2).toInt(0,16));
            }else if(nStrList.at(0).startsWith("TabMinAD")){
                mSatData->setTabMinAD(nStrList.at(2).toInt(0,16));
            }
        }
    }
    nFile.close();
}

//保存温度AD表,将当前QMap中的温度AD表保存(不替换第一、第二档位的温度AD表),AD需要保存为16进制
void TempADOperation::saveADTable(){
    QString nStrFile = mSatData->getTmpAdNewFile();//获取临时的温度AD文件名
    QFile nFile(nStrFile);
    if(!nFile.open(QIODevice::ReadWrite | QIODevice::Text)){//打开出错，则放弃保存
        qDebug("[E]Lin >> Failed to save the AD table!");
        return ;
    }
    nFile.resize(0);//清空文件
    QTextStream out(&nFile);
    QString nStr;
    out<<"[TempADTable]"<<"\n";//输入第一行
    out<<"TabBaseTmp = "<<QString("%1").arg(mSatData->getTabBaseTemp())<<"\n";//第二行
    if(mSatData->getTabBegAD() == 0){//数据为0时，用字符0，主要是不用4个0来存储
        nStr = "0";
    }else{
        nStr = QString("%1").arg(mSatData->getTabBegAD(),4,16,QLatin1Char('0'));
    }
    out<<"TabBegAD = "<<nStr<<"\n";//第三行
    if(mSatData->getTabMaxAD() == 0){//同上
        nStr = "0";
    }else{
        nStr = QString("%1").arg(mSatData->getTabMaxAD(),4,16,QLatin1Char('0'));
    }
    out<<"TabMaxAD = "<<nStr<<"\n";//第四行
    if(mSatData->getTabMinAD() == 0){
        nStr = "0";
    }else{
        nStr = QString("%1").arg(mSatData->getTabMinAD(),4,16,QLatin1Char('0'));
    }
    out<<"TabMinAD = "<<nStr<<"\n";//第五行
    out<<"TabNum = "<<mSatData->getTabNum()<<"\n";//第六行
    out<<"diff30 = "<<mSatData->getDiff30()<<"\n";
    QList<FloatPair*> *nTempList = mSatData->getTempList();
    if(nTempList == NULL || nTempList->isEmpty()){
        for(int i = 1; i <= TEMP_AD_TABLE_TABNUM; i++){
            QString nTempStr = QString("temp%1 = 0\n").arg(i);
            out<<nTempStr;
        }
    }else{
        for(int i = 0; i < nTempList->size(); i++){
            out<<nTempList->at(i)->getKey()<<" = "<<nTempList->at(i)->getValue()<<"\n";
        }
    }

    QList<IntPair*> *nAdList = mSatData->getAdList();
    if(nAdList == NULL || nAdList->isEmpty()){
        for(int i = 1; i <= TEMP_AD_TABLE_TABNUM; i++){
            QString nAdStr = QString("temp%1 = 0\n").arg(i);
            out<<nAdStr;
        }
    }else{
        for(int i = 0; i < nAdList->size(); i++){
            QString nAdStr;
            if(nAdList->at(i)->getValue() == 0){
                nAdStr = "0";
            }else{
                nAdStr = QString("%1").arg(nAdList->at(i)->getValue(),4,16,QLatin1Char('0'));
            }
            out<<nAdList->at(i)->getKey()<<" = "<<nAdStr<<"\n";
        }
    }

    QList<FloatPair*> *nDiffList = mSatData->getDiffList();
    if(nDiffList == NULL || nDiffList->isEmpty()){
        for(int i = 1; i <= TEMP_AD_TABLE_TABNUM; i++){
            QString nDiffStr = QString("temp%1 = 0\n").arg(i);
            out<<nDiffStr;
        }
    }else{
        for(int i = 0; i < nDiffList->size(); i++){
            out<<nDiffList->at(i)->getKey()<<" = "<<nDiffList->at(i)->getValue()<<"\n";
        }
    }
    nFile.close();//文件关闭
}
//更新温度AD表,将当前温度AD表替换第一、第二档位的温度AD表
void TempADOperation::updateADTable()
{
        countTempAD();
        saveADTable();
        QString nFile1 = mSatData->getTmpAdNewFile();//源文件
        QString nFile2 = mSatData->getTmpAdFile();//目标文件  File1--->File2
        FileOpe::copyFile(nFile1,nFile2);
  //    takeEffectADTable();
}

//计算温度AD表的其余数据,计算温度AD表的TabBegAD、TabMaxAD、TabMinAD
void TempADOperation::countTempAD()
{
   //     if(mSatData->getGearMode() == SatData::GEARONE)
            {
            // temp[1,   2, 3,4, 5, 6, 7, 8, 9, 10,11,12,13,  14, 15, 16, 17, 18, 19, 20]
            // temp[-20,-10,0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,250,300]
            //              0       30          70    90,100,120,140,160,180,200,250,300
            int nAD0 = 0x7dd8;
            int nAD30 = 0x8000;
            int nAD70 = 0x83fe;
            QString nTempStr;
            //获取0度的键,下同
            nTempStr = mSatData->findTempKeyForValue(0);//获取0度Temp列表的Key
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));//0度的AD列表的Key
                int nAd = mSatData->findAdValueForKey(nTempStr);//获取0度的AD值
                if(nAd != 0){
                    nAD0 = nAd;
                }
            }
            nTempStr = mSatData->findTempKeyForValue(30);
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));
                int nAd = mSatData->findAdValueForKey(nTempStr);
                if(nAd != 0){
                    nAD30 = nAd;
                }
            }
            nTempStr = mSatData->findTempKeyForValue(70);
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));
                int nAd = mSatData->findAdValueForKey(nTempStr);
                if(nAd != 0){
                    nAD70 = nAd;
                }
            }
            float nA = ((float)(nAD70 - nAD0)/(-70) + (float)(nAD30 - nAD0)/(30))/(-40);
            float nB = (float)(nAD30 - nAD0)/30 - 30*nA;
            float nC = nAD0;
            for(int i = 1; i <= 11; i++){//算到80度
                float nTemp = mSatData->findTempValueForKey(QString("temp%1").arg(i));
                if(nTemp == FLT_MIN){
                    continue;
                }else if(nTemp == 0){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD0);
                }else if(nTemp == 30){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD30);
                }else if(nTemp == 70){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD70);
                }else{
                    int nAd =(int)(nA*nTemp*nTemp + nB*nTemp + nC);
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAd);
                }
                mSatData->modifyDiffList(QString("diff%1").arg(i),0);
            }
            for(int i = 12; i <= 20; i++){
                if(mSatData->findAdValueForKey(QString("AD%1").arg(i)) <= 0){
                    float nTemp = mSatData->findTempValueForKey(QString("temp%1").arg(i));
                    int nAd =(int)(nA*nTemp*nTemp + nB*nTemp + nC);
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAd);
                }
                mSatData->modifyDiffList(QString("diff%1").arg(i),0);
            }
            mSatData->setTabBegAD(mSatData->findAdValueForKey("AD1"));
            mSatData->setTabMinAD(mSatData->findAdValueForKey("AD1"));
            mSatData->setTabMaxAD(mSatData->findAdValueForKey(QString("AD%1").arg(mSatData->getTabNum())));
            mSatData->setDiff30(0);
        }else{
            // AD[1,2, 3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,  14, 15 ,16 ]
            // AD[0,30,60,180,200,250,300,400,500,600,800,1000,1200]
            //    0 30 60 180 200 250 300 400 500 600 800 1000 1200
            int nAD200 = 0x857a;
            int nAD250 = 0x87f6;
            int nAD300 = 0x8b06;
            QString nTempStr = mSatData->findTempKeyForValue(200);
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));
                int nAd = mSatData->findAdValueForKey(nTempStr);
                if(nAd != 0){
                    nAD200 = nAd;
                }
            }
            nTempStr = mSatData->findTempKeyForValue(250);
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));
                int nAd = mSatData->findAdValueForKey(nTempStr);
                if(nAd != 0){
                    nAD250 = nAd;
                }
            }
            nTempStr = mSatData->findTempKeyForValue(300);
            if(nTempStr != NULL && !nTempStr.isEmpty()){
                nTempStr = QString("AD%1").arg(nTempStr.mid(4));
                int nAd = mSatData->findAdValueForKey(nTempStr);
                if(nAd != 0){
                    nAD300 = nAd;
                }
            }
            float nA = ((float)(nAD300 - nAD200)/(-100) + (float)(nAD250 - nAD200)/(50))/(-60);
            float nB = (float)(nAD250 - nAD200)/50 - 450*nA;
            float nC = nAD200 - 200*200*nA - 200*nB;
            for(int i = 5; i <= 7; i++){
                float nTemp = mSatData->findTempValueForKey(QString("temp%1").arg(i));
                if(nTemp == FLT_MIN){
                    continue;
                }else if(nTemp == 200){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD200);
                }else if(nTemp == 250){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD250);
                }else if(nTemp == 300){
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAD300);
                }else{
                    int nAd = (int)(nA*nTemp*nTemp + nB*nTemp + nC);
                    mSatData->modifyAdList(QString("AD%1").arg(i),nAd);
                }
            }
            for(int i = 1; i <= mSatData->getTabNum(); i++){
                if(i < 5 || i > 7){
                    if(mSatData->findAdValueForKey(QString("AD%1").arg(i)) <= 0){
                        float nTemp = mSatData->findTempValueForKey(QString("temp%1").arg(i));
                        int nAd = (int)(nA*nTemp*nTemp + nB*nTemp + nC);
                        mSatData->modifyAdList(QString("AD%1").arg(i),nAd);
                    }
                }
                mSatData->modifyDiffList(QString("diff%1").arg(i),0);
            }
            mSatData->setTabBegAD(mSatData->findAdValueForKey("AD1"));
            mSatData->setTabMinAD(mSatData->findAdValueForKey("AD1"));
            mSatData->setTabMaxAD(mSatData->findAdValueForKey(QString("AD%1").arg(mSatData->getTabNum())));
            mSatData->setDiff30(0);
        }
}

//生效温度AD表，让AD转温度模块读取新的文件数据(ba lin shi biao ti huan zhuan yong biao)
void TempADOperation::takeEffectADTable(){
    QString nFile1 = mSatData->getTmpAdFile();//源文件
    QString nFile2 = QString("%1%2").arg(COF_DIR).arg(TEMP_AD_TABLE_OTH);//目标文件  File1--->File2
    FileOpe::copyFile(nFile1,nFile2);
}

