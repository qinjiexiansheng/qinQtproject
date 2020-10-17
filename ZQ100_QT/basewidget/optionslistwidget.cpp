#include "optionslistwidget.h"
#include "linedelegate.h"
#include "titlebar.h"

/**
 * @name    OptionsListWidget(QWidget *parent, QString title, int rowCount)
 * @details 构造函数
 *          定义了一个通用的选项列表界面,用于AnalysisSettingPage等界面的设计
 * @param   parent  父窗口指针
 * @param   title   标题栏文本
 * @param   rowCount    选项数目

 * @date    2018-11-15
**/
OptionsListWidget::OptionsListWidget(QWidget *parent, QString title, int rowCount) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);

    m_titleBar = new TitleBar(this, GlobalParam::TitleBarStyle::SINGLE_BUTTON, 40, parent->width());
    m_titleBar->setText(title, "Back");
    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)), this,SLOT(on_titleBarClicked(GlobalParam::ButtonType,bool)));

    m_tableWidget = new QTableWidget(rowCount, 2, this);
    //隐藏网格
    m_tableWidget->setShowGrid(false);
    //只显示横线的样式
//    m_tableWidget->setStyleSheet(
//    "QTableWidget::Item{border:0px solid rgb(255,0,0);"
//    "border-bottom:1px solid rgb(0,0,0);"
//    "outline: none;}"
//    );
    //安装代理,取消单元格焦点切换的显示效果
    m_tableWidget->setItemDelegate(new LineDelegate(m_tableWidget));
    m_tableWidget->resize(parent->width(), parent->height()-m_titleBar->height());
    m_tableWidget->move(0, m_titleBar->height());
    //设置行和列的宽度
//    m_tableWidget->verticalHeader()->setDefaultSectionSize((parent->height()-m_titleBar->height())/(double)rowCount);
    m_tableWidget->verticalHeader()->setDefaultSectionSize(33);
    m_tableWidget->horizontalHeader()->setDefaultSectionSize((parent->width()-1)/2.0);
    //隐藏表头
    m_tableWidget->horizontalHeader()->hide();
    m_tableWidget->verticalHeader()->hide();
    //设置选择模式
    m_tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //滚动条的相关设置
    m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //不可编辑
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //默认选中第一行
    m_tableWidget->selectRow(0);
    m_tableWidget->setFocus();

    connect(m_tableWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(optionsClicked(QModelIndex)));
}

/**
 * @name    void setOption(int row, QString optionText)
 * @details 添加选项
 * @param   row 行数
 * @param   optionText  选项名

 * @date    2018-11-15
**/
void OptionsListWidget::setOption(int row, QString optionText)
{\
    QTableWidgetItem *item0 = new QTableWidgetItem;
//    QTableWidgetItem *item1 = new QTableWidgetItem;
    QFont fontStyle(font().family(), -1, QFont::Normal);
    item0->setFont(fontStyle);
    item0->setText(optionText);
    item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    item1->setFont(fontStyle);
//    item1->setText(additionText);
//    item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //表格中第一列为选项的具体名称,第二列为附加的内容,如数值或符号;
    m_tableWidget->setItem(row, 0, item0);
//    m_tableWidget->setItem(row, 1, item1);
}

/**
 * @name    void setExtraText(int row, QString extraText)
 * @details 添加备注文本
 * @param   row 行数
 * @param   extraText  附加的显示

 * @date    2018-11-15
**/
void OptionsListWidget::setExtraText(int row, QString extraText)
{
    QFont fontStyle(font().family(), -1, QFont::Normal);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setFont(fontStyle);
    item1->setText(extraText);
    item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_tableWidget->setItem(row, 1, item1);

}

