#ifndef SETDATEWIDGET_H
#define SETDATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QComboBox>
#include "littlewidget.h"
#include <QGridLayout>

#define YEAR_MAX_COUNT 30
#define CURRENT_YEAR    2018
#define MONTH_MAX_COUNT 12
#define DAY_MAX_COUNT 31


class SetDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetDateWidget(QWidget *parent = 0);
    ~SetDateWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent *se);

private slots:
   void closeSlot();

private:
   void focusNext();
   void focusPrevious();
   QComboBox *mYearBox;
   QComboBox *mMonthBox;
   QComboBox *mDayBox;
   QGridLayout *nGridLayout;
   QLabel *nYearLabel;
   QLabel *nMonthLabel;
   QLabel *nDayLabel;
   QPushButton *nOkButton;
   QPushButton *nCancleButton;
   int mYear;
   int mOldYear;
   int mMonth;
   int mOldMonth;
   int mDay;
   int mOldDay;
   int mIndex;
   int nIndex;
   QList<QWidget*> mList;

};

#endif // SETDATEWIDGET_H
