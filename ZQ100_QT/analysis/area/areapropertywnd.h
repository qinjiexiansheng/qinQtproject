#ifndef AREAPROPERTYWND_H
#define AREAPROPERTYWND_H

#include "globalparam.h"

class Area;
class TitleBar;
class ComboBox;

struct AreaProperty
{
    //property
    int displayMode;//0:hide 1:show
    int maxShowMode;//0:off 2:on
    int minShowMode;//0:off 2:on
    int avgShowMode;//0:off 2:on
};

class AreaPropertyWnd : public QDialog
{
    Q_OBJECT
public:
    explicit AreaPropertyWnd(Area *area);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void accept();
    void reject();
    int exec();

private slots:
    void on_clicked(GlobalParam::ButtonType id, bool status);

private:
    void initView();
    void initStates(const AreaProperty areaProperty);

private:
    //属性窗口服务的Area指针
    Area *m_area;
    TitleBar *m_titleBar;
    QWidget *m_mainWidget;

    //属性控件
    ComboBox *displayCombobox;
    ComboBox *maxShowCombobox;
    ComboBox *minShowCombobox;
    ComboBox *avgShowCombobox;

};

#endif // AREAPROPERTYWND_H
