#ifndef WIFIMANAGERPAGE_H
#define WIFIMANAGERPAGE_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include "globalparam.h"
#include "keyboard/keyboard.h"

class TitleBar;
class QLineEdit;
class QPushButton;
class QProcess;

class WifiManagerPage : public QDialog
{
    Q_OBJECT
public:
    explicit WifiManagerPage(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);


private slots:
    void btnGroupClicked(int id);
    void on_titleBarClicked(GlobalParam::ButtonType id, bool status);

private:
    void readWifi();
    void setWifi();

private:
    QWidget *centralWidget;
    TitleBar *m_titleBar;
    QLineEdit *m_wifiNameEdit;
    QLineEdit *m_wifiPasswdEdit;
    QPushButton *m_stopBtn;
    QPushButton *m_startBtn;

    QString m_curWifiName;
    QString m_curWifiPasswd;

    QProcess *pro;

    KeyBoard *m_keyboard;
};

#endif // WIFIMANAGERPAGE_H
