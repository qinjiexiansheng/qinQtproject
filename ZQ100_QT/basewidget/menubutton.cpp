#include "menubutton.h"

/**
 * @name    MenuButton(QWidget *parent, int duration)
 * @details 构造函数
 *          继承了QPushButton,实现带动画的按键功能
 * @param   parent  父窗口指针
 * @param   duration    动画持续时间

 * @date    2018-11-15
**/
MenuButton::MenuButton(QWidget *parent, int duration):QPushButton(parent)
{
    pAnimation_show = NULL;
    pAnimation_hide = NULL;
    buttonText = NULL;

    m_parent = parent;
    m_duration = duration;

    setFlat(true);
    setCheckable(true);
}

/**
 * @name    void show(bool bShow)
 * @details 当bShow为true时, 按键从左侧弹出; 为false则隐藏按键
 * @param   bShow   显示标志位

 * @date    2018-11-15
**/
void MenuButton::show(bool bShow)
{
    if(pAnimation_show == NULL)
    {
        //为按键安装从左淡进的动画
        pAnimation_show = new QPropertyAnimation;
        pAnimation_show->setTargetObject(this);
        pAnimation_show->setPropertyName("geometry");
        pAnimation_show->setDuration(m_duration);
        pAnimation_show->setStartValue(QRect(-width(), pos().y(),
                                             width(), height()));
        pAnimation_show->setEndValue(QRect(pos().x(), pos().y(),
                                           width(),height()));
    }

    if(pAnimation_hide == NULL)
    {
        //为按键安装从左淡出的动画
        pAnimation_hide = new QPropertyAnimation;
        pAnimation_hide->setTargetObject(this);
        pAnimation_hide->setPropertyName("geometry");
        pAnimation_hide->setDuration(m_duration);
        pAnimation_hide->setEndValue(QRect(-width(), pos().y(),
                                           width(), height()));
        pAnimation_hide->setStartValue(QRect(pos().x(), pos().y(),
                                             width(),height()));
    }

    if(bShow)
    {
        //提升至最顶层
        raise();
        //显示按键的文本信息并启用淡进的动画效果
        if(isChecked())
            buttonText->show();
        pAnimation_show->start();
    }
    else
    {
        //隐藏按键的文本信息并启用淡出的动画效果
        buttonText->hide();
        pAnimation_hide->start();
    }

    QPushButton::show();

    //动画结束后,根据bshow设置按键是否为隐藏状态,以防止其淡出后仍可响应键盘
    setHidden(!bShow);

}

/**
 * @name    void setText(const QString &text)
 * @details 为按键添加文本信息,显示在图标的后面
 * @param   text   按键文本

 * @date    2018-11-15
**/
void MenuButton::setText(const QString &text)
{
    if(buttonText == NULL)
    {
        buttonText = new QLabel(m_parent);
    }

    buttonText->setText(text);
    buttonText->setScaledContents(true);
    buttonText->adjustSize();
}

/**
 * @name    void setFont(const QFont &font, const QColor &color)
 * @details 设置文本字体和颜色
 * @param   font    字体格式
 * @param   color   字体颜色

 * @date    2018-11-15
**/
void MenuButton::setFont(const QFont &font, const QColor &color)
{
    if(buttonText != NULL)
    {
        QPalette palette;
        palette.setColor(QPalette::WindowText, color);
        buttonText->setPalette(palette);
        buttonText->setFont(font);
        buttonText->setScaledContents(true);
        buttonText->adjustSize();
    }
}

/**
 * @name    void move(int x, int y)
 * @details 移动按键时,同步移动按键文本的位置
 * @param   x   x坐标
 * @param   y   y坐标

 * @date    2018-11-15
**/
void MenuButton::move(int x, int y)
{
    if(buttonText != NULL)
    {
        buttonText->move(x+width()+5, y+(height()-buttonText->height())/2);
    }

    QPushButton::move(x, y);
}

/**
 * @name    void move(const QPoint &point)
 * @details 移动按键时,同步移动按键文本的位置
 * @param   point   移动的坐标

 * @date    2018-11-15
**/
void MenuButton::move(const QPoint &point)
{
    if(buttonText != NULL)
    {
        buttonText->move(point.x()+width()+5, point.y()+(height()-buttonText->height())/2);
    }

    QPushButton::move(point);
}

/**
 * @name    void hide()
 * @details 隐藏按键和按键文本

 * @date    2018-11-15
**/
void MenuButton::hide()
{
    buttonText->hide();
    QPushButton::hide();

}

/**
 * @name    void showLabel(bool bShowLabel)
 * @details 显示按键文本
 * @param   bShowLabel  文本显示标志

 * @date    2018-11-15
**/
void MenuButton::showLabel(bool bShowLabel)
{
    if(bShowLabel)
        buttonText->show();
    else
        buttonText->hide();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 键盘事件,屏蔽空格键,按键隐藏时屏蔽键盘响应
 * @param   bShowLabel  文本显示标志

 * @date    2018-11-15
**/
void MenuButton::keyPressEvent(QKeyEvent *e)
{
    if(isHidden())
        return;
    if(e->key() == Qt::Key_Space)
        return;
    QPushButton::keyPressEvent(e);
}




