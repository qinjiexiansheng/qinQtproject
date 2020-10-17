#ifndef LCOMBOBOX_H
#define LCOMBOBOX_H

#include "globalparam.h"

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

signals:

public slots:
};

#endif // LCOMBOBOX_H
