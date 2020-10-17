#include "examplepage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>

ExamplePage::ExamplePage(QWidget *parent, QString text, int btnNum) : QWidget(parent)
{

    QButtonGroup *btnGroup = new QButtonGroup(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for(int i = 1; i <= btnNum; i++)
    {
        QPushButton *btn = new QPushButton(QString("%1 %2").arg(text).arg(i));
        btnGroup->addButton(btn, i);
        mainLayout->addWidget(btn);
    }

    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}
