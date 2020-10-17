#include "tmainpage.h"
#include "basewidget/menubutton.h"
#include "functionpages/Setting/AnalysisSettingPage/analysissettingpage.h"
#include "functionpages/Setting/SystemSettingPage/systemsettingpage.h"
#include "functionpages/Setting/AnalysisSettingPage/comptemppage.h"
#include "functionpages/Analysis/analysismanager.h"
#include "basewidget/slidewidget.h"
#include "globalparam.h"

#define DEF_KEY_OK      167
#define DEF_KEY_ESC     166
#define DEF_KEY_LEFT    163
#define DEF_KEY_UP      162
#define DEF_KEY_RIGHT   164
#define DEF_KEY_DOWN    165

/**
 * @name    TMainPage(QWidget *parent) :
 * @details 主界面,实现多界面的切换显示功能
 * @param   parent  父窗口
 * @author  lee
 * @date    2018-11-15
**/
TMainPage::TMainPage(QWidget *parent) :
    QWidget(parent)
{
    move(0, 0);
    setMaximumSize(320, 240);
    setMinimumSize(320, 240);
    setObjectName("obj");

    //    //qDebug()<<rect();
    //    setAttribute(Qt::WA_StyledBackground,true);
    setWindowFlags(Qt::FramelessWindowHint);
//    setStyleSheet("QWidget#obj {background-color: rgb(254, 254, 254);}\
//                    QLabel{color: rgb(255, 255, 255)}");

      setStyleSheet("QWidget#obj {background-color: rgb(255, 0, 255);}\
                    QLabel{color: rgb(0, 0, 0)}");

    GlobalParam::setParentWidget(this);

    analysisManager = new AnalysisManager(this);


    //打开外部按键驱动
    m_fileKde = open("/dev/input/event0", O_RDONLY);
    if(m_fileKde < 0)
    {
        perror("open()");
    }
    //监听外部按键
    m_socketNotifier = new QSocketNotifier(m_fileKde, QSocketNotifier::Read, this);
    connect(m_socketNotifier, SIGNAL(activated(int)), this, SLOT(readKeyBoardData()));

    //初始化显示
    initMainPage();

    //显示时间
    QTimer *timeUpateTimer = new QTimer(this);
    connect(timeUpateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    timeUpateTimer->start(1000);

    GlobalParam::getFPGA()->init();
}

/**
 * @name    void initMainPage()
 * @details 初始化界面显示
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::initMainPage()
{
    QImage *img = new QImage;
    if(img->load(":/pics/charge_full.png")) //加载图像
    {
//        float scale = 0.06;
//        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    batteryLabel = new QLabel(this);
    batteryLabel->setPixmap(QPixmap::fromImage(*img));
    batteryLabel->resize(img->width(), img->height());
    batteryLabel->move(0, 0);

    if(img->load(":/pics/satlogo_sat.png")) //加载图像
    {
        float scale = 1.2;
        *img = img->scaled(img->width()*scale, img->width()*scale, Qt::KeepAspectRatio);
    }
    satLogoBtn = new QPushButton(this);
    satLogoBtn->setObjectName("SATLOGO");
    satLogoBtn->resize(img->width(), img->height());
    satLogoBtn->setFlat(true);
    satLogoBtn->setIconSize(QSize(img->width(), img->height()));
    satLogoBtn->setIcon(QIcon(QPixmap::fromImage(*img)));
    satLogoBtn->move(this->width()-img->width()-5, 7);
    satLogoBtn->installEventFilter(this);
    connect(satLogoBtn, SIGNAL(clicked(bool)), this, SLOT(satLogoBtnClicked(/*bool*/)));

    wifiLabel = new QLabel(this);
    if(img->load(":/pics/wifi_logo.png")) //加载图像
    {
        float scale = 0.20;
        *img = img->scaled(img->width()*scale, img->height()*scale, Qt::KeepAspectRatio);
    }
    wifiLabel->setPixmap(QPixmap::fromImage(*img));
    wifiLabel->resize(img->width(), img->height());
    wifiLabel->move(batteryLabel->width()+5, 0);

    QFont labelFont(font().family(), 10, QFont::Normal, false);

    tempUnitLabel = new QLabel(this);
    tempUnitLabel->setFont(labelFont);
    tempUnitLabel->setScaledContents(true);

    emissValLabel = new QLabel(this);
    emissValLabel->setFont(labelFont);
    emissValLabel->setScaledContents(true);

    distValLabel = new QLabel(this);
    distValLabel->setFont(labelFont);
    distValLabel->setScaledContents(true);

    updateLabels();

    tempUnitLabel->move(0, height()-tempUnitLabel->height());
    emissValLabel->move(60, height()-emissValLabel->height());
    distValLabel->move(150, height()-distValLabel->height());

    spanLevelMax = new QLabel(this);
    spanLevelMax->setFont(labelFont);
    spanLevelMax->setScaledContents(true);

    spanLevelMin = new QLabel(this);
    spanLevelMin->setFont(labelFont);
    spanLevelMin->setScaledContents(true);

    updateSpan();

    spanLevelMax->move(SCREEN_WIDTH-spanLevelMax->width(),
                       SCREEN_HEIGHT*2/6-spanLevelMax->height()/2);
    spanLevelMin->move(SCREEN_WIDTH-spanLevelMin->width(),
                       SCREEN_HEIGHT*4/6-spanLevelMin->height()/2);

    timeLabel = new QLabel(this);
    timeLabel->setFont(labelFont);
    timeLabel->setScaledContents(true);
    updateTime();
    timeLabel->move(220, height()-timeLabel->height());


    initButtons();
}

