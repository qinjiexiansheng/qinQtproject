#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),mWidget(this)
{
    resize(200, 180);
    setFixedSize(200, 180);

    mWidget.show();

}

MainWindow::~MainWindow()
{
    qDebug("~MainWindow()");
}
