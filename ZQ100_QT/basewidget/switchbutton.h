#ifndef SWITCH_H
#define SWITCH_H

#include "globalparam.h"

class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0, QString text0 = "OFF", QString text1 = "ON");

    void setState(bool);
    bool getState();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void buttonClicked(int);

private:
    QPushButton *m_leftBtn;
    QPushButton *m_rightBtn;
    bool m_state;
};

#endif // SWITCH_H
