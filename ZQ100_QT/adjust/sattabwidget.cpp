#include "sattabwidget.h"
#include "tabdialog.h"


SatTabWidget::SatTabWidget(QWidget *parent) :
    QTabWidget(parent)
{

    this->setGeometry(0, 0, TAB_WIDE, TAB_HIGH);

    setStyleSheet("color: rgb(255, 255, 255);\
                  background-color: rgb(0, 200, 200)");

    nTabPageThree = new TabPageThree(this);
    this->addTab(nTabPageThree, tr("TempAD"));
    this->installEventFilter(this);

    nTabePageOne = new TabPageOne(this);
    this->addTab(nTabePageOne, tr("KTable"));
    nTabePageOne->installEventFilter(this);

    nTabePageTwo = new TabPageTwo(this);
    this->addTab(nTabePageTwo, tr("Setting"));
    nTabePageTwo->installEventFilter(this);

    nTabPageFour = new TabPageFour(this);
    this->addTab(nTabPageFour, tr("Other"));
    nTabPageFour->installEventFilter(this);

    nTabPageFive = new TabPageFive(this);
    this->addTab(nTabPageFive, tr("Test"));
    nTabPageFive->installEventFilter(this);

    mMaxIndex = 5;
    this->setCurrentIndex(0);
}
bool SatTabWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::KeyPress)
    {

        qDebug(" bool TabDialog::eventFilter(QObject *obj, QEvent *ev)");

        QKeyEvent* nKey = (QKeyEvent *)ev;
        if(nKey->isAutoRepeat()){
            return true;
        }
     //   qDebug("nKey->key() =0x%x ",nKey->key());

       switch(nKey->key()){
           case LEFT:
               qDebug("TabDialog case KEY_LEFT");
               prevTab();
               return true;
               break;
           case RIGHT:
               qDebug("TabDialog case KEY_RIGHT");
               nextTab();
               return true;
               break;
       }

    }else if(ev->type() == QEvent::KeyRelease){
        return true;
    }
    return QTabWidget::eventFilter(obj,ev);
}

void SatTabWidget::showEvent(QShowEvent *se)
{
    qDebug("SatTabWidget::showEvent(QShowEvent *se)");
    int nIndex = this->currentIndex();
    this->setCurrentIndex(nIndex);
    QTabWidget::showEvent(se);

}

void SatTabWidget::nextTab()
{
    int nIndex = this->currentIndex();
    nIndex++;
    if(nIndex >= mMaxIndex){
        nIndex = 0;
    }

    this->setCurrentIndex(nIndex);
}

void SatTabWidget::prevTab()
{
    int nIndex = this->currentIndex();
    nIndex--;
    if(nIndex < 0){
        nIndex = mMaxIndex - 1;
    }

    this->setCurrentIndex(nIndex);
}

SatTabWidget::~SatTabWidget()
{

}
