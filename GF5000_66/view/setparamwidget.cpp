#include "setparamwidget.h"

SetParamWidget::SetParamWidget(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();//获取数据类
    connect(this,SIGNAL(doUpdateSignal(QString)),this,SLOT(doUpdateSlot(QString)));
    mFid = mSatData->getFid();
    mOldFid = mFid;
    mGsk = mSatData->getGsk();
    mOldGsk = mGsk;
    mInt = mSatData->getInt();
    mOldInt = mInt;
    mGain = mSatData->getGain();
    mOldGain = mGain;
    this->setFixedSize(250,480);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    mSatTitleBar = new SatTitleBar(tr("SetParam"),this);
    QWidget *nWidget = new QWidget(this);
    QGridLayout *nWidgetLayout = new QGridLayout;
    int nItemNum = 0;
    //Fid显示
    QLabel *nFidLabel = new QLabel(tr("Fid:"),nWidget);
    nWidgetLayout->addWidget(nFidLabel,nItemNum,0,Qt::AlignLeft);
    mFidLineEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mFidLineEdit,nItemNum,1,Qt::AlignLeft);
    mFidLineEdit->installEventFilter(this);
    mFidLineEdit->setText(QString("%1").arg(mFid));
    nItemNum++;
    //Gsk显示
    QLabel *nGskLabel = new QLabel(tr("Gsk:"),nWidget);
    nWidgetLayout->addWidget(nGskLabel,nItemNum,0,Qt::AlignLeft);
    mGskLineEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mGskLineEdit,nItemNum,1,Qt::AlignLeft);
    mGskLineEdit->installEventFilter(this);
    mGskLineEdit->setText(QString("%1").arg(mGsk));
    nItemNum++;
    //Gain显示
    QLabel *nGainLabel = new QLabel(tr("Gain:"),nWidget);
    nWidgetLayout->addWidget(nGainLabel,nItemNum,0,Qt::AlignLeft);
    mGainLineEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mGainLineEdit,nItemNum,1,Qt::AlignLeft);
    mGainLineEdit->installEventFilter(this);
    mGainLineEdit->setText(QString("%1").arg(mGain));
    nItemNum++;
    //Int显示
    QLabel *nIntLabel = new QLabel(tr("INT:"),nWidget);
    nWidgetLayout->addWidget(nIntLabel,nItemNum,0,Qt::AlignLeft);
    mIntLineEdit = new QLineEdit(nWidget);
    nWidgetLayout->addWidget(mIntLineEdit,nItemNum,1,Qt::AlignLeft);
    mIntLineEdit->installEventFilter(this);
    mIntLineEdit->setText(QString("%1").arg(mInt));
    nItemNum++;
    //Det显示
    QLabel *nDetLabel = new QLabel(tr("DET:"),nWidget);
    nWidgetLayout->addWidget(nDetLabel,nItemNum,0,Qt::AlignLeft);
    mDetLabel = new QLabel(nWidget);
    nWidgetLayout->addWidget(mDetLabel,nItemNum,1,Qt::AlignLeft);
    mDetLabel->setText(QString("%1").arg(mSatData->getDet(),4,16,QLatin1Char('0')));//16进制显示
    nItemNum++;
    //Sensor显示
    QLabel *nSensorLabel = new QLabel(tr("Sensor:"),nWidget);
    nWidgetLayout->addWidget(nSensorLabel,nItemNum,0,Qt::AlignLeft);
    mSensorLabel = new QLabel(nWidget);
    nWidgetLayout->addWidget(mSensorLabel,nItemNum,1,Qt::AlignLeft);
    mSensorLabel->setText(QString("%1").arg(mSatData->getSensor()));
    nItemNum++;
    //Ad显示
    QLabel *nAdLabel = new QLabel(tr("AD:"),nWidget);
    nWidgetLayout->addWidget(nAdLabel,nItemNum,0,Qt::AlignLeft);
    mAdLabel = new QLabel(nWidget);
    nWidgetLayout->addWidget(mAdLabel,nItemNum,1,Qt::AlignLeft);
    mAdLabel->setText(QString("%1").arg(mSatData->getGlobalAD(),4,16,QLatin1Char('0')));//16进制显示
    nItemNum++;
    //关闭按钮
    mCloseButton = new QPushButton(tr("Close"),nWidget);
    nWidgetLayout->addWidget(mCloseButton,nItemNum,0);
    mCloseButton->installEventFilter(this);
    connect(mCloseButton,SIGNAL(clicked()),this,SLOT(closeSlot()));
    //ok按钮
    mOkButton = new QPushButton(tr("Save"),nWidget);
    nWidgetLayout->addWidget(mOkButton,nItemNum,1);
    mOkButton->installEventFilter(this);
    connect(mOkButton,SIGNAL(clicked()),this,SLOT(okSlot()));
    nItemNum++;
    nWidgetLayout->setRowStretch(nItemNum-1,1);
    nItemNum++;
    nWidgetLayout->setMargin(5);//外边距
    nWidgetLayout->setSpacing(5);//组件边距
    nWidgetLayout->setColumnStretch(1,1);
    nWidgetLayout->setColumnStretch(0,1);
    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);


    this->setLayout(nMainLayout);
    //将有焦点的组件放入列表
    mList.append(mFidLineEdit);
    mList.append(mGskLineEdit);
    mList.append(mGainLineEdit);
    mList.append(mIntLineEdit);
    mList.append(mCloseButton);
    mList.append(mOkButton);
    mIndex = 0;//当前焦点索引
    mList.at(mIndex)->setFocus();
    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

