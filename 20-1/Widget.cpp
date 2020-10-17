#include "Widget.h"
#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>

Widget::Widget(QWidget *parent) : QWidget(parent),
    ColorDialogBtn(this), InputDialogBtn(this)
{
    ColorDialogBtn.setText("Color Dialog");
    ColorDialogBtn.move(20, 20);
    ColorDialogBtn.resize(160, 30);

    InputDialogBtn.setText("Input Dialog");
    InputDialogBtn.move(20, 70);
    InputDialogBtn.resize(160, 30);

    resize(200, 120);
    setFixedSize(200, 120);

    connect(&ColorDialogBtn, SIGNAL(clicked()), this, SLOT(ColorDialogBtn_Clicked()));
    connect(&InputDialogBtn, SIGNAL(clicked()), this, SLOT(InputDialogBtn_Clicked()));
}

void Widget::ColorDialogBtn_Clicked()
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

void Widget::InputDialogBtn_Clicked()
{
    QInputDialog dlg(this);

    dlg.setWindowTitle("Input Test");
    dlg.setLabelText("Please input an integer:");
    dlg.setInputMode(QInputDialog::TextInput);


    if( dlg.exec() == QInputDialog::Accepted )
    {
        qDebug() << dlg.textValue();
    }
}

Widget::~Widget()
{
    
}
