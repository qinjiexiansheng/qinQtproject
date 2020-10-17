#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w1;
//    w1.show();


    QLabel label("Hello Qt!");
    QWidget w;
   // label.setParent(&w);
    w.show();
    
    return a.exec();
}
