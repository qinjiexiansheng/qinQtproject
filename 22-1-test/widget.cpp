#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),btnTest1(this),btnTest2(this),btnTest3(this),btnTest4(this)

{
    QHBoxLayout* hLayout1 = new QHBoxLayout();
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();

    btnTest1.setText("btnTest1");
    btnTest1.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTest1.setMinimumSize(20,30);

    btnTest2.setText("btnTest1");
    btnTest2.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTest2.setMinimumSize(20,30);

    hLayout1->setSpacing(10);
    hLayout1->addWidget(&btnTest1);
    hLayout1->addWidget(&btnTest2);

    btnTest3.setText("btnTest1");
    btnTest3.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTest3.setMinimumSize(20,30);

    btnTest4.setText("btnTest1");
    btnTest4.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTest4.setMinimumSize(20,30);

    hLayout2->setSpacing(10);
    hLayout2->addWidget(&btnTest3);
    hLayout2->addWidget(&btnTest4);

    vLayout->setSpacing(10);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);

    setMinimumSize(300,200);


}

Widget::~Widget()
{
}
