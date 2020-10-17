#ifndef GLOBALPARAMWIDGET_H
#define GLOBALPARAMWIDGET_H

#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QWidget>
#include <QStackedWidget>


#include "view/smallwidget.h"

//全局参数--左边列表面板
class SatGlobalParamListWidget : public QWidget
{
    Q_OBJECT
public:
    SatGlobalParamListWidget(QWidget *parent = 0);
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//焦点转让信号，当点击确认键发出
    void goBackSignal();//返回信号
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
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





class SatGlobalParamSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatGlobalParamSmallWidget(QWidget *parent = 0);
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


class SatGlobalParamLabel : public QWidget
{
    Q_OBJECT
public:
    SatGlobalParamLabel(QWidget *parent = 0);
    QString getTextString();
    void setTextString(QString nTextString);
    QString getTitleString();
    void setTitleString(QString nTitleString);
signals:
protected:
    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
private slots:
private:
private:
    QLabel *mLabel;
    QLineEdit *mLineEdit;
    QString mTitleString;
    QString mTextString;
};




//
class SatGlobalParamPage : public QWidget
{
    Q_OBJECT
public:
    enum GlobalParamPageType{
        Emiss_Page,//辐射率页面
        Dis_Page,//距离页面
        EnvTemp_Page,//环境温度页面
        RefTemp_Page,//反射温度页面
        RelHum_Page,//相对湿度页面
        CorTemp_Page//修正温度页面
    };
    SatGlobalParamPage(GlobalParamPageType nPageType,QWidget *parent = 0);
signals:
    void focusTransferSignal();
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
private slots:
    void operationSlot(const QString &nStr);//处理按键操作
    void goBackSlot();
private:
    void focusNext();
    void focusPrevious();
    void updateLabel();
    void updateData(bool nIsGet = true);
    void addData();
    void subData();
private:
    QLabel *mLabel;
    QLineEdit *mLineEdit;
    SatData *mSatData;
    GlobalParamPageType mPageType;
    float mData;
    float mGrowth;//增幅
    SatGlobalParamSmallWidget *mSmallWidget;
};






























class GlobalParamWidget : public QWidget
{
    Q_OBJECT
public:
    GlobalParamWidget(QWidget *parent = 0);
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
    SatGlobalParamListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;

};

#endif // GLOBALPARAMWIDGET_H
