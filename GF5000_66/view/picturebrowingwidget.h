#ifndef PICTUREVIEWWIDGET_H
#define PICTUREVIEWWIDGET_H

#include <QWidget>
#include "view/littlewidget.h"
#include <QListWidget>
#include <QKeyEvent>
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QSignalMapper>
#include <QPixmap>
#include "view/smallwidget.h"

//单张图片显示的底部小窗口
class SatPictureViewSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatPictureViewSmallWidget(QWidget *parent = 0);
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


//单张图片显示控件
class SatPictureLabel : public QLabel
{
    Q_OBJECT
public:
    SatPictureLabel(QString nPicStr,QWidget *parent = 0);
    QString getPicStr();
    void setPicStr(QString nPicStr);

    void setZoomFactor(float nZoomFactor);
    float getZoomFactor();


signals:
public slots:
protected:
    void paintEvent(QPaintEvent *event);
private slots:
private:
private:
    int mWidth;
    int mHeight;
    float mZoomFactor;
    QString mPicStr;
};


//单张图片显示窗口
class SatPictureViewWidget : public QWidget
{
    Q_OBJECT
public:
    SatPictureViewWidget(QString nPicStr,QWidget *parent = 0);
    QString getPicStr();
    void setPicStr(QString nPicStr);
signals:
public slots:
protected:
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
private slots:
    void operationSlot(QString nOpeStr);
    void goBackSlot();
private:
    void showPhotoPrevious();
    void showPhotoNext();
    void getImgInfoList();
private:
    QString mPicStr;
    SatTitleBar *mSatTitleBar;
    SatPictureLabel *mPictureLabel;
    SatPictureViewSmallWidget *mSmallWidget;
    SatScrollArea *mScrollArea;
    QFileInfoList *mImgInfoList;
    int mIndex;
};






//图片缩略图按键小窗口
class SatPictureBrowingSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatPictureBrowingSmallWidget(QWidget *parent = 0);
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

//图片缩略图窗口
class PictureBrowingWidget : public QWidget
{
    Q_OBJECT
public:
    PictureBrowingWidget(QString nDirStr,QWidget *parent = 0);
    QString getDirStr();
    void setDirStr(QString nDirStr);
signals:
public slots:
protected:
    void showEvent(QShowEvent *event);
    void focusInEvent(QFocusEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
    void goBackSlot();
    void operationSlot(QString nOpeStr);
private:
    void ergodicPicture();//遍历
    void focusPrevious();
    void focusNext();
private:
    QString mDirStr;
    SatTitleBar *mSatTitleBar;
    QListWidget *mListWidget;
    SatPictureBrowingSmallWidget *mSmallWidget;
    SatPictureViewWidget *mViewWidget;

};

#endif // PICTUREVIEWWIDGET_H
