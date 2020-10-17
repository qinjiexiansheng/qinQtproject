#include "modifyadtablewidget.h"
#include "HexadecimalKeyboard.h"
#include <QHeaderView>

ModifyAdTableWidget::ModifyAdTableWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(240,200);
    this->setGeometry(0, 0, 240,200);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    mView = new QTableView(this);
    mModel = new QStandardItemModel();//创建模型
    mModel->setColumnCount(2);//模型列数
    QStringList nHeader;
    nHeader<<tr("Key")<<tr("Value");
    mModel->setHorizontalHeaderLabels(nHeader);//设置模型的表头名称
  //  mView->verticalHeader()->hide();
 //   mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mView->setCurrentIndex(mModel->index(0,1));//初始焦点在第一行第二列

    mView->installEventFilter(this);
    mView->setModel(mModel);
}

ModifyAdTableWidget::~ModifyAdTableWidget()
{

}

bool ModifyAdTableWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        qDebug("bool ModifyAdTableWidget::eventFilter(QObject *obj, QEvent *event)");
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        switch(nKey->key()){
            case UP:
                qDebug("ModifyAdTableWidget eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("ModifyAdTableWidget eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case Qt::Key_Escape :
                 qDebug("ModifyAdTableWidget eventFilter case Key_Escape");
                 this->close();
                 //save
                 return true;
                 break;
            case ENTER:
                 qDebug("ModifyAdTableWidget eventFilter case ENTER");
                 QString nStr = "12345";
                 HexadecimalKeyboard *nDialog = new HexadecimalKeyboard(nStr, this);
                 if(nDialog->exec()){
                     qDebug("ModifyAdTableWidget nDialog->exec()");
                 }
                 return true;
                 break;

        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }
    return QWidget::eventFilter(obj, event);
}

void ModifyAdTableWidget::focusPrevious()
{
    int i = mView->currentIndex().row();
    int j= mView->currentIndex().column();
    i--;
    if(i < 0){
        i = 0;
    }
    mView->setCurrentIndex(mModel->index(i,j));
}
void ModifyAdTableWidget::focusNext()
{
    int i = mView->currentIndex().row();
    int j= mView->currentIndex().column();
    i++;
    if(i > mModel->rowCount()){
        i = mModel->rowCount() - 1;
    }
    mView->setCurrentIndex(mModel->index(i,j));
}

void ModifyAdTableWidget::showEvent(QShowEvent *se) //显示事件
{
    mView->setCurrentIndex(mModel->index(0,1));
    QWidget::showEvent(se);
}
