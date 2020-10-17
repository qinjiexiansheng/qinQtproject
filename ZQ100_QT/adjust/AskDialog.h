#ifndef ASKDIALOG_H
#define ASKDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QList>
#include "littlewidget.h"
#include <QString>
class AskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AskDialog(QString nStr, QString nStr1, QWidget *parent );
    ~AskDialog();
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听

private:
    void focusNext();
    void focusPrevious();
    QLabel *nWarnLable;
    QLabel *nAskLable;
    QPushButton *nYesButton;
    QPushButton *nNoButton;
    QGridLayout *nGridLayout;
    QList<QPushButton*> mList;
    int mIndex;

};

#endif // ASKDIALOG_H
