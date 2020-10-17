#ifndef SHUTTERINTERVALWIDGET_H
#define SHUTTERINTERVALWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"

#if 0
class SatShutterIntervalListWidget : public QWidget
{
    Q_OBJECT
public:
    SatShutterIntervalListWidget(QWidget *parent = 0);
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


class SatShutterIntervalPage : public QWidget
{
    Q_OBJECT
public:
    SatShutterIntervalPage(QWidget *parent = 0);
signals:
    void focusTransferSignal();
    void goBackSignal();
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QList<QPushButton*> mList;
    QStringList *mStringList;
};




class ShutterIntervalWidget : public QWidget
{
    Q_OBJECT
public:
    ShutterIntervalWidget(QWidget *parent = 0);
public slots:
signals:
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void goBackSlot();
private:
private:
    SatShutterIntervalListWidget *mLeftWidget;
    SatShutterIntervalPage *mRightWidget;
    SatTitleBar *mSatTitleBar;

};
#endif



#if 1

class SatShutterIntervalSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatShutterIntervalSmallWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
signals:
    void operationSignal(QString nOpeStr);
    void goBackSignal();
private:
    void focusNext();
    void focusPrevious();
private slots:
    void handleContent(const QString &nOpeStr);//处理按键操作
private:
    int mIndex;
    QList<SatPhotoButton*> mList;
};


class SatShutterIntervalPage : public QLabel
{
    Q_OBJECT
public:
    SatShutterIntervalPage(QWidget *parent = 0);
    int getData();
    void setData(int nData);
signals:
protected:
    void paintEvent(QPaintEvent *event);
private slots:
private:
private:
    int mData;
};




class ShutterIntervalWidget : public QWidget
{
    Q_OBJECT
public:
    ShutterIntervalWidget(QWidget *parent = 0);
public slots:
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void paintEvent(QPaintEvent *event);
private slots:
    void operationSlot(QString nOpeStr);
    void goBackSlot();
private:
    void addData();
    void subData();
    void queryData();
private:
    int mData;
    SatData *mSatData;
    SatShutterIntervalPage *mPage;
    SatShutterIntervalSmallWidget *mSmallWidget;
    SatTitleBar *mSatTitleBar;

};
#endif


#endif // SHUTTERINTERVALWIDGET_H
