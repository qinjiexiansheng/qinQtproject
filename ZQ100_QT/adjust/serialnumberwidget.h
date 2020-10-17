#ifndef SERIALNUMBERWIDGET_H
#define SERIALNUMBERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include "littlewidget.h"

class SerialNumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialNumberWidget(QWidget *parent = 0);
    ~SerialNumberWidget();

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件

private slots:
    void buttonClose();

private:
    QLabel *serialNumberLabel;
    QPushButton *serialButton;
    QLineEdit *serialLineEdit;
    QGridLayout *nGridLayout;
    int mSerialNumber;
    void focusNext();
    void focusPrevious();
    QList<QWidget*> mList;
    int mIndex;
};

#endif // SERIALNUMBERWIDGET_H
