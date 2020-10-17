#ifndef DIRWIDGET_H
#define DIRWIDGET_H

#include "globalparam.h"

class UpdatePage : public QDialog
{
    Q_OBJECT

public:
    UpdatePage(QWidget *parent = 0);
    void initView();

protected:
    void keyPressEvent(QKeyEvent *event);

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
