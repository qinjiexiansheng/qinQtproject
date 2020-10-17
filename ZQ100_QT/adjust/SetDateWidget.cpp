#include "SetDateWidget.h"

SetDateWidget::SetDateWidget(QWidget *parent) :
    QWidget(parent)
{

    this->setFixedSize(180,200);
    this->setGeometry(0, 0, 180, 200);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    QString nStr;
    nGridLayout = new QGridLayout(this);

    nYearLabel  = new QLabel(" Year:", this);
    nMonthLabel = new QLabel("Month:", this);
    nDayLabel   = new QLabel("  Day:", this);

    mYearBox = new QComboBox(this);
    nGridLayout->addWidget(mYearBox, 0, 1);
    mYearBox->installEventFilter(this);
    mList.append(mYearBox);
    for(int i=0; i < YEAR_MAX_COUNT; i++){
       nStr = QString("%1").arg(CURRENT_YEAR + i);
       mYearBox->addItem(nStr);
    }
    mYear = 2018;
    nStr = QString("%1").arg(mYear);
    nIndex = mYearBox->findText(nStr);
    mYearBox->setCurrentIndex(nIndex);

    mMonthBox = new QComboBox(this);
    nGridLayout->addWidget(mMonthBox, 1, 1);
    mMonthBox->installEventFilter(this);
    mList.append(mMonthBox);
    for(int i=1; i <= MONTH_MAX_COUNT; i++){
       nStr = QString("%1").arg( i);
       mMonthBox->addItem(nStr);
    }
    mMonth = 8;
    nStr = QString("%1").arg(mMonth);
    nIndex = mMonthBox->findText(nStr);
    mMonthBox->setCurrentIndex(nIndex);

    mDayBox = new QComboBox(this);
    nGridLayout->addWidget(mDayBox, 2, 1);
    mDayBox->installEventFilter(this);
    mList.append(mDayBox);
    for(int i=1; i <= DAY_MAX_COUNT; i++){
       nStr = QString("%1").arg( i);
       mDayBox->addItem(nStr);
    }
    mDay = 1;
    nStr = QString("%1").arg(mDay);
    nIndex = mDayBox->findText(nStr);
    mDayBox->setCurrentIndex(nIndex);

    nOkButton = new QPushButton(tr("ok"), this);
    nOkButton->setMinimumSize(20, 10);
    nGridLayout->addWidget(nOkButton, 3, 0);
    nOkButton->installEventFilter(this);
    mList.append(nOkButton);
    connect(nOkButton, SIGNAL(clicked()), this, SLOT(closeSlot()) );

    nCancleButton = new QPushButton(tr("canCel"), this);
    nCancleButton->setMinimumSize(20, 10);
    nGridLayout->addWidget(nCancleButton, 3, 1);
    nCancleButton->installEventFilter(this);
    mList.append(nCancleButton);
    connect(nCancleButton, SIGNAL(clicked()), this, SLOT(closeSlot()) );


    mIndex = 0;
    mList.at(mIndex)->setFocus();

    nGridLayout->addWidget(nYearLabel, 0, 0);
    nGridLayout->addWidget(nMonthLabel, 1, 0);
    nGridLayout->addWidget(nDayLabel, 2, 0);
    nGridLayout->setMargin(10);
    nGridLayout->setSpacing(10);
   // nGridLayout->setRowStretch(6,10);
    this->setLayout(nGridLayout);
}

SetDateWidget::~SetDateWidget()
{

}

void SetDateWidget::closeSlot()
{
    qDebug("SetDateWidget::closeSlot");
    this->close();
}


bool SetDateWidget::eventFilter(QObject *watched, QEvent *event)
{
    QString nStr;

    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        switch(nKey->key()){
            case UP:
                qDebug("SetDateWidget eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("SetDateWidget eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case LEFT:
                qDebug("SetDateWidget eventFilter case LEFT");
                if(watched == mYearBox ){
                    nIndex =  mYearBox->currentIndex();
                    nIndex--;
                    if(nIndex < 0){
                        nIndex = YEAR_MAX_COUNT - 1;
                    }
                    mYearBox->setCurrentIndex(nIndex);
                    mYear = mYearBox->currentText().toInt();
                }else if(watched == mMonthBox){
                    qDebug("watched == mMonthBox");
                    nIndex = mMonthBox->currentIndex();
                    nIndex--;
                    if(nIndex < 0){
                        nIndex = MONTH_MAX_COUNT - 1;
                    }
                    mMonthBox->setCurrentIndex(nIndex);
                    mMonth = mMonthBox->currentText().toInt();
                }else if(watched == mDayBox){
                    nIndex =  mDayBox->currentIndex();
                    nIndex--;
                    if(nIndex < 0){
                        nIndex = DAY_MAX_COUNT -1;
                    }
                    mDayBox->setCurrentIndex(nIndex);
                    mDay = mDayBox->currentText().toInt();
                }
                return true;
                break;
            case RIGHT:
                qDebug("SetDateWidget eventFilter case RIGHT");
                if(watched == mYearBox ){
                    nIndex =  mYearBox->currentIndex();
                    nIndex++;
                    if(nIndex >= YEAR_MAX_COUNT){
                        nIndex = 0;
                    }
                    mYearBox->setCurrentIndex(nIndex);
                    mYear = mYearBox->currentText().toInt();
                }else if(watched == mMonthBox){
                    qDebug("watched == mMonthBox");
                    nIndex = mMonthBox->currentIndex();
                    nIndex++;
                    if(nIndex >= MONTH_MAX_COUNT){
                        nIndex = 0;
                    }
                    mMonthBox->setCurrentIndex(nIndex);
                    mMonth = mMonthBox->currentText().toInt();
                }else if(watched == mDayBox){
                    nIndex =  mDayBox->currentIndex();
                    nIndex++;
                    if(nIndex >= DAY_MAX_COUNT){
                        nIndex = 0;
                    }
                    mDayBox->setCurrentIndex(nIndex);
                    mDay = mDayBox->currentText().toInt();
                }
                return true;
                break;
            case ENTER:
                 qDebug("SetDateWidget eventFilter case ENTER");
                 if(watched->inherits("QPushButton")){
                      ((QPushButton*)watched)->click();
                 }
                 return true;
                 break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(watched,event);

}

void SetDateWidget::showEvent(QShowEvent *se)
{
    mList.at(mIndex)->setFocus();
    QWidget::showEvent(se);
}

void SetDateWidget::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SetDateWidget::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}
