#ifndef SYSTEMCONTROLWIDGET_H
#define SYSTEMCONTROLWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QStackedWidget>

class SatSysControlListWidget : public QWidget
{
    Q_OBJECT
public:
    SatSysControlListWidget(QWidget *parent = 0);
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//焦点转让信号，当点击确认键发出
    void goBackSignal();//返回信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件过滤方法
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);//焦点进入事件
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void focusNext();//焦点移到下一控件
    void focusPrevious();//焦点移到上一控件
    void proofreadIndex();
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};

#if 0
class SatSysControlPageOne : public QWidget
{
    Q_OBJECT
public:
    SatSysControlPageOne(QWidget *parent = 0);
signals:
    void focusTransferSignal();
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void queryMode();
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};
#endif




class SatSysControlPageTwo : public QWidget
{
    Q_OBJECT
public:
    SatSysControlPageTwo(QWidget *parent = 0);
signals:
    void focusTransferSignal();
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void queryMode();
private:
    SatData *mSatData;
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};



#if 0
class SatSysControlPageThree : public QWidget
{
    Q_OBJECT
public:
    SatSysControlPageThree(QWidget *parent = 0);
signals:
    void focusTransferSignal();
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void queryMode();
private:
    SatData *mSatData;
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};
#endif




#if 0
class SatPowerManagePageOne : public QWidget
{
    Q_OBJECT
public:
    SatPowerManagePageOne(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
    void focusTransferSignal();
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void queryMode();
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
    SatData *mSatData;
};

class SatPowerManagePageTwo : public QWidget
{
    Q_OBJECT
public:
    SatPowerManagePageTwo(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
    void focusTransferSignal();
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
    void queryMode();
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
    SatData *mSatData;
};
#endif




class SystemControlWidget : public QWidget
{
    Q_OBJECT
public:
    SystemControlWidget(QWidget *parent = 0);
public slots:
signals:
protected:
private slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void itemChangeSlot(int nIndex);
    void goBackSlot();
private:
private:
    SatSysControlListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;

};

#endif // SYSTEMCONTROLWIDGET_H
