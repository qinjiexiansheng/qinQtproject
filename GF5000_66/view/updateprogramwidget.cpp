#include "updateprogramwidget.h"
#include <QListWidget>
#include <QStandardItem>
#include <QListView>

#if 0
SatUpdateListWidget::SatUpdateListWidget(QString nDirString, QWidget *parent) : QWidget(parent){
    mDirString = nDirString;
    queryUpdateInfo();

}

//获取当前更新文件名
QString SatUpdateListWidget::getUpdateFile(){
    if(mList.size() <= 0 || mIndex < 0 || mIndex >= mList.size()){
        return NULL;
    }
    return mFileInfoList.at(mIndex).filePath();
}

void SatUpdateListWidget::showEvent(QShowEvent *event){
    //要重新载入更新程序包名
    queryUpdateInfo();
    QWidget::showEvent(event);
    if(mList.size() != 0){
        mIndex = 0;
        mList.at(mIndex)->setFocus();
    }
}

void SatUpdateListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    if(mList.size() != 0){
        mList.at(mIndex)->setFocus();
    }
}

void SatUpdateListWidget::paintEvent(QPaintEvent *event){
#if 1
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
//    painter.drawLine(0,0,0,height());//画左边线
//    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
//    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
#endif
    QWidget::paintEvent(event);
}

void SatUpdateListWidget::mouseReleaseEvent(QMouseEvent *event){
    proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

bool SatUpdateListWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            //return false;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                emit focusTransferSignal();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
        }
#endif
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}



void SatUpdateListWidget::focusNext(){
    if(mList.size() != 0){
        mIndex++;
        if(mIndex >= mList.size()){
            mIndex = 0;
        }
        mList.at(mIndex)->setFocus();
        emit indexChangeSignal(mIndex);
    }
}

void SatUpdateListWidget::focusPrevious(){
    if(mList.size() != 0){
        mIndex--;
        if(mIndex < 0){
            mIndex = mList.size() - 1;
        }
        mList.at(mIndex)->setFocus();
        emit indexChangeSignal(mIndex);
    }
}

//校正焦点索引
void SatUpdateListWidget::proofreadIndex(){
    if(mList.size() != 0){
        QWidget *nFocusWidget = focusWidget();
        if(nFocusWidget != mList.at(mIndex)){
            int nIndex = mIndex;
            for(int i=0; i<mList.size(); i++){
                if(mList.at(i) == nFocusWidget){
                    nIndex = i;
                    break;
                }
            }
            mIndex = nIndex;
        }
    }
}

//查找更新包
void SatUpdateListWidget::queryUpdateInfo(){
    mFileInfoList.clear();
    mList.clear();


    QDir nDir(mDirString);
    if(!nDir.exists()){
        return;
    }
    //nDir.setNameFilters("*.gpg");
    nDir.setFilter(QDir::Files | QDir::Hidden | QDir::Executable);
    nDir.setSorting(QDir::Name);
    QFileInfoList nFileInfoList = nDir.entryInfoList();
    for(int i=0; i<nFileInfoList.size(); i++){
        QFileInfo nFileInfo = nFileInfoList.at(i);
        if(nFileInfo.suffix() == "png" || nFileInfo.suffix() == "jpg"){
            mFileInfoList.append(nFileInfo);
        }
    }






    QVBoxLayout *nLayout = new QVBoxLayout;

    //按键组名称
    for(int i=0; i<mFileInfoList.size(); i++){
        QString nTextStr = mFileInfoList.at(i).fileName();
        SatButton *nButton = new SatButton(SatButton::TextLeftButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        mList.append(nButton);
    }
    //配置
    if(mList.size() != 0){
        mIndex = 0;
        mList.at(mIndex)->setFocus();
    }
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
}

#endif


#if 1
SatUpdateListWidget::SatUpdateListWidget(QString nDirString, QWidget *parent) : QWidget(parent){
    mDirString = nDirString;
    mListWidget = new QListWidget(this);
    mListWidget->installEventFilter(this);
    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addWidget(mListWidget);
    nLayout->setSpacing(0);
    nLayout->setContentsMargins(0,0,1,0);
    this->setLayout(nLayout);
    //queryUpdateInfo();//查询列表

    //connect(mListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(indexChangeSlot(int)));

}

//获取当前更新文件名
QString SatUpdateListWidget::getUpdateFile(){
    if(mListWidget->count() <= 0){
        return NULL;
    }
    return mFileInfoList.at(mListWidget->currentRow()).filePath();
}

//显示事件
void SatUpdateListWidget::showEvent(QShowEvent *event){
    //要重新载入更新程序包名
    queryUpdateInfo();
    QWidget::showEvent(event);
    if(mListWidget->count() > 0){
        mListWidget->setCurrentRow(0);
    }
    mListWidget->setFocus();
}

void SatUpdateListWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mListWidget->setFocus();
}

