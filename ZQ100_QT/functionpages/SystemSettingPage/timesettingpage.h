#ifndef TIMESETTINGPAGE_H
#define TIMESETTINGPAGE_H

#include <QWidget>
#include <QDialog>
#include "globalparam.h"

class TitleBar;
class QLabel;

class TimeSettingPage : public QDialog
{
    Q_OBJECT
public:
    explicit TimeSettingPage(QWidget *parent = 0);
    void initView();

private slots:
    void on_titleBarClicked(GlobalParam::ButtonType id, bool status);
    void updateTime();
    void showSettingPage(int);

private:
    //标题栏
    bool m_showColon;
    TitleBar *m_titleBar;

    QWidget *centralWidget;

    QLabel *m_dateLabel;
    QLabel *m_timeLabel;
    QLabel *m_timezoneLabel;
};

#endif // TIMESETTINGPAGE_H
