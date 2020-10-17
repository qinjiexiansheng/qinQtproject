#include "emisstablepage.h"

/**
 * @name    EmissTablePage::EmissTablePage(QWidget *parent)
 * @details 显示辐射率表
 * @param   parent  父窗口指针

 * @date    2018-11-15
**/
EmissTablePage::EmissTablePage(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("color: rgb(255, 255, 255);\
                     background-color: rgb(0, 155, 155)");

    QLabel *title = new QLabel("Emiss Table");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    title->setMinimumHeight(30);

    QPushButton *btn = new QPushButton("Back", title);
    btn->setMaximumHeight(30);
    btn->setMinimumHeight(30);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(close()));

    QTableWidget *centralWidget = new QTableWidget(15, 5);
    centralWidget->setStyleSheet("color: black;background-color: white");
    QStringList headerLabels;
    headerLabels << "Name" << "Type"<<"Min"<<"Max"<<"Default";
    centralWidget->setHorizontalHeaderLabels(headerLabels);
    centralWidget->verticalHeader()->hide();
    centralWidget->setHorizontalHeaderLabels(QStringList());
    centralWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0; i<5; i++)
        centralWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    centralWidget->setSelectionMode(QAbstractItemView::NoSelection);

    //设置辐射率数据
    for(int i=0; i<15; i++)
    {
        int j = 0;
        centralWidget->setItem(i, j++, new QTableWidgetItem("Asphaltum"));
        centralWidget->setItem(i, j++, new QTableWidgetItem("Nonmetal"));
        centralWidget->setItem(i, j++, new QTableWidgetItem("0.75"));
        centralWidget->setItem(i, j++, new QTableWidgetItem("0.85"));
        centralWidget->setItem(i, j++, new QTableWidgetItem("0.75"));
        for(int j=0; j<5; j++)
        {
           centralWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(title);
    mainLayout->addWidget(centralWidget);


    connect(btn, SIGNAL(clicked(bool)), this, SLOT(close()));
}

EmissTablePage::~EmissTablePage()
{

}