/**
 * @name    void initButtons()
 * @details 初始化菜单栏按钮
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::initButtons()
{
    QFont buttonFont(font().family(), 8, QFont::Normal, false);
    QString menuButtonInfo[3][5] = {
        {"Analysis", "Image", "Media", "File", "Settings"},
        {
            ":/pics/D300/dock_analysis.png",
            ":/pics/D300/dock_image.png",
            ":/pics/D300/dock_media.png",
            ":/pics/D300/dock_file.png",
            ":/pics/D300/dock_settings.png",
        },
        {
            ":/pics/D300/dock_analysis_hl.png",
            ":/pics/D300/dock_image_hl.png",
            ":/pics/D300/dock_media_hl.png",
            ":/pics/D300/dock_file_hl.png",
            ":/pics/D300/dock_settings_hl.png",
        }
    };
    QString analysisButtonInfo[3][4] = {
        {"Spot", "Area", "Line", "ISO"},
        {
            ":/pics/D300/dock_spot.png",
            ":/pics/D300/dock_area.png",
            ":/pics/D300/dock_line.png",
            ":/pics/D300/dock_iso.png",
        },
        {
            ":/pics/D300/dock_spot_hl.png",
            ":/pics/D300/dock_area_hl.png",
            ":/pics/D300/dock_line_hl.png",
            ":/pics/D300/dock_iso_hl.png",
        }
    };
    QString imageButtonInfo[3][3] = {
        {"Mode", "Palette", "Adjust"},
        {
            ":/pics/D300/dock_mode.png",
            ":/pics/D300/dock_palette.png",
            ":/pics/D300/dock_adjustmode.png",
        },
        {
            ":/pics/D300/dock_mode_hl.png",
            ":/pics/D300/dock_palette_hl.png",
            ":/pics/D300/dock_adjustmode_hl.png",
        }
    };
    QString mediaButtonInfo[3][5] = {
        {"Snapshot", "Edit", "Voice", "Video", "Replay"},
        {
            ":/pics/D300/dock_snapshot.png",
            ":/pics/D300/dock_edit.png",
            ":/pics/D300/dock_voice.png",
            ":/pics/D300/dock_video_start.png",
            ":/pics/D300/dock_replay.png",
        },
        {
            ":/pics/D300/dock_snapshot_hl.png",
            ":/pics/D300/dock_edit_hl.png",
            ":/pics/D300/dock_voice_hl.png",
            ":/pics/D300/dock_video_start_hl.png",
            ":/pics/D300/dock_replay_hl.png",
        }
    };
    QString settingsButtonInfo[3][5] = {
        {"Analysis", "Sytem", "Image", "Bluetooth", "SytemInfo"},
        {
            ":/pics/D300/dock_parameter.png",
            ":/pics/D300/dock_system.png",
            ":/pics/D300/dock_setimage.png",
            ":/pics/D300/dock_bluetooth.png",
            ":/pics/D300/dock_systeminfo.png",
        },
        {
            ":/pics/D300/dock_parameter_hl.png",
            ":/pics/D300/dock_system_hl.png",
            ":/pics/D300/dock_setimage_hl.png",
            ":/pics/D300/dock_bluetooth_hl.png",
            ":/pics/D300/dock_systeminfo_hl.png",
        }
    };

    curMenuBarId = 0;
    bMainButtonShow = false;
    bAnalysisButtonShow = false;
    bImageButtonShow = false;
    bMediaButtonShow = false;
    bSettingsButtonShow = false;

    mainButtonGroup = new QButtonGroup(this);
    for(int i=0; i<5; i++)
    {
            QString qss=tr("QPushButton {\
                           border:0px;\
                    border-image: url(%1);\
        outline: none;  \
            }\
        QPushButton:checked {\
                border-image: url(%2);\
            }").arg(menuButtonInfo[1][i]).arg(menuButtonInfo[2][i]);
        mainButton[i] = new MenuButton(this, 100);
        mainButton[i]->setText(menuButtonInfo[0][i]);
        mainButton[i]->setFont(buttonFont, Qt::black);
        mainButton[i]->resize(36, 36);
        mainButton[i]->move(0, 30+i*(mainButton[i]->width()+5));
        mainButton[i]->setStyleSheet(qss);
        mainButtonGroup->addButton(mainButton[i], i);
        if(i == 0)
            mainButton[i]->setChecked(true);
        mainButton[i]->hide();
    }

    analysisButtonGroup = new QButtonGroup(this);
    for(int i=0; i<4; i++)
    {
        QString qss=tr("QPushButton {\
                       border:0px;\
                border-image: url(%1);\
        outline: none;  \
        }\
        QPushButton:checked {\
            border-image: url(%2);\
        }").arg(analysisButtonInfo[1][i]).arg(analysisButtonInfo[2][i]);
        analysisButton[i] = new MenuButton(this, 100);
        analysisButton[i]->setText(analysisButtonInfo[0][i]);
        analysisButton[i]->setFont(buttonFont, Qt::black);
        analysisButton[i]->resize(36, 36);
        analysisButton[i]->move(0, 30+i*(analysisButton[i]->width()+5));
        analysisButton[i]->setStyleSheet(qss);
        analysisButtonGroup->addButton(analysisButton[i], i);
        if(i == 0)
        analysisButton[i]->setChecked(true);
        analysisButton[i]->hide();
    }

    imageButtonGroup = new QButtonGroup(this);
    for(int i=0; i<3; i++)
    {
        QString qss=tr("QPushButton {\
                       border:0px;\
                border-image: url(%1);\
        outline: none;  \
        }\
        QPushButton:checked {\
            border-image: url(%2);\
        }").arg(imageButtonInfo[1][i]).arg(imageButtonInfo[2][i]);
        imageButton[i] = new MenuButton(this, 100);
        imageButton[i]->setText(imageButtonInfo[0][i]);
        imageButton[i]->setFont(buttonFont, Qt::black);
        imageButton[i]->resize(36, 36);
        imageButton[i]->move(0, 30+i*(imageButton[i]->width()+5));
        imageButton[i]->setStyleSheet(qss);
        imageButtonGroup->addButton(imageButton[i], i);
        if(i == 0)
        imageButton[i]->setChecked(true);
        imageButton[i]->hide();
    }

    mediaButtonGroup = new QButtonGroup(this);
    for(int i=0; i<5; i++)
    {
        QString qss=tr("QPushButton {\
                       border:0px;\
                border-image: url(%1);\
        outline: none;  \
        }\
        QPushButton:checked {\
            border-image: url(%2);\
        }").arg(mediaButtonInfo[1][i]).arg(mediaButtonInfo[2][i]);
        mediaButton[i] = new MenuButton(this, 100);
        mediaButton[i]->setText(mediaButtonInfo[0][i]);
        mediaButton[i]->setFont(buttonFont, Qt::black);
        mediaButton[i]->resize(36, 36);
        mediaButton[i]->move(0, 30+i*(mediaButton[i]->width()+5));
        mediaButton[i]->setStyleSheet(qss);
        mediaButtonGroup->addButton(mediaButton[i], i);
        if(i == 0)
        mediaButton[i]->setChecked(true);
    mediaButton[i]->hide();
    }

    settingsButtonGroup = new QButtonGroup(this);
    for(int i=0; i<5; i++)
    {
        QString qss=tr("QPushButton {\
                       border:0px;\
                border-image: url(%1);\
        outline: none;  \
        }\
        QPushButton:checked {\
            border-image: url(%2);\
        }").arg(settingsButtonInfo[1][i]).arg(settingsButtonInfo[2][i]);
        settingsButton[i] = new MenuButton(this, 100);
        settingsButton[i]->setText(settingsButtonInfo[0][i]);
        settingsButton[i]->setFont(buttonFont, Qt::black);
        settingsButton[i]->resize(36, 36);
        settingsButton[i]->move(0, 30+i*(settingsButton[i]->width()+5));
        settingsButton[i]->setStyleSheet(qss);
        settingsButtonGroup->addButton(settingsButton[i], i);
        if(i == 0)
        settingsButton[i]->setChecked(true);
        settingsButton[i]->hide();
    }

    connect(mainButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(mainButtonGroupClicked(int)));
    connect(analysisButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(analysisButtonGroupClicked(int)));
    connect(imageButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(imageButtonGroupClicked(int)));
    connect(mediaButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(mediaButtonGroupClicked(int)));
    connect(settingsButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(settingsButtonGroupClicked(int)));

    changeMenuBar(curMenuBarId);
}

/**
 * @name    void updateTime()
 * @details 刷新时间显示
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::updateTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    ////qDebug()<<text;
    if(showColon)
    {
        text[2]=':';
        showColon=false;
    }
    else
    {
        text[2]=' ';
        showColon=true;
    }

    timeLabel->setText(text);
    timeLabel->adjustSize();

    updateSpan();
}

/**
 * @name    void satLogoBtnClicked()
 * @details 响应logo点击事件
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::satLogoBtnClicked(/*bool checked*/)
{
    if(curMenuBarId != 0)
    {
        closeMenuBar();
        curMenuBarId = 0;
        changeMenuBar(curMenuBarId);
    }

    showMenuBar();
}


