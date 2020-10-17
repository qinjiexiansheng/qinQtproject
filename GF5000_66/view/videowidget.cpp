#include "videowidget.h"

SatVideoSmallWidget::SatVideoSmallWidget(QWidget *parent) : QWidget(parent){
    this->setFixedSize(640,60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //停止按钮
    SatPhotoButton *nStopButton = new SatPhotoButton(this);
    nStopButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("stop_normal.png"));
    nStopButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("stop_focus.png"));
    nStopButton->setTextStr(tr("Stop"));
    nStopButton->setTextShowSign(false);
    nStopButton->installEventFilter(this);
    nLayout->addWidget(nStopButton);
    nSignalMapper->setMapping(nStopButton,"Stop");
    connect(nStopButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nStopButton);
    //暂停和播放按钮
    SatPhotoButton *nPauseAndPlayButton = new SatPhotoButton(this);
    nPauseAndPlayButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("pause_normal.png"));
    nPauseAndPlayButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("pause_focus.png"));
    nPauseAndPlayButton->setTwoNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("play_normal.png"));
    nPauseAndPlayButton->setTwoFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("play_focus.png"));
    nPauseAndPlayButton->setTextStr(tr("PauseAndPlay"));
    nPauseAndPlayButton->setTextShowSign(false);
    nPauseAndPlayButton->setTwoState(false);
    nPauseAndPlayButton->installEventFilter(this);
    nLayout->addWidget(nPauseAndPlayButton);
    nSignalMapper->setMapping(nPauseAndPlayButton,"PauseAndPlay");
    connect(nPauseAndPlayButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nPauseAndPlayButton);
    //缩放屏幕按钮
    SatPhotoButton *nZoomButton = new SatPhotoButton(this);
    nZoomButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("full_screen_normal.png"));
    nZoomButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("full_screen_focus.png"));
    nZoomButton->setTwoNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("normal_screen_normal.png"));
    nZoomButton->setTwoFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("normal_screen_focus.png"));
    nZoomButton->setTextStr(tr("Zoom"));
    nZoomButton->setTextShowSign(false);
    nZoomButton->setTwoState(false);
    nZoomButton->installEventFilter(this);
    nLayout->addWidget(nZoomButton);
    nSignalMapper->setMapping(nZoomButton,"Zoom");
    connect(nZoomButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nZoomButton);
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

void SatVideoSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatVideoSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatVideoSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatVideoSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatVideoSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatVideoSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "Stop"){//放大图片
        mIndex = 0;
        emit operationSignal(nOpeStr);
    }else if(nOpeStr == "PauseAndPlay"){
        mIndex = 1;
        if(mList.at(mIndex)->isTwoState()){//
            emit operationSignal("Play");
            mList.at(mIndex)->setTwoState(false);
        }else{
            emit operationSignal("Pause");
            mList.at(mIndex)->setTwoState(true);
        }
    }else if(nOpeStr == "Zoom"){
        mIndex = 2;
        if(mList.at(mIndex)->isTwoState()){
            emit operationSignal("NormalScreen");
            mList.at(mIndex)->setTwoState(false);
        }else{
            emit operationSignal("FullScreen");
            mList.at(mIndex)->setTwoState(true);
        }
    }else if(nOpeStr == "Hide"){
        this->hide();
        return;
    }else if(nOpeStr == "Quit"){
        emit operationSignal("Quit");
        return;
    }
}


SatVideoWidget::SatVideoWidget(QWidget *parent) : QWidget(parent){
    //载入样式表
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    //窗口设置
    this->setWindowFlags(Qt::Window);
    this->setGeometry(0,0,640,480);
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->installEventFilter(this);
    nLayout->addWidget(mSatTitleBar);
    mImageLabel = new QLabel(this);
    mImageLabel->installEventFilter(this);
    nLayout->addWidget(mImageLabel,10,Qt::AlignCenter);
    mSmallWidget = new SatVideoSmallWidget(this);
    nLayout->addWidget(mSmallWidget);
    mSmallWidget->hide();
    //布局参数
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    //线程启动
    mVideoDecode = new VideoDecode();
    QThread *nThread = new QThread();
    mVideoDecode->moveToThread(nThread);
    nThread->start();
    //信号槽连接
    connect(mVideoDecode,SIGNAL(displayImage(QImage)),this,SLOT(showImage(QImage)));
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));
}

QString SatVideoWidget::getVideoStr(){
    return mVideoStr;
}

void SatVideoWidget::setVideoStr(QString nVideoStr){
    mVideoStr = nVideoStr;
    mVideoDecode->setVideoFilename(mVideoStr);
    mVideoDecode->videoPlay();
}

void SatVideoWidget::showImage(QImage nImage){
    nImage = nImage.scaled(640*0.8,480*0.8,Qt::KeepAspectRatio);
    mImageLabel->setPixmap(QPixmap::fromImage(nImage));
    qDebug("[D]Lin >> The VideoWidget Debug!==");
}

