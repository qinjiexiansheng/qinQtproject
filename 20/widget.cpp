#include "widget.h"
#include <QGridLayout>
#include <QColorDialog>
#include <QInputDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(50,50,100,200);

    m_corcolBtn = new QPushButton("corcol" ,this);
    m_inputBtn  = new QPushButton("Input", this);

    QGridLayout * gLayout = new QGridLayout(this);
    gLayout->addWidget(m_corcolBtn, 0, 0);
    gLayout->addWidget(m_inputBtn, 1, 0);

    connect(m_corcolBtn, SIGNAL(clicked()), this,SLOT(CorcolClickedSlot()) );
    connect(m_inputBtn, SIGNAL(clicked()), this,SLOT(InputBtnClickedSlot()) );


}

void Widget::CorcolClickedSlot()
{
    QColorDialog dlg(this);

    dlg.setWindowTitle("Color Editor");
    dlg.setCurrentColor(QColor(100, 111, 222));

    if( dlg.exec() == QColorDialog::Accepted )
    {
        QColor color = dlg.selectedColor();

        qDebug() << color;
        qDebug() << color.red();
        qDebug() << color.green();
        qDebug() << color.blue();
        qDebug() << color.hue();
        qDebug() << color.saturation();
        qDebug() << color.value();
    }
}


void Widget::InputBtnClickedSlot()
{
    QInputDialog dlg(this);

    dlg.setWindowTitle("Input ....");
    dlg.setInputMode(QInputDialog::TextInput);

    if(dlg.exec())
    {
        qDebug() << dlg.textValue();

    }
}

Widget::~Widget()
{
    
}
