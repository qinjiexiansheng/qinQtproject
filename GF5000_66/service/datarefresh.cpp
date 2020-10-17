#include "datarefresh.h"

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
            mSatData->appendTempList(nStr);
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
void TempADOperation::updateADTable(){
    countTempAD();
    saveADTable();
    QString nFile1 = mSatData->getTmpAdNewFile();//源文件
    QString nFile2 = mSatData->getTmpAdFile();//目标文件  File1--->File2
    FileOpe::copyFile(nFile1,nFile2);
    takeEffectADTable();
}



//计算温度AD表的其余数据,计算温度AD表的TabBegAD、TabMaxAD、TabMinAD
void TempADOperation::countTempAD(){
    if(mSatData->getGearMode() == SatData::GEARONE){
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





//生效温度AD表，让AD转温度模块读取新的文件数据
void TempADOperation::takeEffectADTable(){
    QString nFile1 = mSatData->getTmpAdFile();//源文件
    QString nFile2 = QString("%1%2").arg(COF_DIR).arg(TEMP_AD_TABLE_OTH);//目标文件  File1--->File2
    FileOpe::copyFile(nFile1,nFile2);
    mSatData->getTemp()->updateFile();
}





//保存K值表
void KFileOperation::saveKFile(){
    QString nFile1 = QString("%1%2").arg(ROOT_DIR).arg(K_FILE_DEFAULT);;//源文件,根目录下的K值表
    QString nFile2 = mSatData->getKFile();//目标文件
    FileOpe::copyFile(nFile1,nFile2);
}





//K值表开启或关闭,根据标记来开启/关闭K值表，开启时则加载档位K值表，
//如果没有档位K值表则使用默认K值表。关闭时则加载默认K值表
void KFileOperation::adjustKFile(){
    QString nFile1;//源文件
    QString nFile2;//目标文件   File1-->File2
    nFile2 = QString("%1%2").arg(ROOT_DIR).arg(K_FILE_DEFAULT);//需要更新的文件,根目录下
    if(mSatData->getAdjustOpenSign()){//如果标记为真，则加载档位K值表
        nFile1 = mSatData->getKFile();
        if(!QFile::exists(nFile1)){//如果File2文件不存在，则加载默认K值表
            nFile1 = QString("%1%2").arg(COF_DIR).arg(K_FILE_DEFAULT);//默认K值表
        }
    }else{//标记为假，则加载默认K值表
        nFile1 = QString("%1%2").arg(COF_DIR).arg(K_FILE_DEFAULT);//默认K值表
    }
    FileOpe::copyFile(nFile1,nFile2);
    //更新K值加载，刷新红外图像
    updateKFile();
}





//清除K值表,清除当前档位K值文件，并使用默认K值表
void KFileOperation::clearKFile(){
    QString nFile1 = mSatData->getKFile();//源文件
    QString nFile2;//目标文件 nFile1-->nFile2
    nFile2 = QString("%1%2").arg(ROOT_DIR).arg(K_FILE_DEFAULT);//源文件
    //根据档位来删除对应的K值文件
    if(QFile::exists(nFile1)){//如果原来的文件存在,则删除原文件
        QFile::remove(nFile1);
    }
    //更换默认K值表
    nFile1 = QString("%1%2").arg(COF_DIR).arg(K_FILE_DEFAULT);//默认K值表
    FileOpe::copyFile(nFile1,nFile2);
    //更新K值加载，刷新红外图像
    updateKFile();
}




//查询K值表,查询K值表中的标定状态，用于查询坏点情况
void KFileOperation::queryKFile(){
    QString nStr = QString("%1%2").arg(ROOT_DIR).arg(K_FILE_DEFAULT);//根目录下的K值表
    QByteArray nBa = nStr.toLatin1();
    const char *nK_FILE = nBa.data();
    int fd = open(nK_FILE, O_RDWR);//打开文件
    if( fd < 0 ){
        qDebug("[E]Lin >> Open the k file error!");
        return ;
    }
    int offset=0;
    const short K_FLAG = 0x1000;//已校过的标志
    int x = mSatData->getCalBadPointItemX();
    int y = mSatData->getCalBadPointItemY();
    x = (int)(x*1.0 / SCREEN_WIDTH * PIXEL_WIDTH);//坐标换算，记得乘1.0，不然无论怎样都会变为0
    y = (int)(y*1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT);
    short K_STATE;
    offset = y*368+x;//定位
    lseek(fd, offset*2, SEEK_SET);//乘2是因为一个标记占两位
    if(read(fd,&K_STATE,sizeof(K_FLAG)) > 0){//读取成功
        if(K_STATE == K_FLAG){//与坏点标记相同则表示该点校正过
            mSatData->setCalBadPointState(true);
        }else{
            mSatData->setCalBadPointState(false);
        }
    }
    close(fd);
}





//修改K值表，修改K值表中的状态，用于校坏点
void KFileOperation::modifyKFile(){
    QString nStr = QString("%1%2").arg(ROOT_DIR).arg(K_FILE_DEFAULT);//根目录下的K值表
    QByteArray nBa = nStr.toLatin1();//
    const char *nK_FILE = nBa.data();//转为char*类型
    int fd = open(nK_FILE, O_RDWR);
    if( fd < 0 ) {
        qDebug("[E]Lin >> Open the k file error!");
        return ;
    }
    int offset=0;
    const short K_FLAG = 0x1000;
    int x = mSatData->getCalBadPointItemX();
    int y = mSatData->getCalBadPointItemY();
    x = (int)(x*1.0 / SCREEN_WIDTH * PIXEL_WIDTH);//映射到底层的坐标，屏幕坐标和底层坐标不一致
    y = (int)(y*1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT);
    offset = y*368+x;
    lseek(fd, offset*2, SEEK_SET);
    write(fd, &K_FLAG, sizeof(K_FLAG));
    mSatData->setCalBadPointState(true);
    close(fd);
    //需要更新一次底层K值表，主要时更新红外图像
    updateKFile();
    //将修改后的K值表保存（根据档位）
    saveKFile();
}




//非均匀校正（低温） ： LowTempCal
void KFileOperation::lowTempCal(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam lowcal 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    SetKcal(1);
#endif
#endif
}




//非均匀校正（高温） ： HighTempCal
void KFileOperation::highTempCal(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam highcal 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    SetKcal(2);
#endif
#endif
}





//刷新K值表,主要是刷新红外图像，一般在应用层改变了K值表就需要刷新一下，红外图像才会变化
void KFileOperation::updateKFile(){
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam k_reload_flag 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 1
    SetReloadK(1);
#endif
#endif
}





//数据刷新,用于刷新用到的数据，如AD，极点AD，极点坐标，DET等
void DataOperation::dataRefresh(){
#ifdef _SAT_ARM_
#if 0
    //以FIFO的形式更新数据
    /*======================================
      responsefifo
      26.79  8588  1720 2200 380 35  *  *  *
      1、 temp(f)Sensor值
      2、 temp/Det
      3、 Gsk
      4、 Fid
      5、 tInt
      6、 Gain
      7、 设备电量(0 < * <= 100)
      8、 GlobalAD 全局14位AD
      9、 PointInitialAD
      ======================================*/
#if 0
    //第一种实现方式，旧版本的方式，通过FIFO通信，出现的问题：在执行system时程序挂，且没有提示
    system("echo getDetectorInfo > /tmp/eventFifo &");//执行系统命令
#endif
#if 0
    //第二种实现方式，通过FIFO通信，和system出现同样的问题
    FILE * fp;
    fp = popen("echo getDetectorInfo > /tmp/eventFifo &","r");
    pclose(fp);
#endif
#if 0
    //第三种实现方式，也是FIFO通信，手动写入FIFO文件，出现的问题：打档和更新数据一起写入后，大概率造成更新数据的命令
    //没有被识别，然后驱动没有写返回数据的FIFO文件，导致程序阻塞，小概率造成打档命令丢失
    int fd = 0;
    char w_buf[100];
    int nwrite;
    fd=open("/tmp/eventFifo",O_WRONLY|O_NONBLOCK);
    if(fd==-1){
        if(errno==ENXIO){
            printf("open error; no reading process\n");
        }
    }
    strcpy(w_buf,"getDetectorInfo\n");
    if((nwrite=write(fd,w_buf,100))==-1){
        if(errno==EAGAIN){
            printf("The FIFO has not been read yet.Please try later\n");
        }
    }else{
    }
    close(fd);
#endif
#if 0
    //非阻塞读取获取数据的FIFO文件，读到的数据一直为空
    memset(w_buf,'\0',sizeof(w_buf));
    fd=open("/tmp/responseFifo",O_RDONLY|O_NONBLOCK);
    if(fd==-1){
        if(errno==ENXIO){
            printf("open error; no write process\n");
        }
    }else{

        nwrite = read(fd,w_buf,100);
        if(nwrite == -1){
            if(errno == EAGAIN){
                printf("The FIFO has not been write yet.Please try later\n");
            }
        }else{

        }
        printf("[D]Lin >> read [%s] from the FIFO\n",w_buf);
        close(fd);

    }
#endif
#if 0
    //阻塞读取FIFO文件，会因为服务器没有写FIFO文件而被阻塞
    QFile nFile(QString("/tmp/responseFifo"));//打开该文件
    if(!nFile.open(QIODevice::ReadOnly)){
        qDebug("[E]Lin >> ResponseFifo Error");
        return ;
    }
    QTextStream in(&nFile);
    QString nLine = in.readLine();
    if(nLine.isEmpty()){
        qDebug("[E]Lin >> Read Line Error");
        return ;
    }
    nFile.close();
    qDebug("[D]Lin >> Read from the fifo:[%s]",nLine.toStdString().c_str());
    QStringList nLines = nLine.split(" ",QString::SkipEmptyParts);//空格分割
    if(nLines.size() < 9){
        qDebug("[E]Lin >> The Number For Lines is Error");
        return ;
    }
    if(!nLines.at(0).isEmpty()){
        float nSensor = nLines.at(0).toFloat();
        mSatData->setSensor(nSensor);
    }else{
        qDebug("[E]Lin >> The Sensor Value is Error");
    }
    if(!nLines.at(1).isEmpty()){
        int nDet = nLines[1].toInt();
        mSatData->setDet(nDet);
    }else{
        qDebug("[E]Lin >> The Det Value is Error");
    }
    if(!nLines.at(2).isEmpty()){
        int nGsk = nLines[2].toInt();
        mSatData->setGsk(nGsk);
    }else{
        qDebug("[E]Lin >> The Gsk Value is Error");
    }

    if(!nLines.at(3).isEmpty()){
        int nFid = nLines[3].toInt();
        mSatData->setFid(nFid);
    }else{
        qDebug("[E]Lin >> The Fid Value is Error");
    }
    if(!nLines.at(4).isEmpty()){
        int nInt = nLines[4].toInt();
        mSatData->setInt(nInt);
    }else{
        qDebug("[E]Lin >> The Int Value is Error");
    }
    if(!nLines.at(5).isEmpty()){
        int nGain = nLines[5].toInt();
        int n = ~0;
        nGain = nGain & n;
        nGain = nGain >> 4;
        mSatData->setGain(nGain);
    }else{
        qDebug("[E]Lin >> The Gain Value is Error");
    }
    if(!nLines.at(6).isEmpty()){
        float nBattery = nLines[6].toFloat();
        mSatData->setBattery(nBattery);
    }else{
        qDebug("[E]Lin >> The Battery Value is Error");
    }
    if(!nLines.at(7).isEmpty()){
        int nGlobalAD = nLines[7].toInt();
        mSatData->setGlobalAD(nGlobalAD);
    }else{
        qDebug("[E]Lin >> The GlobalAD Value is Error");
    }
    if(!nLines.at(8).isEmpty()){
        int nPointInitialAD = nLines[8].toInt();
        mSatData->setPointInitialAD(nPointInitialAD);
    }else{
        qDebug("[E]Lin >> The PointInitialAD Value is Error");
    }
#endif
#endif
#if 1
    //更新数据，以socket通信
    int nDet = getDET();
    float nSensor = getSENSOR();
    //qDebug("[D]Lin >> The Sensor:%f",nSensor);
#if 0
    //是否更新FID、GSK、GAIN、TINT
    int nFid = getFID();
    int nGsk = getGSK();
    int nGain = getGAIN();
    int n = ~0;
    nGain = nGain & n;
    nGain = nGain >> 4;
    int nInt = getTINT();
#endif
    int nBattery = getBatteryV();
    bool nBatteryState = getBatteryStatus();
    if(nBatteryState && nBattery < BATTERY_SHOTDOWN){//关机操作
        //显示关机画面
        mSatData->setTurnOffSign(true);
        //关机操作
        this->powerOff();
    }
    int nGlobalAD = getGlobalADave();
    int nPointInitialAD = getDotOriginalAD();
    //设置数据类数据
    mSatData->setDet(nDet);
    mSatData->setSensor(nSensor);
#if 0
    mSatData->setFid(nFid);
    mSatData->setGsk(nGsk);
    mSatData->setGain(nGain);
    mSatData->setInt(nInt);
#endif
    mSatData->setBattery(nBattery);
    mSatData->setBatteryState(nBatteryState);
    mSatData->setGlobalAD(nGlobalAD);
    mSatData->setPointInitialAD(nPointInitialAD);
#endif
    int nMaxX,nMaxY;
    int nMinX,nMinY;
    ushort nMaxAd,nMinAd;
    float nMaxT,nMinT;
#if 1
    mTemp->setSensor(mSatData->getSensor());
    int nCenterX = mSatData->getCenterX();
    int nCenterY = mSatData->getCenterY();
    nCenterX = (int)(nCenterX * 1.0 / SCREEN_WIDTH * PIXEL_WIDTH);
    nCenterY = (int)(nCenterY * 1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT);
    int nCenterAd = (int)getAD(nCenterX, nCenterY);//获取中心点的AD值
    float nCenterTemp = mTemp->AdToTemp(nCenterAd).temp;//转成中心温度
    mSatData->setCenterAd(nCenterAd);//保存
    mSatData->setCenterTemp(nCenterTemp);//保存
    getMaxMin(0,0,368,288,&nMaxX,&nMaxY,&nMaxAd,&nMinX,&nMinY,&nMinAd);//获取整个区域的极点AD及坐标
    nMaxX = (int)(nMaxX * 1.0 / PIXEL_WIDTH * SCREEN_WIDTH);
    nMaxY = (int)(nMaxY * 1.0 / PIXEL_HEIGHT * SCREEN_HEIGHT);
    nMinX = (int)(nMinX * 1.0 / PIXEL_WIDTH * SCREEN_WIDTH);
    nMinY = (int)(nMinY * 1.0 / PIXEL_HEIGHT * SCREEN_HEIGHT);

    mSatData->setMaxPointX(nMaxX);//保存
    mSatData->setMaxPointY(nMaxY);//保存
    mSatData->setMinPointX(nMinX);//保存
    mSatData->setMinPointY(nMinY);//保存
    nMaxT = mTemp->AdToTemp(nMaxAd).temp;//转温度
    nMinT = mTemp->AdToTemp(nMinAd).temp;//转温度
    mSatData->setMaxTemp(nMaxT);
    mSatData->setMinTemp(nMinT);
    //qDebug("[D]Lin >> AD:%x,Max AD:%x,Min AD:%x",nCenterAd,nMaxAd,nMinAd);
    //qDebug("[D]Lin >> Center Temp:%f,Max Temp:%f,Min Temp:%f",nCenterTemp,nMaxT,nMinT);
    //qDebug("[D]Lin >> Max[%d,%d,%f],Min[%d,%d,%f]",mSatData->getMaxPointX(),mSatData->getMaxPointY(),mSatData->getMaxTemp(),mSatData->getMinPointX(),mSatData->getMinPointY(),mSatData->getMinTemp());
#endif
#if 1
    if(mSatData->getWindowDisplay() == SatData::CALBADPOINT){//如果处于校坏点模式，则更新坏点的AD值
        int nBadPointX = mSatData->getCalBadPointItemX();
        int nBadPointY = mSatData->getCalBadPointItemY();
        nBadPointX = nBadPointX * 1.0 / SCREEN_WIDTH * PIXEL_WIDTH;
        nBadPointY = nBadPointY * 1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT;
        getMaxMin(nBadPointX-5,nBadPointY-5,3,3,&nMaxX,&nMaxY,&nMaxAd,&nMinX,&nMinY,&nMinAd);
        int nBadPointAD = (int)((nMaxAd+nMinAd)/2);
        mSatData->setCalBadPointAD(nBadPointAD);
    }else if(mSatData->getWindowDisplay() == SatData::COLLECTDATA){//如果处于采集数据模式，则更新采集框中的AD值
        int nCollectDataX1 = mSatData->getCollectDataItemX1();
        int nCollectDataX2 = mSatData->getCollectDataItemX2();
        int nCollectDataY1 = mSatData->getCollectDataItemY1();
        int nCollectDataY2 = mSatData->getCollectDataItemY2();
        nCollectDataX1 = nCollectDataX1*1.0 / SCREEN_WIDTH * PIXEL_WIDTH;
        nCollectDataX2 = nCollectDataX2*1.0 / SCREEN_WIDTH * PIXEL_WIDTH;
        nCollectDataY1 = nCollectDataY1*1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT;
        nCollectDataY2 = nCollectDataY2*1.0 / SCREEN_HEIGHT * PIXEL_HEIGHT;
        getMaxMin(nCollectDataX1-5,nCollectDataY1-35,70,70,&nMaxX,&nMaxY,&nMaxAd,&nMinX,&nMinY,&nMinAd);
        int nCollectDataAD1 = (int)nMaxAd;
        mSatData->setCollectDataItemAD1(nCollectDataAD1);
        getMaxMin(nCollectDataX2-5,nCollectDataY2-35,70,70,&nMaxX,&nMaxY,&nMaxAd,&nMinX,&nMinY,&nMinAd);
        int nCollectDataAD2 = (int)nMaxAd;
        mSatData->setCollectDataItemAD2(nCollectDataAD2);
    }
#endif
#endif
#ifdef _SAT_XNJ_
    mSatData->setCenterAd(mSatData->getCenterAd());
    mTemp->setSensor(mSatData->getSensor());
    float nCenterTemp = mTemp->AdToTemp(mSatData->getCenterAd()).temp;
    //qDebug("[D]Lin >> SatControl End");


    mSatData->setCenterTemp(nCenterTemp);
    mSatData->setMaxPointX(mSatData->getMaxPointX()+qrand()%10-5);
    mSatData->setMaxPointY(mSatData->getMaxPointY()+qrand()%10-5);
    mSatData->setMaxTemp(mSatData->getMaxTemp()+qrand()%10-5);
    mSatData->setMinPointX(mSatData->getMinPointX()+qrand()%10-5);
    mSatData->setMinPointY(mSatData->getMinPointY()+qrand()%10-5);
    mSatData->setMinTemp(mSatData->getMinTemp() - qrand()%10-5);
    mSatData->setSensor(mSatData->getSensor()+0.01);
    mSatData->setDet(mSatData->getDet()+1);
    mSatData->setCalBadPointAD(mSatData->getCalBadPointAD()+1);
    mSatData->setCollectDataItemAD1(mSatData->getCollectDataItemAD1()+1);
    mSatData->setCollectDataItemAD2(mSatData->getCollectDataItemAD2()+2);
    mSatData->setGlobalAD(mSatData->getGlobalAD()+1);
    mSatData->setPointInitialAD(mSatData->getPointInitialAD()+1);
#endif
}





//保存测试数据，将当前的时间，FID，AD等数据保存，用于分析
//以下为保存格式,其中DET和AD需要保存为16进制字符
//2018-05-02-10:53:43,2200,1720,2,380,8000,25.3,8252
//时间，FID，GSK，GAIN，INT，DET，Sensor，AD
void DataOperation::saveTestData(){
    QString nFileStr = mSatData->getTestFile();
    if(nFileStr.isEmpty()){
        nFileStr = QString("%1%2").arg(LOG_DIR).arg(QString(DATA_FILE).arg(1));
    }
    QFile nFile(nFileStr);//打开保存测试数据的文件
    if(!nFile.open(QIODevice::ReadWrite | QIODevice::Append)){
        qDebug("[D]Lin >> Save test data error!");
        return ;
    }
    QTextStream out(&nFile);
    //"yyyy-MM-dd-hh:mm:ss"
    QDateTime nCurrentTime = QDateTime::currentDateTime();//获取当前时间
    QString nDate = nCurrentTime.toString("yyyy-MM-dd");//格式画年月日
    QString nTime = nCurrentTime.toString("hh:mm:ss");//格式化时分秒
    int nFid        = mSatData->getFid();
    int nGsk        = mSatData->getGsk();
    int nGain       = mSatData->getGain();
    int nInt;
    if(mSatData->getAutoIntSign()){
        nInt = mSatData->getAutoInt();
    }else{
        nInt = mSatData->getInt();
    }
    int nDet        = mSatData->getDet();
    float nSensor  = mSatData->getSensor();
    int nAD1      = mSatData->getCollectDataItemAD1();
    int nAD2     = mSatData->getCollectDataItemAD2();
    int nAD14 = mSatData->getGlobalAD();
    QString nStr = "%1-%2,%3,%4,%5,%6,%7,%8,%9,%10,%11\n";
    nStr =  nStr.arg(nDate)
            .arg(nTime)
            .arg(nFid)
            .arg(nGsk)
            .arg(nGain)
            .arg(nInt)
            .arg(nDet,4,16,QLatin1Char('0'))
            .arg(QString::number(nSensor,'f',2))
            .arg(nAD1,4,16,QLatin1Char('0'))
            .arg(nAD2,4,16,QLatin1Char('0'))
            .arg(nAD14,4,16,QLatin1Char('0'));
    out<<nStr;
    nFile.close();
}



//保存测试数据，将当前的时间，FID，AD等数据保存，用于分析
//以下为保存格式,其中DET和AD需要保存为16进制字符
//2018-05-02-10:53:43,2200,1720,2,380,8000,25.3,8252
//时间，FID，GSK，GAIN，INT，DET，Sensor，AD
void DataOperation::saveTestData2(){
    QString nFileStr = mSatData->getNTestFile();
    if(nFileStr.isEmpty()){
        nFileStr = QString("%1%2").arg(LOG_DIR).arg(QString(DATA_FILE_TWO).arg(1));
    }
    QFile nFile(nFileStr);//打开保存测试数据的文件
    if(!nFile.open(QIODevice::ReadWrite | QIODevice::Append)){
        qDebug("[D]Lin >> Save test data error!");
        return ;
    }
    QTextStream out(&nFile);
    //"yyyy-MM-dd-hh:mm:ss"
    QDateTime nCurrentTime = QDateTime::currentDateTime();//获取当前时间
    QString nDate = nCurrentTime.toString("yyyy-MM-dd");//格式画年月日
    QString nTime = nCurrentTime.toString("hh:mm:ss");//格式化时分秒
    int nFid        = mSatData->getFid();
    int nGsk        = mSatData->getGsk();
    int nGain       = mSatData->getGain();
    int nInt;
    if(mSatData->getAutoIntSign()){
        nInt = mSatData->getAutoInt();
    }else{
        nInt = mSatData->getInt();
    }
    int nDet        = mSatData->getDet();
    float nSensor  = mSatData->getSensor();
    int nAD1      = mSatData->getCollectDataItemAD1();
    int nAD2     = mSatData->getCollectDataItemAD2();
    int nAD14 = mSatData->getGlobalAD();
    int nADCenter = mSatData->getCenterAd();
    float nTemp = mSatData->getCenterTemp();
    QString nStr = "%1-%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13\n";
    nStr =  nStr.arg(nDate)
            .arg(nTime)
            .arg(nFid)
            .arg(nGsk)
            .arg(nGain)
            .arg(nInt)
            .arg(nDet,4,16,QLatin1Char('0'))
            .arg(QString::number(nSensor,'f',2))
            .arg(nAD1,4,16,QLatin1Char('0'))
            .arg(nAD2,4,16,QLatin1Char('0'))
            .arg(nAD14,4,16,QLatin1Char('0'))
            .arg(nADCenter,4,16,QLatin1Char('0'))
            .arg(QString::number(nTemp, 'f', 1));
    out<<nStr;
    nFile.close();
}



//关机操作
void DataOperation::powerOff(){
    //解决突然断电sd卡图片数据丢失问题，需结合关机命令
    ::system("busybox fuser -km /root/sdcard");
    ::system("umount /root/sdcard");
    //设置gpio51文件为1来实现关机操作
    const char *nFileName = "/dev/gpio51";
    int fd = open(nFileName, O_RDWR);
    if(fd<0){
        //qDebug("[E]Lin >> [%s,%d] Open gpio error:%s",__FILE__,__LINE__,nFileName);
        return;
    }
    write(fd, "O", 1);
    close(fd);
    fd = -1;
    fd = open(nFileName, O_RDWR);
    if(fd<0){
        //qDebug("[E]Lin >> [%s,%d] Open gpio error:%s",__FILE__,__LINE__,nFileName);
        return;
    }
    write(fd, "O1", 2);
    close(fd);
}



//保存参数
void DataOperation::savePreferences(){
    QString nFileStr = QString("%1%2").arg(COF_DIR).arg(App_Param);
    QFile nFile(nFileStr);//打开保存测试数据的文件
    if(!nFile.open(QIODevice::ReadWrite)){
        qDebug("[E]Lin >> The save preferences is error!");
        return ;
    }
    QTextStream out(&nFile);
    out<<"[App_Preferences]\n";
    out<<QString("AutoShutterSign = %1\n").arg(mSatData->getAutoShutterSign()?1:0);//自动打档标记
    out<<QString("AutoShutterTime = %1\n").arg(mSatData->getAutoShutterTime());//自动打档时间
    out<<QString("SerialNumber = %1\n").arg(mSatData->getSerialNumber());//序列号
    out<<QString("OutFactoryYear = %1\n").arg(mSatData->getOutFactoryYear());//出厂年份
    out<<QString("OutFactoryMonth = %1\n").arg(mSatData->getOutFactoryMonth());//出厂月份
    out<<QString("OutFactoryDay = %1\n").arg(mSatData->getOutFactoryDay());//出厂日
    out<<QString("GearMode = %1\n").arg((int)mSatData->getGearMode());//档位模式
    out<<QString("InfraredMode = %1\n").arg((int)mSatData->getInfraredMode());//红外模式
    out<<QString("DenoiseMode = %1\n").arg((int)mSatData->getDenoiseMode());//降噪模式
    out<<QString("AlarmTemp = %1\n").arg(mSatData->getAlarmTemp());//报警温度（设备）
    out<<QString("RedTemp = %1\n").arg(mSatData->getRedTemp());//红色温度
    out<<QString("OrangeTemp = %1\n").arg(mSatData->getOrangeTemp());//橙色温度
    out<<QString("Dis = %1\n").arg(mSatData->getDis());//距离
    out<<QString("Emiss = %1\n").arg(mSatData->getEmiss());//辐射率
    out<<QString("EnvTemp = %1\n").arg(mSatData->getEnvTemp());//环境温度
    out<<QString("RelHum = %1\n").arg(mSatData->getRelHum());//相对湿度
    out<<QString("RefTemp = %1\n").arg(mSatData->getRefTemp());//反射温度
    out<<QString("CorTemp = %1\n").arg(mSatData->getCorTemp());//修正温度
    out<<QString("LengthUnit = %1\n").arg(mSatData->getLengthUnit());//长度单位
    out<<QString("TempUnit = %1\n").arg(mSatData->getTempUnit());//温度单位
    out<<QString("AutoSavePictureTime = %1\n").arg(mSatData->getAutoSavePictureTime());//自动保存图片时间
    out<<QString("AutoSavePictureSign = %1\n").arg(mSatData->getAutoSavePictureSign());//自动保存图片开关标记






    nFile.close();
}



//获取参数
void DataOperation::obtainPreferences(){
    QString nFileStr = QString("%1%2").arg(COF_DIR).arg(App_Param);//参数文件名
    QFile nFile(nFileStr);
    if(!nFile.open(QIODevice::ReadOnly | QIODevice::Text)){//如果文件不存在，或者打开出错，则初始化程序数据
        qDebug("[W]Lin >> Not exist the app_preferences file!");
        return ;
    }
    QTextStream in(&nFile);
    QString nLineStr = in.readLine();//读入首行
    if(nLineStr != "[App_Preferences]"){//第一行
        qDebug("[W]Lin >> The app_preferences file format is wrong");
    }
    while(!in.atEnd()){
        nLineStr = in.readLine();
        nLineStr = nLineStr.simplified();//去掉重复的空格
        QStringList nStrList = nLineStr.split(' ');//根据空格来分割
        if(nStrList.size() == 3){
            if(nStrList.at(0).startsWith("AutoShutterSign")){//自动打档开关标记
                bool nSign = nStrList.at(2).toInt();
                mSatData->setAutoShutterSign(nSign);
            }else if(nStrList.at(0).startsWith("AutoShutterTime")){//自动打档时间间隔
                int nTime = nStrList.at(2).toInt();
                mSatData->setAutoShutterTime(nTime);
            }else if(nStrList.at(0).startsWith("SerialNumber")){
                int nNumber = nStrList.at(2).toInt();
                mSatData->setSerialNumber(nNumber);
            }else if(nStrList.at(0).startsWith("OutFactoryYear")){
                int nYear = nStrList.at(2).toInt();
                mSatData->setOutFactoryYear(nYear);
            }else if(nStrList.at(0).startsWith("OutFactoryMonth")){
                int nMonth = nStrList.at(2).toInt();
                mSatData->setOutFactoryMonth(nMonth);
            }else if(nStrList.at(0).startsWith("OutFactoryDay")){
                int nDay = nStrList.at(2).toInt();
                mSatData->setOutFactoryDay(nDay);
            }else if(nStrList.at(0).startsWith("GearMode")){
                SatData::GearEnum nEnum = (SatData::GearEnum)nStrList.at(2).toInt();
                mSatData->setGearMode(nEnum);
            }else if(nStrList.at(0).startsWith("InfraredMode")){
                SatData::InfraredEnum nEnum = (SatData::InfraredEnum)nStrList.at(2).toInt();
                mSatData->setInfraredMode(nEnum);
            }else if(nStrList.at(0).startsWith("DenoiseMode")){
                SatData::DenoiseEnum nEnum = (SatData::DenoiseEnum)nStrList.at(2).toInt();
                mSatData->setDenoiseMode(nEnum);
            }else if(nStrList.at(0).startsWith("AlarmTemp")){
                float nTemp = nStrList.at(2).toFloat();
                mSatData->setAlarmTemp(nTemp);
            }else if(nStrList.at(0).startsWith("RedTemp")){
                float nTemp = nStrList.at(2).toFloat();
                mSatData->setRedTemp(nTemp);
            }else if(nStrList.at(0).startsWith("OrangeTemp")){
                float nTemp = nStrList.at(2).toFloat();
                mSatData->setOrangeTemp(nTemp);
            }else if(nStrList.at(0).startsWith("Dis")){
                float nDis = nStrList.at(2).toFloat();
                mSatData->setDis(nDis);
            }else if(nStrList.at(0).startsWith("Emiss")){
                float nEmiss = nStrList.at(2).toFloat();
                mSatData->setEmiss(nEmiss);
            }else if(nStrList.at(0).startsWith("EnvTemp")){
                float nEnvTemp = nStrList.at(2).toFloat();
                mSatData->setEnvTemp(nEnvTemp);
            }else if(nStrList.at(0).startsWith("RelHum")){
                float nRelHum = nStrList.at(2).toFloat();
                mSatData->setRelHum(nRelHum);
            }else if(nStrList.at(0).startsWith("RefTemp")){
                float nRefTemp = nStrList.at(2).toFloat();
                mSatData->setRefTemp(nRefTemp);
            }else if(nStrList.at(0).startsWith("CorTemp")){
                float nCorTemp = nStrList.at(2).toFloat();
                mSatData->setCorTemp(nCorTemp);
            }else if(nStrList.at(0).startsWith("LengthUnit")){
                bool nUnit = nStrList.at(2).toInt();
                mSatData->setLengthUnit(nUnit);
            }else if(nStrList.at(0).startsWith("TempUnit")){
                bool nUnit = nStrList.at(2).toInt();
                mSatData->setTempUnit(nUnit);
            }else if(nStrList.at(0).startsWith("AutoSavePictureTime")){
                int nTime = nStrList.at(2).toInt();
                mSatData->setAutoSavePictureTime(nTime);
            }else if(nStrList.at(0).startsWith("AutoSavePictureSign")){
                bool nSign = nStrList.at(2).toInt();
                mSatData->setAutoSavePictureSign(nSign);
            }
        }
    }
    nFile.close();

}



bool DataOperation::updateApp(QString nUpdateFile){
    //提示正在更新
    mSatData->setUpdateAppState(Update_App_State_Updating);
    //判断文件是否存在
    if(!QFile::exists(nUpdateFile)){
        //更新失败，更新包找不到
        mSatData->setUpdateAppState(Update_App_State_Update_Failure);
        return false;
    }
    //秘钥文件
    if(!generateKeyFile()){
        //生成秘钥失败
        mSatData->setUpdateAppState(Update_App_State_Update_Failure);
        return false;
    }
    //解压压缩包
    if(!QFile::exists(UpdateScript)){
        mSatData->setUpdateAppState(Update_App_State_Update_Failure);
        return false;
    }
    QString nCommand = QString(UpdateScript) + " decompress " + nUpdateFile + "";
    int nStatus = ::system(nCommand.toStdString().c_str());
    if(!judgeState(nStatus)){
        //解压程序包出错
        mSatData->setUpdateAppState(Update_App_State_Update_Failure);
        return false;
    }
    //替换文件
    if(!replaceFiles()){
        //替换文件失败
        mSatData->setUpdateAppState(Update_App_State_Update_Failure);
        return false;
    }
    //所有的准备工作成功
    mSatData->setUpdateAppState(Update_App_State_Update_Reboot);
    //重启
    return rebootSystem();
}


//备份打包方法
bool DataOperation::backupApp(){
    //提示正在备份
    mSatData->setUpdateAppState(Update_App_State_Backuping);
    //生成秘钥文件
    if(!generateKeyFile()){
        //生成秘钥失败
        mSatData->setUpdateAppState(Update_App_State_Backup_Failure);
        return false;
    }
    //生成脚本
    QStringList nLines;
    nLines.append("#!/bin/sh");
    nLines.append("#This script is generated when you click Backup button.");
    nLines.append("");
    //读取备份文件
    QFile nFile(BackupListFile);
    if(!nFile.exists()){//不存在则生成
        if(nFile.open(QIODevice::WriteOnly)){
            QTextStream out(&nFile);
#ifdef _SAT_ARM_
            out<<"/root/Qt4.5.3/GF5000/GF5000";
#endif
#ifdef _SAT_XNJ_
            out<<"/home/sat/Sat/Root/GF5000/backup-test/GF50000919a1\n";
            out<<"/home/sat/Sat/Root/GF5000/backup-test/GF5000/";
#endif
            nFile.close();
        }
    }//存在则继续执行以下操作
    //读取备份文件列表，添加命令到字符串列表
    if(nFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&nFile);
        //判断目录--不存在则创建目录，存在则删除目录里的所有文件
        nLines.append("if [ ! -d \"" + QString(BackupDataDir) + "\" ];then");
        nLines.append("mkdir " + QString(BackupDataDir));
        nLines.append("else");
        nLines.append("rm " + QString(BackupDataDir) + "* -rf");
        nLines.append("fi");
        //判断目录--end--
        //读取文件内柔，将文件内容里的每一个文件加入脚本列表
        while(!in.atEnd()){
            QString nStr = in.readLine();
            QFileInfo nFileInfo(nStr);
            if(nStr.right(1) == "/" || nFileInfo.isDir()){
                backupDir(nStr);//保存目录信息
                nLines.append("cp " + nStr + " " + QString(BackupDataDir) + " -rf");
                nLines.append("");
            }else{
                backupFile(nStr);//保存文件信息
                nLines.append("cp " + nStr + " " + QString(BackupDataDir) + " -rf");
                nLines.append("");
            }
        }
        nFile.close();
        fileEncode();//文件编码，将文件列表信息写入文件
        //其他操作
        nLines.append("mv " + QString("%1%2").arg(BackupDir).arg(BackupInfoDat) + " " + QString(BackupDataDir) + " -f");//复制文件信息文件到打包目录
        nLines.append("cp " + QString(BackupListFile) + " " + QString(BackupDataDir) + " -rf");//复制备份列表文件到备份目录
        nLines.append("cd " + QString(BackupDataDir));//进入目录
        nLines.append("tar zcvf " + QString(BackupTgzFile) + " ./*");//打包目录下的所有文件
        nLines.append("chmod +x " + QString(BackupTgzFile));//增加打包文件权限
        nLines.append("mv " + QString(BackupTgzFile) + " ../ -f");//移动包文件到上一目录
        nLines.append("rm ../" + QString(BackupGpgFile) + " -rf");//删除上一目录的程序备份包
        //======gpg加密压缩包,现在先直接改名===
        nLines.append("cp ../" + QString(BackupTgzFile) + " ../" + QString(BackupGpgFile));
        //=============================
        nLines.append("chmod +x ../" + QString(BackupGpgFile));//加权限
        nLines.append("rm ../" + QString(BackupTgzFile) + " -rf");//删除加密前的打包文件
        nLines.append("rm " + QString(BackupDataDir) + " -rf");//删除备份文件目录内容
        //=========(备份完成,以前时在shell里用qcop来通知备份完成)====
    }else{
        //备份失败,backup.file文件打开时失败（情况很少见）
        mSatData->setUpdateAppState(Update_App_State_Backup_Failure);
        return false;
    }
    nLines.append("rm " + QString("%1%2").arg(BackupDir).arg(BackupScript));//删除备份脚本
    //删除加密秘钥文件
    nLines.append("rm " + QString("%1%2").arg(BackupDir).arg(KeyFile));
    nLines.append("rm " + QString(BackupListFile));//删除文件列表
    nLines.append("exit 0");//正常结束程序
    //将字符串列表写入脚本文件
    QFile nFileScript(QString("%1%2").arg(BackupDir).arg(BackupScript));
    nFileScript.remove();//存在则先删除
    if(nFileScript.open(QIODevice::WriteOnly)){
        QTextStream in(&nFileScript);
        for(QStringList::Iterator nIt = nLines.begin(); nIt != nLines.end(); nIt++){
            in << *nIt << "\n";//写入脚本文件
        }
        nFileScript.close();
    }else{
        //备份失败，backup.sh脚本文件无法创建
        mSatData->setUpdateAppState(Update_App_State_Backup_Failure);
        return false;//失败
    }
    //给脚本加权限
    QString nCommandStr = "chmod +x " + QString(QString("%1%2").arg(BackupDir).arg(BackupScript));//增加可执行权限
    int nStatus;
    nStatus = ::system(nCommandStr.toStdString().c_str());
    if(!judgeState(nStatus)){
        //加权限失败
        mSatData->setUpdateAppState(Update_App_State_Backup_Failure);
        return false;
    }
    //执行脚本
    nCommandStr = QString(QString("%1%2").arg(BackupDir).arg(BackupScript)) + "&";//执行脚本操作
    nStatus = ::system(nCommandStr.toStdString().c_str());
    if(!judgeState(nStatus)){
        //脚本并没有exit 0结束
        mSatData->setUpdateAppState(Update_App_State_Backup_Failure);
        return false;
    }
    //============备份完成(以前用qcop通知完成)=========
    //备份成功
    mSatData->setUpdateAppState(Update_App_State_Backup_Success);
    return true;
}




bool DataOperation::recoveryApp(){
    //====解压备份程序包
    QString nRecoveryFile = QString("%1%2").arg(BackupDir).arg(BackupGpgFile);
    if(!QFile::exists(nRecoveryFile)){
        mSatData->setUpdateAppState(Update_App_State_Recovery_Failure);
        return false;
    }
    //====生成秘钥文件
    if(!generateKeyFile()){
        //生成秘钥文件失败
        mSatData->setUpdateAppState(Update_App_State_Recovery_Failure);
        return false;
    }
    //解压操作
    QString nCommand = QString(UpdateScript) + " decompress " + nRecoveryFile + " &";
    int nStatus = ::system(nCommand.toStdString().c_str());
    if(!judgeState(nStatus)){
        //解压程序包失败
        mSatData->setUpdateAppState(Update_App_State_Recovery_Failure);
        return false;
    }
    //替换操作
    if(!replaceFiles()){
        //替换文件失败
        mSatData->setUpdateAppState(Update_App_State_Recovery_Failure);
        return false;
    }
    //所有准备工作成功
    mSatData->setUpdateAppState(Update_App_State_Recovery_Success);
    //重启
    return rebootSystem();
}





void DataOperation::backupDir(QString nDirStr){
    QDir nDir(nDirStr);
    if(!nDir.exists()){//目录不存在
        return;
    }
    QString nTmpDir = nDirStr;
    if(nTmpDir.right(1) == "/"){//如果路径以/结尾，则去掉结尾
        int nIndex = nTmpDir.length();
        nTmpDir = nTmpDir.left(nIndex - 1);
    }
    QFileInfo nFileInfo(nTmpDir);
    if(nFileInfo.isDir()){//如果是目录，则加入列表
        mFileInfoList.append(nFileInfo);
    }
}


void DataOperation::backupFile(QString nFileStr){
    QFile nFile(nFileStr);
    if(!nFile.exists()){//文件不存在
        return;
    }
    QFileInfo nFileInfo(nFileStr);
    if(nFileInfo.isFile()){
        mFileInfoList.append(nFileInfo);
    }
}


//替换文件，在解压文件后，将文件复制到对应的位置
bool DataOperation::replaceFiles(){
    mFileInfoList.clear();//文件列表清空
    QStringList nLines;
    nLines.append("#!/bin/bash");
    nLines.append("#This script is generated when you click Recovery button.");
    nLines.append("");
    QFile nFile(QString("%1%2").arg(BackupDataDir).arg(BackupInfoDat));//打开文件，该文件存储文件原来的位置
    if(nFile.open(QIODevice::ReadOnly)){
        QDataStream in(&nFile);
        QStringList nTmpLines;
        in >> nTmpLines;//读取文件存储信息
        nFile.close();
        for(int i=0; i<nTmpLines.size(); i++){//提取每一行的信息文件
            fileDecode(nTmpLines.at(i));//解码每一行的信息，存储在mFileInfoList里
        }
        for(int i=0; i<mFileInfoList.size(); i++){//将复制命令存储
            QFileInfo nFileInfo = mFileInfoList.at(i);

            QFileInfo nDataFileInfo(QString(BackupDataDir) + nFileInfo.fileName());

            if(nDataFileInfo.isDir()){
                nLines.append("mv " + QString(BackupDataDir) + nFileInfo.fileName() + "/ " + nFileInfo.path() + "/ -f");
                //nLines.append("sync");
                nLines.append("");
            }else{
                nLines.append("cp " + QString(BackupDataDir) + nFileInfo.fileName() + " " + nFileInfo.filePath() + " -f");
                nLines.append("");
            }
//            if(nFileInfo.fileName() == "GF5000"){
//                nLines.append("mv " + QString(BackupDataDir) + nFileInfo.fileName() + " " + nFileInfo.filePath() + "/ -rf");
//                //nLines.append("sync");
//                nLines.append("");
//            }else{
//                nLines.append("cp " + QString(BackupDataDir) + nFileInfo.fileName() + " " + nFileInfo.filePath() + "/ -rf");
//                nLines.append("");
//            }
        }
        //nLines.append("sync");
        nLines.append("cd ../");
        //nLines.append("rm " + QString(BackupDataDir) + " -rf");
    }else{
         //操作失败
        return false;
    }
    //nLines.append("rm " + QString("%1%2").arg(BackupDir).arg(BackupScript));//删除该脚本文件
    //nLines.append("rm " + QString("%1%2").arg(BackupDataDir).arg(BackupInfoDat));//删除文件信息文件
    nLines.append("exit 0");
    //写入脚本并且执行脚本
    QFile nScriptFile(QString("%1%2").arg(BackupDir).arg(BackupScript));
    nScriptFile.remove();
    if(nScriptFile.open(QIODevice::WriteOnly)){//打开文件写入命令操作
        QTextStream out(&nScriptFile);
        for(int i=0; i<nLines.size(); i++){
            out<<nLines.at(i)<<"\n";
        }
        nScriptFile.close();
        //执行脚本
        QString nCommand = "chmod +x " + QString("%1%2").arg(BackupDir).arg(BackupScript);//脚本文件加权限
        ::system(nCommand.toStdString().c_str());
        nCommand = QString("%1%2").arg(BackupDir).arg(BackupScript) + " &";//运行脚本
        ::system(nCommand.toStdString().c_str());
        return true;
    }
    //打开文件失败
    return false;
}




//文件编码，将文件信息保存
void DataOperation::fileEncode(){
    QStringList nLines;
    if(!mFileInfoList.isEmpty()){//判断列表是否为空
        for(int i=0; i<mFileInfoList.size(); i++){//将文件信息存储在字符串列表
            QString nTmpStr;
            nTmpStr = mFileInfoList.at(i).path() + ":" + mFileInfoList.at(i).fileName() + ":";
            nLines.append(nTmpStr);
        }
        QFile nFile(QString("%1%2").arg(BackupDir).arg(BackupInfoDat));
        nFile.remove();
        if(nFile.open(QIODevice::WriteOnly)){//打开文件写入数据
            QDataStream out(&nFile);
            out<<nLines;
            nFile.close();
        }
#if 0
        if(nFile.open(QIODevice::WriteOnly)){//打开文件写入数据
            QTextStream out(&nFile);
            for(int i=0; i<nLines.size(); i++){
                out<<nLines.at(i);
            }
            nFile.close();
        }
#endif
    }
}



void DataOperation::fileDecode(QString nLine){
    QRegExp nReg(":");
    int nIndex;
    QString nFile;
    QString nDir;
    if((nIndex = nLine.indexOf(nReg)) != -1){//获取文件目录
        nFile = nLine.left(nIndex);
        nLine = nLine.mid(nIndex + 1,300);
    }
    if((nIndex = nLine.indexOf(nReg)) != -1){//获取文件名
        nDir = nLine.left(nIndex);
    }
    QFileInfo nFileInfo(nFile + "/"+ nDir);
    mFileInfoList.append(nFileInfo);
}





//生成秘钥文件
bool DataOperation::generateKeyFile(){
    QStringList nLines;
    nLines.append("12345678");
    //秘钥文件，----/backup/gpg_key
    QFile nFile(QString("%1%2").arg(BackupDir).arg(KeyFile));
    nFile.remove();//先删除
    if(nFile.open(QIODevice::WriteOnly)){
        QTextStream out(&nFile);
        for(int i=0; i<nLines.size(); i++){
            out<<nLines.at(i);
        }
        nFile.close();//关闭文件
        return true;
    }
    return false;//打开失败
}


//重启系统
bool DataOperation::rebootSystem(){
#ifdef _SAT_ARM_
    ::system("reboot");//重启
    return true;
#endif
#ifdef _SAT_XNJ_
    qDebug("reboot");
    return true;
#endif
}


//判断状态
bool DataOperation::judgeState(int nStatus){
    if(nStatus == -1){
        //出错
        return false;
    }else{
        if(WIFEXITED(nStatus)){
            if(WEXITSTATUS(nStatus) == 0){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}





//手动打档
void DataOperation::manualPlay(){
    qDebug("[D]Lin >> -----ManualPlay----Begin-----");
#ifdef _SAT_ARM_
#if 0
    QString nStr = "echo setParam shutter 1 > /tmp/eventFifo &";
    std::string str = nStr.toStdString();
    system(str.c_str());
#endif
#if 0
    FILE * fp;
    fp = popen("echo setParam shutter 1 > /tmp/eventFifo &","r");
    pclose(fp);
#endif
#if 0
    int fd = 0;
    char w_buf[100];
    int nwrite;
    fd=open("/tmp/eventFifo",O_WRONLY|O_NONBLOCK,0);
    if(fd==-1){
        if(errno==ENXIO){
            printf("open error; no reading process\n");
        }
    }
    strcpy(w_buf,"setParam shutter 1\n");
    if((nwrite=write(fd,w_buf,100))==-1){
        if(errno==EAGAIN){
            printf("The FIFO has not been read yet.Please try later\n");
        }
    }else{
        printf("write %s to the FIFO\n",w_buf);
    }
    close(fd);
    usleep(1000*1000);
#endif
#if 1
    SetShutter(1);
#endif
#endif
    QDateTime nCurrentTime = QDateTime::currentDateTime();//获取当前时间
    QString nDate = nCurrentTime.toString("yyyy-MM-dd hh:mm:ss");//格式画年月日
    qDebug("[D]Lin >> -----ManualPlay----[%s]-----",nDate.toStdString().c_str());
}




//保存档位参数,保存FID、GSK、GAIN、INT这几个参数，需要分档位
void DataOperation::saveArg(){
    QString nArgStr = mSatData->getArgFile();//获取当前档位参数文件
    if(nArgStr.isEmpty()){//如果获取的文件名为空，则根据档位来判断
        if(mSatData->getGearMode() == SatData::GEARONE){
            nArgStr = QString("%1%2").arg(COF_DIR).arg(QString(ARG_FILE).arg(1));
        }else{
            nArgStr = QString("%1%2").arg(COF_DIR).arg(QString(ARG_FILE).arg(2));
        }
        mSatData->setArgFile(nArgStr);
    }
    QFile nArgFile(nArgStr);
    if(!nArgFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        return ;
    }
    nArgFile.resize(0);
    QTextStream out(&nArgFile);
    QString nStr = QString("Fid = %1\nGsk = %2\nInt = %3\nGain = %4")
            .arg(mSatData->getFid()).arg(mSatData->getGsk())
            .arg(mSatData->getInt()).arg(mSatData->getGain());
    out<<nStr;
    nArgFile.close();
}





//加载档位参数，从文件中加载FID、GSK、GAIN、INT几个参数，分档位
void DataOperation::loadArg(){
    QString nArgStr = mSatData->getArgFile();//获取当前档位保存文件
    if(nArgStr.isEmpty()){
        mSatData->setFid(DEFAULT_FID);
        mSatData->setGsk(DEFAULT_GSK);
        mSatData->setInt(DEFAULT_INT);
        mSatData->setGain(DEFAULT_GAIN);
        return ;
    }
    QFile nArgFile(nArgStr);
    if(!nArgFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        mSatData->setFid(DEFAULT_FID);
        mSatData->setGsk(DEFAULT_GSK);
        mSatData->setInt(DEFAULT_INT);
        mSatData->setGain(DEFAULT_GAIN);
        return ;
    }
    QTextStream in(&nArgFile);
    while(!in.atEnd()){
        QString nLineStr = in.readLine();//读取一行
        nLineStr = nLineStr.simplified();//去掉多余的空格
        QStringList nStrList = nLineStr.split(' ');//以空格分割
        if(nStrList.size() != 3){//参数行分割后应有三个元素
            continue;
        }
        int nArg = nStrList.at(2).toInt();//将第三个元素变为整形
        if(nLineStr.startsWith("Fid")){//第一个元素匹配为FID，则设置数据
            mSatData->setFid(nArg);
        }else if(nLineStr.startsWith("Gsk")){//同上
            mSatData->setGsk(nArg);
        }else if(nLineStr.startsWith("Int")){
            mSatData->setInt(nArg);
            //qDebug("[D]Lin >> Int:%d",nArg);
        }else if(nLineStr.startsWith("Gain")){
            mSatData->setGain(nArg);
        }
    }
    nArgFile.close();
}






//参考设置，设置档片的打档方式
void DataOperation::reference(){
#ifdef _SAT_ARM_
#if 0
    if(mSatData->getReference() == SatData::OUTSIDE){
        QString nStr = "echo setParam shutter_tpye 0 > /tmp/eventFifo &";
        std::string str = nStr.toStdString();
        system(str.c_str());
    }else{
        QString nStr = "echo setParam shutter_tpye 1 > /tmp/eventFifo &";
        std::string str = nStr.toStdString();
        system(str.c_str());
    }
#endif
#if 1
    if(mSatData->getReference() == SatData::OUTSIDE){
        SetShutter_tpye(0);
    }else{
        SetShutter_tpye(1);
    }
#endif
#endif
}




