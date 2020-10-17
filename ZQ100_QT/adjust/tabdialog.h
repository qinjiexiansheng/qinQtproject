#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include "sattabwidget.h"

/*===========================
 
  
 ============================*/ 

class TabDialog:public QDialog
{
public:
    TabDialog(QWidget *parent =0);

protected:
//    bool eventFilter(QObject *obj, QEvent *ev);
    void keyPressEvent(QKeyEvent *event);
  //  void showEvent(QShowEvent *se);

private:
    SatTabWidget *mTabWidget;
    int mMaxIndex;
    
};

#endif // TABDIALOG_H
