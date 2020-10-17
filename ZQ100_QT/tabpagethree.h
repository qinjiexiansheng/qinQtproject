#ifndef TABPAGETHREE_H
#define TABPAGETHREE_H

#include <QWidget>

namespace Ui {
class TabPageThree;
}

class TabPageThree : public QWidget
{
    Q_OBJECT

public:
    explicit TabPageThree(QWidget *parent = 0);
    ~TabPageThree();

private:
    Ui::TabPageThree *ui;
};

#endif // TABPAGETHREE_H
