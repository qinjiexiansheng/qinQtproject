#include "softkeyboard.h"

DigitKeyboard::DigitKeyboard(QString &nStr, QWidget *parent) : QDialog(parent){
    mInput = &nStr;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);//设置关闭时销毁
    this->setFixedSize(400,380);//键盘大小

    mSatTitleBar = new SatTitleBar(this);
    QWidget *nWidget = new QWidget(this);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);//信号映射
    QGridLayout *nWidgetLayout = new QGridLayout;
    //输入框
    mLineEdit = new QLineEdit((*mInput),nWidget);
    mLineEdit->installEventFilter(this);
    nWidgetLayout->addWidget(mLineEdit,0,0,1,4);
    //1键
    QPushButton *nOneButton   = new QPushButton(tr("1"),nWidget);
    nOneButton->installEventFilter(this);
    nWidgetLayout->addWidget(nOneButton,1,0);
    nSignalMapper->setMapping(nOneButton,"1");//该键映射为"1"
    connect(nOneButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));//连接
    //2键
    QPushButton *nTwoButton    = new QPushButton(tr("2"),nWidget);
    nTwoButton->installEventFilter(this);
    nWidgetLayout->addWidget(nTwoButton,1,1);
    nSignalMapper->setMapping(nTwoButton,"2");
    connect(nTwoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //3键
    QPushButton *nThreeButton  = new QPushButton(tr("3"),nWidget);
    nThreeButton->installEventFilter(this);
    nWidgetLayout->addWidget(nThreeButton,1,2);
    nSignalMapper->setMapping(nThreeButton,"3");
    connect(nThreeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //4键
    QPushButton *nFourButton   = new QPushButton(tr("4"),nWidget);
    nFourButton->installEventFilter(this);
    nWidgetLayout->addWidget(nFourButton,2,0);
    nSignalMapper->setMapping(nFourButton,"4");
    connect(nFourButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //5键
    QPushButton *nFiveButton   = new QPushButton(tr("5"),nWidget);
    nFiveButton->installEventFilter(this);
    nWidgetLayout->addWidget(nFiveButton,2,1);
    nSignalMapper->setMapping(nFiveButton,"5");
    connect(nFiveButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //6键
    QPushButton *nSixButton    = new QPushButton(tr("6"),nWidget);
    nSixButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSixButton,2,2);
    nSignalMapper->setMapping(nSixButton,"6");
    connect(nSixButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //7键
    QPushButton *nSevenButton  = new QPushButton(tr("7"),nWidget);
    nSevenButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSevenButton,3,0);
    nSignalMapper->setMapping(nSevenButton,"7");
    connect(nSevenButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //8键
    QPushButton *nEightButton  = new QPushButton(tr("8"),nWidget);
    nEightButton->installEventFilter(this);
    nWidgetLayout->addWidget(nEightButton,3,1);
    nSignalMapper->setMapping(nEightButton,"8");
    connect(nEightButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //9键
    QPushButton *nNineButton   = new QPushButton(tr("9"),nWidget);
    nNineButton->installEventFilter(this);
    nWidgetLayout->addWidget(nNineButton,3,2);
    nSignalMapper->setMapping(nNineButton,"9");
    connect(nNineButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //0键
    QPushButton *nZeroButton   = new QPushButton(tr("0"),nWidget);
    nZeroButton->installEventFilter(this);
    nWidgetLayout->addWidget(nZeroButton,4,0);
    nSignalMapper->setMapping(nZeroButton,"0");
    connect(nZeroButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Clear键
    QPushButton *nClearButton  = new QPushButton(tr("Clear"),nWidget);
    nClearButton->installEventFilter(this);
    nWidgetLayout->addWidget(nClearButton,1,3);
    nSignalMapper->setMapping(nClearButton,"Clear");
    connect(nClearButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Back键
    QPushButton *nBackButton   = new QPushButton(tr("Back"),nWidget);
    nBackButton->installEventFilter(this);
    nWidgetLayout->addWidget(nBackButton,2,3);
    nSignalMapper->setMapping(nBackButton,"Back");
    connect(nBackButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //Cancel键
    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),nWidget);
    nCancelButton->installEventFilter(this);
    nWidgetLayout->addWidget(nCancelButton,3,3);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //OK键
    QPushButton *nOkButton     = new QPushButton(tr("OK"),nWidget);
    nOkButton->installEventFilter(this);
    nWidgetLayout->addWidget(nOkButton,4,3);
    nSignalMapper->setMapping(nOkButton,"OK");
    connect(nOkButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //点键
    QPushButton *nSpotButton   = new QPushButton(tr("."),nWidget);
    nSpotButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSpotButton,4,1);
    nSignalMapper->setMapping(nSpotButton,"Spot");
    connect(nSpotButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //-键
    QPushButton *nMinusButton  = new QPushButton(tr("-"),nWidget);
    nMinusButton->installEventFilter(this);
    nWidgetLayout->addWidget(nMinusButton,4,2);
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
    nWidgetLayout->setMargin(10);//设置外边距
    nWidgetLayout->setSpacing(10);//设置内边距
    nWidget->setLayout(nWidgetLayout);

    QString nQssStr = QString("%1DigitKeyboard.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::FramelessWindowHint);

    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    this->setLayout(nMainLayout);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);


    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

bool DigitKeyboard::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch (nKey->key()){
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_21:
                focusLeft();
                break;
            case KEY_22:
                focusRight();
                break;
            case KEY_25:
                this->reject();
                break;
            case KEY_18:
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

void DigitKeyboard::paintEvent(QPaintEvent *event){
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
    QDialog::paintEvent(event);
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

/*============================================================================
 ============================================================================*/
HexadecimalKeyboard::HexadecimalKeyboard(QString &nStr, QWidget *parent) : QDialog(parent){
    mInput = &nStr;
    if((*mInput) == "0" || (*mInput) == "0000"){
        (*mInput) = "";
    }
    //加载样式
    QString nQssStr = QString("%1DigitKeyboard.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);//设置关闭时销毁
    this->setFixedSize(400,380);//键盘大小
    mSatTitleBar = new SatTitleBar(this);
    QWidget *nWidget = new QWidget(this);
    QSignalMapper *nSignalMapper = new QSignalMapper(this);
    QGridLayout *nWidgetLayout = new QGridLayout;
    //输入框
    mLineEdit = new QLineEdit((*mInput),nWidget);
    mLineEdit->installEventFilter(this);
    nWidgetLayout->addWidget(mLineEdit,0,0,1,5);
    //1键
    QPushButton *nOneButton   = new QPushButton(tr("1"),nWidget);
    nOneButton->installEventFilter(this);
    nWidgetLayout->addWidget(nOneButton,1,0);
    nSignalMapper->setMapping(nOneButton,"1");
    connect(nOneButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //2键
    QPushButton *nTwoButton    = new QPushButton(tr("2"),nWidget);
    nTwoButton->installEventFilter(this);
    nWidgetLayout->addWidget(nTwoButton,1,1);
    nSignalMapper->setMapping(nTwoButton,"2");
    connect(nTwoButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //3键
    QPushButton *nThreeButton  = new QPushButton(tr("3"),nWidget);
    nThreeButton->installEventFilter(this);
    nWidgetLayout->addWidget(nThreeButton,1,2);
    nSignalMapper->setMapping(nThreeButton,"3");
    connect(nThreeButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //4键
    QPushButton *nFourButton   = new QPushButton(tr("4"),nWidget);
    nFourButton->installEventFilter(this);
    nWidgetLayout->addWidget(nFourButton,1,3);
    nSignalMapper->setMapping(nFourButton,"4");
    connect(nFourButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //5键
    QPushButton *nFiveButton   = new QPushButton(tr("5"),nWidget);
    nFiveButton->installEventFilter(this);
    nWidgetLayout->addWidget(nFiveButton,1,4);
    nSignalMapper->setMapping(nFiveButton,"5");
    connect(nFiveButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //6键
    QPushButton *nSixButton    = new QPushButton(tr("6"),nWidget);
    nSixButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSixButton,2,0);
    nSignalMapper->setMapping(nSixButton,"6");
    connect(nSixButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //7键
    QPushButton *nSevenButton  = new QPushButton(tr("7"),nWidget);
    nSevenButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSevenButton,2,1);
    nSignalMapper->setMapping(nSevenButton,"7");
    connect(nSevenButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //8键
    QPushButton *nEightButton  = new QPushButton(tr("8"),nWidget);
    nEightButton->installEventFilter(this);
    nWidgetLayout->addWidget(nEightButton,2,2);
    nSignalMapper->setMapping(nEightButton,"8");
    connect(nEightButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //9键
    QPushButton *nNineButton   = new QPushButton(tr("9"),nWidget);
    nNineButton->installEventFilter(this);
    nWidgetLayout->addWidget(nNineButton,2,3);
    nSignalMapper->setMapping(nNineButton,"9");
    connect(nNineButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //0键
    QPushButton *nZeroButton   = new QPushButton(tr("0"),nWidget);
    nZeroButton->installEventFilter(this);
    nWidgetLayout->addWidget(nZeroButton,2,4);
    nSignalMapper->setMapping(nZeroButton,"0");
    connect(nZeroButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //A键
    QPushButton *nAButton   = new QPushButton(tr("a"),nWidget);
    nAButton->installEventFilter(this);
    nWidgetLayout->addWidget(nAButton,3,0);
    nSignalMapper->setMapping(nAButton,"a");
    connect(nAButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //B键
    QPushButton *nBButton   = new QPushButton(tr("b"),nWidget);
    nBButton->installEventFilter(this);
    nWidgetLayout->addWidget(nBButton,3,1);
    nSignalMapper->setMapping(nBButton,"b");
    connect(nBButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //C键
    QPushButton *nCButton   = new QPushButton(tr("c"),nWidget);
    nCButton->installEventFilter(this);
    nWidgetLayout->addWidget(nCButton,3,2);
    nSignalMapper->setMapping(nCButton,"c");
    connect(nCButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //D键
    QPushButton *nDButton   = new QPushButton(tr("d"),nWidget);
    nDButton->installEventFilter(this);
    nWidgetLayout->addWidget(nDButton,3,3);
    nSignalMapper->setMapping(nDButton,"d");
    connect(nDButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //E键
    QPushButton *nEButton   = new QPushButton(tr("e"),nWidget);
    nEButton->installEventFilter(this);
    nWidgetLayout->addWidget(nEButton,3,4);
    nSignalMapper->setMapping(nEButton,"e");
    connect(nEButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //F键
    QPushButton *nFButton   = new QPushButton(tr("f"),nWidget);
    nFButton->installEventFilter(this);
    nWidgetLayout->addWidget(nFButton,4,0);
    nSignalMapper->setMapping(nFButton,"f");
    connect(nFButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //.键
    QPushButton *nSpotButton   = new QPushButton(tr("."),nWidget);
    nSpotButton->installEventFilter(this);
    nWidgetLayout->addWidget(nSpotButton,4,1);
    nSignalMapper->setMapping(nSpotButton,"Spot");
    connect(nSpotButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //-键
    QPushButton *nMinusButton  = new QPushButton(tr("-"),nWidget);
    nMinusButton->installEventFilter(this);
    nWidgetLayout->addWidget(nMinusButton,4,2);
    nSignalMapper->setMapping(nMinusButton,"Minus");
    connect(nMinusButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //clear键
    QPushButton *nClearButton  = new QPushButton(tr("Clear"),nWidget);
    nClearButton->installEventFilter(this);
    nWidgetLayout->addWidget(nClearButton,4,3);
    nSignalMapper->setMapping(nClearButton,"Clear");
    connect(nClearButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //back键
    QPushButton *nBackButton   = new QPushButton(tr("Back"),nWidget);
    nBackButton->installEventFilter(this);
    nWidgetLayout->addWidget(nBackButton,4,4);
    nSignalMapper->setMapping(nBackButton,"Back");
    connect(nBackButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //cancle键
    QPushButton *nCancelButton = new QPushButton(tr("Cancel"),nWidget);
    nCancelButton->installEventFilter(this);
    nWidgetLayout->addWidget(nCancelButton,5,0,1,2);
    nSignalMapper->setMapping(nCancelButton,"Cancel");
    connect(nCancelButton,SIGNAL(clicked()),nSignalMapper,SLOT(map()));
    //ok键
    QPushButton *nOkButton     = new QPushButton(tr("OK"),nWidget);
    nOkButton->installEventFilter(this);
    nWidgetLayout->addWidget(nOkButton,5,2,1,3);
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
    nWidgetLayout->setMargin(5);//设置外边距
    nWidgetLayout->setSpacing(10);//设置内边距
    nWidget->setLayout(nWidgetLayout);
    QVBoxLayout *nMainLayout = new QVBoxLayout;
    nMainLayout->addWidget(mSatTitleBar);
    nMainLayout->addWidget(nWidget);
    nMainLayout->setMargin(1);
    nMainLayout->setSpacing(0);
    this->setLayout(nMainLayout);
    connect(nSignalMapper,SIGNAL(mapped(QString)),this,SLOT(handleContent(QString)));
}

bool HexadecimalKeyboard::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch (nKey->key()){
            case KEY_19:
                focusPrevious();
                break;
            case KEY_20:
                focusNext();
                break;
            case KEY_21:
                focusLeft();
                break;
            case KEY_22:
                focusRight();
                break;
            case KEY_25:
                this->reject();
                break;
            case KEY_18:
                {
                    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->click();
                }
                break;
            default:
                break;
           }
          return true;
    }
    return QDialog::eventFilter(obj,event);
}

void HexadecimalKeyboard::paintEvent(QPaintEvent *event){
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
    QDialog::paintEvent(event);
}


void HexadecimalKeyboard::handleContent(const QString &nStr){
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

void HexadecimalKeyboard::focusNext(){
    mRowIndex++;
    if(mRowIndex >= KEYBOARD_ROWS_HEX){
        mRowIndex = KEYBOARD_ROWS_HEX - 1;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}


void HexadecimalKeyboard::focusPrevious(){
    mRowIndex--;
    if(mRowIndex < 0){
        mRowIndex = 0;
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}

void HexadecimalKeyboard::focusLeft(){
    mColIndex--;
    if(mColIndex <= 0){
        mColIndex = 0;
    }else{//如果这个焦点与右边一个焦点是同一组件，则继续向左移焦点，主要是由于Cancel和OK按键占2、3格
        while(mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex) == mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex+1)){
            mColIndex--;
            if(mColIndex <= 0){
                mColIndex = 0;
                break;
            }
        }
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}

void HexadecimalKeyboard::focusRight(){
    mColIndex++;
    if(mColIndex >= KEYBOARD_COLS_HEX){
        mColIndex = KEYBOARD_COLS_HEX - 1;
    }else{//同上
        while(mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex) == mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex-1)){
            mColIndex++;
            if(mColIndex >= KEYBOARD_COLS_HEX){
                mColIndex = KEYBOARD_COLS_HEX - 1;
                break;
            }
        }
    }
    mList.at(mRowIndex*KEYBOARD_ROWS_HEX + mColIndex)->setFocus();
}









