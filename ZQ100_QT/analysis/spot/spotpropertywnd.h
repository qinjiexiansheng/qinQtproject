#ifndef SPOTPROPERTYWND_H
#define SPOTPROPERTYWND_H

#include "globalparam.h"

class Spot;
class TitleBar;
class ComboBox;
class SpinBox;

//Spot的属性结构体
struct SpotProperty
{
    //property
    int displayMode;    //0:hide 1:show
    int analysisMode;   //0:Manual 1:max 2:min
    int posShowMode;    //0:off 1:on
    int tempShowMode;   //0:off 1:on
    int backgroundMode; //0:hide 1:show
    int alarmMode;      //0:off 1:above 2:below 3:equal
    float alarmTempVal; //alram temp val
};

class SpotPropertyWnd : public QDialog
{
    Q_OBJECT
public:
    explicit SpotPropertyWnd(Spot *spot);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void accept();
    void reject();
    int exec();

private slots:
    void on_clicked(GlobalParam::ButtonType id, bool status);
    void sendAlarmTemp(QString);

private:
    void initView();
    void initStates(const SpotProperty spotProperty);

private:
    //属性窗口服务的Spot指针
    Spot *m_spot;
    TitleBar *m_titleBar;
    QWidget *m_mainWidget;

    //属性控件
    ComboBox *displayCombobox;
    ComboBox *modeCombobox;
    ComboBox *posShowCombobox;
    ComboBox *tempShowCombobox;
    ComboBox *backgroundCombobox;
    ComboBox *alarmModeCombobox;
    SpinBox *alarmTempSpinBox;
};

#endif // SPOTPROPERTYWND_H