void SatUpdateListWidget::paintEvent(QPaintEvent *event){
#if 1
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
//    painter.drawLine(0,0,0,height());//画左边线
//    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
//    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
#endif
    QWidget::paintEvent(event);
}

void SatUpdateListWidget::mouseReleaseEvent(QMouseEvent *event){
    //proofreadIndex();
    QWidget::mouseReleaseEvent(event);
}

void SatUpdateListWidget::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
}


bool SatUpdateListWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            //return false;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                emit focusTransferSignal();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
        }
#endif
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}


void SatUpdateListWidget::indexChangeSlot(int nIndex){
    emit indexChangeSignal(nIndex);
}


void SatUpdateListWidget::focusNext(){
    int nIndex = mListWidget->currentRow();
    if(mListWidget->count() > 0){
        nIndex++;
        if(nIndex >= mListWidget->count()){
            nIndex = 0;
        }
        mListWidget->setCurrentRow(nIndex);
        emit indexChangeSignal(nIndex);
    }
}

void SatUpdateListWidget::focusPrevious(){
    int nIndex = mListWidget->currentRow();
    if(mListWidget->count() > 0){
        nIndex--;
        if(nIndex < 0){
            nIndex = mListWidget->count() - 1;
        }
        mListWidget->setCurrentRow(nIndex);
        emit indexChangeSignal(nIndex);
    }
}

//校正焦点索引
void SatUpdateListWidget::proofreadIndex(){
//    if(mList.size() != 0){
//        QWidget *nFocusWidget = focusWidget();
//        if(nFocusWidget != mList.at(mIndex)){
//            int nIndex = mIndex;
//            for(int i=0; i<mList.size(); i++){
//                if(mList.at(i) == nFocusWidget){
//                    nIndex = i;
//                    break;
//                }
//            }
//            mIndex = nIndex;
//        }
//    }
}

//查找更新包
void SatUpdateListWidget::queryUpdateInfo(){
    mFileInfoList.clear();
    mListWidget->clear();
    QDir nDir(mDirString);
    if(!nDir.exists()){
        return;
    }
    //nDir.setNameFilters("*.gpg");
    nDir.setFilter(QDir::Files | QDir::Hidden | QDir::Executable);
    nDir.setSorting(QDir::Name);
    QFileInfoList nFileInfoList = nDir.entryInfoList();
    for(int i=0; i<nFileInfoList.size(); i++){
        QFileInfo nFileInfo = nFileInfoList.at(i);
        //if(nFileInfo.suffix() == "png" || nFileInfo.suffix() == "jpg"){
        if(nFileInfo.suffix() == "gpg"){
            mFileInfoList.append(nFileInfo);
            QListWidgetItem *nItem = new QListWidgetItem;
            nItem->setText(nFileInfoList.at(i).fileName());
            mListWidget->addItem(nItem);
        }
    }
    //mListWidget->setCurrentRow(0);

}

#endif








//===

