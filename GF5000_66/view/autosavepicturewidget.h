#ifndef AUTOSAVEPICTUREWIDGET_H
#define AUTOSAVEPICTUREWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"

#if 1

class SatAutoSavePictureSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatAutoSavePictureSmallWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件

    void changeEvent(QEvent *event);

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


class SatAutoSavePicturePage : public QLabel
{
    Q_OBJECT
public:
    SatAutoSavePicturePage(QWidget *parent = 0);
    int getData();
    void setData(int nData);
signals:
protected:
    void paintEvent(QPaintEvent *event);
    void changeEvent(QEvent *event);
private slots:
private:
private:
    int mData;
};




class AutoSavePictureWidget : public QWidget
{
    Q_OBJECT
public:
    AutoSavePictureWidget(QWidget *parent = 0);
public slots:
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void paintEvent(QPaintEvent *event);
    void changeEvent(QEvent *event);
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
    SatAutoSavePicturePage *mPage;
    SatAutoSavePictureSmallWidget *mSmallWidget;
    SatTitleBar *mSatTitleBar;

};
#endif



#endif // AUTOSAVEPICTUREWIDGET_H
