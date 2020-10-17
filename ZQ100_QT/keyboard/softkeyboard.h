#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H

#include <QDialog>
#include <QList>
#include <QPushButton>
#include <QLineEdit>
#include <QSignalMapper>
#include <QGridLayout>
#include <QFile>
#include <QEvent>
#include <QKeyEvent>
#include "macrodefine.h"
#include "littlewidget.h"
#define KEYBOARD_ROWS_DIG 4
#define KEYBOARD_COLS_DIG 4
#define KEYBOARD_ROWS_HEX 5
#define KEYBOARD_COLS_HEX 5
/*======================================

  数字键盘 ： DigitKeyboard

  ======================================*/
class DigitKeyboard : public QDialog
{
    Q_OBJECT
public:
    DigitKeyboard(QString &nStr , QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);
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
    SatTitleBar *mSatTitleBar;
};

/*======================================

  十六进制键盘 ： HexadecimalKeyboard
  同数字键盘，只是多了几个字符输入，布局不一样

  ======================================*/
class HexadecimalKeyboard : public QDialog
{
    Q_OBJECT
public:
    HexadecimalKeyboard(QString &nStr , QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void handleContent(const QString &nStr);
private:
    void focusNext();
    void focusPrevious();
    void focusLeft();
    void focusRight();
    QString *mInput;
    int mRowIndex;
    int mColIndex;
    QList<QPushButton*> mList;
    QLineEdit *mLineEdit;
    SatTitleBar *mSatTitleBar;
};






#endif // SOFTKEYBOARD_H
