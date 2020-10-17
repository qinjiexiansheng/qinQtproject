#ifndef DIGITKEYBOARD_H
#define DIGITKEYBOARD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "littlewidget.h"
#define KEYBOARD_ROWS_DIG 4
#define KEYBOARD_COLS_DIG 4

class DigitKeyboard : public QDialog
{
    Q_OBJECT
public:
    DigitKeyboard(QString &nStr , QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void handleContent(const QString &nStr);//处理字符
private:
    void focusNext();//下一焦点
    void focusPrevious();//上一焦点
    void focusLeft();//左焦点
    void focusRight();//右焦点
    QString *mInput;//输入字符串
    int mRowIndex;//行索引
    int mColIndex;//列索引
    QList<QPushButton*> mList;//焦点列表
    QLineEdit *mLineEdit;
};

#endif // DIGITKEYBOARD_H
