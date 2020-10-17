#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QThread>
#include "AnotherThread.h"

void test()
{
//    AnotherThread at;

//    at.start();

    AnotherThread *at = new AnotherThread;

    at->start();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "main() tid = " << QThread::currentThreadId();

    test();
    
    return a.exec();
}
