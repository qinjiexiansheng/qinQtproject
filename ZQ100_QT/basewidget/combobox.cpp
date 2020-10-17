#include "combobox.h"

/**
 * @name    ComboBox::ComboBox(QWidget *parent)
 * @details 构造函数
 *          继承了QComboBox, 实现自定义按键功能
 * @param   parent  父窗口指针

 * @date    2018-11-15
**/
ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{

}

/**
 * @name    void ComboBox::keyPressEvent(QKeyEvent *e)
 * @details 重写了QComboBox的按键事件
 *          将上下按键用于切换焦点,左右按键用于切换当前索引,并屏蔽了回车按键
 * @param   e   按键事件对象

 * @date    2018-11-15
**/
void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up)
        focusPreviousChild();
    else if(e->key() == Qt::Key_Down)
        focusNextChild();
    else if(e->key() == Qt::Key_Left)
    {
        int index = currentIndex();
        index--;
        index = index < 0 ? count()-1 : index;
        setCurrentIndex(index);
    }
    else if(e->key() == Qt::Key_Right)
    {
        int index = currentIndex();
        index++;
        index = index > count()-1 ? 0 : index;
        setCurrentIndex(index);
    }
    //    else if(e->key() == Qt::Key_Return)
    //    {
    ////        showPopup();
    //    }
    else
        e->ignore();
}

/**
 * @name    void focusInEvent(QFocusEvent *e)
 * @details 获得焦点时，改变显示效果
 * @param   e   焦点事件指针
 * @author  lee
 * @date    2018-12-21
**/
void ComboBox::focusInEvent(QFocusEvent *e)
{
    QComboBox::focusInEvent(e);
        setStyleSheet("background-color: rgb(0, 100, 100)");
}

/**
 * @name    void focusOutEvent(QFocusEvent *e)
 * @details 失去焦点时，恢复显示效果
 * @param   e   焦点事件指针
 * @author  lee
 * @date    2018-12-21
**/
void ComboBox::focusOutEvent(QFocusEvent *e)
{
    QComboBox::focusOutEvent(e);
        setStyleSheet(CHILDPAGE_STYLESHEET);
}
