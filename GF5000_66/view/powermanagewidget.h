#ifndef POWERMANAGEWIDGET_H
#define POWERMANAGEWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QStackedWidget>

class SatPowerManageListWidget : public QWidget
{
    Q_OBJECT
public:
    SatPowerManageListWidget(QWidget *parent = 0);
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


class SatPowerManagePageOneListWidget : public QWidget
{
    Q_OBJECT
public:
    SatPowerManagePageOneListWidget(QWidget *parent = 0);
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



class SatPowerManagePageTwoListWidget : public QWidget
{
    Q_OBJECT
public:
    SatPowerManagePageTwoListWidget(QWidget *parent = 0);
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











class PowerManageWidget : public QWidget
{
    Q_OBJECT
public:
    PowerManageWidget(QWidget *parent = 0);
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
    SatPowerManageListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;
};

#endif // POWERMANAGEWIDGET_H