void SetParamWidget::registerField(){
    QList<QString> nList;//注册观察字段
    nList.append("Det");
    nList.append("Sensor");
    nList.append("GlobalAD");
    nList.append("AutoInt");
    nList.append("AutoIntSign");
    mSatData->attach(this,nList);
}

void SetParamWidget::doUpdate(QString nStr){//观察字段发生变化
    emit doUpdateSignal(nStr);
}

void SetParamWidget::doUpdateSlot(QString nUpStr){
    if(nUpStr == "Det"){
        mDetLabel->setText(QString("%1").arg(mSatData->getDet(),4,16,QLatin1Char('0')));
    }else if(nUpStr == "Sensor"){
        mSensorLabel->setText(QString("%1").arg(mSatData->getSensor()));
    }else if(nUpStr == "GlobalAD"){
        mAdLabel->setText(QString("%1").arg(mSatData->getGlobalAD(),4,16,QLatin1Char('0')));
    }else if(nUpStr == "AutoIntSign"){
        if(mSatData->getAutoIntSign()){
            mIntLineEdit->setText(QString("%1").arg(mSatData->getAutoInt()));
            mIntLineEdit->setEnabled(false);
        }else{
            mInt = mSatData->getInt();
            mOldInt = mInt;
            mIntLineEdit->setText(QString("%1").arg(mInt));
            mIntLineEdit->setEnabled(true);
        }
    }else if(nUpStr == "AutoInt"){
        if(mSatData->getAutoIntSign()){
            mIntLineEdit->setText(QString("%1").arg(mSatData->getAutoInt()));
        }else{
            //nothing to do
        }
    }
}

