#include <QtGui/QApplication>
#include "QCalculatorUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCalculatorUI* cal = QCalculatorUI::NewInstance();
    int ret = -1;

    if( cal != NULL )
    {
        cal->show();

        ret = a.exec();

        delete cal;
    }

    return ret;
}
