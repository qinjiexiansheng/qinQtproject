#ifndef TABPAGE_H
#define TABPAGE_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QFile>
#include <QVBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QSignalMapper>
#include "uitls/macrodefine.h"
#include "view/smallwidget.h"
#include "view/setparamwidget.h"
#include "view/modifyadtablewidget.h"
#include "view/littlewidget.h"
#include <QScrollArea>
#include <QKeyEvent>
/*======================================

  标签页1 ： TabPageOne
  包含非均匀校正相关操作

  ======================================*/
class TabPageOne : public QWidget
{
    Q_OBJECT
public:
    TabPageOne(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;
};
/*======================================

  标签页2 ： TabPageTwo
  包含与标定相关的操作

  ======================================*/
class TabPageTwo : public QWidget
{
    Q_OBJECT
public:
    TabPageTwo(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;

    SetParamWidget *mSetParamWidget;


    SetGearWidget *mSetGearWidget;
    SetAutoShutterWidget *mSetAutoShutterWidget;
};
/*======================================

  标签页3 ： TabPageThree
  其他的一些操作

  ======================================*/
class TabPageThree : public QWidget
{
    Q_OBJECT
public:
    TabPageThree(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;

    SaveADWidget *mSaveAdWidget;
    ModifyAdTableWidget *mModifyAdWidget;
    ShowAdTableWidget *mShowAdWidget;
};



/*======================================

  标签页4 ： TabPageFour
  其他的一些操作

  ======================================*/
class TabPageFour : public QWidget
{
    Q_OBJECT
public:
    TabPageFour(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;

    SetSerialNumberWidget *mSetSerialWidget;
    SetDateWidget *mSetDateWidget;

};


/*======================================

  标签页5 ： TabPageFive
  其他的一些操作

  ======================================*/
class TabPageFive : public QWidget
{
    Q_OBJECT
public:
    TabPageFive(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;

    SetDisWidget *mSetDisWidget;
};






#endif // TABPAGE_H
