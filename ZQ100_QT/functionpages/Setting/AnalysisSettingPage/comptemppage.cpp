#include "comptemppage.h"
#include "basewidget/slidearea.h"
#include "basewidget/linedelegate.h"
#include "basewidget/spinbox.h"
#include "globalparam.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>

/**
 * @name    CompTempPage(QWidget *parent)
 * @details 温度比较界面,实现了界面显示和按键操作的功能
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-11-15
**/
CompTempPage::CompTempPage(QWidget *parent) : QDialog(parent)
{
    initView();
}

/**
 * @name    void initView()
 * @details 初始化界面显示
 * @author  lee
 * @date    2018-11-15
**/
void CompTempPage::initView()
{
    setStyleSheet("background-color: rgb(0, 155, 155);");
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);

    //标题栏
    m_titleBar = new TitleBar(this, GlobalParam::TitleBarStyle::SWITCH_BUTTON);
    m_titleBar->setText("Comp.Temp", "Back");

    //若未启用Analysis Spot/Area等分析功能,则禁止比较温度开关打开
    m_titleBar->setSwitchEnable(GlobalParam::getSpotCount()+GlobalParam::getAreaCount() > 0);

    QLabel *label = new QLabel(this);
    label->setText("Unable to use comparator!\n\rPlease open the analysis function!");
    label->setAlignment(Qt::AlignCenter);
    label->resize(SCREEN_WIDTH, SCREEN_HEIGHT-m_titleBar->height());
    label->move(0, m_titleBar->height());

    m_mainWidget = new QWidget(this);

    QLabel *label1 = new QLabel("Target");
    QLabel *label2 = new QLabel("Base");
    QLabel *label3 = new QLabel("RefTemp");
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    label1->setFixedHeight(30);
    label2->setFixedHeight(30);
    label3->setFixedHeight(30);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->setMargin(0);
    topLayout->addWidget(label1);
    topLayout->addWidget(label2);
    topLayout->addWidget(label3);
    //两个滑动窗口,一个spinbox控件
    SlideArea *slideArea1 = new SlideArea(m_mainWidget);
    SlideArea *slideArea2 = new SlideArea(m_mainWidget);
    SpinBox *spinBox = new SpinBox(0, GlobalParam::Orientation::VERTICAL);

    QStringList list;
    for(int i=1; i<=GlobalParam::getSpotCount();i++)
        list<<QString("Spot %1").arg(i);
    for(int i=1; i<=GlobalParam::getAreaCount();i++)
        list<<QString("Area %1").arg(i);
    slideArea1->addItems(&list);
    list.insert(0, QString("Base"));
    slideArea2->addItems(&list);
    spinBox->setFixedSize(slideArea2->width()-2, slideArea2->height());
    spinBox->setAlignment(Qt::AlignCenter);
    spinBox->setSingleStep(1);
    spinBox->setRange(-1000, 1000);
    spinBox->setDecimals(0);
    spinBox->setSuffix("°C");
    spinBox->setValue(25);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(0);
    bottomLayout->addWidget(slideArea1);
    bottomLayout->addWidget(slideArea2);
    bottomLayout->addWidget(spinBox);

    QVBoxLayout *widgetLayout = new QVBoxLayout(m_mainWidget);
    widgetLayout->setSpacing(0);
    widgetLayout->setMargin(0);
    widgetLayout->addLayout(topLayout);
    widgetLayout->addLayout(bottomLayout);

    m_mainWidget->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT-m_titleBar->height());
    m_mainWidget->move(0, 30);

    if(GlobalParam::getcompSwitchState())
        slideArea1->setFocus();
    else
        m_titleBar->setFocus();

    showView(GlobalParam::getcompSwitchState());

    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)), this, SLOT(on_clicked(GlobalParam::ButtonType,bool)));

    //qDebug()<<qApp->focusWidget();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义按键事件
 * @param   e 按键事件指针
 * @author  lee
 * @date    2018-11-15
**/
void CompTempPage::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        close();//关闭窗口
    else if(e->key() == Qt::Key_Return)
    {
        //获取比较温度开关的状态,以决定是否允许比较温度的界面显示
        showView(!GlobalParam::getcompSwitchState());
    }
    else
        QDialog::keyPressEvent(e);
}

/**
 * @name    void on_clicked(GlobalParam::ButtonType id, bool status)
 * @details 响应标题栏信号的槽函数
 * @param   id  按键类型
 * @param   status  checked状态
 * @author  lee
 * @date    2018-11-15
**/
void CompTempPage::on_clicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
        reject();
    else if(id == GlobalParam::ButtonType::BUTTON_SWITCH)
    {
        if(GlobalParam::getSpotCount() > 0)
            showView(status);
    }
}

/**
 * @name    void showView(bool show)
 * @details 显示主要界面开关
 * @param   show  控制界面的显示
 * @author  lee
 * @date    2018-11-15
**/
void CompTempPage::showView(bool show)
{
    if(!m_titleBar->switchIsEnable())
    {
        m_mainWidget->hide();
        return;
    }
    if(show)
    {
        m_titleBar->setSwitchState(true);
        m_mainWidget->show();
        focusNextChild();
    }
    else
    {
        m_titleBar->setSwitchState(false);
        m_mainWidget->hide();
        focusPreviousChild();
    }
    GlobalParam::setcompSwitchState(show);
}

