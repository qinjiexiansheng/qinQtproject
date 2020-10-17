#ifndef EMISSIVITYTABLEWIDGET_H
#define EMISSIVITYTABLEWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QKeyEvent>
#include "view/littlewidget.h"
#include <QStackedWidget>
#include <QTableWidget>
#include <QScrollBar>


#include <QHeaderView>

class SatEmissivityTableSmallWidget : public QWidget
{
    Q_OBJECT
public:
    SatEmissivityTableSmallWidget(QWidget *parent = 0);
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



class SatEmissivityTablePage : public QTableWidget
{
    Q_OBJECT
public:
    SatEmissivityTablePage(QWidget *parent = 0);
public slots:
    void moveUpSlot();
    void moveDownSlot();
    void leftShiftSlot();
    void rightShiftSlot();
};




class EmissivityTableWidget : public QWidget
{
    Q_OBJECT
public:
    EmissivityTableWidget(QWidget *parent = 0);
signals:
protected:

    void changeEvent(QEvent *event);

    void showEvent(QShowEvent *event);
    void focusInEvent(QFocusEvent *event);
    bool eventFilter(QObject *nObject, QEvent *event);
private slots:
    void goBackSlot();
    void operationSlot(QString nOpeStr);
private:
    void focusPrevious();
    void focusNext();
private:
    SatTitleBar *mSatTitleBar;
    SatEmissivityTableSmallWidget *mSmallWidget;
    SatEmissivityTablePage *mRightWidget;
};

#endif // EMISSIVITYTABLEWIDGET_H
