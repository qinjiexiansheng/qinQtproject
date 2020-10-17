#ifndef LITTLEWIDGET_H
#define LITTLEWIDGET_H

#include <QPushButton>
#include <QLineEdit>
#include <QStyle>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QScrollBar>
#include <QScrollArea>
#include <QKeyEvent>
#include <QWidget>
#include "satdefine.h"
//#include "tabpageone.h"




class SatButton : public QPushButton
{
    Q_OBJECT
public:
    SatButton (const QString &nText, QWidget *parent = 0);

protected:
   // void mousePressEvent(QMouseEvent *event);
      void keyPressEvent(QKeyEvent *event);
  //    void keyReleaseEvent(QKeyEvent *event);
   //   void enterEvent(QEvent*);
 //     void leaveEvent(QEvent*);

private slots:
    void switchOnState();

};


#endif // LITTLEWIDGET_H
