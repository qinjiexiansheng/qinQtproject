#include "AskDialog.h"

AskDialog::AskDialog(QString nStr, QString nStr1, QWidget *parent = 0 ) :
    QDialog(parent)
{
    this->setFixedSize(300,120);
    this->setGeometry(0, 0, 300, 120);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);

    nGridLayout = new QGridLayout(this);

    nWarnLable = new QLabel("Warning:", this);
    nGridLayout->addWidget(nWarnLable, 0, 0, 1, 4, Qt::AlignLeft);

    nAskLable = new QLabel(nStr,this);
    nGridLayout->addWidget(nAskLable, 1, 0, 1 ,4, Qt::AlignCenter);

    nAskLable = new QLabel(nStr1,this);
    nGridLayout->addWidget(nAskLable, 2, 0, 1 ,4, Qt::AlignCenter);

    nYesButton = new QPushButton("Yes", this);
    nGridLayout->addWidget(nYesButton, 3, 0, 1, 2);
    mList.append(nYesButton);
    connect(nYesButton, SIGNAL(clicked()), this, SLOT(accept()) );

    nNoButton = new QPushButton("No", this);
    nGridLayout->addWidget(nNoButton, 3, 2, 1, 2);
    mList.append(nNoButton);
    connect(nNoButton, SIGNAL(clicked()), this, SLOT(reject()) );

    mIndex = 0;
    mList.at(mIndex)->setFocus();

    this->setLayout(nGridLayout);
}

AskDialog::~AskDialog()
{

}
bool AskDialog::eventFilter(QObject *obj, QEvent *event)
{

  if(event->type() == QEvent::KeyPress){
      QKeyEvent* nKey = (QKeyEvent *)event;
      if(nKey->isAutoRepeat()){
          return true;
      }

      switch(nKey->key()){
          case UP:
              qDebug("AskDialog eventFilter case UP");
              focusPrevious();
              return true;
              break;
          case DOWN:
              qDebug("AskDialog eventFilter case DOWN");
              focusNext();
              return true;
              break;
          case ENTER:
               qDebug("AskDialog eventFilter case ENTER");
               mList.at(mIndex)->click();
               return true;
               break;
      }
      //这里不能返回真，因为上层需要左右按键事件来切换标签页
  }

  return QWidget::eventFilter(obj,event);
}

void AskDialog::AskDialog::focusNext()
{
    mIndex++;
    if(mIndex >= mList.size() ){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void AskDialog::AskDialog::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() -1 ;
    }
    mList.at(mIndex)->setFocus();
}