SatUpdateSmallWidget::SatUpdateSmallWidget(QWidget *parent) : QWidget(parent){
    //this->setFixedSize(640,60);
    this->setFixedHeight(60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //更新按钮
    SatPhotoButton *nUpdateButton = new SatPhotoButton(this);
    nUpdateButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nUpdateButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nUpdateButton->setTextStr(tr("Update"));
    nUpdateButton->setTextShowSign(false);
    nUpdateButton->installEventFilter(this);
    nLayout->addWidget(nUpdateButton);
    nSignalMapper->setMapping(nUpdateButton,"Update");
    connect(nUpdateButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nUpdateButton);


    //备份按钮
    SatPhotoButton *nBackupButton = new SatPhotoButton(this);
    nBackupButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nBackupButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nBackupButton->setTextStr(tr("Backup"));
    nBackupButton->setTextShowSign(false);
    nBackupButton->installEventFilter(this);
    nLayout->addWidget(nBackupButton);
    nSignalMapper->setMapping(nBackupButton,"Backup");
    connect(nBackupButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nBackupButton);


    //恢复按钮
    SatPhotoButton *nRecoveryButton = new SatPhotoButton(this);
    nRecoveryButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nRecoveryButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nRecoveryButton->setTextStr(tr("Recovery"));
    nRecoveryButton->setTextShowSign(false);
    nRecoveryButton->installEventFilter(this);
    nLayout->addWidget(nRecoveryButton);
    nSignalMapper->setMapping(nRecoveryButton,"Recovery");
    connect(nRecoveryButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRecoveryButton);



    //隐藏按钮
    SatPhotoButton *nHideButton = new SatPhotoButton(this);
    nHideButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_normal.png"));
    nHideButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_focus.png"));
    nHideButton->setTextStr(tr("Hide"));
    nHideButton->setTextShowSign(false);
    nHideButton->installEventFilter(this);
    nLayout->addWidget(nHideButton);
    nSignalMapper->setMapping(nHideButton,"Hide");
    connect(nHideButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nHideButton);



    //退出按钮
    SatPhotoButton *nQuitButton = new SatPhotoButton(this);
    nQuitButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_normal.png"));
    nQuitButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("quit_focus.png"));
    nQuitButton->setTextStr(tr("Quit"));
    nQuitButton->setTextShowSign(false);
    nQuitButton->installEventFilter(this);
    nLayout->addWidget(nQuitButton);
    nSignalMapper->setMapping(nQuitButton,"Quit");
    connect(nQuitButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nQuitButton);
    //配置
    nLayout->addStretch();
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->setMargin(0);
    nLayout->setSpacing(10);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatUpdateSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatUpdateSmallWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_26:
                focusPrevious();
                break;
            case KEY_27:
                focusNext();
                break;
            case KEY_16:
                mList.at(mIndex)->click();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatUpdateSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatUpdateSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatUpdateSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatUpdateSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == tr("Update")){
        mIndex = 0;
    }else if(nOpeStr == tr("Backup")){
        mIndex = 1;
    }else if(nOpeStr == tr("Recovery")){
        mIndex = 2;
    }else if(nOpeStr == tr("Hide")){
        this->hide();
    }else if(nOpeStr == tr("Quit")){
        this->hide();
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}


















#if 0
SatUpdatePage::SatUpdatePage(QWidget *parent) : QWidget(parent){
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    //信息显示面板
    mInfoLabel = new QLabel(this);
    nLayout->addWidget(mInfoLabel);
    nLayout->setStretchFactor(mInfoLabel,10);
    //按键组名称
    mStringList = new QStringList();
    mStringList->append(tr("Update"));
    mStringList->append(tr("Backup"));
    mStringList->append(tr("Recovery"));
    mStringList->append(tr("Cancel"));
    mStringList->append(tr("Close"));
    for(int i=0; i<mStringList->size(); i++){
        QString nTextStr = mStringList->value(i);
        SatButton *nButton = new SatButton(SatButton::TextLeftButton,this);
        nButton->setText(nTextStr);
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,nTextStr);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    //配置
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    nLayout->addStretch();
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

void SatUpdatePage::setInfoText(QString nInfoText){
    mInfoLabel->setText(nInfoText);
}

void SatUpdatePage::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

bool SatUpdatePage::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
#if 1
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                mList.at(mIndex)->click();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
            case KEY_18:
                mList.at(mIndex)->click();
                break;
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_25:
                return false;
            case KEY_21:
                emit focusTransferSignal();
                break;
        }
