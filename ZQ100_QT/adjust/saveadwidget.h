#ifndef SAVEADWIDGET_H
#define SAVEADWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include "littlewidget.h"
#include <QList>

class SaveADWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SaveADWidget(QWidget *parent = 0);
    ~SaveADWidget();

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件

private slots:
   void saveSlot();
   void cancelSlot();

private:
    QLabel *nTempLabel;
    QComboBox *mComboxBox;
    QLabel *nADLable;
    QLabel *mAdLable;
 //   SatButton *nSaveButton;
 //   SatButton *nCancelButton;
    QPushButton *nSaveButton;
    QPushButton *nCancelButton;
    QGridLayout *nGridLayout ;
    QList<QWidget*> mList;
    QList<QString> nStrList;
    int mMaxIndex;
    void focusNext();
    void focusPrevious();
    int mIndex;

};

#endif // SAVEADWIDGET_H