bool SetParamWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        switch (nKey->key()){
            case KEY_19:
                {
                    if(!nKey->isAutoRepeat()){//重复的不处理
                        focusPrevious();
                    }
                    break;
                }
            case KEY_20:
                {
                    if(!nKey->isAutoRepeat()){
                        focusNext();
                    }
                    break;
                }
            case KEY_23:
            case KEY_26:
                {
                    emit operationSignal(Manual_Play,NULL);
                    break;
                }
            case KEY_25://关闭窗口
                closeSlot();
                break;
            case KEY_21://左按键
                {
                    if(obj == mFidLineEdit){
                        mFid--;
                        if(mFid < MIN_FID){
                            mFid = MIN_FID;
                        }
                        mFidLineEdit->setText(QString("%1").arg(mFid));
                    }else if(obj == mGskLineEdit){
                        mGsk--;
                        if(mGsk < MIN_GSK){
                            mGsk = MIN_GSK;
                        }
                        mGskLineEdit->setText(QString("%1").arg(mGsk));
                    }else if(obj == mIntLineEdit){
                        mInt--;
                        if(mInt < MIN_INT){
                            mInt = MIN_INT;
                        }
                        mIntLineEdit->setText(QString("%1").arg(mInt));
                    }else if(obj == mGainLineEdit){
                        mGain--;
                        if(mGain < MIN_GAIN){
                            mGain = MIN_GAIN;
                        }
                        mGainLineEdit->setText(QString("%1").arg(mGain));
                    }else if(obj == mCloseButton || obj == mOkButton){
                        focusPrevious();
                    }
                }
                break;
            case KEY_22://右按键
                {
                    if(obj == mFidLineEdit){
                        mFid++;
                        if(mFid > MAX_FID){
                            mFid = MAX_FID;
                        }
                        mFidLineEdit->setText(QString("%1").arg(mFid));
                    }else if(obj == mGskLineEdit){
                         mGsk++;
                         if(mGsk > MAX_GSK){
                             mGsk = MAX_GSK;
                         }
                         mGskLineEdit->setText(QString("%1").arg(mGsk));
                    }else if(obj == mIntLineEdit){
                        mInt++;
                        if(mInt > MAX_INT){
                            mInt = MAX_INT;
                        }
                        mIntLineEdit->setText(QString("%1").arg(mInt));
                    }else if(obj == mGainLineEdit){
                        mGain++;
                        if(mGain > MAX_GAIN){
                            mGain = MAX_GAIN;
                        }
                        mGainLineEdit->setText(QString("%1").arg(mGain));
                    }else if(obj == mCloseButton || obj == mOkButton){
                        focusNext();
                    }
                }
                break;
            case KEY_18://中间键
                {
                    if(!nKey->isAutoRepeat()){
                        if(obj == mCloseButton){
                            mCloseButton->click();
                        }else if(obj == mOkButton){
                            mOkButton->click();
                        }else{
                            okSlot();
                        }
                    }
                }
                break;
            default:
                break;
           }
          return true;
    }else if(event->type() == QEvent::KeyRelease){//按键释放事件
        switch (((QKeyEvent *)event)->key()){
            case KEY_21:
            case KEY_22://如果左右按键，则设置数据层的参数值，并发射业务操作信号
                {
                    if(obj == mFidLineEdit){
                        emit operationSignal(Set_Fid,QString("Fid=%1").arg(mFid));
                    }else if(obj == mGskLineEdit){
                        mSatData->setGsk(mGsk);
                        emit operationSignal(Set_Gsk,QString("Gsk=%1").arg(mGsk));
                    }else if(obj == mIntLineEdit){
                        emit operationSignal(Set_Int,QString("Int=%1").arg(mInt));
                    }else if(obj == mGainLineEdit){
                        emit operationSignal(Set_Gain,QString("Gain=%1").arg(mGain));
                    }
                }
                break;
            default:
                break;
           }
          return true;
    }
    return QWidget::eventFilter(obj,event);
}

void SetParamWidget::showEvent(QShowEvent *se){//显示事件，主要是重新显示时，调好窗口焦点
    mFid = mSatData->getFid();
    mOldFid = mFid;
    mGsk = mSatData->getGsk();
    mOldGsk = mGsk;
    mInt = mSatData->getInt();
    mOldInt = mInt;
    mGain = mSatData->getGain();
    mOldGain = mGain;
    mFidLineEdit->setText(QString("%1").arg(mFid));
    mGskLineEdit->setText(QString("%1").arg(mGsk));
    mGainLineEdit->setText(QString("%1").arg(mGain));
    if(mSatData->getAutoIntSign()){
        mIntLineEdit->setText(QString("%1").arg(mSatData->getAutoInt()));
    }else{
        mIntLineEdit->setText(QString("%1").arg(mInt));
    }
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SetParamWidget::focusNext(){
    mIndex++;
    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    if(mSatData->getAutoIntSign() && mList.at(mIndex) == mIntLineEdit){
        mIndex++;
        if(mIndex >= mList.size()){
            mIndex = 0;
        }
    }
    mList.at(mIndex)->setFocus();
}

void SetParamWidget::focusPrevious(){
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    if(mSatData->getAutoIntSign() && mList.at(mIndex) == mIntLineEdit){
        mIndex--;
        if(mIndex < 0){
            mIndex = mList.size() - 1;
        }
    }
    mList.at(mIndex)->setFocus();
}

void SetParamWidget::closeSlot(){//close按键槽，如果窗口设置了关闭时销毁，则需要注销观察字段
    if(mOldFid != mSatData->getFid()){
        emit operationSignal(Set_Fid,QString("Fid=%1").arg(mOldFid));
    }
    if(mOldGsk != mSatData->getGsk()){
        emit operationSignal(Set_Gsk,QString("Gsk=%1").arg(mOldGsk));
    }
    if(mOldInt != mSatData->getInt()){
        emit operationSignal(Set_Int,QString("Int=%1").arg(mOldInt));
    }
    if(mOldGain != mSatData->getGain()){
        emit operationSignal(Set_Gain,QString("Gain=%1").arg(mOldGain));
    }
    this->hide();
}

void SetParamWidget::okSlot(){//ok按键槽，需要保存档位参数（到文件），如果窗口是关闭销毁，则需要注销观察字段
    emit operationSignal(Save_Arg,NULL);
    this->hide();
}


void SetParamWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}
