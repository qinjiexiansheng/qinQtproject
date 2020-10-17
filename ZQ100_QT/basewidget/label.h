#ifndef LABEL_H
#define LABEL_H

#include "globalheader.h"

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void click();

public slots:
};

#endif // LABEL_H
