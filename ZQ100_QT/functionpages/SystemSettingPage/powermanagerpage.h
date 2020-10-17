#ifndef POWERMANAGERPAGE_H
#define POWERMANAGERPAGE_H

#include <QWidget>
#include <QDialog>
#include "globalparam.h"

class TitleBar;
class QLabel;

class PowerManagerPage : public QDialog
{
    Q_OBJECT
public:
    explicit PowerManagerPage(QWidget *parent = 0);

private:
    void initView();
    void updateLabels();

private slots:
    void on_titleBarClicked(GlobalParam::ButtonType id, bool status);
    void showSettingPage(int);

private:
    //标题栏
    TitleBar *m_titleBar;

    QWidget *centralWidget;

    QLabel *m_screenSaverLabel;
    QLabel *m_powerOffLabel;
};

#endif // POWERMANAGERPAGE_H
