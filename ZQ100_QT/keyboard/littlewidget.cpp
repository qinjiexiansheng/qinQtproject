#include "littlewidget.h"


/*===============================================================================
  @classname     xx
  @describe      xx
  @author        Helin
  @date          2018-06-08
  ===============================================================================*/
SatButton::SatButton(QWidget *parent) : QPushButton(parent){
    mType = NormalButton;
    initWidget();
}

SatButton::SatButton(ButtonType nType, QWidget *parent) : QPushButton(parent){
    mType = nType;
    initWidget();
}



SatButton::SatButton(const QString &nText,QWidget *parent) : QPushButton(parent),mText(nText){
    mText = nText;
    mType = NormalButton;
    initWidget();
}

SatButton::SatButton(const QString &nText,ButtonType nType,QWidget *parent) : QPushButton(parent){
    mText = nText;
    mType = nType;
    initWidget();
}

void SatButton::initWidget(){
    mHighLight = false;
    mPixelSize = 18;
    mFontColor = QColor("#000000");
    mOnState = false;
    mIsSelect = false;
    if(mType == RadioTickButton){
        mArrowPath = QString("%1%2").arg(IMG_DIR).arg(TICK_PNG);
    }else{
        mArrowPath = QString("%1%2").arg(IMG_DIR).arg(ARROW_PNG);
    }
    if(mType == PictureSwitchButton){
        mOnPath = QString("%1%2").arg(IMG_DIR).arg(ON_PNG);
        mOffPath = QString("%1%2").arg(IMG_DIR).arg(OFF_PNG);
    }
    connect(this,SIGNAL(clicked()),this,SLOT(switchOnState()));
}


void SatButton::switchOnState(){
    if(mOnState){
        this->setOnState(false);
    }else{
        this->setOnState(true);
    }
}

void SatButton::setHighLight(bool nHighLight){
    if(mHighLight != nHighLight){
        mHighLight = nHighLight;
        if(mHighLight == true){
            QObjectList nList = this->parentWidget()->children();//获取该对象的父对象的所有子对象
            foreach (QObject *nObj, nList) {//遍历列表
                if(nObj->inherits("HighLight") && nObj != this){//如果该对象继承了高亮，并且非自身
                    HighLight *nHighObj = (HighLight *)((SatButton *)nObj);//不可以直接从QObject转到HighLight
                    if(nHighObj->isHighLight()){
                        nHighObj->setHighLight(false);
                    }
                }
            }
        }
        this->style()->unpolish(this);
        this->style()->polish(this);
    }
}

bool SatButton::isHighLight(){
    return mHighLight;
}

void SatButton::setPixelSize(int nPixelSize){
    if(mPixelSize != nPixelSize){
        mPixelSize = nPixelSize;
        update();
    }
}

int SatButton::getPixelSize(){
    return mPixelSize;
}

void SatButton::setText(const QString &nText){
    if(mText != nText){
        mText = nText;
        update();
    }

}

QString SatButton::getText(){
    return mText;
}

void SatButton::setArrowPath(QString nArrowPath){
    if(mArrowPath != nArrowPath){
        mArrowPath = nArrowPath;
        update();
    }
}

QString SatButton::getArrowPath(){
    return mArrowPath;
}

void SatButton::setFontColor(const QColor &nFontColor){
    if(mFontColor != nFontColor){
        mFontColor = nFontColor;
        update();
    }
}

QColor SatButton::getFontColor(){
    return mFontColor;
}

void SatButton::setOnState(bool nOnState){
    if(mOnState != nOnState){
        mOnState = nOnState;
        update();
    }
}

bool SatButton::isOnState(){
    return mOnState;
}

void SatButton::setOnPath(QString nOnPath){
    if(mOnPath != nOnPath){
        mOnPath = nOnPath;
        update();
    }
}

QString SatButton::getOnPath(){
    return mOnPath;
}

void SatButton::setOffPath(QString nOffPath){
    if(mOffPath != nOffPath){
        mOffPath = nOffPath;
        update();
    }
}

QString SatButton::getOffPath(){
    return mOffPath;
}

