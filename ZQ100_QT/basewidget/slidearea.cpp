#include "slidearea.h"
#include "scrollarea.h"

/**
 * @name    SlideArea(QWidget *parent, int H_Spacing, int V_Spacing)
 * @details 构造函数
 *          实现了一个滑动设置参数的窗口
 * @param   parent  父窗口指针
 * @param   H_Spacing   水平的间隙
 * @param   V_Spacing   垂直的间隙

 * @date    2018-11-15
**/
SlideArea::SlideArea(QWidget *parent, int H_Spacing, int V_Spacing) :
    QWidget(parent)
{
    m_itemNum = 0;
    m_highlightItem = 0;
    m_itemList.clear();

    m_horizontal_margins = H_Spacing;
    m_vertical_Spacing = V_Spacing;


    initView();
}

/**
 * @name    void SlideArea::initView()
 * @details 初始化界面显示

 * @date    2018-11-15
**/
void SlideArea::initView()
{
    //添加两端水平线以表示item选中的范围
    m_topLine = new QFrame(this);
    m_topLine->setFrameShape(QFrame::HLine);
    m_bottomLine = new QFrame(this);
    m_bottomLine->setFrameShape(QFrame::HLine);

    //实现滑动窗口
    m_widget = new QWidget(this);
    m_gridLayout = new QGridLayout(m_widget);
    m_gridLayout->setContentsMargins(m_horizontal_margins, 0, m_horizontal_margins, 0);
    m_gridLayout->setSpacing(m_vertical_Spacing);
    m_scrollArea = new ScrollArea(this);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);

    hide();

    connect(m_scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(valueChangedSlot(int)));
}

/**
 * @name    void SlideArea::adjustLayout()
 * @details 调整窗口的布局

 * @date    2018-11-15
**/
void SlideArea::adjustLayout()
{
    m_labelSize.setHeight(m_labelSize.height()+m_gridLayout->spacing());
    m_scrollArea->setFixedSize(m_labelSize.width() < m_gridLayout->sizeHint().width() ?
                             m_gridLayout->sizeHint().width() : m_labelSize.width(),
                         m_labelSize.height()*3-m_gridLayout->spacing());
    m_widget->setFixedSize(m_gridLayout->sizeHint());
    m_scrollArea->setItemSize(m_labelSize);
    m_scrollArea->setItemNum(m_itemNum);
    m_scrollArea->setWidget(m_widget);

    setHightLight(0);

    setFixedSize(m_scrollArea->size());

    m_topLine->setGeometry(QRect(width()/5.0, height()/3.0, width()/5.0*3.0, 1));
    m_topLine->raise();

    m_bottomLine->setGeometry(QRect(width()/5.0, height()/3.0*2.0, width()/5.0*3.0, 1));
    m_bottomLine->raise();

    if(this->parentWidget())
        show();
}

/**
 * @name    void addItems(QStringList *options)
 * @details 为滑动窗口添加数据,只能设置一次
 * @param   options 数据列表

 * @date    2018-11-15
**/
void SlideArea::addItems(QStringList *options)
{
    if(m_itemNum > 0 || options->count() <= 0)
    {
        return;
    }

    m_itemNum = options->count();

    QLabel *beginLabel= new QLabel;
    m_gridLayout->addWidget(beginLabel, 0, 0);
    for(int i=0; i<m_itemNum; i++)
    {
        QLabel *label = new QLabel(options->at(i));
        label->setAlignment(Qt::AlignCenter);
        m_labelSize = label->sizeHint();
        m_itemList.append(label);
        m_gridLayout->addWidget(label, i+1, 0);
    }
    QLabel *endLabel= new QLabel;
    QLabel *endLabel1= new QLabel;
    m_gridLayout->addWidget(endLabel, m_itemNum+1, 0);
    m_gridLayout->addWidget(endLabel1, m_itemNum+2, 0);

    adjustLayout();
}

/**
 * @name    void setHightLight(int index)
 * @details 自定义选中数据的显示效果
 * @param   index 数据索引

 * @date    2018-11-15
**/
void SlideArea::setHightLight(int index)
{
    if(m_itemList.count() < 1)
        return;
    m_itemList.at(m_highlightItem)->setStyleSheet("color : rgb(0, 0, 0);");
    m_highlightItem = index;
    m_itemList.at(m_highlightItem)->setStyleSheet("color : rgb(255, 255, 255);");
}

