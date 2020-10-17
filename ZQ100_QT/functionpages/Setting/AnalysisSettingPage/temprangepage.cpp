#include "temprangepage.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QDebug>
#include <QEvent>
#include "globalparam.h"

/**
 * @name    TempRangePage(QWidget *parent)
 * @details 温度档位的界面,实现设置档位和显示的功能
 * @param   parent  父窗口
 * @author  lee
 * @date    2018-11-15
**/
TempRangePage::TempRangePage(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(200, 180);

    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("color: white; background-color: rgb(0, 155, 155);");


    //创建各个控件
    m_title = new QLabel("Temp. Range");
    m_title->setStyleSheet("background-color: rgb(0, 200, 200)");
    m_title->setFocusPolicy(Qt::NoFocus);
    m_title->setMinimumHeight(30);
    m_title->setMaximumHeight(30);
    m_title->setAlignment(Qt::AlignCenter);

    m_leftBtn = new QPushButton("Cancel");
    m_leftBtn->setObjectName("leftBtn");
    m_leftBtn->setFocusPolicy(Qt::NoFocus);
    m_leftBtn->setStyleSheet("background-color: rgb(0, 200, 200)");
    m_leftBtn->setMinimumHeight(30);
    m_leftBtn->setMaximumHeight(30);

    m_rightBtn = new QPushButton("Ok");
    m_rightBtn->setObjectName("rightBtn");
    m_rightBtn->setFocusPolicy(Qt::NoFocus);
    m_rightBtn->setStyleSheet("background-color: rgb(0, 200, 200)");
    m_rightBtn->setMinimumHeight(30);
    m_rightBtn->setMaximumHeight(30);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(0);
    bottomLayout->addWidget(m_leftBtn);
    bottomLayout->addWidget(m_rightBtn);

    m_levelBtn1 =  new QPushButton("1");
    m_levelBtn1->installEventFilter(this);
    m_levelBtn1->setFocusPolicy(Qt::NoFocus);
    m_levelBtn1->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127);}\
                               QPushButton:checked{background-color: rgb(0, 100, 200);}");
                               m_levelBtn1->setCheckable(true);
            m_levelBtn1->setChecked(true);
    m_levelBtn1->setMinimumHeight(50);
    m_levelBtn1->setMaximumHeight(50);

    m_levelBtn2 =  new QPushButton("2");
    m_levelBtn2->setFocusPolicy(Qt::NoFocus);
    m_levelBtn2->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127);}\
                               QPushButton:checked{background-color: rgb(0, 100, 200);}");
                               m_levelBtn2->setCheckable(true);
            m_levelBtn2->setMinimumHeight(50);
    m_levelBtn2->setMaximumHeight(50);

    m_levelBtnGroup = new QButtonGroup;
    m_levelBtnGroup->addButton(m_levelBtn1);
    m_levelBtnGroup->addButton(m_levelBtn2);

    lowerLimit = GlobalParam::getLowerLimit();
    upperLimit = GlobalParam::getUpperLimit();
    m_curRange = QString("%1 ~ %2").arg(lowerLimit).arg(upperLimit);

    m_curLevelLabel = new QLabel(QString("Current : ")+m_curRange);
    m_curLevelLabel->setAlignment(Qt::AlignCenter);


    QHBoxLayout *levelBtnLayout = new QHBoxLayout;
    levelBtnLayout->setSpacing(0);
    levelBtnLayout->setContentsMargins(20, 10, 20, 5);
    levelBtnLayout->addWidget(m_levelBtn1);
    levelBtnLayout->addWidget(m_levelBtn2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_title);
    mainLayout->addLayout(levelBtnLayout);
    mainLayout->addWidget(m_curLevelLabel);
    mainLayout->addLayout(bottomLayout);

    connect(m_leftBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(m_rightBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(m_levelBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeCurLevelLabel()));
}

TempRangePage::~TempRangePage()
{
}

/**
 * @name    void setCurrentIndex(int id)
 * @details 设置温度档位
 * @param   id  档位等级
 * @author  lee
 * @date    2018-11-15
**/
void TempRangePage::setCurrentIndex(int id)
{
    if(id == 0)
        m_levelBtn1->click();
    else if(id == 1)
        m_levelBtn2->click();
}

/**
 * @name    int getCurrentIndex() const
 * @details 获取温度档位
 * @return   温度档位
 * @author  lee
 * @date    2018-11-15
**/
int TempRangePage::getCurrentIndex() const
{
    if(m_levelBtn1->isChecked())
        return 0;
    else if(m_levelBtn2->isChecked())
        return 1;
    return 0;

}

/**
 * @name    QString getText() const
 * @details 获取温度档位文本
 * @return   温度档位文本
 * @author  lee
 * @date    2018-11-15
**/
QString TempRangePage::getText() const
{
    return m_curRange;
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义按键事件
 * @param   e 按键事件指针
 * @author  lee
 * @date    2018-11-15
**/
void TempRangePage::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        m_leftBtn->click();//关闭窗口
    else if(e->key() == Qt::Key_Return)
        m_rightBtn->click();//保存档位并关闭窗口
    else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
    {
        //切换档位
        m_levelBtn1->setChecked(e->key() == Qt::Key_Left);
        m_levelBtn2->setChecked(e->key() == Qt::Key_Right);
        changeCurLevelLabel();
    }
    else if(e->key() == Qt::Key_Space)
    {
        //屏蔽空格键
    }
    else
        QDialog::keyPressEvent(e);
}

/**
 * @name    void TempRangePage::changeCurLevelLabel()
 * @details 切换温度档位文本的显示
 * @author  lee
 * @date    2018-11-15
**/
void TempRangePage::changeCurLevelLabel()
{
    if(m_levelBtn1->isChecked())
    {
        lowerLimit = -20;
        upperLimit = 150;
    }
    else
    {
        lowerLimit = 140;
        upperLimit = 600;
    }
    //更新温度档位的上下限
    GlobalParam::setLowerLimit(lowerLimit);
    GlobalParam::setUpperLimit(upperLimit);
    GlobalParam::setTempRangeLevel(getCurrentIndex());
    m_curRange = QString("%1 ~ %2").arg(lowerLimit).arg(upperLimit);
    m_curLevelLabel->setText(QString("Current : ")+m_curRange);
}