/**
 * @name    void readKeyBoardData()
 * @details 读取外部按键数据,并发送标准的按键事件
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::readKeyBoardData()
{
    struct input_event ev_key;
    QKeyEvent *keyEvent;
    Qt::Key key;

    read(m_fileKde,&ev_key,sizeof(struct input_event));

    if(ev_key.type !=0)
    {
        //        qWarning("ev_key.code = %d", ev_key.code);

        switch (ev_key.code) {
        case DEF_KEY_ESC:
            key = Qt::Key_Escape;
            break;
        case DEF_KEY_OK:
            key = Qt::Key_Return;
            break;
        case DEF_KEY_LEFT:
            key = Qt::Key_Left;
            break;
        case DEF_KEY_UP:
            key = Qt::Key_Up;
            break;
        case DEF_KEY_RIGHT:
            key = Qt::Key_Right;
            break;
        case DEF_KEY_DOWN:
            key = Qt::Key_Down;
            break;
        default:
            break;
        }
        if(ev_key.value != 0)
            keyEvent = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier);
        else
            keyEvent = new QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier);
        //        //qDebug()<<qApp->focusWidget();
        if(qApp->focusWidget() == NULL)
            return;
        qApp->sendEvent(qApp->focusWidget(), keyEvent);
    }
}

/**
 * @name    void showMenuBar()
 * @details 显示菜单栏
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::showMenuBar()
{
    //    //qDebug()<<"Begin: "<<bMainButtonShow<<", "<<bAnalysisButtonShow
    //              <<", "<<bImageButtonShow<<", "<<bMediaButtonShow
    //              <<", "<<bSettingsButtonShow;

    (*pbShow) = !(*pbShow);

    //    //qDebug()<<"End: "<<bMainButtonShow<<", "<<bAnalysisButtonShow
    //              <<", "<<bImageButtonShow<<", "<<bMediaButtonShow
    //              <<", "<<bSettingsButtonShow;

    for(int i=0; i<pButtonGroup->buttons().count(); i++)
    {
        pButton[i]->show((*pbShow));
    }
    if((*pbShow))
        pButton[pButtonGroup->checkedId()]->setFocus();
    else
        satLogoBtn->setFocus();
}

/**
 * @name    void closeMenuBar()
 * @details 关闭菜单栏
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::closeMenuBar()
{
    if((*pbShow))
    {
        (*pbShow) = false;
        for(int i=0; i<pButtonGroup->buttons().count(); i++)
            pButton[i]->show((*pbShow));
        satLogoBtn->setFocus();
    }

}

/**
 * @name    void changeMenuBar(int curMenuBarId)
 * @details 切换当前的菜单栏
 * @param   curMenuBarId    菜单栏的id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::changeMenuBar(int curMenuBarId)
{
    switch (curMenuBarId) {
    case 0:
        pbShow = &bMainButtonShow;
        pButton = mainButton;
        pButtonGroup = mainButtonGroup;
        break;
    case 1:
        pbShow = &bAnalysisButtonShow;
        pButton = analysisButton;
        pButtonGroup = analysisButtonGroup;
        break;
    case 2:
        pbShow = &bImageButtonShow;
        pButton = imageButton;
        pButtonGroup = imageButtonGroup;
        break;
    case 3:
        pbShow = &bMediaButtonShow;
        pButton = mediaButton;
        pButtonGroup = mediaButtonGroup;
        break;
    case 5:
        pbShow = &bSettingsButtonShow;
        pButton = settingsButton;
        pButtonGroup = settingsButtonGroup;
        break;
    default:
        break;
    }
}


/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义按键事件
 * @param   e    按键事件指正
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space)
        return;

    if((*pbShow))
    {
        //上下按键切换选项
        if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)
        {
            int id = pButtonGroup->checkedId();
            pButton[id]->showLabel(false);

            if(e->key() == Qt::Key_Up)
                id = --id < 0 ? pButtonGroup->buttons().count()-1 : id;
            else if(e->key() == Qt::Key_Down)
                id = ++id > pButtonGroup->buttons().count()-1 ? 0 : id;
            pButton[id]->setChecked(true);
            pButton[id]->showLabel(true);
            pButton[id]->setFocus();
        }
        else if(e->key() == Qt::Key_Return)
            pButton[pButtonGroup->checkedId()]->click();
    }

    //Esc按键切换菜单栏的显示状态
    if(e->key() == Qt::Key_Escape)
    {
        if((*pbShow))
        {
            if(curMenuBarId != 0)
            {
                curMenuBarId = 0;
                closeMenuBar();
                changeMenuBar(curMenuBarId);
                showMenuBar();
            }
            else
                closeMenuBar();
        }
        else
            showMenuBar();
    }

    //    QWidget::keyPressEvent(e);

}

/**
 * @name    void mousePressEvent(QMouseEvent *e)
 * @details 鼠标点击事件,点击空白处关闭菜单栏
 * @param   e    鼠标点击事件指正
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::mousePressEvent(QMouseEvent *e)
{

    closeMenuBar();

    return QWidget::mousePressEvent(e);
}

/**
 * @name    bool eventFilter(QObject *watched, QEvent *event)
 * @details 过滤logoBtn的默认的key_space按键
 * @param   watched 产生事件的对象
 * @param   event   事件指针
 * @author  lee
 * @date    2018-11-15
**/
bool TMainPage::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (watched == satLogoBtn) {
            if(keyEvent->key() == Qt::Key_Space)
            {
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @name    void mainButtonGroupClicked(int id)
 * @details 主菜单栏的点击事件
 * @param   id  点击的图标id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::mainButtonGroupClicked(int id)
{
    if(id != 3)
    {
        //切换对应的菜单栏
        closeMenuBar();
        curMenuBarId = id+1;
        //        qWarning("curMenuBarId = %d", curMenuBarId);
        changeMenuBar(curMenuBarId);
        showMenuBar();
        return;
    }
    else
    {
        QMessageBox::information(this, "Button Clicked",
                                 tr("Button %1 is clicked!").arg(id));
    }
}

/**
 * @name    void analysisButtonGroupClicked(int id)
 * @details Analysis菜单栏的点击事件
 * @param   id  点击的图标id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::analysisButtonGroupClicked(int id)
{
    closeMenuBar();
    switch (id) {
    case 0:
    {
        //        //添加Spot测温

        Spot * spot = analysisManager->addSpot(/*GlobalParam::getSpotCount()*/);
        if(spot != NULL)
        {
            GlobalParam::addSpotCount();
//            if(spot->isHidden())
//                spot->move((width()-spot->width())/2, (height()-spot->height())/2);
            spot->show();
        }
        else
            QMessageBox::information(this, "Warning", "Spot num is out of range!");
        break;
    }
    case 1:
    {
        //        //添加Area测温
        Area * area = analysisManager->addArea(GlobalParam::getAreaCount());
        GlobalParam::addAreaCount();
        if(area->isHidden())
            area->move((width()-area->width())/2, (height()-area->height())/2);
        area->show();

        break;
    }
    case 2:
    {
        //        //添加Line测温
        Line * line = analysisManager->addLine();
        //        QMessageBox::information(this, "Add Spot",
        //                                 tr("Add a spot! \nNow has %1 spots!").arg(GlobalParam::getSpotCount()));
        if(line->isHidden())
            line->move(0, (height()-line->height())/2);
        line->show();

        break;
    }
    default:
        QMessageBox::information(this, "Analysis Button Clicked",
                                 tr("Analysis Button %1 is clicked!").arg(id));
        break;
    }
}

