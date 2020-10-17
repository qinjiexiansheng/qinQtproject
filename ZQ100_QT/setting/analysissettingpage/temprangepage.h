#ifndef LTEMPRANGEPAGE_H
#define LTEMPRANGEPAGE_H

#include "globalparam.h"

class TempRangePage : public QDialog
{
    Q_OBJECT

public:
    TempRangePage(QWidget *parent = 0);
    ~TempRangePage();

    void setCurrentIndex(int);
    int getCurrentIndex() const;

    QString getText() const;

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void changeCurLevelLabel();

private:
    QLabel *m_title;
    QPushButton *m_leftBtn;
    QPushButton *m_rightBtn;

    QButtonGroup *m_levelBtnGroup;
    QPushButton *m_levelBtn1;
    QPushButton *m_levelBtn2;
    QLabel *m_curLevelLabel;

    int lowerLimit;
    int upperLimit;

    int m_curLevel;
    QString m_curRange;
};

#endif // LTEMPRANGEPAGE_H