void SatButton::setSelect(bool nIsSelect){
    if(mIsSelect != nIsSelect){
        mIsSelect = nIsSelect;
        if(mIsSelect == true){
            QObjectList nList = this->parentWidget()->children();//获取该对象的父对象的所有子对象
            foreach (QObject *nObj, nList) {//遍历列表
                if(nObj->inherits("SatButton") && nObj != this){//如果该对象属于SatButton，并且非自身
                    SatButton *nSatButton = (SatButton *)nObj;//不可以直接从QObject转到HighLight
                    if(nSatButton->getType() == RadioTickButton && nSatButton->getSelect()){
                        nSatButton->setSelect(false);
                    }
                }
            }
        }
        update();
    }

}

bool SatButton::getSelect(){
    return mIsSelect;
}

SatButton::ButtonType SatButton::getType(){
    return mType;
}

void SatButton::focusInEvent(QFocusEvent *event){
    setHighLight(true);
    QPushButton::focusInEvent(event);
}

void SatButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter nPainter(this);
    nPainter.setRenderHint(QPainter::Antialiasing);
    QFont nFont = this->font();
    nFont.setPixelSize(mPixelSize);
    nPainter.setFont(nFont);
    nPainter.setBrush(mFontColor);
    if(mType == NormalButton){//正常按钮，只是多了高亮属性
        QPushButton::setText(mText);
        return;
    }else{
        if(!mText.isEmpty()){
            nPainter.drawText(20,0,width()-height(),height(),Qt::AlignLeft | Qt::AlignVCenter,mText);
        }
    }
    if(mType == ArrowButton){//箭头按钮=文本+箭头图标
        if(!mArrowPath.isEmpty()){
            if(QFile::exists(mArrowPath)){
                QPixmap nPixmap;
                nPixmap.load(mArrowPath);
                int h = 20;
                int w = 20;
                nPixmap = nPixmap.scaled(h,w);
                nPainter.drawPixmap(width()-h-10,(height()-w)/2,w,h,nPixmap);
            }
        }
    }else if(mType == PictureSwitchButton){//图标切换按钮=文本+图标（开/关）
        int w = 60;
        int h = height()-10;
        if(mOnState){//开状态
            if(!mOnPath.isEmpty()){
                if(QFile::exists(mOnPath)){
                    QPixmap nPixmap;
                    nPixmap.load(mOnPath);
                    nPixmap = nPixmap.scaled(h,w);
                    nPainter.drawPixmap(width()-w-10,(height()-h)/2,w,h,nPixmap);
                }
            }
        }else{//关状态
            if(!mOffPath.isEmpty()){
                if(QFile::exists(mOffPath)){
                    QPixmap nPixmap;
                    nPixmap.load(mOffPath);
                    nPixmap = nPixmap.scaled(h,w);
                    nPainter.drawPixmap(width()-w-10,(height()-h)/2,w,h,nPixmap);
                }
            }
        }
    }else if(mType == TextSwitchButton){//文本切换按钮=文本+文本（开/关）
        int w = 50;
        int h = height()-20;
        if(mOnState){//开状态
            if(!mOnPath.isEmpty()){
                nPainter.drawText(width()-w-15,(height()-h)/2,w,h,Qt::AlignRight | Qt::AlignVCenter,mOnPath);
            }
        }else{//关状态
            if(!mOffPath.isEmpty()){
                nPainter.drawText(width()-w-15,(height()-h)/2,w,h,Qt::AlignRight | Qt::AlignVCenter,mOffPath);
            }
        }
    }else if(mType == TextArrowButton){//文本箭头按钮=文本+文本（小字体）+箭头，小文本用onPath里的字符串
        if(!mArrowPath.isEmpty()){
            if(QFile::exists(mArrowPath)){
                QPixmap nPixmap;
                nPixmap.load(mArrowPath);
                int h = 20;
                int w = 20;
                nPixmap = nPixmap.scaled(h,w);
                nPainter.drawPixmap(width()-h-10,(height()-w)/2,w,h,nPixmap);
            }
        }
    }else if(mType == RadioTickButton){//单选按钮=文本+勾，勾路径用mArrowPath的路径
        if(mIsSelect && !mArrowPath.isEmpty()){
            if(QFile::exists(mArrowPath)){
                QPixmap nPixmap;
                nPixmap.load(mArrowPath);
                int h = 20;
                int w = 20;
                nPixmap = nPixmap.scaled(h,w);
                nPainter.drawPixmap(width()-h-10,(height()-w)/2,w,h,nPixmap);
            }
        }
    }
}

