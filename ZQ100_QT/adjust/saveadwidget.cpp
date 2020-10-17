#include "saveadwidget.h"

SaveADWidget::SaveADWidget(QWidget *parent) :
    QWidget(parent)
{   
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    setFixedWidth( 130);
    setFixedHeight( 120);
  //  this->setWindowFlags(Qt::FramelessWindowHint);
  //  Qt::FramelessWindowHint |
    this->setGeometry(0, 0, 130, 120);


    setStyleSheet("color: rgb(255, 255, 255);\
                  background-color: rgb(122, 155, 155)");

    nGridLayout = new QGridLayout(this);

    nTempLabel = new QLabel("Temp:", this);
    nGridLayout->addWidget(nTempLabel, 0 ,0);
    mComboxBox = new QComboBox(this);
    nGridLayout->addWidget(mComboxBox, 0, 1);
    mComboxBox->installEventFilter(this);
    mList.append(mComboxBox);

    if(1) //(mEnum == SatData::GEARONE)
    {
        nStrList.append("0");
        nStrList.append("30");
        nStrList.append("70");
        nStrList.append("90");
        nStrList.append("100");
        nStrList.append("120");
        nStrList.append("140");
        nStrList.append("160");
        nStrList.append("180");
        nStrList.append("200");
        nStrList.append("250");
        nStrList.append("300");
    }else{
        nStrList.append("0");
        nStrList.append("30");
        nStrList.append("60");
        nStrList.append("180");
        nStrList.append("200");
        nStrList.append("250");
        nStrList.append("300");
        nStrList.append("400");
        nStrList.append("500");
        nStrList.append("600");
        nStrList.append("800");
        nStrList.append("1000");
        nStrList.append("1200");
    }
    mMaxIndex = nStrList.size();
    for(int i = 0; i < nStrList.size(); i++){
        mComboxBox->addItem(nStrList.at(i));
    }
    mComboxBox->setCurrentIndex(0);

    nADLable = new QLabel("AD:", this);
    nGridLayout->addWidget(nADLable, 1, 0);
    mAdLable = new QLabel(this);
    mAdLable->setText(QString("%1").arg(100,4,10,QLatin1Char('0')) );
    nGridLayout->addWidget(mAdLable, 1 ,1);

    nSaveButton =new QPushButton("save", this);
    nSaveButton->setText(tr("save"));
    nSaveButton->setStyleSheet("QPushButton:!enabled{background-color: gray;}");
    nSaveButton->setFocusPolicy(Qt::NoFocus);
    nGridLayout->addWidget(nSaveButton, 2, 0);
    nSaveButton->installEventFilter(this);
    mList.append(nSaveButton);
    connect(nSaveButton, SIGNAL(clicked()), this, SLOT(saveSlot()) );

    nCancelButton = new QPushButton("cancel", this);
    nCancelButton->setText(tr("Cancle"));
    nCancelButton->setFocusPolicy(Qt::NoFocus);
    nGridLayout->addWidget(nCancelButton, 2, 1);
    mList.append(nCancelButton);
    nCancelButton->installEventFilter(this);
    connect(nCancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));

//    this->setLayout(nGridLayout);
    mIndex = 0;
    mList.at(mIndex)->setFocus();

}

void SaveADWidget::saveSlot()
{
    qDebug("SaveADWidget::saveSlot()");
}
void SaveADWidget::cancelSlot()
{
    qDebug("SaveADWidget::cancelSlot()");
}

bool SaveADWidget::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress){
        qDebug("bool SaveADWidget::eventFilter(QObject *obj, QEvent *event)");
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        qDebug("nKey->key() =0x%x ",nKey->key());

        switch(nKey->key()){
            case UP:
                qDebug("SaveADWidget eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("SaveADWidget eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case LEFT:
                qDebug("SaveADWidget eventFilter case LEFT");
                if(obj == mComboxBox){
                    int nIndex = mComboxBox->currentIndex();
                     nIndex--;
                     if(nIndex < 0)
                         nIndex = mMaxIndex -1;
                     mComboxBox->setCurrentIndex(nIndex);
                }
                return true;
                break;
            case RIGHT:
                qDebug("SaveADWidget eventFilter case RIGHT");
                if(obj == mComboxBox){
                    int nIndex = mComboxBox->currentIndex();
                     nIndex++;
                     if(nIndex > mMaxIndex)
                         nIndex = 0;
                     mComboxBox->setCurrentIndex(nIndex);
                }
                return true;
                break;
            case ENTER:
                 qDebug("SaveADWidget eventFilter case ENTER");
                 if(obj != mComboxBox){
                     ((QPushButton*)(obj))->click();
                 }
                 return true;
                 break;
            case Qt::Key_Escape:
                this->close();
                return true;
                break;
        }
        return true;//其他按键事件拦截
    }

    return QWidget::eventFilter(obj,event);
}


void SaveADWidget::showEvent(QShowEvent *se)
{
    qDebug("void SaveADWidget::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void SaveADWidget::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SaveADWidget::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

SaveADWidget::~SaveADWidget()
{
}
