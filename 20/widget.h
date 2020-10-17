#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void CorcolClickedSlot();
    void InputBtnClickedSlot();

private:
    QPushButton *m_corcolBtn;
    QPushButton *m_inputBtn;

};

#endif // WIDGET_H