/**
 * @name    void setCurrentIndex(int index)
 * @details 设置当前的索引,并滑动到相应位置
 * @param   index 索引值

 * @date    2018-11-15
**/
void SlideArea::setCurrentIndex(int index)
{
    if(index > m_itemList.count()-1)
        index = m_itemList.count()-1;
    m_scrollArea->verticalScrollBar()->setValue(index*m_labelSize.height());
    setHightLight(index);
}

/**
 * @name    int getCurrentIndex() const
 * @details 获取当前的索引值
 * @return  当前的索引值

 * @date    2018-11-15
**/
int SlideArea::getCurrentIndex() const
{
    return m_highlightItem;
}

/**
 * @name    bool isEmpty() const
 * @details 判断数据列表是否为空
 * @return  为空则返回true,否则为false

 * @date    2018-11-15
**/
bool SlideArea::isEmpty() const
{
    return m_itemNum == 0;
}

/**
 * @name    void valueChanged(int val)
 * @details 响应ScrollArea滑动信号的槽函数
 * @param   val 当前滑动条的数值

 * @date    2018-11-15
**/
void SlideArea::valueChangedSlot(int val)
{
    float index = (float)val/m_labelSize.height();
    if(index > m_itemList.count()-1)
        index = m_itemList.count()-1;

    setHightLight(qRound(index));

    if ( index - (int) index == 0)
        emit valueChangedSig();
}

/**
 * @name    void setCurrentText(int  value)
 * @details 设置当前的数值，并滑动到相应位置
 * @param   value 数值

 * @date    2018-11-15
**/
void SlideArea::setCurrentText(int  value)
{
    foreach (QLabel *item, m_itemList) {
        if(item->text().toInt() == value)
        {
            int index =  m_itemList.indexOf(item);
            m_scrollArea->verticalScrollBar()->setValue(index*m_labelSize.height());
            setHightLight(index);
        }
    }
}

/**
 * @name    void setCurrentText(QString text)
 * @details 设置当前的文本，并滑动到相应位置
 * @param   text 文本数据

 * @date    2018-11-15
**/
void SlideArea::setCurrentText(QString text)
{
    foreach (QLabel *item, m_itemList) {
        if(text == item->text())
        {
            int index =  m_itemList.indexOf(item);
            m_scrollArea->verticalScrollBar()->setValue(index*m_labelSize.height());
            setHightLight(index);
        }
    }
}

/**
 * @name    QString getCurrentText() const
 * @details 获取当前数据的文本
 * @param   当前数据的文本

 * @date    2018-11-15
**/
QString SlideArea::getCurrentText() const
{
    if(m_itemList.count() > 0)
        return  m_itemList.at(m_highlightItem)->text();
    return "0";
}

/**
 * @name    QString getText(int index) const
 * @details 获取指定索引处的文本
 * @param   指定索引处的文本

 * @date    2018-11-15
**/
QString SlideArea::getText(int index) const
{
    if(index >= m_itemList.count())
    {
        qWarning("out of range");
        return "0";
    }
    if(m_itemList.count() > 0)
        return  m_itemList.at(index)->text();
    return "0";
}

/**
 * @name    void setFocus()
 * @details 重写setFocus,将焦点移至滑动窗口

 * @date    2018-11-15
**/
void SlideArea::setFocus()
{
    m_scrollArea->setFocus();\
}

/**
 * @name    void setShowItemNum(int num)
 * @details 限制滑动窗口中的显示的item数目为num
 * @param   num 显示的item数
 * @date    2018-11-15
**/
void SlideArea::setShowItemNum(int num)
{
    if(num > m_itemList.count())
        return;

    m_itemNum = num;
    m_scrollArea->setItemNum(m_itemNum);

    if(getCurrentIndex() > m_itemNum-1)
        setCurrentIndex(m_itemNum-1);

    for(int j=0; j < m_itemList.count(); j++)
    {
        if(j >= num)
            m_itemList.at(j)->setStyleSheet("color : rgb(0, 155, 155);");
        else
        {
            if(m_highlightItem == j)
                m_itemList.at(j)->setStyleSheet("color : white;");
            else
                m_itemList.at(j)->setStyleSheet("color : black");
        }

    }
}
