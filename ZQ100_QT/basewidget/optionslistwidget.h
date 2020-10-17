#ifndef OPTIONSLISTWIDGET_H
#define OPTIONSLISTWIDGET_H

#include "globalparam.h"

class TitleBar;

class OptionsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsListWidget(QWidget *parent = 0, QString title = "UNTITLED", int rowCount = 6);
    void setOption(int row, QString optionText = "");
    void setExtraText(int row, QString extraText = "");
    void setSwitch(int row, bool state = false);
    int getCurrentIndex();
    bool getSwitchState();
    void show();

protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void optionsClickedSig(int id);

private slots:
    void on_switchClicked();
    void on_titleBarClicked(GlobalParam::ButtonType id, bool status);
    void optionsClicked(QModelIndex index);

private:
    //主要的显示窗口
    QTableWidget *m_tableWidget;
    //标题栏
    TitleBar *m_titleBar;
    QMap<int, QPushButton*> m_buttonMap;
};

#endif // OPTIONSLISTWIDGET_H