bool SatVideoWidget::eventFilter(QObject *nObject, QEvent *event){
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
                break;
            case KEY_27:
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void SatVideoWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
}

void SatVideoWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == "Stop"){

    }else if(nOpeStr == "Pause"){

    }else if(nOpeStr == "Quit"){
        goBackSlot();
    }
}

void SatVideoWidget::goBackSlot(){
    mSmallWidget->hide();
    this->hide();
}





SatVideoBrowingSmallWidget::SatVideoBrowingSmallWidget(QWidget *parent) : QWidget(parent){
    this->setFixedSize(640,60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //播放按钮
    SatPhotoButton *nCheckButton = new SatPhotoButton(this);
    nCheckButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("play_normal.png"));
    nCheckButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("play_focus.png"));
    nCheckButton->setTextStr(tr("Play"));
    nCheckButton->setTextShowSign(false);
    nCheckButton->installEventFilter(this);
    nLayout->addWidget(nCheckButton);
    nSignalMapper->setMapping(nCheckButton,"Play");
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

void SatVideoBrowingSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatVideoBrowingSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatVideoBrowingSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatVideoBrowingSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatVideoBrowingSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatVideoBrowingSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "Play"){
        mIndex = 0;
    }else if(nOpeStr == "Delete"){
        mIndex = 1;
    }else if(nOpeStr == "Hide"){
        this->hide();
        return;
    }else if(nOpeStr == "Quit"){
    }
    emit operationSignal(nOpeStr);
}








//图片缩略图窗口
VideoBrowingWidget::VideoBrowingWidget(QString nDirStr,QWidget *parent) : QWidget(parent){
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
    mSatTitleBar->setTitle(tr("Video Browing"));
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
    mSmallWidget = new SatVideoBrowingSmallWidget(this);
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
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));

    mViewWidget = NULL;

}

QString VideoBrowingWidget::getDirStr(){
    return mDirStr;
}

void VideoBrowingWidget::setDirStr(QString nDirStr){
    if(mDirStr != nDirStr){
        mDirStr = nDirStr;
    }
}

void VideoBrowingWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mListWidget->clear();
    ergodicVideo();
    //重新显示
    mListWidget->setCurrentRow(0);
    mSmallWidget->hide();
}

void VideoBrowingWidget::focusInEvent(QFocusEvent *event){
    QWidget::focusInEvent(event);
    mListWidget->setCurrentRow(0);
}

bool VideoBrowingWidget::eventFilter(QObject *nObject, QEvent *event){
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

void VideoBrowingWidget::goBackSlot(){
    this->hide();
}

void VideoBrowingWidget::operationSlot(QString nOpeStr){

    if(nOpeStr == "Play"){
        if(mListWidget->count() <= 0){
            return;
        }
        if(mViewWidget == NULL){
            mViewWidget = new SatVideoWidget(this);
        }
        mViewWidget->setVideoStr(mDirStr + mListWidget->currentItem()->text());
        mViewWidget->show();
    }else if(nOpeStr == "Delete"){
        if(mListWidget->count() <= 0){
            return;
        }
        QString nStr;
        nStr = tr("The Video will be deleted!");
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
    }else if(nOpeStr == "Quit"){
        goBackSlot();
    }
}

void VideoBrowingWidget::ergodicVideo(){
    QDirIterator nDirIt(mDirStr,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);	//遍历所有目录和文件
    QIcon nIcon;
    QPixmap nPixmap;
    nPixmap.load(QString(VIDEO_PICTURE));
    nPixmap = nPixmap.scaled(mListWidget->iconSize());
    nIcon.addPixmap(nPixmap);

    while(nDirIt.hasNext()){
        QString nName = nDirIt.next();//读取
        QFileInfo nInfo(nName);
        if (nInfo.isDir()){
            //不递归浏览目录
        }else{
            if(nInfo.suffix() == "MP4" || nInfo.suffix() == "mp4"){
                if(nInfo.size() <= 0){
                    continue;
                }
#if 1
                QListWidgetItem *nImageItem = new QListWidgetItem;
                nImageItem->setIcon(nIcon);
#endif
                nImageItem->setText(nInfo.fileName());
                mListWidget->addItem(nImageItem);
            }
        }
    }
}

void VideoBrowingWidget::focusPrevious(){
    int nRow = mListWidget->currentRow();
    nRow--;
    if(nRow < 0){
        nRow = 0;
    }
    mListWidget->setCurrentRow(nRow);
}

void VideoBrowingWidget::focusNext(){
    int nRow = mListWidget->currentRow();
    nRow++;
    if(nRow >= mListWidget->count()){
        nRow = mListWidget->count() - 1;
    }
    mListWidget->setCurrentRow(nRow);
}




















