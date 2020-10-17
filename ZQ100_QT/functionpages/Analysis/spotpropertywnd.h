#ifndef SPOTPROPERTYWND_H
#define SPOTPROPERTYWND_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include "globalparam.h"

class Spot;
class TitleBar;
class ComboBox;
class SpinBox;

struct SpotProperty
{
    //property
    int displayIndex = 1;
    int modeIndex = 0;
    int posIndex = 0;
    int tempIndex = 1;
    int backgroundIndex = 0;
    int alarmModeIndex = 0;
    int alarmTempValue = 0.0;
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

private slots:
    void on_clicked(GlobalParam::ButtonType id, bool status);

    void setDisplayState(int val);

private:
    void initView();
    void setStates(const SpotProperty &spotProperty);

private:
    Spot *m_spot;
    TitleBar *m_titleBar;
    QWidget *m_mainWidget;

    ComboBox *displayCombobox;
    ComboBox *modeCombobox;
    ComboBox *posCombobox;
    ComboBox *tempCombobox;
    ComboBox *backgroundCombobox;
    ComboBox *alarmCombobox;
    SpinBox *alarmTempSpinBox;

    SpotProperty m_property;



};

#endif // SPOTPROPERTYWND_H
