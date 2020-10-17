#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QGridLayout>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include "uitls/interface.h"
#include "uitls/operationfield.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include "view/softkeyboard.h"
#include "view/littlewidget.h"

/*======================================

  保存AD窗口 ： SaveADWidget
  用于保存AD当Map里，制成温度AD表

 ======================================*/
class SaveADWidget : public QWidget , public DataObserver
{
    Q_OBJECT
public:
    SaveADWidget(QWidget *parent = 0);
    void doUpdate(QString nStr);//观察字段变化时被调用的方法
    void registerField();//注册监听字段
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤
    void showEvent(QShowEvent *se);//显示事件
    void paintEvent(QPaintEvent *event);//绘制事件
signals:
    void doUpdateSignal(QString nUpStr);//字段变化信号（将字段更新的操作转为同线程）
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void doUpdateSlot(QString nUpStr);//字段变化槽（同字段变化信号）
    void closeSlot();//关闭按钮槽
    void saveSlot();//save按键槽
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QComboBox *mComboBox;//组合框
    QLabel *mAdLabel;//显示AD值的标签
    int mIndex;//当前焦点索引
    int mMaxIndex;//组合框最大索引
    QList<QWidget*> mList;//焦点列表
    SatData *mSatData;
    SatData::GearEnum mEnum;
    SatTitleBar *mSatTitleBar;
};




/*======================================

  设置档位窗口 ： SetGearWidget
  选择档位，目前存在两档

 ======================================*/
class SetGearWidget : public QWidget
{
    Q_OBJECT
public:
    SetGearWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void okSlot();
    void closeSlot();//关闭
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QComboBox *mComboBox;//组合框
    int mIndex;//当前焦点索引
    int mMaxIndex;//组合框最大索引
    SatData::GearEnum mOldGear;
    SatData *mSatData;
    QList<QWidget*> mList;//焦点列表
    SatTitleBar *mSatTitleBar;
};



/*======================================

  询问对话框 ： AskDialog

 ======================================*/
class AskDialog : public QDialog
{
    Q_OBJECT
public:
    AskDialog(QString nStr, QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    int mIndex;
    QList<QPushButton*> mList;
    SatTitleBar *mSatTitleBar;
};



class SetAutoShutterWidget : public QWidget
{
    Q_OBJECT
public:
    SetAutoShutterWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void closeSlot();//关闭
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QComboBox *mAutoBox;//组合框
    QLineEdit *mTimeEdit;
    int mAutoTime;
    int mOldAutoTime;
    bool mOldAutoSign;
    int mIndex;//当前焦点索引
    int mAutoBoxMaxIndex;//组合框最大索引
    QList<QWidget*> mList;//焦点列表
    SatData *mSatData;
    SatTitleBar *mSatTitleBar;
};


class SetSerialNumberWidget : public QWidget
{
    Q_OBJECT
public:
    SetSerialNumberWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void closeSlot();//关闭
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QLineEdit *mSerialEdit;
    int mSerialNumber;
    int mOldSerialNumber;
    int mIndex;//当前焦点索引
    QList<QWidget*> mList;//焦点列表
    SatData *mSatData;
    SatTitleBar *mSatTitleBar;
};



class SetDateWidget : public QWidget
{
    Q_OBJECT
public:
    SetDateWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void closeSlot();//关闭
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QComboBox *mYearBox;
    QComboBox *mMonthBox;
    QComboBox *mDayBox;
    int mYear;
    int mOldYear;
    int mMonth;
    int mOldMonth;
    int mDay;
    int mOldDay;
    int mIndex;//当前焦点索引
    QList<QWidget*> mList;//焦点列表
    SatData *mSatData;
    SatTitleBar *mSatTitleBar;
};



class SetDisWidget : public QWidget
{
    Q_OBJECT
public:
    SetDisWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj,QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
    void paintEvent(QPaintEvent *event);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void closeSlot();//关闭按钮响应槽
    void okSlot();//OK按钮响应槽
private:
    void focusNext();//将焦点转移到下一组件
    void focusPrevious();//将焦点转移到上一组件
    float mDistance;
    SatData* mSatData;
    int mIndex;//当前焦点所在窗口组件的索引
    QList<QWidget *> mList;//窗口组件指针列表
    //窗口组件
    QLineEdit *mDisLineEdit;//FID输入框
    QPushButton *mCloseButton;//关闭按钮
    QPushButton *mOkButton;//OK按钮
    SatTitleBar *mSatTitleBar;
};


class ShutDownWidget : public QWidget
{
    Q_OBJECT
public:
    ShutDownWidget(QWidget *parent = 0);
    QString getTextString();
    void setTextString(QString nTextString);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString mTextString;
};


#endif // SMALLWIDGET_H