/**
 * @name   void setSwitch(int row, bool state)
 * @details 添加开关
 * @param   row 行数
 * @param   state  状态

 * @date    2018-11-15
**/
void OptionsListWidget::setSwitch(int row, bool state)
{
    QWidget *backWidget = new QWidget;
    backWidget->setObjectName("translateWidget");
    backWidget->setStyleSheet("background-color:rgba(0,0,0,0)");

    QString qss=tr("QPushButton {\
                   border:0px;\
                border-image: url(%1);\
                outline: none;  \
                }\
                QPushButton:checked {\
                    border-image: url(%2);\
                }").arg(":/pics/D300/switch_off.png").arg(":/pics/D300/switch_on.png");
    QPushButton *m_switch = new QPushButton;
    m_switch->setStyleSheet(qss);
    m_switch->setCheckable(true);
    m_switch->setFocusPolicy(Qt::NoFocus);
    m_switch->setChecked(state);

    m_switch->setFixedSize(m_tableWidget->horizontalHeader()->defaultSectionSize()/2,
                           m_tableWidget->verticalHeader()->defaultSectionSize()/1.5);
    QHBoxLayout *backwidgetLayout = new QHBoxLayout(backWidget);
    backwidgetLayout->setMargin(0);
    backwidgetLayout->setSpacing(0);

    connect(m_switch, SIGNAL(clicked(bool)), this, SLOT(on_switchClicked()));

    m_buttonMap.insert(row, m_switch);

    backwidgetLayout->addWidget(m_switch,1,Qt::AlignRight);
    m_tableWidget->setCellWidget(row, 1, backWidget);
}

/**
* @name   void on_switchClicked()
* @details 开关点击处理函数，点击开关时选中行，并发射点击事件

* @date    2018-11-15
**/
void OptionsListWidget::on_switchClicked()
{
    if(m_buttonMap.isEmpty())
        return;
    foreach (QPushButton *btn, m_buttonMap)
    {
       if(btn == qobject_cast<QPushButton *>(sender()))
       {
           int index = m_buttonMap.key(btn);
           m_tableWidget->selectRow(index);
           emit optionsClickedSig(index);
       }
    }
}

/**
 * @name    bool getSwitchState()
 * @details 获取当前行的开关状态
 * @return  当前行的开关状态

 * @date    2018-11-15
**/
bool OptionsListWidget::getSwitchState()
{
    if(!m_buttonMap.isEmpty())
    {
        QPushButton *btn = m_buttonMap[m_tableWidget->currentRow()];
        return btn->isChecked();
    }
    return false;
}

/**
 * @name    int getCurrentIndex()
 * @details 获取当前索引，行
 * @return  当前索引，行

 * @date    2018-11-15
**/
int OptionsListWidget::getCurrentIndex()
{
    return m_tableWidget->currentIndex().row();
}

/**
 * @name    void optionsClicked(QModelIndex index)
 * @details 响应点击时的槽函数
 * @param   index  点击发生的索引位置

 * @date    2018-11-15
**/
void OptionsListWidget::optionsClicked(QModelIndex index)
{
    if(!m_buttonMap.isEmpty())
    {
        QPushButton *btn = m_buttonMap[index.row()];
        if(btn)
            btn->click();
    }

    emit optionsClickedSig(index.row());
}

/**
 * @name    void show()
 * @details 显示并获取焦点

 * @date    2018-11-15
**/
void OptionsListWidget::show()
{
    m_tableWidget->setFocus();
    QWidget::show();
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 按键事件,自定义回车键和Esc键的功能
 * @param   event 按键事件对象

 * @date    2018-11-15
**/
void OptionsListWidget::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Return)
    {
        //发送选项被点击的信号
        optionsClicked(m_tableWidget->currentIndex());
    }
    else if(event->key() == Qt::Key_Escape)
    {
        //关闭
        close();
        parentWidget()->close();
    }
}

/**
 * @name    void on_titleBarClicked(GlobalParam::ButtonType id, bool status)()
 * @details 处理标题栏信号的槽函数
 * @param   id  响应的按键类型
 * @param   status  响应的按键状态,默认为false,BUTTON_SWITCH时为实际的checked状态

 * @date    2018-11-15
**/
void OptionsListWidget::on_titleBarClicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
    {
        //关闭
        close();
        parentWidget()->close();
    }
}
