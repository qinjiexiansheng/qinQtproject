#ifndef SATTITLEBAR_H
#define SATTITLEBAR_H

#include "globalparam.h"

#define DEF_WIDTH    320
#define DEF_HEIGHT   30

class TitleBar : public QWidget
{
    Q_OBJECT
public:
public:
    explicit TitleBar(QWidget *parent=0,
                      GlobalParam::TitleBarStyle type=GlobalParam::TitleBarStyle::DOUBLE_BUTTON, int height = DEF_HEIGHT,
                      int width = DEF_WIDTH);

    void setText(QString title = "UNTITLED",
                 QString button1 = "BACK",
                 QString button2 = "SAVE");
    void setSwitchState(bool val);
    bool getSwitchState();
    void setSwitchEnable(bool val);
    bool switchIsEnable();
signals:
    //id: 0 LEFT BUTTON     status: always false.
    //    1 RIGHT BUTTON            always false.
    //    2 SWITCH BUTTON           checked status.
    void clicked(GlobalParam::ButtonType id, bool status);

private:
    void initView(GlobalParam::TitleBarStyle type, int width, int height);

private slots:
    void on_clicked(bool status);

private:
    QLabel *m_title;
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_switch;
};

#endif // SATTITLEBAR_H
