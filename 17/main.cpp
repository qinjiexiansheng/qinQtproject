#include <QtGui/QApplication>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include "Dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dlg;
    int r = dlg.exec();
   // dlg.exec();


    if( r == QDialog::Accepted )
    {
        qDebug() << "Accepted";
    }
    else if( r == QDialog::Rejected )
    {
        qDebug() << "Rejected";
    }
    else
    {
        qDebug() << r;
    }
    
    return r;

}
