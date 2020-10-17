#ifndef TABPAGE_H
#define TABPAGE_H

#include "littlewidget.h"
#include <QWidget>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QEvent>
#include <QTimer>
#include <QList>
#include <QObject>
#include "satdefine.h"
#include <QVBoxLayout>


class TabPageOne : public QWidget
{
   // Q_OBJECT
public:
    TabPageOne(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *se);//显示事件

 private:
    SatButton *nAdjustOpenButton;
    SatButton *nAdjustOpenButton2;
    void focusNext();
    void focusPrevious();
    int mIndex;
    QList<SatButton*> mList;

};


class TabPageTwo : public QWidget
{
    Q_OBJECT
public:
    TabPageTwo(QWidget *parent = 0);
     SatButton *nSettingButton;

signals:
    void clicked(TabPageTwo *);

private slots:
        void satbuttonClicked();

};



#endif // TABPAGE_H
