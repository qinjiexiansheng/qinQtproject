#include "picturebrowingwidget.h"

SatPictureViewSmallWidget::SatPictureViewSmallWidget(QWidget *parent) : QWidget(parent){
    this->setFixedSize(640,60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //放大按钮
    SatPhotoButton *nEnlargeButton = new SatPhotoButton(this);
    nEnlargeButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("enlarge_normal.png"));
    nEnlargeButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("enlarge_focus.png"));
    nEnlargeButton->setTextStr(tr("Enlarge"));
    nEnlargeButton->setTextShowSign(false);
    nEnlargeButton->installEventFilter(this);
    nLayout->addWidget(nEnlargeButton);
    nSignalMapper->setMapping(nEnlargeButton,"Enlarge");
    connect(nEnlargeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nEnlargeButton);
    //缩小按钮
    SatPhotoButton *nNarrowButton = new SatPhotoButton(this);
    nNarrowButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("narrow_normal.png"));
    nNarrowButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("narrow_focus.png"));
    nNarrowButton->setTextStr(tr("Narrow"));
    nNarrowButton->setTextShowSign(false);
    nNarrowButton->installEventFilter(this);
    nLayout->addWidget(nNarrowButton);
    nSignalMapper->setMapping(nNarrowButton,"Narrow");
    connect(nNarrowButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nNarrowButton);
    //上移按钮
    SatPhotoButton *nMoveUpButton = new SatPhotoButton(this);
    nMoveUpButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("moveup_normal.png"));
    nMoveUpButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("moveup_focus.png"));
    nMoveUpButton->setTextStr(tr("MoveUp"));
    nMoveUpButton->setTextShowSign(false);
    nMoveUpButton->installEventFilter(this);
    nLayout->addWidget(nMoveUpButton);
    nSignalMapper->setMapping(nMoveUpButton,"MoveUp");
    connect(nMoveUpButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nMoveUpButton);
    //下移
    SatPhotoButton *nMoveDownButton = new SatPhotoButton(this);
    nMoveDownButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("movedown_normal.png"));
    nMoveDownButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("movedown_focus.png"));
    nMoveDownButton->setTextStr(tr("MoveDown"));
    nMoveDownButton->setTextShowSign(false);
    nMoveDownButton->installEventFilter(this);
    nLayout->addWidget(nMoveDownButton);
    nSignalMapper->setMapping(nMoveDownButton,"MoveDown");
    connect(nMoveDownButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nMoveDownButton);
    //左移
    SatPhotoButton *nLeftShiftButton = new SatPhotoButton(this);
    nLeftShiftButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("leftshift_normal.png"));
    nLeftShiftButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("leftshift_focus.png"));
    nLeftShiftButton->setTextStr(tr("LeftShift"));
    nLeftShiftButton->setTextShowSign(false);
    nLeftShiftButton->installEventFilter(this);
    nLayout->addWidget(nLeftShiftButton);
    nSignalMapper->setMapping(nLeftShiftButton,"LeftShift");
    connect(nLeftShiftButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nLeftShiftButton);
    //右移
    SatPhotoButton *nRightShiftButton = new SatPhotoButton(this);
    nRightShiftButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("rightshift_normal.png"));
    nRightShiftButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("rightshift_focus.png"));
    nRightShiftButton->setTextStr(tr("RightShift"));
    nRightShiftButton->setTextShowSign(false);
    nRightShiftButton->installEventFilter(this);
    nLayout->addWidget(nRightShiftButton);
    nSignalMapper->setMapping(nRightShiftButton,"RightShift");
    connect(nRightShiftButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nRightShiftButton);
#if 0
    //删除
    SatPhotoButton *nDeleteButton = new SatPhotoButton(this);
    nDeleteButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("delete_normal.png"));
    nDeleteButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("delete_focus.png"));
    nDeleteButton->setTextStr(tr("Delete"));
    nDeleteButton->setTextShowSign(false);
    nDeleteButton->installEventFilter(this);
    nLayout->addWidget(nDeleteButton);
    nSignalMapper->setMapping(nDeleteButton,"Delete");
    connect(nDeleteButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDeleteButton);
#endif
    //隐藏
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
    //退出
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

void SatPictureViewSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatPictureViewSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatPictureViewSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatPictureViewSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPictureViewSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPictureViewSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "Enlarge"){//放大图片
        mIndex = 0;
        //emit operationSignal(nOpeStr);
    }else if(nOpeStr == "Narrow"){
        mIndex = 1;
        //emit operationSignal(nOpeStr);
    }else if(nOpeStr == "MoveUp"){
        mIndex = 2;
    }else if(nOpeStr == "MoveDown"){
        mIndex = 3;
    }else if(nOpeStr == "LeftShift"){
        mIndex = 4;
    }else if(nOpeStr == "RightShift"){
        mIndex = 5;
    }else if(nOpeStr == "Delete"){
        mIndex = 6;
    }else if(nOpeStr == "Hide"){
        this->hide();
        return;
    }else if(nOpeStr == "Quit"){
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}


