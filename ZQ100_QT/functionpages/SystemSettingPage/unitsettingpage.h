#ifndef UNITSETTINGPAGE_H
#define UNITSETTINGPAGE_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>

class SwitchButton;

class UnitSettingPage : public QDialog
{
    Q_OBJECT
public:
    explicit UnitSettingPage(QWidget *parent = 0);

protected:
    void accept();
    void keyPressEvent(QKeyEvent *e);
private:
    void initView();
    void updateLabels();

private:
    SwitchButton *m_lengthSwitch;
    SwitchButton *m_tempSwitch;
};

#endif // UNITSETTINGPAGE_H