/**
 * @name    void imageButtonGroupClicked(int id)
 * @details Image菜单栏的点击事件
 * @param   id  点击的图标id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::imageButtonGroupClicked(int id)
{
    closeMenuBar();

    //显示对应的滑动选择窗口
    switch (id) {
    case 0:
    {
        SlideWidget *w = new SlideWidget;
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setTitle("Image Mode");
        w->setLButton("Cancel");
        w->setRButton("Ok");
        QStringList list;
        list.clear();
        list<<"IR"<<"CCD"<<"Merge"<<"Merge Plus"<<"Image Only";
        w->addItems(&list);
        w->setCurrentIndex(GlobalParam::getImageMode());
        w->move(this->pos().x()+width()-w->width(), this->pos().y()+(size().height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            GlobalParam::getFPGA()->fpga_imageMode_set(GlobalParam::getCurrentIndex());
            GlobalParam::setImageMode(GlobalParam::getCurrentIndex());
            qWarning("Image Mode: Ok");
        }
        else
            qWarning("Image Mode: Cancel");

        break;
    }
    case 1:
    {
        SlideWidget *w = new SlideWidget(0, 0, 30);
        w->setStyleSheet("background-color: rgb(0, 155, 155)");
        w->setTitle("Palette");
        w->setLButton("Close");
        w->setRButton("Ok");
        QStringList list;
        list<<"Iron"<<"Iron Inv"<<"RainBow"<<"Grey"<<"Grey Inv";
        w->addItems(&list);
        w->setCurrentIndex(GlobalParam::getPaletteMode());
        w->move(this->pos().x()+width()-w->width(), this->pos().y()+(size().height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            GlobalParam::getFPGA()->fpga_colorTable_set(GlobalParam::getCurrentIndex());
            GlobalParam::setPaletteMode(GlobalParam::getCurrentIndex());
            qWarning("Image Mode: Ok");
        }
        else
        {
            qWarning("Image Mode: Cancel");
        }

        break;
    }
    default:
        QMessageBox::information(this, "Image Button Clicked",
                                 tr("Image Button %1 is clicked!").arg(id));
        break;
    }

    showMenuBar();
}

/**
 * @name    void mediaButtonGroupClicked(int id)
 * @details Media菜单栏的点击事件
 * @param   id  点击的图标id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::mediaButtonGroupClicked(int id)
{
    QMessageBox::information(this, "Media Button Clicked",
                             tr("Media Button %1 is clicked!").arg(id));
}

/**
 * @name    void settingsButtonGroupClicked(int id)
 * @details Setting菜单栏的点击事件
 * @param   id  点击的图标id
 * @author  lee
 * @date    2018-11-15
**/
void TMainPage::settingsButtonGroupClicked(int id)
{
    closeMenuBar();

    switch (id) {
    case 0:
    {
        //打开Analysis Setting界面
        AnalysisSettingPage *a = new AnalysisSettingPage;
        a->move(0, 0);
        a->exec();
        break;
    }
    case 1:
    {
        //打开System Setting界面
        SystemSettingPage *a = new SystemSettingPage;
        a->move(0, 0);
        a->exec();
        break;
    }
    default:
        QMessageBox::information(this, "Settings Button Clicked",
                                 tr("Settings Button %1 is clicked!").arg(id));
        break;
    }

    showMenuBar();
}

