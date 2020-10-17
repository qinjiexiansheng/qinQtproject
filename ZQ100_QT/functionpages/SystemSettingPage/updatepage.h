#ifndef DIRWIDGET_H
#define DIRWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QModelIndex>

class QDirModel;
class QTreeView;
class QLabel;

class UpdatePage : public QDialog
{
    Q_OBJECT

public:
    UpdatePage(QWidget *parent = 0);
    void initView();

private slots:
    void showDetailInfo();

private:
    QString getPrintSize(qint64 size);
private slots:
    void updateConfirm();
    void clickedSlot(QModelIndex);


private:
    QDirModel *model;
    QTreeView *tree;

    QWidget *leftWidget;
    QLabel *fileNumLabel;
    QLabel *fileSizeLabel;
    QLabel *fileModifiedLabel;
};

#endif // DIRWIDGET_H
