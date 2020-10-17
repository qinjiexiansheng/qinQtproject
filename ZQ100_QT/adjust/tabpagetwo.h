#ifndef TABPAGETWO_H
#define TABPAGETWO_H

#include "littlewidget.h"
#include <QWidget>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QEvent>
#include <QTimer>
#include <QList>
#include <QObject>
#include "satdefine.h"
#include <QVBoxLayout>
#include <QSignalMapper>
#include "standardparamsetting.h"
#include "SetGearWidget.h"
#include "SatControl.h"

class TabPageTwo : public QWidget
{
    Q_OBJECT

public:
    explicit TabPageTwo(QWidget *parent = 0);
    ~TabPageTwo();
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件

private slots:
    void handleContent(const QString &nStr);

private:
    SatButton *nSettingButton;
    SatButton *nSettingButton2;
    SatButton *nSetRangeButton;
    QSignalMapper *nSignalMapper;
    void focusNext();
    void focusPrevious();
    int mIndex;
   QList<SatButton*> mList;
   Standardparamsetting *standerd ;
   SetGearWidget *nSetGearWidget;
};

#endif // TABPAGETWO_H
