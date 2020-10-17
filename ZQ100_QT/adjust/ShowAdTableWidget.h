#ifndef SHOWADTABLEWIDGET_H
#define SHOWADTABLEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include "littlewidget.h"
#include "QVBoxLayout"
#include <QLabel>

class ShowAdTableWidget : public QWidget
{
    Q_OBJECT

public:
    ShowAdTableWidget(QWidget *parent = 0);
    void loadFile();
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤
    void showEvent(QShowEvent *event);
private:
    QTextBrowser *mView;
    QLabel *TitleLable;
    QVBoxLayout *nVBoxLayout;

};

#endif // SHOWADTABLEWIDGET_H