#endif
        return true;
    }else if(event->type() == QEvent::KeyRelease){
#if 0
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){//重复事件不处理
            return true;
        }
        switch(nKey->key()){
            case KEY_16://确认键，即点击
                mList.at(mIndex)->click();
                break;
            case KEY_26://左键
                focusPrevious();
                break;
            case KEY_27://右键
                focusNext();
                break;
            case KEY_18:
                mList.at(mIndex)->click();
                break;
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_25:
                return false;
            case KEY_21:
                emit focusTransferSignal();
                break;
        }
#endif
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatUpdatePage::handleContent(const QString &nStr){
    //点击时，改变索引
    int nIndex = mStringList->indexOf(nStr);
    if(nIndex < 0){
        return;
    }else if(nIndex != mIndex){
        mIndex = nIndex;
    }
    //操作判断
    if(nStr == tr("Update")){
        emit updateProgramSignal();
    }else if(nStr == tr("Backup")){
        emit backupProgramSignal();
    }else if(nStr == tr("Recovery")){
        emit recoveryProgramSignal();
    }else if(nStr == tr("Cancel")){
        mList.at(mIndex)->setHighLight(false);
        emit focusTransferSignal();
    }else if(nStr == tr("Close")){
        mList.at(mIndex)->setHighLight(false);
        emit goBackSignal();
    }
}

void SatUpdatePage::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatUpdatePage::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

#endif


















UpdateProgramWidget::UpdateProgramWidget(QWidget *parent) : QWidget(parent){
//    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
//    QFile nQss(nQssStr);
//    nQss.open(QFile::ReadOnly);
//    this->setStyleSheet(nQss.readAll());
//    nQss.close();
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->installEventFilter(this);
    mSatTitleBar->setTitle(tr("Update Program"));

    QWidget *nTmpWidget = new QWidget(this);
    //nTmpWidget->installEventFilter(this);
    //mLeftWidget = new SatScrollArea(nTmpWidget);
    //mLeftWidget->installEventFilter(this);
#if 0
    mRightWidget = new SatUpdatePage(nTmpWidget);
    QString nInfo = tr("Available update package:%1\nSize:%2").arg(3).arg("10M");
    mRightWidget->setInfoText(nInfo);
#endif


    mLabel = new QLabel(nTmpWidget);
    mLabel->installEventFilter(this);
    //mLabel->setAlignment(Qt::AlignCenter);
    //mLabel->setText("Size:10M");


    //mListWidget = new SatUpdateListWidget(PICTURE_DIR,nTmpWidget);
    mListWidget = new SatUpdateListWidget("/home/sat/Sat/Root/GF5000/backup/",nTmpWidget);
    //mListWidget->installEventFilter(mLeftWidget);

    //mLeftWidget->setWidget(mListWidget);
    //mLeftWidget->setAlignment(Qt::AlignTop);
    //mLeftWidget->setWidgetResizable(true);
    //内布局
    QHBoxLayout *nHLayout = new QHBoxLayout;
    //nHLayout->addWidget(mLeftWidget,2);
    nHLayout->addWidget(mListWidget,2);
#if 0
    nHLayout->addWidget(mRightWidget,3);
#endif

    nHLayout->addWidget(mLabel,3);


    nHLayout->setSpacing(0);
    nHLayout->setMargin(0);
    //nHLayout->setContentsMargins(0,0,1,0);
    nTmpWidget->setLayout(nHLayout);


    mSmallWidget = new SatUpdateSmallWidget(this);
    mSmallWidget->hide();
    //总布局
    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar);
    nVLayout->addWidget(nTmpWidget);
    nVLayout->addWidget(mSmallWidget);
    nVLayout->setMargin(0);//设置外边框
    nVLayout->setSpacing(0);//设置内边框
    this->setLayout(nVLayout);

    //connect(mListWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusLeftToRightSlot()));
    //connect(mListWidget,SIGNAL(indexChangeSignal(int)),this,SLOT(indexChangeSlot(int)));

    connect(mListWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusLeftToRightSlot()));
    connect(mListWidget,SIGNAL(indexChangeSignal(int)),this,SLOT(indexChangeSlot(int)));

