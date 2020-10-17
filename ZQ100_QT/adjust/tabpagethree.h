#ifndef TABPAGETHREE_H
#define TABPAGETHREE_H

#include <QSignalMapper>
#include "saveadwidget.h"
#include "modifyadtablewidget.h"
#include "ShowAdTableWidget.h"
#include "SatControl.h"
#include "operationfile.h"

class TabPageThree : public QWidget
{
    Q_OBJECT

public:
    explicit TabPageThree(QWidget *parent = 0);
    ~TabPageThree();
signals:
    void operationSignal(int nOpeStr,QString nParStr);//发送业务操作信号
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件监听
    void showEvent(QShowEvent *se);//显示事件

private:
    QSignalMapper *nSignalMapper;
    QVBoxLayout *nLayout;
    SatButton *nSaveADButton;
    SatButton *nShowTableButton;
    SatButton *nReloadTableButton;
    SatButton *nModifyTableButton;
    SatButton *nUpdateTableButton;
    SaveADWidget *mSaveAdWidget;
    ShowAdTableWidget *nShowAdTableWidget;
    ModifyAdTableWidget *mModifyAdTableWidget;
    void focusNext();
    void focusPrevious();
    QList<SatButton*> mList;
    int mIndex;
    satData *mSatData;


private slots:
    void handleContent(const QString &nStr);

};

#endif // TABPAGETHREE_H
