#ifndef MODIFYADTABLEWIDGET_H
#define MODIFYADTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStringList>
#include <QEvent>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QScrollBar>
#include <QLabel>
#include "uitls/macrodefine.h"
#include "uitls/operationfield.h"
#include "view/softkeyboard.h"
#include "controller/satcontrol.h"
#include "model/satdata.h"
#include "view/littlewidget.h"

/*======================================

  修改AD表窗口 ： ModifyAdTableWidget

  ======================================*/
class ModifyAdTableWidget : public QWidget
{
    Q_OBJECT
public:
    ModifyAdTableWidget(QWidget *parent = 0);
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj,QEvent *event);//事件监听
    void showEvent(QShowEvent *se);
    void paintEvent(QPaintEvent *event);
private:
    void focusNext();//下一焦点
    void focusPrevious();//上一焦点
    QStandardItemModel *mModel;
    QTableView *mView;//视图
    SatTitleBar *mSatTitleBar;
    SatData *mSatData;
};

/*======================================

  显示AD表窗口 ： ShowAdTableWidget

  ======================================*/
class ShowAdTableWidget : public QWidget
{
    Q_OBJECT
public:
    ShowAdTableWidget(QWidget *parent = 0);
    void loadFile();
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QTextBrowser *mView;
    SatTitleBar *mSatTitleBar;
    SatData *mSatData;
};





#endif // MODIFYADTABLEWIDGET_H