void SatButton::wheelEvent(QWheelEvent *event){
    //qDebug("[D]Lin >> SatButton--wheelEvent()");
    QPushButton::wheelEvent(event);
}

void SatButton::mousePressEvent(QMouseEvent *event){
    //qDebug("[D]Lin >> SatButton--mousePressEvent()");
    QPushButton::mousePressEvent(event);
}

void SatButton::mouseMoveEvent(QMouseEvent *event){
    //qDebug("[D]Lin >> SatButton--mouseMoveEvent()");
    QPushButton::mouseMoveEvent(event);
}

void SatButton::mouseReleaseEvent(QMouseEvent *event){
    //qDebug("[D]Lin >> SatButton--mouseReleaseEvent()");
    QPushButton::mouseReleaseEvent(event);
}

void SatButton::keyPressEvent(QKeyEvent *event){
    //qDebug("[D]Lin >> SatButton--keyPressEvent()");
    QPushButton::keyPressEvent(event);
}

void SatButton::keyReleaseEvent(QKeyEvent *event){
    //qDebug("[D]Lin >> SatButton--keyReleaseEvent()");
    QPushButton::keyReleaseEvent(event);
}

bool SatButton::eventFilter(QObject *nObject, QEvent *event){
#if 0
    if(event->type() == QEvent::Wheel){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::Wheel");
    }else if(event->type() == QEvent::MouseButtonPress){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::MouseButtonPress");
    }else if(event->type() == QEvent::MouseMove){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::MouseMove");
    }else if(event->type() == QEvent::MouseButtonRelease){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::MouseButtonRelease");
    }else if(event->type() == QEvent::KeyPress){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::KeyPress");
    }else if(event->type() == QEvent::KeyRelease){
        qDebug("[D]Lin >> SatButton--eventFilter()--QEvent::KeyRelease");
    }
#endif
    return QPushButton::eventFilter(nObject,event);
}

bool SatButton::event(QEvent *event){
#if 0
    if(event->type() == QEvent::Wheel){
        qDebug("[D]Lin >> SatButton--eventF()--QEvent::Wheel");
    }else if(event->type() == QEvent::MouseButtonPress){
        qDebug("[D]Lin >> SatButton--event()--QEvent::MouseButtonPress");
    }else if(event->type() == QEvent::MouseMove){
        qDebug("[D]Lin >> SatButton--event()--QEvent::MouseMove");
    }else if(event->type() == QEvent::MouseButtonRelease){
        qDebug("[D]Lin >> SatButton--event()--QEvent::MouseButtonRelease");
    }else if(event->type() == QEvent::KeyPress){
        qDebug("[D]Lin >> SatButton--event()--QEvent::KeyPress");
    }else if(event->type() == QEvent::KeyRelease){
        qDebug("[D]Lin >> SatButton--event()--QEvent::KeyRelease");
    }
#endif
    return QPushButton::event(event);
}





/*===============================================================================
  @classname     xx
  @describe      xx
  @author        Helin
  @date          2018-06-08
  ===============================================================================*/

SatLineEdit::SatLineEdit(QWidget *parent) : QLineEdit(parent){
    mHighLight = false;
}

void SatLineEdit::setHighLight(bool nHighLight){
    if(mHighLight != nHighLight){
        mHighLight = nHighLight;
        if(mHighLight == true){
            QObjectList nList = this->parentWidget()->children();
            foreach (QObject *nObj, nList) {
                if(nObj->inherits("HighLight") && nObj != this){
                    HighLight *nHighObj = (HighLight *)((SatLineEdit *)nObj);
                    if(nHighObj->isHighLight()){
                        nHighObj->setHighLight(false);
                    }
                }
            }
        }
        this->style()->unpolish(this);
        this->style()->polish(this);
    }
}

bool SatLineEdit::isHighLight(){
    return mHighLight;
}

void SatLineEdit::focusInEvent(QFocusEvent *event){
    setHighLight(true);
    QLineEdit::focusInEvent(event);
}







//
SatTitleBar::SatTitleBar(QWidget *parent) : QWidget(parent){
    initWidget();
}
SatTitleBar::SatTitleBar(QString nTitle, QWidget *parent) : QWidget(parent){
    mTitle = nTitle;
    initWidget();
}

