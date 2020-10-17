#ifndef LGLOBALPARAMPAGE_H
#define LGLOBALPARAMPAGE_H

#include <QDialog>

class QLabel;
class SpinBox;
class ComboBox;

class GlobalParamPage : public QDialog
{
    Q_OBJECT

public:
    GlobalParamPage(QWidget *parent = 0);

    void initView();
protected:
    void keyPressEvent(QKeyEvent *e);

public slots:
    void processEvent();
    void createSlideWindow(SpinBox *p);

private:
    void applyValue();

public:
    QLabel *m_title;
    QPushButton *m_leftBtn;
    QPushButton *m_rightBtn;

    SpinBox *m_emissSpinBox;
    SpinBox *m_distSpinBox;
    SpinBox *m_ambiTSpinBox;
    SpinBox *m_reflTSpinBox;
    SpinBox *m_humiSpinBox;
    SpinBox *m_offsetSpinBox;
    ComboBox *m_backgroundComboBox;

};

#endif // LGLOBALPARAMPAGE_H


