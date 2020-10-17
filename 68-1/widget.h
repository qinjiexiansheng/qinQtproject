#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QGroupBox *m_group;
    QRadioButton *m_freeBtn;
    QRadioButton *m_lineBtn;
    QRadioButton *m_rectBtn;
    QRadioButton *m_ellipseBtn;
    QComboBox *m_colorBox;
};

#endif // WIDGET_H
