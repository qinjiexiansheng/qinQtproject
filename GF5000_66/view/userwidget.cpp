#include "userwidget.h"

SatSchemaWidget::SatSchemaWidget(QWidget *parent) : QWidget(parent){
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setFixedSize(50,310);
#if 1
    this->setAutoFillBackground(false);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //this->setWindowOpacity(0.5);
#endif
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    mSatData = SatData::initance();
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    //QHBoxLayout *nLayout = new QHBoxLayout;
    QVBoxLayout *nLayout = new QVBoxLayout;
    //按钮排布，如果布局变化，则showEvent（）里也可能需要变化
    //开启、关闭非均匀校正按钮（用于加载不同的K值表）
    nLayout->addStretch();

    int nSchemaMaxNum = mSatData->getSchemaListSize();
    for(int i = 0; i < nSchemaMaxNum; i++){
        AbstractSchema *nSchema = mSatData->getSchema(i);
        SatPhotoHighLightButton *nButton = new SatPhotoHighLightButton(this);
        nButton->setFocusFilename(nSchema->imageFocus());
        nButton->setNormalFilename(nSchema->imageNormal());
        nButton->setHighLightFilename(nSchema->imageLight());
        nButton->setTextString(nSchema->name());
        nButton->installEventFilter(this);
        nLayout->addWidget(nButton);
        nSignalMapper->setMapping(nButton,i);
        connect(nButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
        mList.append(nButton);
    }
    nLayout->addStretch();
    mIndex = mSatData->getCurrentSchemaIndex();
    mList.at(mIndex)->setHighLight(true);
    mList.at(mIndex)->setFocus();
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(10);//设置内边距
    this->setLayout(nLayout);
    connect(nSignalMapper,SIGNAL(mapped(int)),this,SLOT(handleContent(int)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

void SatSchemaWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor(32,176,80,255));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.setBrush(QColor(32,176,80,255));
    //painter.setBrush(QColor(Qt::white));
    painter.drawRect(0,0, this->width(), this->height());
    //painter.drawLine(0,0,0,this->height());
    //painter.drawLine(0,0,width(),0);
    //painter.drawLine(width()-1,0,width()-1,height()-1);
    //painter.drawLine(0,height()-1,width()-1,height()-1);
    QWidget::paintEvent(event);
}


void SatSchemaWidget::showEvent(QShowEvent *event){
    mIndex = mSatData->getCurrentSchemaIndex();
    mList.at(mIndex)->setHighLight(true);
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(event);
}

void SatSchemaWidget::focusOutEvent(QFocusEvent *event){
    this->close();
    QWidget::focusOutEvent(event);
}


bool SatSchemaWidget::eventFilter(QObject *obj, QEvent *event){
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
                //this->close();
                mList.at(mIndex)->click();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SatSchemaWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}


void SatSchemaWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size()-1;
    }
    mList.at(mIndex)->setFocus();
}


void SatSchemaWidget::handleContent(int nIndex){
    if(nIndex < 0){
        nIndex = 0;
    }else if(nIndex >= mList.size()){
        nIndex = mList.size() - 1;
    }
    if(nIndex != mSatData->getCurrentSchemaIndex()){
        int nOpeStr = mSatData->getCurrentSchema()->leaveMode();
        emit operationSignal(nOpeStr,NULL);
        mIndex = nIndex;
        QString nParStr = QString("Schema=%1").arg(mIndex);
        emit operationSignal(Set_Schema,nParStr);
        nOpeStr = mSatData->getSchema(mIndex)->entryMode();
        emit operationSignal(nOpeStr,NULL);
        mList.at(mIndex)->setFocus();
        this->hide();
        //this->parentWidget()->show();
    }else{
        this->hide();
        //this->parentWidget()->show();
    }
}







//=======================================