void TMainPage::updateLabels()
{
    tempUnitLabel->setText(GlobalParam::getTempUnit() ? "°F" : "°C");
    emissValLabel->setText("Emiss : "+ QString::number(GlobalParam::getEmissivity(), 'f', 2));
    float distanceValue = GlobalParam::getDistance();
    if(GlobalParam::getLengthUnit())
        distanceValue = distanceValue * 0.3048;
    distValLabel->setText("Dist : "+ QString::number(distanceValue, 'f', 1));

    tempUnitLabel->adjustSize();
    emissValLabel->adjustSize();
    distValLabel->adjustSize();
}

void TMainPage::updateSpan()
{
    unsigned short span, level;
    GlobalParam::getFPGA()->fpgaLevelGet(&level);
    GlobalParam::getFPGA()->fpgaSpanGet(&span);

    float spanTemp = GlobalParam::getFPGA()->AdToTemp(span).temp;
    float levelTemp = GlobalParam::getFPGA()->AdToTemp(level).temp;

    float maxTemp = spanTemp + levelTemp;
    float minTemp = levelTemp;

//    qDebug("updateSpan>>>>\nlevelAD = 0x%X, spanAD = 0x%X\n\
//            spanTemp = %f, levelTemp = %f",
//    level, span, spanTemp, levelTemp);

    spanLevelMax->setText(QString("Max: ")
                          +QString::number(maxTemp, 'f', 1));
    spanLevelMin->setText(QString("Min: ")
                          +QString::number(minTemp, 'f', 1));
    spanLevelMax->adjustSize();
    spanLevelMin->adjustSize();
}
