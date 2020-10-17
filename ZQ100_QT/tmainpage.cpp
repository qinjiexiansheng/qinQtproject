#include "tmainpage.h"
#include "basewidget/menubutton.h"
#include "setting/analysissettingpage/analysissettingpage.h"
#include "setting/systemsettingpage/systemsettingpage.h"
#include "setting/analysissettingpage/comptemppage.h"
#include "analysis/analysismanager.h"
#include "analysis/analysisfuncpage.h"
#include "basewidget/slidewidget.h"
#include "basewidget/label.h"

#define DEF_KEY_OK      167
#define DEF_KEY_LEFT    163
#define DEF_KEY_UP      162
#define DEF_KEY_RIGHT   164
#define DEF_KEY_DOWN    165
#define DEF_KEY_S       160
//#define DEF_KEY_F       161
#define DEF_KEY_A       166
#define DEF_KEY_C       161

/**
 * @name    TMainPage(QWidget *parent) :
 * @details 主界面,实现多界面的切换显示功能
 * @param   parent  父窗口

 * @date    2018-11-15
**/
TMainPage::TMainPage(QWidget *parent) :
    QWidget(parent)
{
    move(0, 0);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    setObjectName("obj");

    setWindowFlags(Qt::FramelessWindowHint);

    setStyleSheet(MAINPAGE_STYLESHEET);

    GlobalParam::setParentWidget(this);

    analysisManager = new AnalysisManager(this);

#ifdef ARM
    //打开外部按键驱动
    m_fileKde = open("/dev/input/event0", O_RDONLY);
    if(m_fileKde < 0)
    {
        perror("open()");
    }
    //监听外部按键
    m_socketNotifier = new QSocketNotifier(m_fileKde, QSocketNotifier::Read, this);
    connect(m_socketNotifier, SIGNAL(activated(int)), this, SLOT(readKeyBoardData()));
#endif

    GlobalParam::getFPGA()->init();

    //初始化显示
    initMainPage();

    //显示时间
    QTimer *timeUpateTimer = new QTimer(this);
    connect(timeUpateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    timeUpateTimer->start(1000);
}

/**
 * @name    void initMainPage()
 * @details 初始化界面显示

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
    wifiLabel->hide();

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

    spanLevelMax = new Label(this);
    spanLevelMax->setFont(labelFont);
    spanLevelMax->setFixedSize(30, 20);
    spanLevelMax->setAlignment(Qt::AlignRight);

    spanLevelMin = new Label(this);
    spanLevelMin->setFont(labelFont);
    spanLevelMin->setFixedSize(30, 20);
    spanLevelMin->setAlignment(Qt::AlignRight);

    if(GlobalParam::getAdjustMode() == 0)
    {
        spanLevelMax->setStyleSheet("text-decoration:underline");
        spanLevelMin->setStyleSheet("text-decoration:underline");
    }
    else
    {
        spanLevelMax->setStyleSheet("");
        spanLevelMin->setStyleSheet("");
    }

    connect(spanLevelMax, SIGNAL(click()), this, SLOT(levelSpanClicked()));
    connect(spanLevelMin, SIGNAL(click()), this, SLOT(levelSpanClicked()));

    updateLevelSpan();

    spanLevelMax->move(SCREEN_WIDTH-spanLevelMax->width(),
                       SCREEN_HEIGHT*2/6-spanLevelMax->height()/2-30);
    spanLevelMin->move(SCREEN_WIDTH-spanLevelMin->width(),
                       SCREEN_HEIGHT*4/6-spanLevelMin->height()/2+30);

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

    if(GlobalParam::getAdjustMode() == 1)
        updateLevelSpan();

    updateWifiState();
}

/**
 * @name    void satLogoBtnClicked()
 * @details 响应logo点击事件

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
        case DEF_KEY_C:
            key = Qt::Key_Escape;
            break;
        case DEF_KEY_A:
            //打档？
            qWarning("*******************Shutter*******************");
            break;
//        case DEF_KEY_F:
//            //对焦
//            qWarning("*******************Focus*******************");
//            break;
        case DEF_KEY_S:
            //冻结
            qWarning("*******************Freeze*******************");
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

void TMainPage::levelSpanClicked()
{
    closeMenuBar();

    if(GlobalParam::getAdjustMode() != 0)
        return;
    Label *p = qobject_cast<Label *>(sender());
    SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::VALUE);
    int integerMin, integerMax;
    int decimalsNum = 9;
    QStringList integerList;
    QStringList decimalsList;
    float value = p->text().toFloat();

    //分割浮点数为整数部分和小数部分
    QString tmp = QString::number(value, 'f', 1);
    QStringList splitList = tmp.split(".");
    int integerValue = splitList[0].toInt();
    int decimalValue = splitList[1].toInt();

    if(p == spanLevelMax)
    {
        integerMin = (int)spanLevelMin->text().toFloat()+1;
        integerMax = 2000;
        w->setTitle("Max Temp");
    }
    else
    {
        integerMin = -40;
        integerMax = (int)spanLevelMax->text().toFloat()-1;
        w->setTitle("Min Temp");
    }

    //为整数值时只使用一个滑动窗口
    for(int i=integerMin; i<=integerMax;i++)
        integerList<<QString::number(i);
    for(int i=0; i<=decimalsNum;i++)
        decimalsList<<QString::number(i);
    //创建滑动窗口
    w->setStyleSheet(CHILDPAGE_STYLESHEET);
    w->setLButton("Cancel");
    w->setRButton("Ok");
    //添加整数滑动窗口和小数滑动窗口
    w->addItems(&integerList);
    w->addItems(&decimalsList, 1);
    //设置滑动窗口的当前数值
    w->setCurrentText(integerValue);
    w->setCurrentText(decimalValue, 1);
    w->move(0, this->pos().y()+(height() - w->height())/2);
    if(w->exec() == QDialog::Accepted)
    {
        p->setText(QString::number(GlobalParam::getParamSettingValue(), 'f', 1));
    }
}

/**
 * @name    void showMenuBar()
 * @details 显示菜单栏

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
    else
    {
        switch (e->key()) {
        case Qt::Key_Up:
        {
            qWarning("Span up !!!");
//            float span = abs(spanLevelMax->text().toFloat()) - abs(spanLevelMin->text().toFloat());
//            span = span ? span : 10.0;
//            spanLevelMax->setText(QString::number(spanLevelMax->text().toFloat()+0.1, 'f', 1));
//            spanLevelMin->setText(QString::number(spanLevelMax->text().toFloat()-span, 'f', 1));
            break;
        }
        case Qt::Key_Down:
            qWarning("Span down !!!");
            break;
        case Qt::Key_Left:
            qWarning("level down !!!");
            break;
        case Qt::Key_Right:
            qWarning("level up !!!");
            break;
        default:
            break;
        }
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
 * @param   e    鼠标点击事件指针

 * @date    2018-11-15
**/
void TMainPage::mousePressEvent(QMouseEvent *e)
{

    closeMenuBar();
    setFocus();

    return QWidget::mousePressEvent(e);
}

/**
 * @name    void mouseDoubleClickEvent(QMouseEvent *e)
 * @details 鼠标双击事件,保留，后续添加功能
 * @param   e    鼠标点击事件指针

 * @date    2018-12-18
**/
void TMainPage::mouseDoubleClickEvent(QMouseEvent *e)
{
//    AnalysisFuncPage *page = new AnalysisFuncPage;
//    page->move(0, (pos().y()+SCREEN_HEIGHT-page->height())/2);
    //    page->show();
    QWidget::mouseDoubleClickEvent(e);
}

/**
 * @name    void mouseMoveEvent(QMouseEvent *e)
 * @details 鼠标移动事件, 上下滑动改变LEVELSPAN
 * @param   e    鼠标点击事件指针

 * @date    2018-12-18
**/
void TMainPage::mouseMoveEvent(QMouseEvent *e)
{
//    spanLevelMax->setText(QString::number(spanLevelMax->text().toFloat()+0.1, 'f', 1));
    QWidget::mouseMoveEvent(e);
}

/**
 * @name    bool eventFilter(QObject *watched, QEvent *event)
 * @details 过滤logoBtn的默认的key_space按键
 * @param   watched 产生事件的对象
 * @param   event   事件指针

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
        Area * area = analysisManager->addArea(/*GlobalParam::getAreaCount()*/);
        if(area != NULL)
        {
            GlobalParam::addAreaCount();
//            if(area->isHidden())
//                area->move((width()-area->width())/2, (height()-area->height())/2);
            area->show();
        }
        else
            QMessageBox::information(this, "Warning", "Spot num is out of range!");
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
        w->setStyleSheet(CHILDPAGE_STYLESHEET);
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
        SlideWidget *w = new SlideWidget;
        w->setStyleSheet(CHILDPAGE_STYLESHEET);
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
    case 2:
    {
        SlideWidget *w = new SlideWidget;
        w->setStyleSheet(CHILDPAGE_STYLESHEET);
        w->setTitle("Adjust Mode");
        w->setLButton("Close");
        w->setRButton("Ok");
        QStringList list;
        list<<"Manual"<<"Auto";
        w->addItems(&list);
        w->setCurrentIndex(GlobalParam::getAdjustMode());
        w->move(this->pos().x()+width()-w->width(), this->pos().y()+(size().height() - w->height())/2);
        if(w->exec() == QDialog::Accepted)
        {
            GlobalParam::getFPGA()->fpga_adjustMode_set(GlobalParam::getCurrentIndex());
            GlobalParam::setAdjustMode(GlobalParam::getCurrentIndex());

            if(GlobalParam::getAdjustMode() == 0)
            {
                spanLevelMax->setStyleSheet("text-decoration:underline");
                spanLevelMin->setStyleSheet("text-decoration:underline");
            }
            else
            {
                spanLevelMax->setStyleSheet("");
                spanLevelMin->setStyleSheet("");
            }
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

/**
 * @name    void updateLabels()
 * @details 更新主界面的温度时间辐射率等参数显示

 * @date    2018-12-18
**/
void TMainPage::updateLabels()
{
    tempUnitLabel->setText(GlobalParam::getTempUnit() ? "°F" : "°C");
    emissValLabel->setText("Emiss : "+
                           QString::number(GlobalParam::getFPGA()->getTempSetup().Emiss, 'f', 2));
    float distanceValue = GlobalParam::getFPGA()->getTempSetup().Dist;
    qDebug()<<GlobalParam::getFPGA()->getTempSetup().Emiss;
    if(GlobalParam::getLengthUnit())
        distanceValue = distanceValue * 0.3048;
    distValLabel->setText("Dist : "+ QString::number(distanceValue, 'f', 1));

    tempUnitLabel->adjustSize();
    emissValLabel->adjustSize();
    distValLabel->adjustSize();
}

/**
 * @name    void updateSpan()
 * @details 更新主界面的levelspan的最大最小值

 * @date    2018-12-18
**/
void TMainPage::updateLevelSpan()
{
    unsigned short span, level;
    GlobalParam::getFPGA()->fpgaLevelGet(&level);
    GlobalParam::getFPGA()->fpgaSpanGet(&span);

//    float spanTemp = GlobalParam::getFPGA()->AdToTemp(span).temp;
//    float levelTemp = GlobalParam::getFPGA()->AdToTemp(level).temp;

//    float maxTemp = spanTemp + levelTemp;
//    float minTemp = levelTemp;

//    spanLevelMax->setText(QString("Max: ")
//                          +QString::number(maxTemp, 'f', 1));
//    spanLevelMin->setText(QString("Min: ")
//                          +QString::number(minTemp, 'f', 1));

    IrTempStru spanTemp = GlobalParam::getFPGA()->AdToTemp(span);
    IrTempStru levelTemp = GlobalParam::getFPGA()->AdToTemp(level);
    spanLevelMax->setText(QString::number(spanTemp.AD, 16));
    spanLevelMin->setText(QString::number(levelTemp.AD, 16));
}

/**
 * @name    void updateWifiState()
 * @details 更新主界面的wifi图标的显示

 * @date    2018-12-18
**/
void TMainPage::updateWifiState()
{
    int temp = m_curWifiState;
    m_curWifiState = GlobalParam::getCurrentWifiState();

    if(temp != m_curWifiState)
    {
        if(m_curWifiState == 0)
            wifiLabel->hide();
        else
            wifiLabel->show();
    }
}
