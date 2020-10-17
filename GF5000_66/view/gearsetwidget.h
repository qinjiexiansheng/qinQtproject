#ifndef GEARSETWIDGET_H
#define GEARSETWIDGET_H

#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QWidget>
#include <QStackedWidget>



//设置档位--左边列表窗口
class SatGearSetListWidget : public QWidget
{
    Q_OBJECT
public:
    SatGearSetListWidget(QWidget *parent = 0);
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    //void focusTransferSignal();//焦点转让信号，当点击确认键发出
    void goBackSignal();//返回信号
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:

    void changeEvent(QEvent *event);

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
    SatData *mSatData;
};




class SatGearSetPage : public QWidget
{
    Q_OBJECT
public:
    enum GearSetPageType{
        GearOne_Page,
        GearTwo_Page
    };
    SatGearSetPage(GearSetPageType nPageType,QWidget *parent = 0);
protected:
    void changeEvent(QEvent *event);
private:
    GearSetPageType mPageType;
    QLabel *mLabel;
};







class GearSetWidget : public QWidget
{
    Q_OBJECT
public:
    GearSetWidget(QWidget *parent = 0);
signals:
public slots:
protected:
    void changeEvent(QEvent *event);
private slots:
    void itemChangeSlot(int nIndex);
    void goBackSlot();
private:
    SatGearSetListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;

};

#endif // GEARSETWIDGET_H
