#include "linedelegate.h"

/**
 * @name    LineDelegate(QTableView* tableView, bool lineOn)
 * @details 构造函数
 *          主要用于QTableWidget的自定义显示,取消了网格显示
 * @param   parent  父窗口指针
 * @param   lineOn  画横线开关

 * @date    2018-11-15
**/
LineDelegate::LineDelegate(QTableView* tableView)
{
    pen = QPen(Qt::black, 0, tableView->gridStyle());
}

/**
 * @name    void paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index) const
 * @details 画图事件
 *          重绘横线,并屏蔽了选中时的显示效果
 * @param   painter 画笔
 * @param   option  样式选项
 * @param   index   索引

 * @date    2018-11-15
**/
void LineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

//    if (option.state.testFlag(QStyle::State_HasFocus))
//    {
//        //屏蔽选中时的显示效果
//        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
//        viewOption.state &= QStyle::State_ReadOnly;
//    }

//    //    if(m_lineOn)
//    {
//        QPen oldPen = painter->pen();
//        painter->setPen(pen);
//        //画横线
//        painter->drawLine(viewOption.rect.bottomLeft(), viewOption.rect.bottomRight());
//        painter->setPen(oldPen);
//    }

    if (option.state.testFlag(QStyle::State_HasFocus))
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    //调用父类的画图事件
    QStyledItemDelegate::paint(painter, viewOption, index);
}
