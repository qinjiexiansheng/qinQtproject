#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "globalheader.h"

class KeyBoard : public QDialog
{
    Q_OBJECT

public:
    KeyBoard(QWidget *parent = 0);
    KeyBoard(QLineEdit *target, QWidget *parent = 0);
    ~KeyBoard();

    void initView();
    void setTarget(QLineEdit *target);

private slots:
    void addDot();
    void deleteInput();
    void clearInput();
    void updateText(int val);
    void exitConfirmWnd();

private:
    QLineEdit *m_target;
    QLineEdit *m_previewLabel;
};

#endif // KEYBOARD_H
