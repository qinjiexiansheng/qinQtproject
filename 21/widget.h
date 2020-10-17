#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QPushButton>
#include "upadateprogress.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void FontDialogClickedSlot();
    void ProcessDialogClickedSlot();
    void PrintDialogClickedSlot();
    void GetTimeOutSlot(int m_steps);
private:
    QPushButton *m_fontDialogBtn;
    QPushButton *m_processDialogBtn;
    QPushButton *m_printDialogBtn;
    QProgressDialog *m_pressDlg;

};

#endif // WIDGET_H
