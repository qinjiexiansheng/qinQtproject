#include <QApplication>
#include "model/satdata.h"
#include "uitls/interface.h"
#include "controller/satcontrol.h"
#include "controller/keyscan.h"
#include "view/mainwindow.h"
#include <QFontDatabase>
#include <QTranslator>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));


    QTranslator nTranslator;
//    nTranslator.load(QString("qzher_en.qm"));
    a.installTranslator(&nTranslator);


    QFont nFont;

#ifdef _SAT_ARM_
    nFont.setFamily("unifont");
#endif
#ifdef _SAT_XNJ_
    nFont.setFamily("Fangsong Ti" );
#endif
    nFont.setPointSize(20);
    a.setFont(nFont);
    //qInstallMsgHandler();
    //后台线程
    SatControl *nSatControl = SatControl::initance();
    //qDebug("[D]Lin >> The SatControl before:%d",nSatControl->thread()->currentThreadId());

    //按键线程创建及启动
    KeyScan *nKeyScan = new KeyScan();
    //qDebug("[D]Lin >> The KeyScan before:%d",nKeyScan->thread()->currentThreadId());


    QThread *nControlThread = new QThread();
    nSatControl->setTranslator(&nTranslator);
    nSatControl->moveToThread(nControlThread);
    nControlThread->start();



    MainWindow *nWindow = new MainWindow();
    QObject::connect(nWindow,SIGNAL(operationSignal(int,QString)),nSatControl,SLOT(doService(int,QString)));
    QObject::connect(nKeyScan,SIGNAL(keyChangeSignal(int,bool,bool)),nWindow,SLOT(keyToEvent(int,bool,bool)));
    nWindow->show();
    nWindow->registerField();








    QThread* nKeyScanThread = new QThread();//新开一个线程
    nKeyScan->moveToThread(nKeyScanThread);
    //QObject::connect(nKeyScanThread,SIGNAL(started()),nKeyScan,SLOT(init()));
    nKeyScanThread->start();
    //qDebug("[D]Lin >> The KeyScan after:%d",nKeyScanThread->thread()->currentThreadId());
    //qDebug("[D]Lin >> The MainWindow after:%d",nWindow->thread()->currentThreadId());


    //字体查询
//    QFontDatabase database;
//    foreach (const QString &family, database.families()){
//        qDebug()<<family;
//    }
//    qDebug()<<"\n now is chinese font. \n";//下面为支持简体中文字体库
//    foreach (const QString &family, database.families(QFontDatabase::SimplifiedChinese)){
//        qDebug()<<family;
//    }
    return a.exec();
}
