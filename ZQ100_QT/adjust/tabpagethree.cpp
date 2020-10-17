#include "tabpagethree.h"
#include "modifyadtablewidget.h"
#include "AskDialog.h"
#include "satdefine.h"

TabPageThree::TabPageThree(QWidget *parent) :
    QWidget(parent)
{
    mSatData = satData::initance();

    this->setWindowFlags(Qt::FramelessWindowHint);
    nSignalMapper = new QSignalMapper(this);
    nLayout = new QVBoxLayout(this);

    nSaveADButton = new SatButton(tr("Save AD"),this);
    nSaveADButton->installEventFilter(this);
    nLayout->addWidget(nSaveADButton);
    nSignalMapper->setMapping(nSaveADButton, "SaveAD");
    connect(nSaveADButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
    mList.append(nSaveADButton);     

    nShowTableButton = new SatButton(tr("Show Table"), this);
    nShowTableButton->installEventFilter(this);
    nLayout->addWidget(nShowTableButton);
    nSignalMapper->setMapping(nShowTableButton, "ShowTable");
    connect(nShowTableButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()));
    mList.append(nShowTableButton);

    nReloadTableButton = new SatButton(tr("Take Effect Table"), this);
    nReloadTableButton->installEventFilter(this);
    nLayout->addWidget(nReloadTableButton);
    nSignalMapper->setMapping(nReloadTableButton, "TakeEffectTable");
    connect(nReloadTableButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()));
    mList.append(nReloadTableButton);

    nModifyTableButton = new SatButton(tr("Modify Table"), this);
    nModifyTableButton->installEventFilter(this);
    nLayout->addWidget(nModifyTableButton);
    nSignalMapper->setMapping(nModifyTableButton, "ModifyTable");
    connect(nModifyTableButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()));
    mList.append(nModifyTableButton);

    nUpdateTableButton = new SatButton(tr("Update Table"),this);
    nUpdateTableButton->installEventFilter(this);
    nLayout->addWidget(nUpdateTableButton);
    nSignalMapper->setMapping(nUpdateTableButton, "UpdateTable");
    connect(nUpdateTableButton, SIGNAL(clicked()), nSignalMapper, SLOT(map()) );
    mList.append(nUpdateTableButton);   

    mSaveAdWidget =new SaveADWidget(this);
    mSaveAdWidget->hide();

    nShowAdTableWidget = new ShowAdTableWidget(this);
    nShowAdTableWidget->hide();

    mModifyAdTableWidget =new ModifyAdTableWidget(this);
    mModifyAdTableWidget->hide();

    //布局调整
    nLayout->addStretch();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(5);//设置内边距
    this->setLayout(nLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));

    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类

}

bool TabPageThree::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        switch(nKey->key()){
            case UP:
                qDebug("TabPageThree eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("TabPageThree eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case ENTER:
                 qDebug("TabPageThree eventFilter case ENTER");
                 mList.at(mIndex)->click();
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }
    return QWidget::eventFilter(obj,event);
}

void TabPageThree::showEvent(QShowEvent *se)
{
    qDebug("void TabPageThree::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void TabPageThree::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void TabPageThree::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}


void TabPageThree::handleContent(const QString &nStr)
{
    qDebug("TabPageThree::handleContent(const QString &nStr)");
    if(nStr == "SaveAD"){
        qDebug("SaveAD");
        mSaveAdWidget->show();
    }else if(nStr == "ShowTable"){
        qDebug("ShowTable");
        nShowAdTableWidget->show();
    }else if(nStr == "ModifyTable"){
        qDebug("ModifyTable");
        mModifyAdTableWidget->show();
    }else if(nStr == "UpdateTable"){
        qDebug("UpdateTable");
        QString nStr;
        QString nStr2;

        if(mSatData->getGearMode() == satData::GEARONE){
            nStr = QString("The file(%1%2) will replace")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(1));
           nStr2 = QString("the file(%1%2).Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
        }else{
            nStr = QString("The file(%1%2) will replace")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE_NEW).arg(2));
           nStr2 = QString("the file(%1%2).Are you sure?")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(2));
        }
        AskDialog *nDialog = new AskDialog(nStr, nStr2, this);
        if(nDialog->exec()){
            emit operationSignal(Update_TempAd_Table,NULL);
        }
    }else if(nStr == "TakeEffectTable"){
        QString nStr;
        QString nStr2;

        if(mSatData->getGearMode() == SatData::GEARONE)
        {
            nStr = QString("The file(%1%2) ")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
            nStr2 = "will take effect.Are you sure?";
        }
        else
        {
            nStr = QString("The file(%1%2) ")
                    .arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(2));
            nStr2 = "will take effect.Are you sure?";
        }
//        qDebug("nStr = %s", qPrintable(nStr));
        AskDialog *nDialog = new AskDialog(nStr, nStr2, this);
        if(nDialog->exec()){
            emit operationSignal(Effect_TempAd_Table,NULL);//为什么只有了 0 30 70度的AD事测出来，其他AD都是算出来呢
        }

    }
}


TabPageThree::~TabPageThree()
{
}
