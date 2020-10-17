#ifndef LDOUBLESLIDEWIDGET_H
#define LDOUBLESLIDEWIDGET_H

#include "globalparam.h"

#define H_SPACING 30
#define V_SPACING 30

class SlideArea;

class SlideWidget : public QDialog
{
    Q_OBJECT

public:
    SlideWidget(QWidget *parent = 0, int H_Spacing = H_SPACING, int V_Spacing = V_SPACING,
                 GlobalParam::ValueType valueType = GlobalParam::ValueType::DEFAULT);

    void addItems(QStringList *options, int areaID = 0);
    void setCurrentIndex(int index, int areaID = 0);
    int getCurrentIndex(int areaID = 0) const;
    void setCurrentText(int value, int areaID = 0);
    void setCurrentText(QString text, int areaID = 0);
    QString getCurrentText(int areaID = 0) const;
    QString getText(int index, int areaID = 0) const;

    void setTitle(QString);
    void setLButton(QString);
    void setRButton(QString);
    void setSeparatorText(QString);
    void setValueType(GlobalParam::ValueType valueType);

    void show();

protected:
    void keyPressEvent(QKeyEvent *e);
    void accept();

private:
    void initView();
    void adjustLayout();

private:
    int m_hSpacing;
    int m_vSpacing;

    QLabel *m_title;
    QPushButton *m_LButton;
    QPushButton *m_RButton;

    SlideArea *m_area1;
    SlideArea *m_area2;

    QLabel *m_dot;
    int m_decimals;
    GlobalParam::ValueType m_currentValueType;


};

#endif // LDOUBLESLIDEWIDGET_H
