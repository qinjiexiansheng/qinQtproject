#ifndef NWIDGET_H
#define NWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>


class nWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit nWidget(QWidget *parent = 0);
    ~nWidget();
    
private:
    QPushButton btn1;
    QPushButton btn2;
    QPushButton btn3;
    QVBoxLayout *nVboxLay;
};

#endif // NWIDGET_H
