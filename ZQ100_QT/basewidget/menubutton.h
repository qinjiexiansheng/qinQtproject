#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "globalparam.h"

class MenuButton : public QPushButton
{
public:
    explicit MenuButton(QWidget *parent=0, int duration = 0);

public:
    void show(bool bStatus);
    void setText(const QString &text);
    void setFont(const QFont &font, const QColor &color);
    void move(const QPoint &point);
    void move(int x, int y);
    void hide();
    void showLabel(bool bShowLabel);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    //动画
    QPropertyAnimation *pAnimation_show;
    QPropertyAnimation *pAnimation_hide;
    //持续事件
    int m_duration;
    //按键文本
    QLabel *buttonText;
    //父窗口指针
    QWidget *m_parent;
    //隐藏标志
    bool m_hidden;
};

#endif // MENUBUTTON_H
