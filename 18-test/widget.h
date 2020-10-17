#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Qlogindialog.h"



class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void TestBtn_Clicked();
    
private:
    QPushButton testBtn;
};

#endif // WIDGET_H