//=======


SatPictureLabel::SatPictureLabel(QString nPicStr, QWidget *parent) : QLabel(parent){
    mPicStr = nPicStr;
    mWidth = 640*0.8;
    mHeight = 480*0.8;
    mZoomFactor = 1;
    this->setFixedSize(mWidth*mZoomFactor,mHeight*mZoomFactor);
}

QString SatPictureLabel::getPicStr(){
    return mPicStr;
}

void SatPictureLabel::setPicStr(QString nPicStr){
    mPicStr = nPicStr;
    mWidth = 640*0.8;
    mHeight = 480*0.8;
    mZoomFactor = 1;
    this->setFixedSize(mWidth*mZoomFactor,mHeight*mZoomFactor);
    update();
}

void SatPictureLabel::setZoomFactor(float nZoomFactor){
    //qDebug("[D]Lin >> The nZoomFactor:%f,mZoomFactor:%f",nZoomFactor,mZoomFactor);
    if(nZoomFactor < 0.2){
        return;
    }
    if(nZoomFactor > 2.5){
        return;
    }
    mZoomFactor = nZoomFactor;
    this->setFixedSize(mWidth*mZoomFactor,mHeight*mZoomFactor);
    //update();
}

float SatPictureLabel::getZoomFactor(){
    return mZoomFactor;
}


void SatPictureLabel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(QFile::exists(mPicStr)){
        QPixmap nPixmap;
        nPixmap.load(mPicStr);
        nPixmap = nPixmap.scaled(width(),height(),Qt::KeepAspectRatio);
        painter.drawPixmap(0,0,nPixmap);
    }else{
        painter.drawText(0,0,width(),height(),Qt::AlignCenter,tr("Image loading error!"));
    }
    QLabel::paintEvent(event);
}







SatPictureViewWidget::SatPictureViewWidget(QString nPicStr, QWidget *parent) : QWidget(parent){
    mPicStr = nPicStr;
    //加载样式
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);

    QFileInfo nInfo = QFileInfo(mPicStr);

    //标题
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(nInfo.fileName());
    mSatTitleBar->installEventFilter(this);
    //图片标签
    mScrollArea = new SatScrollArea(this);
    mPictureLabel = new SatPictureLabel(mPicStr,mScrollArea);
    mPictureLabel->installEventFilter(this);
    mScrollArea->setWidget(mPictureLabel);
    mScrollArea->setAlignment(Qt::AlignCenter);
    mScrollArea->setWidgetResizable(true);
    //操作小窗口
    mSmallWidget = new SatPictureViewSmallWidget(this);
    mSmallWidget->hide();
    //总布局
    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar,0,Qt::AlignTop);
    nVLayout->addWidget(mScrollArea);
    nVLayout->addWidget(mSmallWidget,0,Qt::AlignBottom);
    //nVLayout->setMargin(0);//设置外边框
    nVLayout->setContentsMargins(0,0,0,10);
    nVLayout->setSpacing(0);//设置内边框
    nVLayout->setStretchFactor(mPictureLabel,10);
    this->setLayout(nVLayout);
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));

    mImgInfoList = NULL;

}

QString SatPictureViewWidget::getPicStr(){
    return mPicStr;
}

void SatPictureViewWidget::setPicStr(QString nPicStr){
    mPicStr = nPicStr;
}

bool SatPictureViewWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_16:
                mSmallWidget->show();
                break;
            case KEY_26:
                showPhotoPrevious();
                break;
            case KEY_27:
                showPhotoNext();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatPictureViewWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    getImgInfoList();
    mPictureLabel->setPicStr(mPicStr);
}

void SatPictureViewWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == "Enlarge"){//放大图片
        mPictureLabel->setZoomFactor(mPictureLabel->getZoomFactor()+0.1);
    }else if(nOpeStr == "Narrow"){
        mPictureLabel->setZoomFactor(mPictureLabel->getZoomFactor()-0.1);
    }else if(nOpeStr == "MoveUp"){
        int nValue = mScrollArea->verticalScrollBar()->value();
        nValue -= 50;
        mScrollArea->verticalScrollBar()->setValue(nValue);
    }else if(nOpeStr == "MoveDown"){
        int nValue = mScrollArea->verticalScrollBar()->value();
        nValue += 50;
        mScrollArea->verticalScrollBar()->setValue(nValue);
    }else if(nOpeStr == "LeftShift"){
        int nValue = mScrollArea->horizontalScrollBar()->value();
        nValue -= 50;
        mScrollArea->horizontalScrollBar()->setValue(nValue);
    }else if(nOpeStr == "RightShift"){
        int nValue = mScrollArea->horizontalScrollBar()->value();
        nValue += 50;
        mScrollArea->horizontalScrollBar()->setValue(nValue);
    }else if(nOpeStr == "Delete"){
    }
}