void SatTitleBar::initWidget(){
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    QHBoxLayout *nLayout = new QHBoxLayout;
    mReturnButton = new SatPhotoButton(this);
    //mReturnButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("left_arrow.png"));
    //mReturnButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("left_arrow.png"));

    //mReturnButton->setNormalPhotoStr(QString("%1%2").arg(IMG_DIR).arg("arrowl.png"));
    //mReturnButton->setFocusPhotoStr(QString("%1%2").arg(IMG_DIR).arg("arrowl.png"));

    mReturnButton->setTextShowSign(false);

    //mReturnButton->setStyleSheet("border-image:url(/home/sat/Sat/Root/GF5000/img/arrowl.png)");
    mReturnButton->setIcon(QIcon(QString("%1%2").arg(IMG_DIR).arg("arrowl.png")));

    //mReturnButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //mReturnButton->setStyle(Qt::ToolButtonTextBesideIcon);
    //QStyle* style = QApplication::style();
    //QIcon icon = style->standardIcon(QStyle::SP_ArrowBack);
    //mReturnButton->setIcon(icon);
  //  mReturnButton->setText(QString("123"));

    QString nQssStr = QString("%1DigitKeyboard.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::FramelessWindowHint);

    mReturnButton->setIconSize(QSize(20,20));

    connect(mReturnButton,SIGNAL(clicked()),this,SIGNAL(returnButtonClick()));
    nLayout->addWidget(mReturnButton,0,Qt::AlignCenter);

    mTitleLabel = new QLabel(mTitle,this);
    nLayout->addWidget(mTitleLabel);
    nLayout->setStretchFactor(mTitleLabel,100);
    nLayout->setMargin(0);
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
}

void SatTitleBar::setTitle(QString nTitle){
    mTitle = nTitle;
    mTitleLabel->setText(mTitle);
}

QString SatTitleBar::getTitle(){
    return mTitle;
}











//
SatScrollArea::SatScrollArea(QWidget *parent) : QScrollArea(parent) , mOldPoint(QPoint(0,0)){
    this->installEventFilter(this);
    mIsStartMove = false;
    mIsContinueMove = false;
}

void SatScrollArea::focusInEvent(QFocusEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--focusInEvent()--");
    QScrollArea::focusInEvent(event);
    this->widget()->setFocus();
}

void SatScrollArea::paintEvent(QPaintEvent *event){
    QScrollArea::paintEvent(event);
}

void SatScrollArea::wheelEvent(QWheelEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--wheelEvent()--");
    QScrollArea::wheelEvent(event);
}

void SatScrollArea::mousePressEvent(QMouseEvent *event){
#if 0
    qDebug("[D]Lin >> SatScrollArea--mousePressEvent()--");
    mIsStartMove = true;
    mIsContinueMove = false;
    mOldPoint = event->globalPos();
#endif
    QScrollArea::mousePressEvent(event);
}

void SatScrollArea::mouseMoveEvent(QMouseEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--mouseMoveEvent()--");
    if(event->buttons() & Qt::LeftButton){
        if(mIsStartMove){
            QPoint nNewPoint = event->globalPos();
            int nOffsetX = nNewPoint.x() - mOldPoint.x();
            int nOffsetY = nNewPoint.y() - mOldPoint.y();
            if(!mIsContinueMove && (nOffsetX > -10 && nOffsetX < 10) && (nOffsetY > -10 && nOffsetY < 10)){
                return;
            }
            mIsContinueMove = true;
            QScrollBar *nScrollBarX = this->horizontalScrollBar();
            QScrollBar *nScrollBarY = this->verticalScrollBar();
            nScrollBarX->setValue(nScrollBarX->value() - nOffsetX);
            nScrollBarY->setValue(nScrollBarY->value() - nOffsetY);
            mOldPoint = nNewPoint;
        }else{
            mIsStartMove = true;
            mIsContinueMove = false;
            mOldPoint = event->globalPos();
        }
    }
    QScrollArea::mouseMoveEvent(event);
}

void SatScrollArea::mouseReleaseEvent(QMouseEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--mouseReleaseEvent()--");
    mIsStartMove = false;
    mIsContinueMove = false;
    QScrollArea::mouseReleaseEvent(event);
}

void SatScrollArea::keyPressEvent(QKeyEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--keyPressEvent()--");
    if(!this->widget()->hasFocus()){
        //qDebug("[D]Lin >> SatScrollArea--event()--the widget is not focus.");
        this->widget()->setFocus();
    }
    QScrollArea::keyPressEvent(event);
}

void SatScrollArea::keyReleaseEvent(QKeyEvent *event){
    //qDebug("[D]Lin >> SatScrollArea--keyReleaseEvent()--");
    calcRoll();
    QScrollArea::keyReleaseEvent(event);
}

bool SatScrollArea::eventFilter(QObject *nObject, QEvent *event){
#if 0
    if(event->type() == QEvent::KeyPress){
        if(event->isAccepted()){
            qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::KeyPress--isAccepted==true");
        }
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::KeyPress");
    }else if(event->type() == QEvent::MouseButtonPress){
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::MouseButtonPress");
    }else if(event->type() == QEvent::KeyRelease){
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::KeyRelease");
    }else if(event->type() == QEvent::MouseMove){
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::MouseMove");
    }else if(event->type() == QEvent::MouseButtonRelease){
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::MouseButtonRelease");
    }else if(event->type() == QEvent::Wheel){
        qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::Wheel");
    }
#endif
    if(event->type() == QEvent::FocusIn){
       //qDebug("[D]Lin >> SatScrollArea--eventFilter()--QEvent::FocusIn--");
    }
    return QScrollArea::eventFilter(nObject,event);
}

bool SatScrollArea::event(QEvent *event){
#if 0
    if(event->type() == QEvent::MouseButtonPress){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::MouseButtonPress");
    }else if(event->type() == QEvent::KeyPress){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::KeyPress");
        if(!this->widget()->hasFocus()){
            qDebug("[D]Lin >> SatScrollArea--event()--the widget is not focus.");
            this->widget()->setFocus();
        }else{
            qDebug("[D]Lin >> SatScrollArea--event()--the widget is focus.");
        }
        if(focusWidget()->inherits("SatButton")){
            qDebug("[D]Lin >> SatScrollArea--event()--the focus widget is SatButton");
        }else{
            qDebug("[D]Lin >> SatScrollArea--event()--the focus widget is not SatButton");
        }
        if(focusWidget()->inherits("QPushButton")){
            qDebug("[D]Lin >> SatScrollArea--event()--the focus widget is QPushButton");
        }else{
            qDebug("[D]Lin >> SatScrollArea--event()--the focus widget is not QPushButton");
        }
        int nWidgetX = focusWidget()->pos().x();
        int nWidgetY = focusWidget()->pos().y();
        int nWidgetW = focusWidget()->width();
        int nWidgetH = focusWidget()->height();
//        int nWidgetX = focusWidget()->rect().x();
//        int nWidgetY = focusWidget()->rect().y();
//        int nWidgetW = focusWidget()->rect().width();
//        int nWidgetH = focusWidget()->rect().height();
        qDebug("[D]Lin >> SatScrollArea--event()--the widget[%d,%d,%d,%d]",nWidgetX,nWidgetY,nWidgetW,nWidgetH);
        int nAreaX = this->pos().x();
        int nAreaY = this->pos().y();
        int nAreaW = this->width();
        int nAreaH = this->height();
//        int nAreaX = this->rect().x();
//        int nAreaY = this->rect().y();
//        int nAreaW = this->rect().width();
//        int nAreaH = this->rect().height();
        qDebug("[D]Lin >> SatScrollArea--event()--the Area[%d,%d,%d,%d]",nAreaX,nAreaY,nAreaW,nAreaH);
        int nValue = this->verticalScrollBar()->value();
        qDebug("[D]Lin >> SatScrollArea--event()--the Value[%d]",nValue);
    }else if(event->type() == QEvent::KeyRelease){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::KeyRelease");
        int nWidgetX = focusWidget()->pos().x();
        int nWidgetY = focusWidget()->pos().y();
        int nWidgetW = focusWidget()->width();
        int nWidgetH = focusWidget()->height();
//        int nWidgetX = focusWidget()->rect().x();
//        int nWidgetY = focusWidget()->rect().y();
//        int nWidgetW = focusWidget()->rect().width();
//        int nWidgetH = focusWidget()->rect().height();
        qDebug("[D]Lin >> SatScrollArea--event()--the widget[%d,%d,%d,%d]",nWidgetX,nWidgetY,nWidgetW,nWidgetH);
        int nAreaX = this->pos().x();
        int nAreaY = this->pos().y();
        int nAreaW = this->width();
        int nAreaH = this->height();
//        int nAreaX = this->rect().x();
//        int nAreaY = this->rect().y();
//        int nAreaW = this->rect().width();
//        int nAreaH = this->rect().height();
        qDebug("[D]Lin >> SatScrollArea--event()--the Area[%d,%d,%d,%d]",nAreaX,nAreaY,nAreaW,nAreaH);
        int nValue = this->verticalScrollBar()->value();
        qDebug("[D]Lin >> SatScrollArea--event()--the Value[%d]",nValue);
        calcRoll();
    }else if(event->type() == QEvent::MouseMove){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::MouseMove");
    }else if(event->type() == QEvent::MouseButtonRelease){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::MouseButtonRelease");
    }else if(event->type() == QEvent::Wheel){
        qDebug("[D]Lin >> SatScrollArea--event()--QEvent::Wheel");
    }
#endif
    return QScrollArea::event(event);
}

void SatScrollArea::calcRoll(){
    QWidget *nFocusWidget = this->focusWidget();
    if(nFocusWidget){
        int nScrollBarValue = this->verticalScrollBar()->value();
        int nWidgetY = nFocusWidget->pos().y();
        int nWidgetH = nFocusWidget->height();
        int nAreaY = this->pos().y();
        int nAreaH = this->height();
        int nDeltaValue = 0;
        if(nWidgetY < (nAreaY + nScrollBarValue)){
            nDeltaValue = (nAreaY + nScrollBarValue) - nWidgetY;
        }else if((nWidgetY + nWidgetH) > (nAreaH + nScrollBarValue)){
            nDeltaValue = (nAreaH + nScrollBarValue) - (nWidgetY + nWidgetH);
        }else{
            return;
        }
        this->verticalScrollBar()->setValue(nScrollBarValue - nDeltaValue);
    }
}







//=====

SatPhotoButton::SatPhotoButton(QWidget *parent) : QPushButton(parent){
    mTextShowSign = false;
    mTwoState = false;
}

QString SatPhotoButton::getTextStr(){
    return mTextStr;
}

void SatPhotoButton::setTextStr(QString nTextStr){
    mTextStr = nTextStr;
    update();
}

bool SatPhotoButton::isTextShowSign(){
    return mTextShowSign;
}

void SatPhotoButton::setTextShowSign(bool nTextShowSign){
    mTextShowSign = nTextShowSign;
    update();
}

QString SatPhotoButton::getNormalPhotoStr(){
    return mNormalPhotoStr;
}

void SatPhotoButton::setNormalPhotoStr(QString nNormalPhotoStr){
    mNormalPhotoStr = nNormalPhotoStr;
    update();
}

QString SatPhotoButton::getFocusPhotoStr(){
    return mFocusPhotoStr;
}

void SatPhotoButton::setFocusPhotoStr(QString nFocusPhotoStr){
    mFocusPhotoStr = nFocusPhotoStr;
    update();
}

bool SatPhotoButton::isTwoState(){
    return mTwoState;
}

void SatPhotoButton::setTwoState(bool nTwoState){
    if(mTwoState != nTwoState){
        mTwoState = nTwoState;
        update();
    }
}

QString SatPhotoButton::getTwoNormalPhotoStr(){
    return mTwoNormalPhotoStr;
}

void SatPhotoButton::setTwoNormalPhotoStr(QString nTwoNormalPhotoStr){
    mTwoNormalPhotoStr = nTwoNormalPhotoStr;
    update();
}

QString SatPhotoButton::getTwoFocusPhotoStr(){
    return mTwoFocusPhotoStr;
}

void SatPhotoButton::setTwoFocusPhotoStr(QString nTwoFocusPhotoStr){
    mTwoFocusPhotoStr = nTwoFocusPhotoStr;
    update();
}


void SatPhotoButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter nPainter(this);
    nPainter.setRenderHint(QPainter::Antialiasing);
    QString nPixmapString;
    QPen nPen;
    if(this->hasFocus()){
        if(!mTwoState){
            nPixmapString = mFocusPhotoStr;
        }else{
            nPixmapString = mTwoFocusPhotoStr;
        }
        nPen.setColor(Qt::blue);
    }else{
        if(!mTwoState){
            nPixmapString = mNormalPhotoStr;
        }else{
            nPixmapString = mTwoNormalPhotoStr;
        }
        nPen.setColor(QColor("#888888"));
    }
    if(!nPixmapString.isEmpty() && QFile::exists(nPixmapString)){
        QPixmap nPixmap;
        nPixmap.load(nPixmapString);
        nPixmap = nPixmap.scaled(width(),width());
        nPainter.drawPixmap(0,0,nPixmap);
    }
    if(mTextShowSign && !mTextStr.isEmpty()){
        nPainter.setPen(nPen);
        nPainter.drawText(0,width(),width(),height()-width(),Qt::AlignCenter,mTextStr);
    }
}







