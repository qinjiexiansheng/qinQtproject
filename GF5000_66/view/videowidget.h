#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QImage>
#include <QListWidget>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QPixmap>
#include "view/littlewidget.h"
#include "view/smallwidget.h"
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include "controller/videodecode.h"
#include <QThread>

//单个视频播放界面的操作小窗口
class SatVideoSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatVideoSmallWidget(QWidget *parent = 0);
signals:
    void operationSignal(QString nOpeStr);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
    void showEvent(QShowEvent *event);
private:
    void focusNext();
    void focusPrevious();
private slots:
    void handleContent(const QString &nOpeStr);
private:
    int mIndex;
    QList<SatPhotoButton*> mList;
};


class SatVideoWidget : public QWidget
{
    Q_OBJECT
public:
    SatVideoWidget(QWidget *parent = 0);
    QString getVideoStr();
    void setVideoStr(QString nVideoStr);
signals:
public slots:
    void showImage(QImage nImage);
protected:
    bool eventFilter(QObject *nObject, QEvent *event);
    void showEvent(QShowEvent *event);
private slots:
    void operationSlot(QString nOpeStr);
    void goBackSlot();
private:
    QString mVideoStr;//视频文件路径
    SatTitleBar *mSatTitleBar;
    QLabel *mImageLabel;
    SatVideoSmallWidget *mSmallWidget;
    VideoDecode *mVideoDecode;
};






class SatVideoBrowingSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatVideoBrowingSmallWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
    void showEvent(QShowEvent *event);//显示事件
signals:
    void operationSignal(QString nOpeStr);
private:
    void focusNext();
    void focusPrevious();
private slots:
    void handleContent(const QString &nOpeStr);//处理按键操作
private:
    int mIndex;
    QList<SatPhotoButton*> mList;
};

class VideoBrowingWidget : public QWidget
{
    Q_OBJECT
public:
    VideoBrowingWidget(QString nDirStr,QWidget *parent = 0);
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
    void ergodicVideo();//遍历
    void focusPrevious();
    void focusNext();
private:
    QString mDirStr;
    SatTitleBar *mSatTitleBar;
    QListWidget *mListWidget;
    SatVideoBrowingSmallWidget *mSmallWidget;
    SatVideoWidget *mViewWidget;
};




#endif // VIDEOWIDGET_H