SatMainSmallWidget::SatMainSmallWidget(QWidget *parent) : QWidget(parent){
    //样式
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setFixedSize(50,310);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
#if 1
    this->setAutoFillBackground(false);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //this->setWindowOpacity(0.8);


//    QPalette pal = palette();

//    pal.setColor(QPalette::Background,QColor(0x00,0xff,0x00,0x00));
//    setPalette(pal);

#endif
    //按键布局
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addStretch();
    //模式
    SatPhotoButton *nSchemaButton = new SatPhotoButton(this);
    nSchemaButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("model_normal.png"));
    nSchemaButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("model_focus.png"));
    nSchemaButton->setTextStr(tr("Schema"));
    nSchemaButton->setTextShowSign(true);
    nSchemaButton->installEventFilter(this);
    nLayout->addWidget(nSchemaButton);
    nSignalMapper->setMapping(nSchemaButton,"Schema");
    connect(nSchemaButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSchemaButton);
    //图片
    SatPhotoButton *nPhotoButton = new SatPhotoButton(this);
    nPhotoButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("photo_normal.png"));
    nPhotoButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("photo_focus.png"));
    nPhotoButton->setTextStr(tr("Photo"));
    nPhotoButton->setTextShowSign(true);
    nPhotoButton->installEventFilter(this);
    nLayout->addWidget(nPhotoButton);
    nSignalMapper->setMapping(nPhotoButton,"Photo");
    connect(nPhotoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nPhotoButton);
    //视频
    SatPhotoButton *nVideoButton = new SatPhotoButton(this);
    nVideoButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("video_normal.png"));
    nVideoButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("video_focus.png"));
    nVideoButton->setTextStr(tr("Video"));
    nVideoButton->setTextShowSign(true);
    nVideoButton->installEventFilter(this);
    nLayout->addWidget(nVideoButton);
    nSignalMapper->setMapping(nVideoButton,"Video");
    connect(nVideoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nVideoButton);
    //设置
    SatPhotoButton *nSetupButton = new SatPhotoButton(this);
    nSetupButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("setup_normal.png"));
    nSetupButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("setup_focus.png"));
    nSetupButton->setTextStr(tr("Setup"));
    nSetupButton->setTextShowSign(true);
    nSetupButton->installEventFilter(this);
    nLayout->addWidget(nSetupButton);
    nSignalMapper->setMapping(nSetupButton,"Setup");
    connect(nSetupButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nSetupButton);
    //隐藏
    SatPhotoButton *nHideButton = new SatPhotoButton(this);
    nHideButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_normal.png"));
    nHideButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("hide_focus.png"));
    nHideButton->setTextStr(tr("Hide"));
    nHideButton->setTextShowSign(true);
    nHideButton->installEventFilter(this);
    nLayout->addWidget(nHideButton);
    nSignalMapper->setMapping(nHideButton,"Hide");
    connect(nHideButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nHideButton);
    //布局设置
    nLayout->addStretch();
    mIndex = mList.size() - 1;
    nLayout->setMargin(0);//设置外边距
    nLayout->setSpacing(10);//设置内边距
    this->setLayout(nLayout);
    mList.at(mIndex)->setFocus();
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));

    mSchemaWidget = new SatSchemaWidget(this);
    mSchemaWidget->move(0,85);
    mSchemaWidget->hide();
    mPictureBrowingWidget = NULL;
    mSystemWidget = NULL;
    mVideoWidget = NULL;

}

void SatMainSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //painter.fillRect(this->rect(), QColor(255, 255, 255, 0));

#if 0
    QPainter p(this);
    p.setCompositionMode( QPainter::CompositionMode_Clear );
    p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
#endif

    QPen nPen;
    nPen.setColor(QColor(32,176,80,255));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.setBrush(QColor(32,176,80,255));
//    //painter.setBrush(QColor(Qt::white));
    painter.drawRect(0,0, this->width(), this->height());
//    painter.drawLine(0,0,0,this->height());
    //painter.drawLine(0,0,width(),0);
//    painter.drawLine(width()-1,0,width()-1,height()-1);
//    painter.drawLine(0,height()-1,width()-1,height()-1);
    QWidget::paintEvent(event);
}


void SatMainSmallWidget::showEvent(QShowEvent *event){
//    if(mIndex >= mList.size() - 1){
//        mIndex = 0;
//    }
    mIndex = 0;
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(event);
}

void SatMainSmallWidget::focusOutEvent(QFocusEvent *event){
    this->close();
    QWidget::focusOutEvent(event);
}


bool SatMainSmallWidget::eventFilter(QObject *obj, QEvent *event){
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
                //this->close();
                mList.at(mIndex)->click();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SatMainSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}


void SatMainSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size()-1;
    }
    mList.at(mIndex)->setFocus();
}


void SatMainSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == "Schema"){//放大图片
        //
        this->hide();
        mSchemaWidget->show();
    }else if(nOpeStr == "Photo"){
        //
        this->hide();
        if(mPictureBrowingWidget == NULL){
            mPictureBrowingWidget = new PictureBrowingWidget(QString(PICTURE_DIR),this);
        }
        mPictureBrowingWidget->show();
    }else if(nOpeStr == "Video"){
        //

        if(mVideoWidget == NULL){
            mVideoWidget = new VideoBrowingWidget(QString(VIDEO_DIR),this);
        }
        mVideoWidget->show();

#if 0
        this->hide();
        QString nStr;
        nStr = tr("Function not implemented!");
        AskDialog *nDialog = new AskDialog(nStr,this);
        nDialog->move((640-nDialog->width())/2,(480-nDialog->height())/2);
        if(nDialog->exec()){
            //重置 
        }
#endif
    }else if(nOpeStr == "Setup"){
        //
        if(mSystemWidget == NULL){
            mSystemWidget = new SystemWidget(this);
        }
        mSystemWidget->show();
    }else if(nOpeStr == "Hide"){
        this->hide();
    }
}