#if 0
    connect(mRightWidget,SIGNAL(focusTransferSignal()),this,SLOT(focusRightToLeftSlot()));
    connect(mRightWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
#endif
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));

    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));


    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));


}

void UpdateProgramWidget::doUpdate(QString nStr){
    emit doUpdateSignal(nStr);
}

void UpdateProgramWidget::registerField(){
    SatData *nSatData = SatData::initance();
    QList<QString> nList;//窗口观察数据字段
    nList.append("UpdateAppState");//观察电量
    nSatData->attach(this,nList);//注册观察者及字段
}

void UpdateProgramWidget::doUpdateSlot(QString nOpeStr){
    if(nOpeStr == "UpdateAppState"){
        SatData *nSatData = SatData::initance();
        int nState = nSatData->getUpdateAppState();
        if(nState == Update_App_State_Hide){
            //隐藏提示窗口
        }else if(nState == Update_App_State_Backuping){
            //提示窗口显示正在备份
        }else if(nState == Update_App_State_Backup_Success){
            //提示窗口提示备份成功
        }
    }
}



void UpdateProgramWidget::focusLeftToRightSlot(){
#if 0
    mRightWidget->setFocus();
#endif
    mSmallWidget->show();
}

void UpdateProgramWidget::focusRightToLeftSlot(){
    mSmallWidget->hide();
    //mLeftWidget->widget()->setFocus();
    mListWidget->setFocus();
}

void UpdateProgramWidget::goBackSlot(){
    mSmallWidget->hide();
    this->hide();
}

void UpdateProgramWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == tr("Update")){
        QString nStr = tr("Do you want to update this package?");
        AskDialog *nDialog = new AskDialog(nStr,this);
        nDialog->move((640-nDialog->width())/2,(480-nDialog->height())/2);
        if(nDialog->exec()){
            emit operationSignal(Update_App,mListWidget->getUpdateFile());
        }
    }else if(nOpeStr == tr("Backup")){
        QString nStr = tr("Confirm the backup program?");
        AskDialog *nDialog = new AskDialog(nStr,this);
        nDialog->move((640-nDialog->width())/2,(480-nDialog->height())/2);
        if(nDialog->exec()){
            emit operationSignal(Backup_App,NULL);
        }
    }else if(nOpeStr == tr("Recovery")){
        QString nStr = tr("Did you restore the last backup?");
        AskDialog *nDialog = new AskDialog(nStr,this);
        nDialog->move((640-nDialog->width())/2,(480-nDialog->height())/2);
        if(nDialog->exec()){
            emit operationSignal(Recovery_App,NULL);
        }
    }else if(nOpeStr == tr("Hide")){
        mSmallWidget->hide();
        mListWidget->setFocus();
    }else if(nOpeStr == tr("Quit")){
        goBackSlot();
    }
}

void UpdateProgramWidget::indexChangeSlot(int /*nIndex*/){
    updateLabel();
}


void UpdateProgramWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    //mListWidget->setFocus();
    updateLabel();
}


bool UpdateProgramWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_16:
                mSmallWidget->show();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        //return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void UpdateProgramWidget::updateLabel(){

    QString nUpFile = mListWidget->getUpdateFile();
    if(nUpFile.isEmpty()){
        mLabel->setText(tr(" No update!"));
    }else{
        QFile nFile(nUpFile);
        if(!nFile.exists()){
            mLabel->setText(tr(" File lost or damaged!"));
            return;
        }
        QFileInfo nFileInfo(nUpFile);
//        QDateTime nModifiedTime = nFileInfo.lastModified();
//        QDate nDate = nModifiedTime.date();
        QString nSizeString;
        int nSize = nFileInfo.size();
        if(nSize < 1024){
            nSizeString = tr("%1 K").arg(nSize);
        }else{
            nSize = nSize/1024;
            if(nSize < 1024){
                nSizeString = tr("%1 KB").arg(nSize);
            }else{
                nSizeString = tr("%1 M").arg(QString::number((float)(nSize/1024.0),'f',2));
            }
        }
        QString nText = tr(" Update package name:\n\n\t%1\n The size:\n\n\t%2")
                .arg(nFileInfo.fileName()).arg(nSizeString);
        mLabel->setText(nText);
    }
}