void SatPictureViewWidget::goBackSlot(){
    mSmallWidget->hide();
    this->hide();
}

void SatPictureViewWidget::showPhotoPrevious(){
    if(mImgInfoList == NULL){
        getImgInfoList();
    }
    if(mIndex == 0){
        return;
    }
    mIndex--;
    if(mIndex < 0){
        mIndex = 0;
    }
    mPicStr = mImgInfoList->at(mIndex).absoluteFilePath();
    mPictureLabel->setPicStr(mPicStr);
    mSatTitleBar->setTitle(mPicStr);
}

void SatPictureViewWidget::showPhotoNext(){
    if(mImgInfoList == NULL){
        getImgInfoList();
    }
    if(mIndex == mImgInfoList->count()-1){
        return;
    }
    mIndex++;
    if(mIndex > mImgInfoList->count() - 1){
        mIndex = mImgInfoList->count() - 1;
    }
    mPicStr = mImgInfoList->at(mIndex).absoluteFilePath();
    mPictureLabel->setPicStr(mPicStr);
    mSatTitleBar->setTitle(mPicStr);
}

void SatPictureViewWidget::getImgInfoList(){
    if(mImgInfoList == NULL){
        mImgInfoList = new QFileInfoList();
    }else{
        mImgInfoList->clear();
    }
    QDir nDir = QFileInfo(mPicStr).absolutePath();
    QFileInfoList nInfoList = nDir.entryInfoList(QDir::Files);
    QFileInfo nInfo;
    for(int i=0; i<nInfoList.count(); i++){
        nInfo = nInfoList.at(i);
        QString nSuffix = nInfo.suffix();
        if(nSuffix == "jpg" || nSuffix == "bmp" || nSuffix == "png"){
            mImgInfoList->append(nInfo);
        }
    }
    QFileInfo nCurrentImageInfo = QFileInfo(mPicStr);
    for(int i=0; i<mImgInfoList->count(); i++){
        nInfo = mImgInfoList->at(i);
        if(nInfo.fileName() == nCurrentImageInfo.fileName()){
            mIndex = i;
        }
    }
}















//================

SatPictureBrowingSmallWidget::SatPictureBrowingSmallWidget(QWidget *parent) : QWidget(parent){
    this->setFixedSize(640,60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //查看按钮
    SatPhotoButton *nCheckButton = new SatPhotoButton(this);
    nCheckButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nCheckButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nCheckButton->setTextStr(tr("Check"));
    nCheckButton->setTextShowSign(false);
    nCheckButton->installEventFilter(this);
    nLayout->addWidget(nCheckButton);
    nSignalMapper->setMapping(nCheckButton,"Check");
    connect(nCheckButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nCheckButton);
    //删除按钮
    SatPhotoButton *nDeleteButton = new SatPhotoButton(this);
    nDeleteButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("delete_normal.png"));
    nDeleteButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("delete_focus.png"));
    nDeleteButton->setTextStr(tr("Delete"));
    nDeleteButton->setTextShowSign(false);
    nDeleteButton->installEventFilter(this);
    nLayout->addWidget(nDeleteButton);
    nSignalMapper->setMapping(nDeleteButton,"Delete");
    connect(nDeleteButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nDeleteButton);
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

void SatPictureBrowingSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatPictureBrowingSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatPictureBrowingSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatPictureBrowingSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatPictureBrowingSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatPictureBrowingSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "Check"){
        mIndex = 0;
    }else if(nOpeStr == "Delete"){
        mIndex = 1;
    }else if(nOpeStr == "Hide"){
        this->hide();
        return;
    }else if(nOpeStr == "Quit"){
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}








//图片缩略图窗口
PictureBrowingWidget::PictureBrowingWidget(QString nDirStr,QWidget *parent) : QWidget(parent){
    //加载样式
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);
    mDirStr = nDirStr;

    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Picture Browing"));
    mSatTitleBar->installEventFilter(this);

    mListWidget = new QListWidget(this);
    mListWidget->installEventFilter(this);
    mListWidget->setViewMode(QListWidget::IconMode);
    mListWidget->setIconSize(QSize(180,120));
    mListWidget->setSpacing(10);
    mListWidget->setResizeMode(QListWidget::Adjust);
    mListWidget->setMovement(QListWidget::Static);
    //
    //ergodicPicture();
    //==
    mSmallWidget = new SatPictureBrowingSmallWidget(this);
    mSmallWidget->hide();
    //总布局
    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar);
    nVLayout->addWidget(mListWidget);
    nVLayout->addWidget(mSmallWidget);
    //nVLayout->setMargin(0);//设置外边框
    nVLayout->setContentsMargins(0,0,0,10);
    nVLayout->setSpacing(0);//设置内边框
    this->setLayout(nVLayout);
    mListWidget->setFocus();
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));

    mViewWidget = NULL;

}

