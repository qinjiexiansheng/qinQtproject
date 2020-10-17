#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include "view/tabpage.h"


/*======================================

  标定窗口 ： TabDialog

 ======================================*/
class TabDialog : public QDialog
{
    Q_OBJECT
public:
    TabDialog(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
private slots:
    //void currentChange(int nIndex);
private:
    void nextTab();
    void prevTab();
private:
    int mMaxIndex;
    QTabWidget *mTabWidget;
};

#endif // TABDIALOG_H
