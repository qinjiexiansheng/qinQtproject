#include "tabpageone.h"



TabPageOne::TabPageOne(QWidget *parent): QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//

    QVBoxLayout *nLayout = new QVBoxLayout(this);
    nSignalMapper = new QSignalMapper(this);

 // this->setFixedSize(100,200);//窗口大小

    qDebug("TabPageOne::TabPageOne(QWidget *parent): QWidget(parent)");

    nAdjustOpenButton = new SatButton(tr("Adjust"),this);
    nAdjustOpenButton->installEventFilter(this);
    mList.append(nAdjustOpenButton);
    nSignalMapper->setMapping(nAdjustOpenButton, "Adjust");
    connect(nAdjustOpenButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
    nLayout->addWidget(nAdjustOpenButton);


    nAdjustSaveButton = new SatButton(tr("Save"),this);
    nAdjustSaveButton->installEventFilter(this);
    nLayout->addWidget(nAdjustSaveButton);
    nSignalMapper->setMapping(nAdjustSaveButton, "Save");
    mList.append(nAdjustSaveButton);
    connect(nAdjustSaveButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );

    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(10);//设置外边距
    nLayout->setSpacing(10);//设置内边距
    this->setLayout(nLayout);

    mIndex = 0;
    mList.at(mIndex)->setFocus();

    connect(nSignalMapper, SIGNAL(mapped(QString)), this, SLOT(handleContent(QString)) );

}

/*
void TabPageOne::keyPressEvent(QKeyEvent *event)
{
    qDebug(" TabPageOne::keyPressEvent(QKeyEvent *event)");
//  QWidget::keyPressEvent(event);
}
*/
bool TabPageOne::eventFilter(QObject *obj, QEvent *event)
{

  //  qDebug("bool TabPageOne::eventFilter(QObject *obj, QEvent *event)");

    if(event->type() == QEvent::KeyPress){

   //   qDebug("bool TabPageOne::eventFilter(QObject *obj, QEvent *event)");

        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        qDebug("nKey->key() =0x%x ",nKey->key());

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
                 mList.at(mIndex)->click();
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);

}
/*
void TabPageOne::keyReleaseEvent(QKeyEvent *event)
{


}
*/

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



void TabPageOne::handleContent(const QString &nStr)
{

    qDebug("TabPageOne::handleContent");

    if(nStr == "Adjust"){
        qDebug(" nstr Adjust");
        ::system("/mnt/sd/adjust_k.sh");
    }else if(nStr == "Save"){
        qDebug(" nstr Save");
        ::system("/mnt/sd/save_k.sh");
    }


}


TabPageOne::~TabPageOne()
{

}
