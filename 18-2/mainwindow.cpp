#include "mainwindow.h"
#include "QloginDialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), nMainButton(this)
{
    nMainButton.setText("Dialog");

    setFixedSize(200, 50);


    connect(&nMainButton, SIGNAL(clicked()), this, SLOT(nMainButtonClicked()));


}

MainWindow::~MainWindow()
{
    
}

void MainWindow::nMainButtonClicked(void)
{
    qDebug("nMainButtonClicked");

    QLoginDialog dlg;

    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug() << "User: " + dlg.getUser();
        qDebug() << "Pwd: " + dlg.getPwd();
    }
}
