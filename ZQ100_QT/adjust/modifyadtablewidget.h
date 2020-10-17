#ifndef MODIFYADTABLEWIDGET_H
#define MODIFYADTABLEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>

class ModifyAdTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyAdTableWidget(QWidget *parent = 0);
    ~ModifyAdTableWidget();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *se);//显示事件

private:
    void focusPrevious();
    void focusNext();
    QStandardItemModel *mModel;
    QTableView *mView;

};

#endif // MODIFYADTABLEWIDGET_H
