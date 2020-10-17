#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include "view/littlewidget.h"
#include "model/satdata.h"
#include "controller/satcontrol.h"
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QStackedWidget>

class SatDateTimeListWidget : public QWidget
{
    Q_OBJECT
public:
    SatDateTimeListWidget(QWidget *parent = 0);
signals:
    void indexChangeSignal(int nIndex);//索引改变信号，当控件切换时发出
    void focusTransferSignal();//焦点转让信号，当点击确认键发出
    void goBackSignal();//返回信号
protected:

    void changeEvent(QEvent *event);

    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);//焦点进入事件
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件过滤方法
private:
    void focusNext();//焦点移到下一控件
    void focusPrevious();//焦点移到上一控件
    void proofreadIndex();
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};






class SatDateTimePageOne : public QWidget
{
    Q_OBJECT
public:
    SatDateTimePageOne(QWidget *parent = 0);
signals:
    void focusTransferSignal();
protected:

    void changeEvent(QEvent *event);

    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//校正焦点索引，在mouseReleaseEvent中被调用，将索引改为有焦点的部件
    void updateData(bool nIsGet = true);
    void updatePanel();//更新数据显示面板
    void modifyYear(bool nIsAdd);
    void modifyMonth(bool nIsAdd);
    void modifyDay(bool nIsAdd);
    int numberDay(int nYear,int nMonth);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<QPushButton*> mList;
    QStringList *mStringList;
    int mYear;
    int mMonth;
    int mDay;
    QLabel *mLabel;
};



class SatDateTimePageTwo : public QWidget
{
    Q_OBJECT
public:
    SatDateTimePageTwo(QWidget *parent = 0);
signals:
    void focusTransferSignal();
protected:

    void changeEvent(QEvent *event);

    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//校正焦点索引，在mouseReleaseEvent中被调用，将索引改为有焦点的部件
    void updateData(bool nIsGet = true);
    void updatePanel();//更新数据显示面板
    void modifyHour(bool nIsAdd);
    void modifyMinute(bool nIsAdd);
    void modifySecond(bool nIsAdd);
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<QPushButton*> mList;
    QStringList *mStringList;
    int mHour;
    int mMinute;
    int mSecond;
    QLabel *mLabel;
};




class SatDateTimePageThreeListWidget : public QWidget
{
    Q_OBJECT
public:
    SatDateTimePageThreeListWidget(QWidget *parent = 0);
    QString getSelectTimeZone();
signals:
    void focusTransferSignal();//焦点转让信号，当点击确认键发出
protected:

    void changeEvent(QEvent *event);

    void showEvent(QShowEvent *event);//显示事件
    void focusInEvent(QFocusEvent *event);//焦点进入事件
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件过滤方法
private:
    void focusNext();//焦点移到下一控件
    void focusPrevious();//焦点移到上一控件
    void proofreadIndex();
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<SatButton*> mList;
    QStringList *mStringList;
};





class SatDateTimePageThree : public QWidget
{
    Q_OBJECT
public:
    SatDateTimePageThree(QWidget *parent = 0);
signals:
    void focusTransferSignal();
protected:

    void changeEvent(QEvent *event);

    void focusInEvent(QFocusEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);//事件监听
private:
    void focusNext();
    void focusPrevious();
    void proofreadIndex();//校正焦点索引，在mouseReleaseEvent中被调用，将索引改为有焦点的部件
private slots:
    void focusUpToDownSlot();
    void handleContent(const QString &nStr);//处理按键操作
private:
    int mIndex;
    QList<QPushButton*> mList;
    QStringList *mStringList;
    SatDateTimePageThreeListWidget *mListWidget;
    SatScrollArea *mScrollArea;
};



class DateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    DateTimeWidget(QWidget *parent = 0);
public slots:
signals:
protected:
    void changeEvent(QEvent *event);
private slots:
    void focusLeftToRightSlot();
    void focusRightToLeftSlot();
    void itemChangeSlot(int nIndex);
    void goBackSlot();
private:
private:
    SatDateTimeListWidget *mLeftWidget;
    QStackedWidget *mRightWidget;
    SatTitleBar *mSatTitleBar;

};

#endif // DATETIMEWIDGET_H
