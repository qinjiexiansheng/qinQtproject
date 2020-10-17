#include "autosavepicturewidget.h"
#if 1

SatAutoSavePictureSmallWidget::SatAutoSavePictureSmallWidget(QWidget *parent) : QWidget(parent){
    //this->setFixedSize(640,60);
    this->setFixedHeight(60);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QHBoxLayout *nLayout = new QHBoxLayout;
    nLayout->addStretch();
    //确认按钮
    SatPhotoButton *nConfirmButton = new SatPhotoButton(this);
    nConfirmButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_normal.png"));
    nConfirmButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("check_focus.png"));
    nConfirmButton->setTextStr(tr("Confirm"));
    nConfirmButton->setTextShowSign(false);
    nConfirmButton->installEventFilter(this);
    nLayout->addWidget(nConfirmButton);
    nSignalMapper->setMapping(nConfirmButton,"Confirm");
    connect(nConfirmButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    mList.append(nConfirmButton);
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

void SatAutoSavePictureSmallWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,width(),0);
    QWidget::paintEvent(event);
}

bool SatAutoSavePictureSmallWidget::eventFilter(QObject *nObject, QEvent *event){
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

void SatAutoSavePictureSmallWidget::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    mIndex = 0;
    mList.at(mIndex)->setFocus();
}

void SatAutoSavePictureSmallWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            mList.at(0)->setTextStr(tr("Confirm"));
            mList.at(1)->setTextStr(tr("Hide"));
            mList.at(2)->setTextStr(tr("Quit"));
            break;
        default:
            break;
    }
}


void SatAutoSavePictureSmallWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SatAutoSavePictureSmallWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SatAutoSavePictureSmallWidget::handleContent(const QString &nOpeStr){
    if(nOpeStr == tr("Confirm")){
        mIndex = 0;
    }else if(nOpeStr == tr("Hide")){
        this->hide();
        return;
    }else if(nOpeStr == tr("Quit")){
        this->hide();
        emit goBackSignal();
        return;
    }
    emit operationSignal(nOpeStr);
}






//自动保存图片面板
SatAutoSavePicturePage::SatAutoSavePicturePage(QWidget *parent) : QLabel(parent){
    mData = 0;
}

int SatAutoSavePicturePage::getData(){
    return mData;
}

void SatAutoSavePicturePage::setData(int nData){
    if(mData != nData){
        mData = nData;
        update();
    }
}


void SatAutoSavePicturePage::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    QString nText;
    if(mData <= 60){
        nText = tr("%1 Seconds").arg(mData);
    }else if(mData <= 3600){
        if(mData % 60 == 0){
            if(mData/60 <= 1){
                nText = tr("%1 Minute").arg(mData/60);
            }else{
                nText = tr("%1 Minutes").arg(mData/60);
            }
        }else{
            if(mData/60 <= 1){
                nText = tr("%1 Minute %2 Seconds").arg(mData/60).arg(mData%60);
            }else{
                nText = tr("%1 Minutes %2 Seconds").arg(mData/60).arg(mData%60);
            }
        }
    }
    painter.drawText(0,0,width(),height(),Qt::AlignCenter,nText);
    QLabel::paintEvent(event);
}

void SatAutoSavePicturePage::changeEvent(QEvent *event){
    QLabel::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            update();
            break;
        default:
            break;
    }
}




AutoSavePictureWidget::AutoSavePictureWidget(QWidget *parent) : QWidget(parent){
    //this->setWindowFlags(Qt::Window);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setGeometry(195,140,250,200);
    mSatData = SatData::initance();
    queryData();
    //标题
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(tr("Auto Save Picture"));
    mSatTitleBar->installEventFilter(this);
    //
    mPage = new SatAutoSavePicturePage(this);
    mPage->setData(mData);
    //操作小窗口
    mSmallWidget = new SatAutoSavePictureSmallWidget(this);
    mSmallWidget->hide();
    //总布局
    QVBoxLayout *nVLayout = new QVBoxLayout;
    nVLayout->addWidget(mSatTitleBar,0,Qt::AlignTop);
    nVLayout->addWidget(mPage);
    nVLayout->addWidget(mSmallWidget,0,Qt::AlignBottom);
    nVLayout->setContentsMargins(1,1,1,1);
    nVLayout->setSpacing(0);//设置内边框
    nVLayout->setStretchFactor(mPage,10);
    this->setLayout(nVLayout);
    connect(mSatTitleBar,SIGNAL(returnButtonClick()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(goBackSignal()),this,SLOT(goBackSlot()));
    connect(mSmallWidget,SIGNAL(operationSignal(QString)),this,SLOT(operationSlot(QString)));
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

bool AutoSavePictureWidget::eventFilter(QObject *nObject, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *nKey = (QKeyEvent*)event;
#if 0
        if(nKey->isAutoRepeat()){
            return true;
        }
#endif
        switch(nKey->key()){
            case KEY_16:
                mSmallWidget->show();
                break;
            case KEY_26:
                subData();
                break;
            case KEY_27:
                addData();
                break;
        }
        return true;
    }else if(event->type() == QEvent::KeyRelease){
        return true;
    }
    return QWidget::eventFilter(nObject,event);
}

void AutoSavePictureWidget::showEvent(QShowEvent *event){
    queryData();
    QWidget::showEvent(event);
}

void AutoSavePictureWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#3485FB"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}

void AutoSavePictureWidget::changeEvent(QEvent *event){
    QWidget::changeEvent(event);
    switch(event->type()){
        case QEvent::LanguageChange:
            mSatTitleBar->setTitle(tr("Auto Save Picture"));
            break;
        default:
            break;
    }
}



void AutoSavePictureWidget::operationSlot(QString nOpeStr){
    if(nOpeStr == tr("Confirm")){
        emit operationSignal(Set_SavePhotoTime,QString("Time=%1").arg(mData));
        mSmallWidget->hide();
        this->hide();
    }
}

void AutoSavePictureWidget::goBackSlot(){
    this->hide();
}

void AutoSavePictureWidget::addData(){
    mData++;
    if(mData < 30){
        mData = 30;
    }
    if(mData > 3600){
        mData = 3600;
    }
    mPage->setData(mData);
}

void AutoSavePictureWidget::subData(){
    mData--;
    if(mData < 30){
        mData = 30;
    }
    if(mData > 3600){
        mData = 3600;
    }
    mPage->setData(mData);
}

void AutoSavePictureWidget::queryData(){
    mData = mSatData->getAutoSavePictureTime();
}
#endif


















