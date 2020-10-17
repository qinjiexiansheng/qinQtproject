#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "view/littlewidget.h"
#include "uitls/interface.h"
#include <QPainter>
#include "model/satdata.h"
#include <QSignalMapper>
#include "controller/satcontrol.h"
#include <QKeyEvent>
#include "view/picturebrowingwidget.h"
#include "view/systemwidget.h"
#include <QMovie>


#include "view/videowidget.h"




class SatSchemaWidget : public QWidget
{
    Q_OBJECT
public:
    SatSchemaWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusOutEvent(QFocusEvent *event);//焦点移出事件
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private:
    void focusNext();
    void focusPrevious();
private slots:
    void handleContent(int nIndex);//处理按键操作
private:
    int mIndex;
    QList<SatPhotoHighLightButton*> mList;
    SatData *mSatData;
};

















class SatMainSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatMainSmallWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
    void focusOutEvent(QFocusEvent *event);//焦点移出事件
signals:
private:
    void focusNext();
    void focusPrevious();
private slots:
    void handleContent(const QString &nOpeStr);//处理按键操作
private:
    int mIndex;
    QList<SatPhotoButton*> mList;
    SatSchemaWidget *mSchemaWidget;
    PictureBrowingWidget *mPictureBrowingWidget;
    SystemWidget *mSystemWidget;



    VideoBrowingWidget *mVideoWidget;


};













#endif // USERWIDGET_H
