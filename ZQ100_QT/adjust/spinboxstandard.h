#ifndef LLINEEDIT_H
#define LLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include "globalparam.h"
#include <QFocusEvent>

class QPushButton;
class QTimer;

class SpinBoxStandard : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QString m_prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString m_suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(int m_decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double m_minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double m_maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double m_singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(double m_value READ value WRITE setValue)
public:
    explicit SpinBoxStandard(QWidget *parent = 0, GlobalParam::Orientation orientation = GlobalParam::Orientation::HORIZONTAL);

    double value() const{ return m_value; }
    void setValue(double val);

    QString prefix() const{ return m_prefix; }
    void setPrefix(const QString &prefix);

    QString suffix() const{ return m_suffix; }
    void setSuffix(const QString &suffix);

    double singleStep() const{ return m_singleStep; }
    void setSingleStep(double val);

    double minimum() const{ return m_minimum; }
    void setMinimum(double min);

    double maximum() const{ return m_maximum; }
    void setMaximum(double max);

    void setRange(double min, double max);

    int decimals() const{ return m_decimals; }
    void setDecimals(int prec);

    void setLongPressInterval(int msec);


protected:
    void moveEvent(QMoveEvent *e);
    void mousePressEvent(QMouseEvent *e){}
    void mouseMoveEvent(QMouseEvent *e){}
    void mouseDoubleClickEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
//    bool eventFilter(QObject *watched, QEvent *event);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void setSelection(){}

signals:
    void clicked(SpinBoxStandard *);

public slots:
    void buttonClicked();
    void onTimeout();

private:
    void adjustLayout();
    void showValue();

private:
    QString m_prefix;
    QString m_suffix;
    int  m_decimals;
    double m_minimum;
    double m_maximum;
    double m_singleStep;
    double m_singleStepTemp;
    double m_value;
    GlobalParam::Orientation m_curOrientation;
    bool m_isPressed;
    int m_longPressInterval;
    QTimer *m_longPressTimer;

    QPushButton *m_reduceBtn;
    QPushButton *m_addBtn;
};


#endif // LLINEEDIT_H
