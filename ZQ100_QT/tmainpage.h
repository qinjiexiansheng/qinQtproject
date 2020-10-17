#ifndef TMAINPAGE_H
#define TMAINPAGE_H

#include "globalparam.h"

class MenuButton;
class AnalysisManager;
class Label;

class TMainPage : public QWidget
{
    Q_OBJECT
public:
    explicit TMainPage(QWidget *parent = 0);
    void updateLabels();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void initMainPage();
    void initButtons();
    void updateLevelSpan();
    void updateWifiState();

private slots:
    void updateTime();
    void showMenuBar();
    void closeMenuBar();
    void changeMenuBar(int curMenuBarId = 0);
    void mainButtonGroupClicked(int id);
    void analysisButtonGroupClicked(int id);
    void imageButtonGroupClicked(int id);
    void mediaButtonGroupClicked(int id);
    void settingsButtonGroupClicked(int id);
    void satLogoBtnClicked(/*bool checked*/);
    void readKeyBoardData();
    void levelSpanClicked();


private:
    //显示电池图片
    QLabel *batteryLabel;
    //显示LOGO
    QPushButton *satLogoBtn;
    //显示wifi状态
    QLabel *wifiLabel;

    //分别显示温度、辐射率、距离、时间
    QLabel *tempUnitLabel;
    QLabel *emissValLabel;
    QLabel *distValLabel;
    QLabel *timeLabel;

    //Span/Level的最大最小值
    Label *spanLevelMax;
    Label *spanLevelMin;

    //当前菜单栏id
    int curMenuBarId;
    //暂存当前菜单栏显示状态
    bool *pbShow;
    //暂存当前菜单栏数据
    MenuButton **pButton;
    //暂存当前菜单栏按键组
    QButtonGroup *pButtonGroup;

    //菜单栏相关变量
    bool bMainButtonShow;
    bool bAnalysisButtonShow;
    bool bImageButtonShow;
    bool bMediaButtonShow;
    bool bSettingsButtonShow;
    QButtonGroup *mainButtonGroup;
    QButtonGroup *analysisButtonGroup;
    QButtonGroup *imageButtonGroup;
    QButtonGroup *mediaButtonGroup;
    QButtonGroup *settingsButtonGroup;
    MenuButton *mainButton[5];
    MenuButton *analysisButton[4];
    MenuButton *imageButton[3];
    MenuButton *mediaButton[5];
    MenuButton *settingsButton[5];

    //按键驱动的文件描述符
    qintptr m_fileKde;
    //监听按键可读，并触发信号进入读取按键信息
    QSocketNotifier* m_socketNotifier;
    //用于显示事件的分隔符:，隔一秒闪烁一次
    bool showColon;
    //管理Spot/Area/Line测温工具
    AnalysisManager *analysisManager;
    //检测Wifi状态
    int m_curWifiState;
};

#endif // TMAINPAGE_H