QString PictureBrowingWidget::getDirStr(){
    return mDirStr;
}

void PictureBrowingWidget::setDirStr(QString nDirStr){
    if(mDirStr != nDirStr){
        mDirStr = nDirStr;
    }
}

void PictureBrowingWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mListWidget->clear();
    ergodicPicture();
    //重新显示
    mListWidget->setCurrentRow(0);
    mSmallWidget->hide();
}

void PictureBrowingWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mListWidget->setCurrentRow(0);
}

bool PictureBrowingWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
#if 0
        if(nKey->isAutoRepeat()){
            return ture;
        }
#endif
        switch(nKey->key()){
            case KEY_16:
                {
                    //float nPercent = mListWidget->verticalScrollBar()->value()*1.0/mListWidget->verticalScrollBar()->maximum();
                    mSmallWidget->show();
                    //int nValue = mListWidget->verticalScrollBar()->maximum()*nPercent;
                    //mListWidget->verticalScrollBar()->setValue(nValue);
                }
                break;
            case KEY_26:
                focusPrevious();
                break;
            case KEY_27:
                focusNext();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void PictureBrowingWidget::goBackSlot(){
    this->hide();
}

void PictureBrowingWidget::operationSlot(QString nOpeStr){

    if(nOpeStr == "Check"){
        if(mListWidget->count() <= 0){
            return;
        }
        if(mViewWidget == NULL){
            mViewWidget = new SatPictureViewWidget(mDirStr + mListWidget->currentItem()->text(),this);
        }else{
            mViewWidget->setPicStr(mDirStr + mListWidget->currentItem()->text());
        }
        mViewWidget->show();
    }else if(nOpeStr == "Delete"){
        if(mListWidget->count() <= 0){
            return;
        }
        QString nStr;
        nStr = tr("The picture will be deleted!");
        AskDialog *nDialog = new AskDialog(nStr,this);
        if(nDialog->exec()){
            QString nFilename = mDirStr + mListWidget->currentItem()->text();
            if(QFile::exists(nFilename)){
                QFile::remove(nFilename);
            }
            QListWidgetItem *nItem = mListWidget->takeItem(mListWidget->currentRow());
            delete nItem;
            mSmallWidget->hide();
        }
    }
}

void PictureBrowingWidget::ergodicPicture(){
    QDirIterator nDirIt(mDirStr,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);	//遍历所有目录和文件
    while(nDirIt.hasNext()){
        QString nName = nDirIt.next();//读取
        QFileInfo nInfo(nName);
        if (nInfo.isDir()){
            //
        }else{
            if(nInfo.suffix() == "jpg" || nInfo.suffix() == "bmp" || nInfo.suffix() == "png"){
                if(nInfo.size() <= 0){
                    continue;
                }
                //qDebug("[D]Lin >> The %s's size:%d",nInfo.absoluteFilePath().toStdString().c_str(),nInfo.size());



#if 1
                QIcon nIcon;
                QPixmap nPixmap;
                nPixmap.load(nInfo.absoluteFilePath());
                if(nPixmap.isNull()){
                    continue;
                }
                nPixmap = nPixmap.scaled(mListWidget->iconSize());
                if(nPixmap.isNull()){
                    continue;
                }
                nIcon.addPixmap(nPixmap);


                QListWidgetItem *nImageItem = new QListWidgetItem;
                nImageItem->setIcon(nIcon);
#endif

                //nIcon.addFile(nInfo.absoluteFilePath(),QSize(50,50));
                //nImageItem->setIcon(nIcon);
#if 0
                nImageItem->setIcon(QIcon(nInfo.absoluteFilePath()));
#endif
                nImageItem->setText(nInfo.fileName());
                mListWidget->addItem(nImageItem);

            }
        }
    }
}

void PictureBrowingWidget::focusPrevious(){
    int nRow = mListWidget->currentRow();
    nRow--;
    if(nRow < 0){
        nRow = 0;
    }
    mListWidget->setCurrentRow(nRow);
}

void PictureBrowingWidget::focusNext(){
    int nRow = mListWidget->currentRow();
    nRow++;
    if(nRow >= mListWidget->count()){
        nRow = mListWidget->count() - 1;
    }
    mListWidget->setCurrentRow(nRow);
}
