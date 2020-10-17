#include "keyboard.h"

#define KEYBOARD_SIZE   QSize(200, 200)
#define BTN_WIDTH   width()/4
#define BTN_HEIGHT   height()/4
#define BTN_SIZE    QSize(BTN_WIDTH, BTN_HEIGHT)

/**
 * @name    KeyBoard(QWidget *parent)
 * @details 简易键盘，目前只有数字按键
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-12-21
**/
KeyBoard::KeyBoard(QWidget *parent) :
    QDialog(parent)
{
    initView();
}

/**
 * @name    KeyBoard(QLineEdit *target, QWidget *parent)
 * @details 简易键盘，目前只有数字按键
 * @param   target 键盘所服务的输入框指针
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-12-21
**/
KeyBoard::KeyBoard(QLineEdit *target, QWidget *parent)
{
    setTarget(target);
    initView();
}

KeyBoard::~KeyBoard()
{

}

/**
 * @name    void initView()
 * @details 初始化键盘显示和功能
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::initView()
{
    QString btnQss = "QPushButton{text-align: center}";

    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setStyleSheet(btnQss);
    //    ui->setupUi(this);

    setFixedSize(KEYBOARD_SIZE);

    m_previewLabel = new QLineEdit;
    m_previewLabel->setFocusPolicy(Qt::NoFocus);
    m_previewLabel->setStyleSheet("background-color: rgb(255, 255, 255)");
    m_previewLabel->setFixedSize(width(), 30);

    QButtonGroup *numBtnGroup = new QButtonGroup(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_previewLabel, 0, 0, 1, 4);

    int num = 1;
    for(int i = 1; i<4; i++)
    {
        for(int j=0; j<3; j++)
        {
            QPushButton *btn = new QPushButton(QString::number(num++));
            btn->setFixedSize(BTN_SIZE);
            numBtnGroup->addButton(btn, btn->text().toInt());
            mainLayout->addWidget(btn, i, j);
        }
    }
    QPushButton *zeroBtn = new QPushButton("0");
    zeroBtn->setFixedHeight(BTN_HEIGHT);
    numBtnGroup->addButton(zeroBtn, zeroBtn->text().toInt());
    QPushButton *dotBtn = new QPushButton(".");
    dotBtn->setFixedSize(BTN_SIZE);
    numBtnGroup->addButton(dotBtn, 10);
    QPushButton *deleteBtn = new QPushButton("←");
    deleteBtn->setFixedSize(BTN_SIZE);
    numBtnGroup->addButton(deleteBtn, 11);
    QPushButton *clearBtn = new QPushButton("C");
    clearBtn->setFixedSize(BTN_SIZE);
    numBtnGroup->addButton(clearBtn, 12);
    QPushButton *closeBtn = new QPushButton("Exit");
    closeBtn->setFixedSize(BTN_WIDTH, BTN_HEIGHT*2);
    numBtnGroup->addButton(closeBtn, 14);

    mainLayout->addWidget(zeroBtn, 5, 0, 1, 2);
    mainLayout->addWidget(dotBtn, 5, 2);
    mainLayout->addWidget(deleteBtn, 1, 3);
    mainLayout->addWidget(clearBtn, 2, 3);
    mainLayout->addWidget(closeBtn, 3, 3);

    connect(dotBtn, SIGNAL(clicked(bool)), this, SLOT(addDot()));
    connect(deleteBtn, SIGNAL(clicked(bool)), this, SLOT(deleteInput()));
    connect(clearBtn, SIGNAL(clicked(bool)), this, SLOT(clearInput()));
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(exitConfirmWnd()));
    connect(numBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(updateText(int)));
}

/**
 * @name    void setTarget(QLineEdit *target)
 * @details 设置键盘所服务的输入框指针、
 * @param   target  键盘所服务的输入框指针
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::setTarget(QLineEdit *target)
{
    m_target = target;
    m_previewLabel->clear();
    if(m_target->echoMode() != QLineEdit::Password)
    {
//        m_previewLabel->setText(m_target->text());
        m_previewLabel->setPlaceholderText("WIFI NAME");
    }
    else
    {
        m_previewLabel->setPlaceholderText("WIFI PASSWD");
    }
}

/**
 * @name    void addDot()
 * @details 响应点按键的槽，在输入框内添加点
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::addDot()
{
    QString str = m_previewLabel->text();
    str += QString(".");
    m_previewLabel->setText(str);
}

/**
 * @name    void deleteInput()
 * @details 响应删除按键的槽，回退输入框的内容
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::deleteInput()
{
    QString str = m_previewLabel->text();
    str = str.left(str.length()-1);
    m_previewLabel->setText(str);
}

/**
 * @name    void clearInput()
 * @details 响应清楚按键的槽，清楚输入框内容
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::clearInput()
{
    m_previewLabel->clear();
}

/**
 * @name    void updateText(int val)
 * @details 响应数字按键的槽，添加输入框的内容
 * @param   val 添加的数字
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::updateText(int val)
{
    if(val > 9)
        return;
    QString str = m_previewLabel->text();
    str += QString::number(val);
    m_previewLabel->setText(str);
}

/**
 * @name    void KeyBoard::exitConfirmWnd()
 * @details 响应退出按键的槽，退出前做确认操作和输入文本的限制
 * @author  lee
 * @date    2018-12-21
**/
void KeyBoard::exitConfirmWnd()
{
    int length = m_previewLabel->text().length();
    if(length > 0 &&
       (QMessageBox::Ok == QMessageBox::information(this, "Exit Confirm", "Apply the input text ?",
        QMessageBox::Ok, QMessageBox::Cancel)))
    {
        if(m_target->echoMode() != QLineEdit::Password)
        {
            if(length < 1 && length > 32)
            {
                QMessageBox::warning(this, "Input Error", "Wifi name length error![1-32]");
                return;
            }
        }
        else
        {
            if(m_previewLabel->text().length() < 8)
            {
                QMessageBox::warning(this, "Input Error", "Wifi passwd length error![8-32]");
                return;
            }

        }
        m_target->setText(m_previewLabel->text());
    }
    hide();
}