SatPhotoHighLightButton::SatPhotoHighLightButton(QWidget *parent) : QPushButton(parent){
    mHighLight = false;
    mTextShowSign = false;
}

void SatPhotoHighLightButton::setHighLight(bool nHighLight){
    if(mHighLight != nHighLight){
        mHighLight = nHighLight;
        if(mHighLight == true){
            QObjectList nList = this->parentWidget()->children();//获取该对象的父对象的所有子对象
            foreach (QObject *nObj, nList) {//遍历列表
                if(nObj->inherits("HighLight") && nObj != this){//如果该对象继承了高亮，并且非自身
                    HighLight *nHighObj = (HighLight *)((SatPhotoHighLightButton *)nObj);//不可以直接从QObject转到HighLight
                    if(nHighObj->isHighLight()){
                        nHighObj->setHighLight(false);
                    }
                }
            }
        }
        update();
    }
}

bool SatPhotoHighLightButton::isHighLight(){
    return mHighLight;
}

void SatPhotoHighLightButton::setTextShowSign(bool nTextShowSign){
    if(mTextShowSign != nTextShowSign){
        mTextShowSign = nTextShowSign;
        update();
    }
}

bool SatPhotoHighLightButton::isTextShowSign(){
    return mTextShowSign;
}

void SatPhotoHighLightButton::setTextString(QString nTextString){
    if(mTextString != nTextString){
        mTextString = nTextString;
        update();
    }
}

