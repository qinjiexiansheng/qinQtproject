#include "updatepage.h"
#include <QApplication>
#include <QFileSystemModel>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDirModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeView>

#define UPDATE_PCKAGES_PATH "/mnt/sd/UpdateDir"
//#define UPDATE_PCKAGES_PATH "/home/osrc/lee/testDir"

/**
 * @name    UpdatePage(QWidget *parent)
 * @details 更新界面,已实现基本的显示和控制功能;
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-11-19
**/
UpdatePage::UpdatePage(QWidget *parent)
    : QDialog(parent)
{
    initView();
}

/**
 * @name    initView()
 * @details 初始化显示和信号链接
 * @author  lee
 * @date    2018-11-19
**/
void UpdatePage::initView()
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    QLabel *title = new QLabel("Update");
//    title->setStyleSheet("border: 1px solid black");
    title->setAlignment(Qt::AlignCenter);
    title->setFixedHeight(30);

    model = new QDirModel;
//    model->setFilter(QDir::Files);

//    QStringList nameFilter;
//    nameFilter << "*.tgz.gpg";
//    model->setNameFilters(nameFilter);


    tree= new QTreeView(this);
//    tree->setStyleSheet("QTreeView{background-color: white;}\
//                        QHeaderView{background-color: gray;}");
    tree->setModel(model);
    tree->setRootIndex(model->index(UPDATE_PCKAGES_PATH));
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tree->setFixedSize(200, 180);
    tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    tree->setIndentation(0);
    tree->setSortingEnabled(true);
    tree->header()->setSortIndicator(3, Qt::AscendingOrder);
    tree->header()->setSortIndicatorShown(true);


    leftWidget = new QWidget(this);
    fileNumLabel = new QLabel;
    fileSizeLabel = new QLabel;
    fileModifiedLabel = new QLabel;
    fileNumLabel->setAlignment(Qt::AlignCenter);
    fileSizeLabel->setAlignment(Qt::AlignCenter);
    fileModifiedLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(0);
    leftLayout->setMargin(0);
    leftLayout->addWidget(fileNumLabel);
    leftLayout->addWidget(fileSizeLabel);
    leftLayout->addWidget(fileModifiedLabel);

    leftWidget->setFixedSize(120, 180);

    setFixedSize(320, 240);

    QPushButton *btn1 = new QPushButton("Update");
    QPushButton *btn2 = new QPushButton("Close");
    btn1->setFocusPolicy(Qt::NoFocus);
    btn2->setFocusPolicy(Qt::NoFocus);
    btn1->setFixedHeight(30);
    btn2->setFixedHeight(btn1->height());

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->setMargin(0);
    topLayout->addWidget(tree);
    topLayout->addWidget(leftWidget);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(0);
    bottomLayout->addWidget(btn1);
    bottomLayout->addWidget(btn2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(title);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    fileNumLabel->setText(QString("Total %1 update\r\npackages.")
                          .arg(model->rowCount(tree->rootIndex())));
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setCurrentIndex(tree->rootIndex().child(0, 0));

    showDetailInfo();

    connect(tree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(showDetailInfo()));
    connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedSlot(QModelIndex)));
    connect(tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(updateConfirm()));
    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(updateConfirm()));
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

/**
 * @name    showDetailInfo()
 * @details 显示更新文件的详细信息,如大小和修改日期等
 * @author  lee
 * @date    2018-11-19
**/
void UpdatePage::showDetailInfo()
{
    QFileInfo info(model->filePath(tree->currentIndex()));

    fileSizeLabel->setText(QString("Size: \r\n%1")
                           .arg(getPrintSize(info.size())));
    fileModifiedLabel->setText(QString("Date: \r\n%1\r\n%2")
                               .arg(info.lastModified().date().toString("yyyy-MM-dd"))
                               .arg(info.lastModified().time().toString()));
}

/**
 * @name    QString getPrintSize(qint64 size)
 * @details 将字节大小转换为适应的单位,如KB/MB;
 * @param   size    文件的大小,以字节为单位
 * @author  lee
 * @date    2018-11-19
**/
QString UpdatePage::getPrintSize(qint64 size)
{
    qint64 rest = 0;
    if(size < 1024){
        return QString::number(size) + "B";
    }else{
        size /= 1024;
    }

    if(size < 1024){
        return QString::number(size) + "KB";
    }else{
        rest = size % 1024;
        size /= 1024;
    }
    if(size < 1024){
        size = size * 100;
        return QString::number((size / 100)) + "." + QString::number((rest * 100 / 1024 % 100)) + "MB";
    }else{
        size = size * 100 / 1024;
        return QString::number((size / 100)) + "." + QString::number((size % 100)) + "GB";
    }
}

/**
 * @name    void updateConfirm()
 * @details 更新操作,根据选择执行更新过程,后续实现
 * @author  lee
 * @date    2018-11-19
**/
void UpdatePage::updateConfirm()
{
    QFileInfo info(model->filePath(tree->currentIndex()));

//    //qDebug()<<info.fileName();

    if(QMessageBox::Ok ==  QMessageBox::information(this,
                                                    "Update Program",
                                                    "The operation will update your\n\r"
                                                    "current application program,\n\r"
                                                    "are you sure?", QMessageBox::Ok,
                                                    QMessageBox::Cancel))
        qWarning("Update start!");
    else
        qWarning("Update cancel!");
}

void UpdatePage::clickedSlot(QModelIndex index)
{
    tree->setCurrentIndex(tree->model()->index(index.row(), 0, index.parent()));
}
