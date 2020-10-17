#include "tabpage.h"

TabPageOne::TabPageOne(QWidget *parent): QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//

    QVBoxLayout *nLayout = new QVBoxLayout(this);

 // this->setFixedSize(100,200);//窗口大小

    qDebug("TabPageOne::TabPageOne(QWidget *parent): QWidget(parent)");

    nAdjustOpenButton = new SatButton(tr("Adjust"),this);
    nAdjustOpenButton->installEventFilter(this);
    mList.append(nAdjustOpenButton);
    nLayout->addWidget(nAdjustOpenButton);


    nAdjustOpenButton2 = new SatButton(tr("Adjust2"),this);
    nAdjustOpenButton2->installEventFilter(this);
    nLayout->addWidget(nAdjustOpenButton2);
    mList.append(nAdjustOpenButton2);

    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(0);//设置内边距
    this->setLayout(nLayout);

    mIndex = 0;
    mList.at(mIndex)->setFocus();



}

TabPageTwo::TabPageTwo(QWidget *parent): QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//
    this->setFixedSize(300,240);//窗口大小

    nSettingButton = new SatButton(tr("Setting"),this);
    nSettingButton->installEventFilter(this);
    connect(nSettingButton, SIGNAL(clicked(bool)), this, SLOT(satbuttonClicked()));

}

void TabPageTwo::satbuttonClicked()
{
    qDebug("TabPageTwo::buttonClicked()");
}

void TabPageOne::keyPressEvent(QKeyEvent *event)
{
    qDebug(" TabPageOne::keyPressEvent(QKeyEvent *event)");
  //  QWidget::keyPressEvent(event);
}

bool TabPageOne::eventFilter(QObject *obj, QEvent *event)
{

  //  qDebug("bool TabPageOne::eventFilter(QObject *obj, QEvent *event)");

    if(event->type() == QEvent::KeyPress){

      qDebug("bool TabPageOne::eventFilter(QObject *obj, QEvent *event)");

        QKeyEvent* nKey = (QKeyEvent *)event;
        switch(nKey->key()){
            case UP:
                qDebug("TabPageOne eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("TabPageOne eventFilter case DOWN");
                focusNext();
                return true;
                break;
             case ENTER:
                 qDebug("TabPageOne eventFilter case ENTER");
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);

}

void TabPageOne::showEvent(QShowEvent *se)
{
    qDebug("void TabPageOne::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void TabPageOne::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageOne::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}
