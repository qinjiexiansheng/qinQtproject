#ifndef SATTABWIDGET_H
#define SATTABWIDGET_H

#include <QTabWidget>
#include "tabpageone.h"
#include "tabpagetwo.h"
#include "tabpagethree.h"
#include "tabpagefour.h"
#include "TabPageFive.h"

class SatTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SatTabWidget(QWidget *parent = 0);
    ~SatTabWidget();
protected:
    bool eventFilter(QObject *obj, QEvent *ev);
    void showEvent(QShowEvent *se);

private:
    TabPageOne *nTabePageOne;
    TabPageTwo *nTabePageTwo;
    TabPageThree *nTabPageThree;
    TabPageFour *nTabPageFour;
    TabPageFive *nTabPageFive;
    int mMaxIndex;
    void nextTab();
    void prevTab();
};

#endif // SATTABWIDGET_H
