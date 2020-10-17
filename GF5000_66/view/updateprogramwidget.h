#ifndef UPDATEPROGRAMWIDGET_H
#define UPDATEPROGRAMWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QDir>
#include <QListWidget>
#include <QFileInfo>

#include "view/smallwidget.h"


#if 0
class SatUpdateListWidget : public QWidget
{
    Q_OBJECT
public:
    SatUpdateListWidget(QString nDirString,QWidget *parent = 0);
    QString getUpdateFile();//获取更新文件名
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//移出焦点
protected:
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//校正焦点索引
    void queryUpdateInfo();
private:
    int mIndex;
    QList<SatButton*> mList;
    QList<QFileInfo> mFileInfoList;
    QString mDirString;
};
#endif

#if 1
class SatUpdateListWidget : public QWidget
{
    Q_OBJECT
public:
    SatUpdateListWidget(QString nDirString,QWidget *parent = 0);
    QString getUpdateFile();//获取更新文件名
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//移出焦点
protected:
    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
    void indexChangeSlot(int nIndex);
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//校正焦点索引
    void queryUpdateInfo();
private:
    QList<QFileInfo> mFileInfoList;
    QString mDirString;
    QListWidget *mListWidget;

};
#endif



class SatUpdateSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatUpdateSmallWidget(QWidget *parent = 0);
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






#if 0
class SatUpdatePage : public QWidget
{
    Q_OBJECT
public:
    SatUpdatePage(QWidget *parent = 0);
    void setInfoText(QString nInfoText);
signals:
    void goBackSignal();
    void focusTransferSignal();
    void updateProgramSignal();
    void backupProgramSignal();
    void recoveryProgramSignal();
protected:
    void focusInEvent(QFocusEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
    void handleContent(const QString &nStr);
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QLabel *mInfoLabel;
    QList<SatButton*> mList;
    QStringList *mStringList;
};
#endif





class UpdateProgramWidget : public QWidget , public DataObserver
{
    Q_OBJECT
public:
    UpdateProgramWidget(QWidget *parent = 0);
    void doUpdate(QString nStr);
    void registerField();//注册监听字段
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
    void doUpdateSignal(QString nOpeStr);

public slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void goBackSlot();
    void operationSlot(QString nOpeStr);
    void indexChangeSlot(int nIndex);

    void doUpdateSlot(QString nOpeStr);

protected:
    void showEvent(QShowEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private:
    void updateLabel();
private:
    SatScrollArea *mLeftWidget;
    SatUpdateListWidget *mListWidget;
#if 0
    SatUpdatePage *mRightWidget;
#endif

    SatUpdateSmallWidget *mSmallWidget;
    QLabel *mLabel;
    SatTitleBar *mSatTitleBar;
};

#endif // UPDATEPROGRAMWIDGET_H
