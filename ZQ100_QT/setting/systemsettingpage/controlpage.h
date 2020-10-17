#ifndef CONTROLPAGE_H
#define CONTROLPAGE_H

#include "globalparam.h"

class OptionsListWidget;

class ControlPage : public QDialog
{
    Q_OBJECT
public:
    explicit ControlPage(QWidget *parent = 0);

private slots:
    void optionsClicked(int index);

private:
    void updateView();

private:
    OptionsListWidget *centralWidget;
};

#endif // CONTROLPAGE_H
