#ifndef DATESLIDEEDITOR_H
#define DATESLIDEEDITOR_H

#include "globalparam.h"

#define H_SPACING 20
#define V_SPACING 30

class SlideArea;

class DateEditor : public QDialog
{
    Q_OBJECT
public:
    DateEditor(QWidget *parent = 0, int H_Spacing = H_SPACING, int V_Spacing = V_SPACING);

private:
    void initView();
    void adjustLayout();
    void installData();
    int getDaysInMonth(int year,int month);

protected:
    void accept();
    void keyPressEvent(QKeyEvent *e);

private slots:
    void adjustDay();

private:
    int m_hSpacing;
    int m_vSpacing;

    QLabel *m_title;
    QPushButton *m_LButton;
    QPushButton *m_RButton;

    SlideArea *m_monthArea;
    SlideArea *m_dayArea;
    SlideArea *m_yearArea;

    QLabel *m_dot;
    QLabel *m_dot2;
    int m_decimals;
};

#endif // DATESLIDEEDITOR_H
