#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QStackedWidget>
#include "view/globalparamwidget.h"
#include "view/gearsetwidget.h"
#include "view/emissivitytablewidget.h"
#include "view/languagewidget.h"
#include "view/updateprogramwidget.h"
#include "view/datetimewidget.h"
#include "view/systemcontrolwidget.h"
#include "view/setunitwidget.h"
#include "view/powermanagewidget.h"
#include "view/shutterintervalwidget.h"
#include "view/autosavepicturewidget.h"


#include "view/smallwidget.h"

//系统界面--左边列表窗口
class SatSysListWidget : public QWidget
{
    Q_OBJECT
public:
    SatSysListWidget(QWidget *parent = 0);
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//焦点转让信号，当点击确认键发出
    void goBackSignal();//返回信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件过滤方法
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);//焦点进入事件
    void paintEvent(QPaintEvent *event);
private:
    void focusNext();//焦点移到下一控件
    void focusPrevious();//焦点移到上一控件
private slots:
    void handleContent(int nOpe);//处理按键操作
private:
    int mIndex;
    QList<SatButton*> mList;
};


//系统界面--右边面板--参数设置面板
class SatSysStackPageOne : public QWidget
{
    Q_OBJECT
public:
    SatSysStackPageOne(QWidget *parent = 0);
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
private:
    int mIndex;
    QList<SatButton*> mList;

    GlobalParamWidget *mGlobalParamWidget;
    GearSetWidget *mGearSetWidget;
    EmissivityTableWidget *mEmissTableWidget;


};


//系统界面--右边面板--系统设置面板
class SatSysStackPageTwo : public QWidget
{
    Q_OBJECT
public:
    SatSysStackPageTwo(QWidget *parent = 0);
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
private:
    int mIndex;
    QList<SatButton*> mList;

    LanguageWidget *mLanguageWidget;
    UpdateProgramWidget *mUpdateProgramWidget;
    DateTimeWidget *mDateTimeWidget;
    SystemControlWidget *mSystemControlWidget;
    SetUnitWidget *mSetUnitWidget;
    PowerManageWidget *mPowerManageWidget;

};


//系统界面--右边面板--图像设置面板
class SatSysStackPageThree : public QWidget , public DataObserver
{
    Q_OBJECT
public:
    SatSysStackPageThree(QWidget *parent = 0);
    void doUpdate(QString nStr);
    void registerField();
signals:
    void focusTransferSignal();
    void doUpdateSignal(QString nOpeStr);
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void doUpdateSlot(QString nOpeStr);
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;

    ShutterIntervalWidget *mShutterIntervalWidget;
    AutoSavePictureWidget *mAutoSavePictureWidget;

};



//系统界面--右边面板--系统信息面板
class SatSysStackPageFour : public QWidget
{
    Q_OBJECT
public:
    SatSysStackPageFour(QWidget *parent = 0);
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
private:
    int mIndex;
    QList<SatButton*> mList;
    SatData *mSatData;
};




class SystemWidget : public QWidget
{
    Q_OBJECT
public:
    SystemWidget(QWidget *parent = 0);
public slots:
signals:
protected:
    void showEvent(QShowEvent *event);
private slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void itemChangeSlot(int nIndex);
    void goBackSlot();
private:
private:
    SatSysListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;



};

#endif // SYSTEMWIDGET_H
