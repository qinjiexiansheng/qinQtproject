#ifndef TABPAGEFOUR_H
#define TABPAGEFOUR_H

#include <QWidget>
#include "littlewidget.h"
#include <QSignalMapper>
#include "serialnumberwidget.h"
#include "SetDateWidget.h"

class TabPageFour : public QWidget
{
    Q_OBJECT

public:
    explicit TabPageFour(QWidget *parent = 0);
    ~TabPageFour();

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件

private:
    QSignalMapper *nSignalMapper;
    QVBoxLayout *nLayout;
    SatButton *nSerialNumberButton;
    SatButton *nSetFactoryDateButton;
    SatButton *nTableToSDButton;
    SatButton *nSDToTableButton;
    SerialNumberWidget *nSerialNumberWidget;
    SetDateWidget *nSetDateWidget;
    void focusNext();
    void focusPrevious();
    QList<SatButton*> mList;
    int mIndex;

private slots:
    void handleContent(const QString &nStr);


};

#endif // TABPAGEFOUR_H
