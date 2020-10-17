#include "DigitKeyboard.h"
#include <QGridLayout>
#include <QSignalMapper>

DigitKeyboard::DigitKeyboard(QString &nStr, QWidget *parent) : QDialog(parent){
    mInput = &nStr;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);//设置关闭时销毁
    this->setFixedSize(240,200);//键盘大小
    this->setGeometry(0, 0, 240, 200);

    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QGridLayout *nQGridLayout = new QGridLayout;
    //输入框
    mLineEdit = new QLineEdit((*mInput),this);
    mLineEdit->installEventFilter(this);
    nQGridLayout->addWidget(mLineEdit,0,0,1,4);
    //1键
    QPushButton *nOneButton   = new QPushButton(tr("1"),this);
    nOneButton->installEventFilter(this);
    nQGridLayout->addWidget(nOneButton,1,0);
    nSignalMapper->setMapping(nOneButton,"1");//该键映射为"1"
    connect(nOneButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));//连接
    //2键
    QPushButton *nTwoButton    = new QPushButton(tr("2"),this);
    nTwoButton->installEventFilter(this);
    nQGridLayout->addWidget(nTwoButton,1,1);
    nSignalMapper->setMapping(nTwoButton,"2");
    connect(nTwoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //3键
    QPushButton *nThreeButton  = new QPushButton(tr("3"),this);
    nThreeButton->installEventFilter(this);
    nQGridLayout->addWidget(nThreeButton,1,2);
    nSignalMapper->setMapping(nThreeButton,"3");
    connect(nThreeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //4键
    QPushButton *nFourButton   = new QPushButton(tr("4"),this);
    nFourButton->installEventFilter(this);
    nQGridLayout->addWidget(nFourButton,2,0);
    nSignalMapper->setMapping(nFourButton,"4");
    connect(nFourButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //5键
    QPushButton *nFiveButton   = new QPushButton(tr("5"),this);
    nFiveButton->installEventFilter(this);
    nQGridLayout->addWidget(nFiveButton,2,1);
    nSignalMapper->setMapping(nFiveButton,"5");
    connect(nFiveButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //6键
    QPushButton *nSixButton    = new QPushButton(tr("6"),this);
    nSixButton->installEventFilter(this);
    nQGridLayout->addWidget(nSixButton,2,2);
    nSignalMapper->setMapping(nSixButton,"6");
    connect(nSixButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //7键
    QPushButton *nSevenButton  = new QPushButton(tr("7"),this);
    nSevenButton->installEventFilter(this);
    nQGridLayout->addWidget(nSevenButton,3,0);
    nSignalMapper->setMapping(nSevenButton,"7");
    connect(nSevenButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //8键
    QPushButton *nEightButton  = new QPushButton(tr("8"),this);
    nEightButton->installEventFilter(this);
    nQGridLayout->addWidget(nEightButton,3,1);
    nSignalMapper->setMapping(nEightButton,"8");
    connect(nEightButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //9键
    QPushButton *nNineButton   = new QPushButton(tr("9"),this);
    nNineButton->installEventFilter(this);
    nQGridLayout->addWidget(nNineButton,3,2);
    nSignalMapper->setMapping(nNineButton,"9");
    connect(nNineButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //0键
    QPushButton *nZeroButton   = new QPushButton(tr("0"),this);
    nZeroButton->installEventFilter(this);
    nQGridLayout->addWidget(nZeroButton,4,0);
    nSignalMapper->setMapping(nZeroButton,"0");
    connect(nZeroButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Clear键
    QPushButton *nClearButton  = new QPushButton(tr("Clear"),this);
    nClearButton->installEventFilter(this);
    nQGridLayout->addWidget(nClearButton,1,3);
    nSignalMapper->setMapping(nClearButton,"Clear");
    connect(nClearButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Back键
    QPushButton *nBackButton   = new QPushButton(tr("Back"),this);
    nBackButton->installEventFilter(this);
    nQGridLayout->addWidget(nBackButton,2,3);
    nSignalMapper->setMapping(nBackButton,"Back");
    connect(nBackButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Cancel键
    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),this);
    nCancelButton->installEventFilter(this);
    nQGridLayout->addWidget(nCancelButton,3,3);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //OK键
    QPushButton *nOkButton     = new QPushButton(tr("OK"),this);
    nOkButton->installEventFilter(this);
    nQGridLayout->addWidget(nOkButton,4,3);
    nSignalMapper->setMapping(nOkButton,"OK");
    connect(nOkButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //点键
    QPushButton *nSpotButton   = new QPushButton(tr("."),this);
    nSpotButton->installEventFilter(this);
    nQGridLayout->addWidget(nSpotButton,4,1);
    nSignalMapper->setMapping(nSpotButton,"Spot");
    connect(nSpotButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //-键
    QPushButton *nMinusButton  = new QPushButton(tr("-"),this);
    nMinusButton->installEventFilter(this);
    nQGridLayout->addWidget(nMinusButton,4,2);
    nSignalMapper->setMapping(nMinusButton,"Minus");
    connect(nMinusButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //将组件加入焦点列表
    mList.append(nOneButton);
    mList.append(nTwoButton);
    mList.append(nThreeButton);
    mList.append(nClearButton);
    mList.append(nFourButton);
    mList.append(nFiveButton);
    mList.append(nSixButton);
    mList.append(nBackButton);
    mList.append(nSevenButton);
    mList.append(nEightButton);
    mList.append(nNineButton);
    mList.append(nCancelButton);
    mList.append(nZeroButton);
    mList.append(nSpotButton);
    mList.append(nMinusButton);
    mList.append(nOkButton);
    mRowIndex = 0;
    mColIndex = 0;
    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->setFocus();
    nQGridLayout->setMargin(10);//设置外边距
    nQGridLayout->setSpacing(10);//设置内边距
    this->setLayout(nQGridLayout);

    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

bool DigitKeyboard::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch (nKey->key()){
            case UP:
                focusPrevious();
                break;
            case DOWN:
                focusNext();
                break;
            case LEFT:
                focusLeft();
                break;
            case RIGHT:
                focusRight();
                break;
            case Qt::Key_Escape:
                this->reject();
                break;
            case ENTER:
                {
                    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->click();
                }
                break;
            default:
                break;
           }
          return true;
    }
    return QDialog::eventFilter(obj,event);
}

void DigitKeyboard::handleContent(const QString &nStr){
    if(nStr == "0"){//0键被按下
        if((*mInput) != "0" && (*mInput) != "-0"){//非0 且 非-0
            (*mInput).append('0');
        }
    }else if(nStr == "Minus"){//负号键被按下
        if((*mInput).isEmpty() || (*mInput) == "0"){
            (*mInput) = "-";
        }
    }else if(nStr == "Spot"){
        if(!(*mInput).isEmpty() && (*mInput) != "-" && (*mInput).indexOf('.') == -1 ){
            (*mInput).append('.');
        }
    }else if(nStr == "Cancel"){//关闭对话框
        this->reject();
    }else if(nStr == "OK"){
        this->accept();
    }else if(nStr == "Back"){
        (*mInput) = (*mInput).left((*mInput).length()-1);
    }else if(nStr == "Clear"){
        (*mInput).clear();
    }else{
        (*mInput).append(nStr);
    }
    mLineEdit->setText(*mInput);
}

void DigitKeyboard::focusNext(){
    mRowIndex++;
    if(mRowIndex >= KEYBOARD_ROWS_DIG){
        mRowIndex = KEYBOARD_ROWS_DIG - 1;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->setFocus();
}

void DigitKeyboard::focusPrevious(){
    mRowIndex--;
    if(mRowIndex < 0){
        mRowIndex = 0;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->setFocus();
}

void DigitKeyboard::focusLeft(){
    mColIndex--;
    if(mColIndex < 0){
        mColIndex = 0;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->setFocus();
}

void DigitKeyboard::focusRight(){
    mColIndex++;
    if(mColIndex >= KEYBOARD_COLS_DIG){
        mColIndex = KEYBOARD_COLS_DIG - 1;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_DIG + mColIndex)->setFocus();
}
