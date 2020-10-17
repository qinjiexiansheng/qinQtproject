#ifndef SETGEARWIDGET_H
#define SETGEARWIDGET_H

#include <QWidget>
#include "littlewidget.h"
#include <QComboBox>

class SetGearWidget : public QWidget
{
    Q_OBJECT
public:
    SetGearWidget(QWidget *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);
//signals:
//    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
private slots:
    void okSlot();
    void closeSlot();//关闭
private:
    void focusNext();//焦点移到下一组件
    void focusPrevious();//焦点移到上一组件
    QComboBox *mComboBox;//组合框
    int mIndex;//当前焦点索引
    int mMaxIndex;//组合框最大索引
//    SatData::GearEnum mOldGear;
//    SatData *mSatData;
    QList<QWidget*> mList;//焦点列表
    QGridLayout *nGridLayout;
    QPushButton *nOkButton;
    QPushButton *nCancelButton;
};

#endif // SETGEARWIDGET_H
