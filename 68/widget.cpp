#include "widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setGeometry(10, 20, 640, 480);
    m_group  = new QGroupBox("setting" ,this);
    m_group->setGeometry(20,10,600,60);

    m_freeBtn = new QRadioButton("Free", this);
    m_freeBtn->resize(60,20);

    m_lineBtn = new QRadioButton("Line", this);
    m_lineBtn->resize(60,20);

    m_rectBtn = new QRadioButton("Rect", this);
    m_rectBtn->resize(60,20);

    m_ellipseBtn = new QRadioButton("ellip", this);
    m_ellipseBtn->resize(60,20);

    m_colorBox = new QComboBox(this);
    m_colorBox->resize(80,20);
    m_colorBox->addItem("Black");
    m_colorBox->addItem("Blue");
    m_colorBox->addItem("Green");
    m_colorBox->addItem("Red");
    m_colorBox->addItem("Yellow");

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget(m_freeBtn, 0, 0 , 1, 1);
    gLayout->addWidget(m_lineBtn, 0, 1 , 1, 1);
    gLayout->addWidget(m_rectBtn, 0, 2 , 1, 1);
    gLayout->addWidget(m_ellipseBtn, 0, 3 , 1, 1);
    gLayout->addWidget(m_colorBox, 0, 4 , 1, 1);
    //gLayout->setMargin(20);
    m_group->setLayout(gLayout);

}

Widget::~Widget()
{

}
