#ifndef EXAMPLEPAGE_H
#define EXAMPLEPAGE_H

#include "globalparam.h"

class ExamplePage : public QWidget
{
    Q_OBJECT
public:
    ExamplePage(QWidget *parent = 0, QString text = "Examples", int btnNum = 4);

signals:
    void buttonClicked(int);
public slots:
};

#endif // EXAMPLEPAGE_H
