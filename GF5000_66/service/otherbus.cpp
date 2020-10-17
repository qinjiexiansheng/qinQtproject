#include "otherbus.h"


//复制到SD卡,将项目的参数文件复制到SD卡里，如温度AD表、档位参数文件等
void OtherBus::tableToSD(){
    FileOpe::copyDir(COF_DIR,SD_DIR);
    FileOpe::copyDir(LOG_DIR,SD_DIR);
}



//SD卡复制,从SD卡复制参数文件到项目中，相当于恢复
void OtherBus::SDToTable(){
    FileOpe::copyDir(SD_DIR,COF_DIR);
}



//加载温度AD表窗口的model
void OtherBus::loadModelData(){
    QString nStr = mSatData->getTmpAdFile();
    QStandardItemModel *nModel = mSatData->getModel();
    QFile nFile(nStr);
    if(!nFile.open(QIODevice::ReadOnly | QIODevice::Text)){//打开文件
        qDebug("[E]Lin >> Open the temp ad table error!");
        return ;
    }
    QTextStream in(&nFile);
    QString nLineStr = in.readLine();
    if(nLineStr != "[TempADTable]"){//检查第一行是否一致
        qDebug("[W]Lin >> The temp ad table format not true!");
    }
    int nRow = 0;
    nModel->clear();
    nModel->setColumnCount(2);

    while(!in.atEnd()){
        nLineStr = in.readLine();//读取一行
        nLineStr = nLineStr.simplified();//去掉多余的空格
        QStringList nStrList = nLineStr.split(' ');//用空格分割
        if(nStrList.size() == 3){//正常应该有三个字段,××× = ×××
            nModel->setItem(nRow,0,new QStandardItem(nStrList.at(0)));//第一列数据
            nModel->setItem(nRow,1,new QStandardItem(nStrList.at(2)));//第二列数据
            //nModel->item(nRow,0)->setEditable(false);//第一列设置为不可以编辑
            nRow++;
        }
    }
    nFile.close();//关闭文件
}


//保存Model
void OtherBus::saveModelData(){
    QString nStr = mSatData->getTmpAdFile();
    QStandardItemModel *nModel = mSatData->getModel();
    QFile nFile(nStr);
    if(!nFile.open(QIODevice::ReadWrite | QIODevice::Text)){//打开文件
        qDebug("[E]Lin >> Open the temp ad table error!");
        return ;
    }
    nFile.resize(0);//清空内容
    QTextStream out(&nFile);
    out<<"[TempADTable]"<<"\n";//写入首行标记
    for(int i = 0; i < nModel->rowCount(); i++){
        out<<nModel->data(nModel->index(i,0)).toString()<<" = "
           <<nModel->data(nModel->index(i,1)).toString()<<"\n";
    }
    nFile.close();
}



//打开激光
void OtherBus::openLaser(){
#ifdef _SAT_ARM_
    SetLaser(1);
#endif
}


//关闭激光
void OtherBus::stopLaser(){
#ifdef _SAT_ARM_
    SetLaser(0);
#endif
}





void OtherBus::obtainReleaseDate(){
    //QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy");







}




