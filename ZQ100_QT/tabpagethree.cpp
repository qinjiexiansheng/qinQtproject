#include "tabpagethree.h"
#include "ui_tabpagethree.h"

TabPageThree::TabPageThree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabPageThree)
{
    ui->setupUi(this);
}

TabPageThree::~TabPageThree()
{
    delete ui;
}
