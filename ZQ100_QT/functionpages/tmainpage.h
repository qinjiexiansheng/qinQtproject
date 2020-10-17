#ifndef TMAINPAGE_H
#define TMAINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QMessageBox>
#include <QPalette>
#include <QFont>
#include <QTime>
#include <QTimer>
#include <QToolButton>
#include <QIcon>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMovie>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QWidget>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <QSocketNotifier>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

class MenuButton;
class AnalysisManager;

class TMainPage : public QWidget
{
    Q_OBJECT
public:
    explicit TMainPage(QWidget *parent = 0);
    void updateLabels();

protected:
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void initMainPage();
    void initButtons();
    void updateSpan();

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


private:
    QLabel *movieLabel;

    QLabel *batteryLabel;
    QPushButton *satLogoBtn;
    QLabel *wifiLabel;

    QLabel *tempUnitLabel;
    QLabel *emissValLabel;
    QLabel *distValLabel;
    QLabel *timeLabel;

    QLabel *spanLevelMax;
    QLabel *spanLevelMin;

    int curMenuBarId;

    bool *pbShow;
    MenuButton **pButton;
    QButtonGroup *pButtonGroup;

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

    bool bShowMenuBar;


    qintptr m_fileKde;
    QSocketNotifier* m_socketNotifier;

    bool showColon;

    AnalysisManager *analysisManager;
};

#endif // TMAINPAGE_H