QString SatPhotoHighLightButton::getTextString(){
    return mTextString;
}

void SatPhotoHighLightButton::setFocusFilename(QString nFocusFilename){
    if(mFocusFilename != nFocusFilename){
        mFocusFilename = nFocusFilename;
    }
}

QString SatPhotoHighLightButton::getFocusFilename(){
    return mFocusFilename;
}

void SatPhotoHighLightButton::setNormalFilename(QString nNormalFilename){
    if(mNormalFilename != nNormalFilename){
        mNormalFilename = nNormalFilename;
    }
}

QString SatPhotoHighLightButton::getNormalFilename(){
    return mNormalFilename;
}

void SatPhotoHighLightButton::setHighLightFilename(QString nHighLightFilename){
    if(mHighLightFilename != nHighLightFilename){
        mHighLightFilename = nHighLightFilename;
    }
}

QString SatPhotoHighLightButton::getHighLightFilename(){
    return mHighLightFilename;
}

void SatPhotoHighLightButton::focusInEvent(QFocusEvent *event){
    QPushButton::focusInEvent(event);
}

void SatPhotoHighLightButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter nPainter(this);
    nPainter.setRenderHint(QPainter::Antialiasing);
    QString nPixmapString;
    if(this->hasFocus()){
        nPixmapString = mFocusFilename;
    }else if(mHighLight){
        nPixmapString = mHighLightFilename;
    }else{
        nPixmapString = mNormalFilename;
    }
    if(!nPixmapString.isEmpty() && QFile::exists(nPixmapString)){
        QPixmap nPixmap;
        nPixmap.load(nPixmapString);
        nPixmap = nPixmap.scaled(width(),width());
        nPainter.drawPixmap(0,0,nPixmap);
    }
    if(mTextShowSign && !mTextString.isEmpty()){
        nPainter.drawText(0,width(),width(),height()-width(),Qt::AlignCenter,mTextString);
    }
}





