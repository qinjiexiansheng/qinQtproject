#include "examplepage.h"

/**
 * @name    ExamplePage(QWidget *parent, QString text, int btnNum)
 * @details 作为Analysis界面的示例窗口
 * @param   parent  父窗口指针
 * @param   text    按键名称
 * @param   btnNum  按键个数
 * @author  lee
 * @date    2018-12-20
**/
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
