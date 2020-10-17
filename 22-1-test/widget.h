#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    QPushButton btnTest1;
    QPushButton btnTest2;
    QPushButton btnTest3;
    QPushButton btnTest4;

};

#endif // WIDGET_H
