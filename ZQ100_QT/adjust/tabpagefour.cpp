#include "tabpagefour.h"
#include <QDebug>
#include "AskDialog.h"

TabPageFour::TabPageFour(QWidget *parent) :
    QWidget(parent)
{

    nSignalMapper = new QSignalMapper(this);
    nLayout = new QVBoxLayout(this);

    nSerialNumberButton = new SatButton("Serial Number", this);
    nSerialNumberButton->installEventFilter(this);
    nLayout->addWidget(nSerialNumberButton);
    nSignalMapper->setMapping(nSerialNumberButton, "SerialNumber");
    connect(nSerialNumberButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
    mList.append(nSerialNumberButton);

    nSetFactoryDateButton = new SatButton("Set Factory Date", this);
    nSetFactoryDateButton->installEventFilter(this);
    nLayout->addWidget(nSetFactoryDateButton);
    nSignalMapper->setMapping(nSetFactoryDateButton, "Date");
    connect(nSetFactoryDateButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()));
    mList.append(nSetFactoryDateButton);

    nTableToSDButton =new SatButton("Table To SD", this);
    nLayout->addWidget(nTableToSDButton);
    nTableToSDButton->installEventFilter(this);
    mList.append(nTableToSDButton);
    nSignalMapper->setMapping(nTableToSDButton, "TableToSD");
    connect(nTableToSDButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );

    nSDToTableButton =new SatButton("SD To Table", this);
    nLayout->addWidget(nSDToTableButton);
    nSDToTableButton->installEventFilter(this);
    mList.append(nSDToTableButton);
    nSignalMapper->setMapping(nSDToTableButton, "SDToTable");
    connect(nSDToTableButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );

    nSerialNumberWidget = new SerialNumberWidget(this);

    nSetDateWidget = new SetDateWidget(this);
    nSetDateWidget->hide();

    mIndex=0;
    mList.at(mIndex)->setFocus();

    //布局设置
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(5);//设置内边距
    this->setLayout(nLayout);

    connect(nSignalMapper, SIGNAL(mapped(QString)), this, SLOT(handleContent(QString)));

}

TabPageFour::~TabPageFour()
{

}

bool TabPageFour::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress){
        qDebug("bool TabPageFour::eventFilter(QObject *obj, QEvent *event)");

        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        qDebug("nKey->key() =0x%x ",nKey->key());

        switch(nKey->key()){
            case UP:
                qDebug("TabPageFour eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("TabPageFour eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case ENTER:
                 qDebug("TabPageFour eventFilter case ENTER");
                 mList.at(mIndex)->click();
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);
}
void TabPageFour::showEvent(QShowEvent *se)
{
    qDebug("void TabPageFour::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void TabPageFour::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFour::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageFour::handleContent(const QString &nStr)
{
    qDebug("TabPageFour::handleContent");

    if(nStr == "SerialNumber"){
       qDebug("nStr == SerialNumber");
       nSerialNumberWidget->show();
    }else if( nStr == "Date"){
        qDebug(" nStr == Date ");
        nSetDateWidget->show();
        mList.at(mIndex)->setFocus();
    }else if(nStr == "SDToTable"){
        qDebug("nStr == SDToTable");
        QString nStr;
        QString nStr1;
        nStr = "This will restore the file from the SD card.";
        nStr1 = "Are you sure?";
        AskDialog *nDialg = new AskDialog(nStr, nStr1, this);
        if(nDialg->exec()){
            qDebug("nDialg->exec()");
        }
    }else if(nStr == "TableToSD"){
        qDebug("nStr == TableToSD");
        QString nStr;
        QString nStr1;
        nStr = "This will be backed up to the SD card.";
        nStr1 = "Are you sure?";
        AskDialog *nDialg = new AskDialog(nStr, nStr1, this);
        if(nDialg->exec()){
            qDebug("22 nDialg->exec()");
        }
    }

}
