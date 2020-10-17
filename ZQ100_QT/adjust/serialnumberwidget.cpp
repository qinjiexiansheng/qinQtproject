#include "serialnumberwidget.h"
#include "DigitKeyboard.h"

SerialNumberWidget::SerialNumberWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(200,100);//窗口大小
    this->setGeometry(0, 0, 200, 100);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);


    nGridLayout = new QGridLayout;

    serialNumberLabel = new QLabel("serialNumber:",this);

    serialLineEdit = new QLineEdit(this);
    serialLineEdit->setText("123456");
    serialLineEdit->installEventFilter(this);
    mList.append(serialLineEdit);

    serialButton = new QPushButton("buttonOk", this);
    serialButton->installEventFilter(this);
    mList.append(serialButton);

    nGridLayout->addWidget(serialNumberLabel, 0, 0);
    nGridLayout->addWidget(serialLineEdit, 0, 1);
    nGridLayout->addWidget(serialButton, 1, 0, 1, 2);
    nGridLayout->setMargin(10);
    nGridLayout->setSpacing(10);
    nGridLayout->setRowStretch(1,10);
    this->setLayout(nGridLayout);

    mIndex =1;
    mList.at(mIndex)->setFocus();

    connect(serialButton, SIGNAL(clicked()), this, SLOT(buttonClose()) );
}

SerialNumberWidget::~SerialNumberWidget()
{

}

bool SerialNumberWidget::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::KeyPress){
        qDebug("bool SerialNumberWidget::eventFilter(QObject *obj, QEvent *event)");

        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        qDebug("nKey->key() =0x%x ",nKey->key());

        switch(nKey->key()){
            case UP:
                qDebug("SerialNumberWidget eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("SerialNumberWidget eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case ENTER:
                 qDebug("SerialNumberWidget eventFilter case ENTER");
                 if( obj==serialLineEdit ){
                     QString nStr = QString("%1").arg(mSerialNumber);//获取当前项的数据
                     DigitKeyboard *nDialog= new DigitKeyboard(nStr);
                     if(nDialog->exec()){
                         if(nStr.isEmpty()){
                             nStr = "0";
                         }
                       }
                        // mSerialNumber = nStr.toInt();
                        // serialLineEdit->setText(QString("%1").arg(mSerialNumber));
                     serialLineEdit->setText(nStr);
                 }else{
                     ((QPushButton*)obj)->click();//产生点击事件
                 }
                 return true;
                 break;
            case Qt::Key_Escape:
                qDebug("SerialNumberWidget eventFilter case Qt::Key_Escape");
                this->close();
                return true;
                break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }

    return QWidget::eventFilter(obj,event);
}
void SerialNumberWidget::showEvent(QShowEvent *se)
{
    qDebug("void SerialNumberWidget::showEvent(QShowEvent *se)");
    QWidget::showEvent(se);
    mList.at(mIndex)->setFocus();
}

void SerialNumberWidget::focusNext()
{
    mIndex++;

    if(mIndex >= mList.size()){
        mIndex = 0;
    }
    mList.at(mIndex)->setFocus();
}

void SerialNumberWidget::focusPrevious()
{
    mIndex--;
    if(mIndex < 0){
        mIndex = mList.size() - 1;
    }
    mList.at(mIndex)->setFocus();
}

void SerialNumberWidget::buttonClose()
{
    this->close();
}
