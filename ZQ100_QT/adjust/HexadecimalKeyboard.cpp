#include "HexadecimalKeyboard.h"
#include <QSignalMapper>

HexadecimalKeyboard::HexadecimalKeyboard(QString &nStr , QWidget *parent ) :
    QDialog(parent)
{
    mInput = &nStr;
    if((*mInput) == "0" || (*mInput) == "0000"){
        (*mInput) = "";
    }
    setStyleSheet("color: rgb(255, 255, 255);\
                  background-color: rgb(10, 255, 255)");

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);//设置关闭时销毁
    this->setFixedSize(240,200);//键盘大小
    QSignalMapper *nSignalMapper = new QSignalMapper(this);
    QGridLayout *nGridLayout = new QGridLayout;
    //输入框
    mLineEdit = new QLineEdit((*mInput),this);
    mLineEdit->installEventFilter(this);
    nGridLayout->addWidget(mLineEdit,0,0,1,5);
    //1键
    QPushButton *nOneButton   = new QPushButton(tr("1"),this);
    nOneButton->installEventFilter(this);
    nGridLayout->addWidget(nOneButton,1,0);
    nSignalMapper->setMapping(nOneButton,"1");
    connect(nOneButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //2键
    QPushButton *nTwoButton    = new QPushButton(tr("2"),this);
    nTwoButton->installEventFilter(this);
    nGridLayout->addWidget(nTwoButton,1,1);
    nSignalMapper->setMapping(nTwoButton,"2");
    connect(nTwoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //3键
    QPushButton *nThreeButton  = new QPushButton(tr("3"),this);
    nThreeButton->installEventFilter(this);
    nGridLayout->addWidget(nThreeButton,1,2);
    nSignalMapper->setMapping(nThreeButton,"3");
    connect(nThreeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //4键
    QPushButton *nFourButton   = new QPushButton(tr("4"),this);
    nFourButton->installEventFilter(this);
    nGridLayout->addWidget(nFourButton,1,3);
    nSignalMapper->setMapping(nFourButton,"4");
    connect(nFourButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //5键
    QPushButton *nFiveButton   = new QPushButton(tr("5"),this);
    nFiveButton->installEventFilter(this);
    nGridLayout->addWidget(nFiveButton,1,4);
    nSignalMapper->setMapping(nFiveButton,"5");
    connect(nFiveButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //6键
    QPushButton *nSixButton    = new QPushButton(tr("6"),this);
    nSixButton->installEventFilter(this);
    nGridLayout->addWidget(nSixButton,2,0);
    nSignalMapper->setMapping(nSixButton,"6");
    connect(nSixButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //7键
    QPushButton *nSevenButton  = new QPushButton(tr("7"),this);
    nSevenButton->installEventFilter(this);
    nGridLayout->addWidget(nSevenButton,2,1);
    nSignalMapper->setMapping(nSevenButton,"7");
    connect(nSevenButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //8键
    QPushButton *nEightButton  = new QPushButton(tr("8"),this);
    nEightButton->installEventFilter(this);
    nGridLayout->addWidget(nEightButton,2,2);
    nSignalMapper->setMapping(nEightButton,"8");
    connect(nEightButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //9键
    QPushButton *nNineButton   = new QPushButton(tr("9"),this);
    nNineButton->installEventFilter(this);
    nGridLayout->addWidget(nNineButton,2,3);
    nSignalMapper->setMapping(nNineButton,"9");
    connect(nNineButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //0键
    QPushButton *nZeroButton   = new QPushButton(tr("0"),this);
    nZeroButton->installEventFilter(this);
    nGridLayout->addWidget(nZeroButton,2,4);
    nSignalMapper->setMapping(nZeroButton,"0");
    connect(nZeroButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //A键
    QPushButton *nAButton   = new QPushButton(tr("a"),this);
    nAButton->installEventFilter(this);
    nGridLayout->addWidget(nAButton,3,0);
    nSignalMapper->setMapping(nAButton,"a");
    connect(nAButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //B键
    QPushButton *nBButton   = new QPushButton(tr("b"),this);
    nBButton->installEventFilter(this);
    nGridLayout->addWidget(nBButton,3,1);
    nSignalMapper->setMapping(nBButton,"b");
    connect(nBButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //C键
    QPushButton *nCButton   = new QPushButton(tr("c"),this);
    nCButton->installEventFilter(this);
    nGridLayout->addWidget(nCButton,3,2);
    nSignalMapper->setMapping(nCButton,"c");
    connect(nCButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //D键
    QPushButton *nDButton   = new QPushButton(tr("d"),this);
    nDButton->installEventFilter(this);
    nGridLayout->addWidget(nDButton,3,3);
    nSignalMapper->setMapping(nDButton,"d");
    connect(nDButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //E键
    QPushButton *nEButton   = new QPushButton(tr("e"),this);
    nEButton->installEventFilter(this);
    nGridLayout->addWidget(nEButton,3,4);
    nSignalMapper->setMapping(nEButton,"e");
    connect(nEButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //F键
    QPushButton *nFButton   = new QPushButton(tr("f"),this);
    nFButton->installEventFilter(this);
    nGridLayout->addWidget(nFButton,4,0);
    nSignalMapper->setMapping(nFButton,"f");
    connect(nFButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //.键
    QPushButton *nSpotButton   = new QPushButton(tr("."),this);
    nSpotButton->installEventFilter(this);
    nGridLayout->addWidget(nSpotButton,4,1);
    nSignalMapper->setMapping(nSpotButton,"Spot");
    connect(nSpotButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //-键
    QPushButton *nMinusButton  = new QPushButton(tr("-"),this);
    nMinusButton->installEventFilter(this);
    nGridLayout->addWidget(nMinusButton,4,2);
    nSignalMapper->setMapping(nMinusButton,"Minus");
    connect(nMinusButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //clear键
    QPushButton *nClearButton  = new QPushButton(tr("Clear"),this);
    nClearButton->installEventFilter(this);
    nGridLayout->addWidget(nClearButton,4,3);
    nSignalMapper->setMapping(nClearButton,"Clear");
    connect(nClearButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //back键
    QPushButton *nBackButton   = new QPushButton(tr("Back"),this);
    nBackButton->installEventFilter(this);
    nGridLayout->addWidget(nBackButton,4,4);
    nSignalMapper->setMapping(nBackButton,"Back");
    connect(nBackButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //cancle键
    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),this);
    nCancelButton->installEventFilter(this);
    nGridLayout->addWidget(nCancelButton,5,0,1,2);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //ok键
    QPushButton *nOkButton     = new QPushButton(tr("OK"),this);
    nOkButton->installEventFilter(this);
    nGridLayout->addWidget(nOkButton,5,2,1,3);
    nSignalMapper->setMapping(nOkButton,"OK");
    connect(nOkButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //组件加入焦点列表
    mList.append(nOneButton);
    mList.append(nTwoButton);
    mList.append(nThreeButton);
    mList.append(nFourButton);
    mList.append(nFiveButton);
    mList.append(nSixButton);
    mList.append(nSevenButton);
    mList.append(nEightButton);
    mList.append(nNineButton);
    mList.append(nZeroButton);
    mList.append(nAButton);
    mList.append(nBButton);
    mList.append(nCButton);
    mList.append(nDButton);
    mList.append(nEButton);
    mList.append(nFButton);
    mList.append(nSpotButton);
    mList.append(nMinusButton);
    mList.append(nClearButton);
    mList.append(nBackButton);
    mList.append(nCancelButton);
    mList.append(nCancelButton);
    mList.append(nOkButton);
    mList.append(nOkButton);
    mList.append(nOkButton);
    mRowIndex = 0;
    mColIndex = 0;
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
    nGridLayout->setMargin(5);//设置外边距
    nGridLayout->setSpacing(10);//设置内边距
    this->setLayout(nGridLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));

}

bool HexadecimalKeyboard::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        qDebug("bool HexadecimalKeyboard::eventFilter(QObject *obj, QEvent *event)");
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }

        switch(nKey->key()){
            case UP:
                qDebug("HexadecimalKeyboard eventFilter case UP");
                focusPrevious();
                return true;
                break;
            case DOWN:
                qDebug("HexadecimalKeyboard eventFilter case DOWN");
                focusNext();
                return true;
                break;
            case LEFT:
                 qDebug("HexadecimalKeyboard eventFilter case LEFT");
                 focusLeft();
                 return true;
                 break;
            case RIGHT:
                 qDebug("HexadecimalKeyboard eventFilter case RIGHT");
                 focusRight();
                 return true;
                 break;
            case ENTER:
                 qDebug("HexadecimalKeyboard eventFilter case RIGHT");
                 mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->click();
                 return true;
                 break;
            case Qt::Key_Escape:
                qDebug("HexadecimalKeyboard eventFilter case Qt::Key_Escape");
                this->reject();
                return true;
                break;
        }
        //这里不能返回真，因为上层需要左右按键事件来切换标签页
    }
    return QWidget::eventFilter(obj,event);
}

void HexadecimalKeyboard::handleContent(const QString &nStr)
{
    if(nStr == "0"){
        if((*mInput) != "0" && (*mInput) != "-0"){
            (*mInput).append('0');
        }
    }else if(nStr == "Minus"){
        if((*mInput).isEmpty() || (*mInput) == "0"){
            (*mInput) = "-";
        }
    }else if(nStr == "Spot"){
        if(!(*mInput).isEmpty() && (*mInput) != "-" && (*mInput).indexOf('.') == -1 ){
            (*mInput).append('.');
        }
    }else if(nStr == "Cancel"){
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

void HexadecimalKeyboard::focusPrevious()
{
    mRowIndex--;
    if(mRowIndex < 0){
         mRowIndex = KEYBOARD_COLS_HEX - 1;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}

void HexadecimalKeyboard::focusNext()
{
    mRowIndex++;
    if(mRowIndex >= KEYBOARD_COLS_HEX){
         mRowIndex = 0;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}

void HexadecimalKeyboard::focusLeft()
{
    mColIndex--;
    if(mColIndex < 0){
         mColIndex = KEYBOARD_COLS_HEX - 1;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}

void HexadecimalKeyboard::focusRight()
{
    mColIndex++;
    if(mColIndex >= KEYBOARD_COLS_HEX){
         mColIndex = 0;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}
