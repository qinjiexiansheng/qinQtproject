#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include "globalparam.h"

class LineDelegate : public QStyledItemDelegate
{
public:
    LineDelegate(QTableView* tableView);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    //画笔
    QPen pen;
};

#endif // LINEDELEGATE_H
