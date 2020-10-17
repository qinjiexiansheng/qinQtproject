#ifndef SETPARAMWIDGET_H
#define SETPARAMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>
#include "uitls/interface.h"
#include "uitls/operationfield.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include "view/littlewidget.h"

/*======================================

  设置参数窗口 ： SetParamWidget
  用于设置FID、GSK等值
  在一直按下来调参数时，不需要发底层的操作字段

  ======================================*/
class SetParamWidget : public QWidget , public DataObserver
{
    Q_OBJECT
public:
    SetParamWidget(QWidget *parent = 0);
    void doUpdate(QString nStr);//观察者更新方法
    void registerField();
protected:
    bool eventFilter(QObject *obj,QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
    void paintEvent(QPaintEvent *event);
signals:
    void doUpdateSignal(QString nUpStr);
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void doUpdateSlot(QString nUpStr);
    void closeSlot();//关闭按钮响应槽
    void okSlot();//OK按钮响应槽
private:
    void focusNext();//将焦点转移到下一组件
    void focusPrevious();//将焦点转移到上一组件
    int mFid;
    int mOldFid;
    int mGsk;
    int mOldGsk;
    int mGain;
    int mOldGain;
    int mInt;
    int mOldInt;
    SatData* mSatData;
    int mIndex;//当前焦点所在窗口组件的索引
    QList<QWidget *> mList;//窗口组件指针列表
    //窗口组件
    QLineEdit *mFidLineEdit;//FID输入框
    QLineEdit *mGskLineEdit;//GSK输入框
    QLineEdit *mIntLineEdit;//INT输入框
    QLineEdit *mGainLineEdit;//GAIN输入框
    QLabel    *mDetLabel;//DET显示框
    QLabel    *mSensorLabel;//SenSor显示框
    QLabel    *mAdLabel;//AD显示框
    QPushButton *mCloseButton;//关闭按钮
    QPushButton *mOkButton;//OK按钮
    SatTitleBar *mSatTitleBar;
};

#endif // SETPARAMWIDGET_H
