#ifndef HEXADECIMALKEYBOARD_H
#define HEXADECIMALKEYBOARD_H

#include <QDialog>
#include "littlewidget.h"
#include <QLineEdit>
#include <QString>

#define KEYBOARD_ROWS_HEX 5
#define KEYBOARD_COLS_HEX 5

class HexadecimalKeyboard : public QDialog
{
    Q_OBJECT
public:
    HexadecimalKeyboard(QString &nStr, QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
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
};

#endif // HEXADECIMALKEYBOARD_H
