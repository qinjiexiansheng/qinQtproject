#ifndef TABPAGEONE_H
#define TABPAGEONE_H

#include <QWidget>
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
#include <QSignalMapper>

class TabPageOne : public QWidget
{
    Q_OBJECT
public:
    TabPageOne(QWidget *parent = 0);
    ~TabPageOne();
//    int myKey;

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
 //   void keyReleaseEvent(QKeyEvent *event);
 //   void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *se);//显示事件

private  slots:
    void handleContent(const QString &nStr);

private:
    SatButton *nAdjustOpenButton;
    SatButton *nAdjustSaveButton;
    QSignalMapper *nSignalMapper;
    void focusNext();
    void focusPrevious();
    int mIndex;
   QList<SatButton*> mList;

};

#endif // TABPAGEONE_H
