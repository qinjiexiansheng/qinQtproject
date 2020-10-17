#ifndef STANDARDPARAMSETTING_H
#define STANDARDPARAMSETTING_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "spinboxstandard.h"
#include "fpga/fpgaInterface.h"

class Standardparamsetting: public QWidget
{
    Q_OBJECT
public:
    Standardparamsetting(QWidget *parent = 0);
    ~Standardparamsetting();

    unsigned char getStandardparamsVsk();
    unsigned char getStandardparamsFid();
    unsigned char getStandardparamsGain();
    void loadIRParameter();


protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void keyPressEvent(QKeyEvent *ke);
    virtual void showEvent ( QShowEvent * );
protected slots:
    void spinBoxChange(const QString &text);
private:
    void okClicked();
    void cancleClicked();
    void saveIRParameter();

    static unsigned char s_vsk;
    static unsigned char s_fid;
    static unsigned char s_gain;
    static int  s_dly;
    static int  s_level;
    static float s_span;

private:
    void layoutInit();

    QLabel  *m_tempRange;
    QLabel  *m_tempRangeBtn;

    QLabel *m_vskLabel;
    SpinBoxStandard *m_vskBtn;

    QLabel *m_fidLabel;
    SpinBoxStandard *m_fidBtn;

    QLabel *m_gainLabel;
    SpinBoxStandard *m_gainBtn;

    QLabel *_dlyLabel;
    SpinBoxStandard *m_dlyBtn;

    QLabel *_levelspanLabel;
    SpinBoxStandard *m_levelBtn;

    QLabel *_spanLabel;
    SpinBoxStandard *m_spanBtn;

    QLabel *m_adLabel;
    QLabel *m_ad;

    QLabel *m_Lens;
    QLabel *m_lensLaber;

    QPushButton *m_okBtn;
    QPushButton *m_cancleBtn;

    QList<QWidget*>  m_list;
    int focusIndex;

};

#endif // STANDARDPARAMSETTING_H
