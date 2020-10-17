#ifndef TABPAGEFIVE_H
#define TABPAGEFIVE_H

#include <QWidget>
#include "littlewidget.h"
#include <QSignalMapper>
#include <QVBoxLayout>

class TabPageFive : public QWidget
{
    Q_OBJECT
public:
    TabPageFive(QWidget *parent = 0);
signals:
 //   void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件
private slots:
    void handleContent(const QString &nStr);//处理按键操作
private:
    void focusNext();
    void focusPrevious();
private:
    int mIndex;
    QList<SatButton*> mList;
    QSignalMapper *nSignalMapper;
    QVBoxLayout *nVBoxLayout;
    SatButton *nAutoIntButton;
    SatButton *nRecordArgButton;
    SatButton *nDistanceButton;
};

#endif // TABPAGEFIVE_H
