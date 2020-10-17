#ifndef STANDARD_H
#define STANDARD_H

#include <QMainWindow>

namespace Ui {
class Standard;
}

class Standard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Standard(QWidget *parent = 0);
    ~Standard();

private:
    Ui::Standard *ui;
};

#endif // STANDARD_H
