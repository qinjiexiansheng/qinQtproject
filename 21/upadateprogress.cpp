#include "upadateprogress.h"
#include <QDebug>
UpadateProgress::UpadateProgress(QObject *parent) :
    QObject(parent)
{

    moveToThread(&m_thread);
    m_steps =0;
/***************************************
 这段程序放在这里不行，以为槽函数的线程被改变了，
****************************************/
    m_time = new QTimer;
    m_time->start(50);
    QObject::connect(m_time,SIGNAL(timeout()), this, SLOT(TimeOutSlot()));


    QObject::connect(&m_thread,SIGNAL(started()), this, SLOT(UpadateProgressSlot()));

}

void UpadateProgress::UpadateProgressSlot()
{


//    m_time = new QTimer(this);
//    m_time->start(50);
//    QObject::connect(m_time,SIGNAL(timeout()), this, SLOT(TimeOutSlot()));

    qDebug() << "void UpadateProgress::UpadateProgressSlot()";
    qDebug() << "UpadateProgressSlot = " << QThread::currentThreadId();


}


void UpadateProgress::TimeOutSlot()
{


    if(m_steps < 99)
    {
       // m_progressDlg->setValue(m_steps++);
        qDebug()<< "UpadateProgress::TimeOutSlot()";
        emit UpdateSteps(m_steps++);
        qDebug() << "TimeOutSlot = " << QThread::currentThreadId();


    }

}

void UpadateProgress::start()
{
    m_thread.start();

}
