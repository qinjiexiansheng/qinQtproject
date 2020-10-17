#ifndef SYSTEMSETTINGPAGE_H
#define SYSTEMSETTINGPAGE_H

#include <QWidget>
#include <QDialog>

class OptionsListWidget;

class SystemSettingPage : public QDialog
{
    Q_OBJECT
public:
    explicit SystemSettingPage(QWidget *parent = 0);

signals:

private slots:
    void optionsClicked(int index);

private:
     OptionsListWidget *centralWidget;
};

#endif // SYSTEMSETTINGPAGE_H
