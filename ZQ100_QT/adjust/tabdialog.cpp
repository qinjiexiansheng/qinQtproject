#include "tabdialog.h"
#include <Qt>

TabDialog::TabDialog(QWidget *parent): QDialog(parent)
{

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0, 0, 200,240);

    mTabWidget = new SatTabWidget(this);
//  mTabWidget->installEventFilter(this);

}


/*
 bool TabDialog::eventFilter(QObject *obj, QEvent *ev)
 {

     if(ev->type() == QEvent::KeyPress)
     {

         qDebug(" bool TabDialog::eventFilter(QObject *obj, QEvent *ev)");

         QKeyEvent* nKey = (QKeyEvent *)ev;
         if(nKey->isAutoRepeat()){
             return true;
         }

         qDebug("nKey->key() =0x%x ",nKey->key());

        switch(nKey->key()){
            case Qt::Key_A:
                qDebug("TabDialog case Key_A");
              //  prevTab();
                break;

            default:
                qDebug("TabDialog case default");
                break;
        }
        return true;

     }else if(ev->type() == QEvent::KeyRelease){
         return true;
     }
     return QDialog::eventFilter(obj,ev);
 }
*/
void TabDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        this->close();
        qDebug("TabDialog::keyPressEvent Key_A");
    }
    /*
    if(event->key() == Qt::Key_B){
        this->show();
        qDebug("TabDialog::keyPressEvent Key_B");
    }
    */

}


/*
 void TabDialog::nextTab()
 {
     int nIndex = mTabWidget->currentIndex();
     nIndex++;
     if(nIndex >= mMaxIndex){
         nIndex = 0;
     }

     mTabWidget->setCurrentIndex(nIndex);
 }

 void TabDialog::prevTab()
 {
     int nIndex = mTabWidget->currentIndex();
     nIndex--;
     if(nIndex < 0){
         nIndex = mMaxIndex - 1;
     }

     mTabWidget->setCurrentIndex(nIndex);
 }

 void TabDialog::showEvent(QShowEvent *se){
     qDebug("void TabDialog::showEvent(QShowEvent *se)");
     int nIndex = mTabWidget->currentIndex();
     mTabWidget->setCurrentIndex(nIndex);
     QDialog::showEvent(se);
 }
*/
