#ifndef LSLIDEAREA_H
#define LSLIDEAREA_H

#include "globalparam.h"

#define H_SPACING 30
#define V_SPACING 30

class ScrollArea;

class SlideArea : public QWidget
{
    Q_OBJECT
public:
    explicit SlideArea(QWidget *parent = 0, int H_Spacing = H_SPACING, int V_Spacing = V_SPACING);

    void addItem(QString option);
    void addItems(QStringList *options);
    void setCurrentIndex(int index);
    int getCurrentIndex() const;
    bool isEmpty() const;
    void setCurrentText(int  value);
    void setCurrentText(QString text);
    QString getCurrentText() const;
    QString getText(int index) const;
    void setFocus();

    void setShowItemNum(int );

signals:
    void valueChangedSig();

private slots:
    void valueChangedSlot(int);

private:
    void initView();
    void adjustLayout();
    void setHightLight(int index);


private:
    //存储数据
    QList<QLabel *>m_itemList;
    QSize m_labelSize;

    QWidget *m_widget;
    QGridLayout *m_gridLayout;
    ScrollArea *m_scrollArea;

    int m_highlightItem;
    int m_itemNum;
    int m_horizontal_margins;
    int m_vertical_Spacing;

    QFrame *m_topLine;
    QFrame *m_bottomLine;

};

#endif // LSLIDEAREA_H
