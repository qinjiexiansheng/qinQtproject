#include "spotpropertywnd.h"
#include "spot.h"
#include "basewidget/titlebar.h"
#include "basewidget/spinbox.h"
#include "basewidget/combobox.h"

#define PROPERTYWND_WIDTH    280
#define PROPERTYWND_HEIGHT   200
#define PROPERTYWND_SIZE     QSize(PROPERTYWND_WIDTH, PROPERTYWND_HEIGHT)

/**
 * @name    SpotPropertyWnd(Spot *spot)
 * @details 获取Spot的指针，并初始化窗口的显示和功能

 * @date    2018-12-21
**/
SpotPropertyWnd::SpotPropertyWnd(Spot *spot) : m_spot(spot)
{
    initView();
}

/**
 * @name    void initView()
 * @details 初始化窗口的显示和功能

 * @date    2018-12-21
**/
void SpotPropertyWnd::initView()
{
    setWindowFlags(Qt::FramelessWindowHint);
    //    setAttribute(Qt::WA_DeleteOnClose,true);
    setModal(true);
    setFixedSize(PROPERTYWND_SIZE);

    setStyleSheet(CHILDPAGE_STYLESHEET);
    move((SCREEN_WIDTH-width())/2+m_spot->parentWidget()->pos().x(),
         (SCREEN_HEIGHT-height())/2+m_spot->parentWidget()->pos().y());

    m_titleBar = new TitleBar(0, GlobalParam::TitleBarStyle::DOUBLE_BUTTON, 30, PROPERTYWND_WIDTH);
    m_titleBar->setText(QString("Spot %1").arg(m_spot->id()), "Back", "Save");

    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)), this, SLOT(on_clicked(GlobalParam::ButtonType,bool)));

    m_mainWidget = new QWidget;

    QLabel *displayLabel = new QLabel("Display:");
    displayCombobox = new ComboBox;
    displayCombobox->insertItem(0, "Hide");
    displayCombobox->insertItem(1, "Show");

    QLabel *modeLabel = new QLabel("Mode:");
    modeCombobox = new ComboBox;
    modeCombobox->insertItem(0, "Manual");
    modeCombobox->insertItem(1, "Max");
    modeCombobox->insertItem(2, "Min");

    QLabel *posLabel = new QLabel("Position:");
    posShowCombobox = new ComboBox;
    posShowCombobox->insertItem(0, "Off");
    posShowCombobox->insertItem(1, "On");

    QLabel *tempLabel = new QLabel("Temp:");
    tempShowCombobox = new ComboBox;
    tempShowCombobox->insertItem(0, "Off");
    tempShowCombobox->insertItem(1, "On");

    QLabel *backgroundLabel = new QLabel("Background:");
    backgroundCombobox = new ComboBox;
    backgroundCombobox->insertItem(0, "Hide");
    backgroundCombobox->insertItem(1, "Show");

    QLabel *alarmLabel = new QLabel("Alarm:");
    alarmModeCombobox = new ComboBox;
    alarmModeCombobox->insertItem(0, "Off");
    alarmModeCombobox->insertItem(1, "Above");
    alarmModeCombobox->insertItem(2, "Below");
    alarmModeCombobox->insertItem(3, "Equal");

    QLabel *alarmTempLabel = new QLabel("Alarm Temp:");
    alarmTempSpinBox = new SpinBox;
    alarmTempSpinBox->setAlignment(Qt::AlignCenter);
    alarmTempSpinBox->setSingleStep(0.1);
    alarmTempSpinBox->setRange(-40.0, 2000.0);
    alarmTempSpinBox->setDecimals(1);

    QGridLayout *widgetLayout = new QGridLayout(m_mainWidget);
    widgetLayout->setHorizontalSpacing(50);
    widgetLayout->setVerticalSpacing(2);
    widgetLayout->addWidget(displayLabel, 0, 0);
    widgetLayout->addWidget(displayCombobox, 0, 2);
    widgetLayout->addWidget(modeLabel, 1, 0);
    widgetLayout->addWidget(modeCombobox, 1, 2);
    widgetLayout->addWidget(tempLabel, 2, 0);
    widgetLayout->addWidget(tempShowCombobox, 2, 2);
    widgetLayout->addWidget(posLabel, 3, 0);
    widgetLayout->addWidget(posShowCombobox, 3, 2);
    widgetLayout->addWidget(backgroundLabel, 4, 0);
    widgetLayout->addWidget(backgroundCombobox, 4, 2);
    widgetLayout->addWidget(alarmLabel, 5, 0);
    widgetLayout->addWidget(alarmModeCombobox, 5, 2);
    widgetLayout->addWidget(alarmTempLabel, 6, 0);
    widgetLayout->addWidget(alarmTempSpinBox, 6, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(m_mainWidget);

    connect(displayCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setDisplay(int)));
    connect(modeCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setMode(int)));
    connect(tempShowCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setTempShow(int)));
    connect(posShowCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setPosShow(int)));
    connect(backgroundCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setBackground(int)));
    connect(alarmModeCombobox, SIGNAL(currentIndexChanged(int)),
            m_spot, SLOT(setAlarmMode(int)));
    connect(alarmTempSpinBox, SIGNAL(textChanged(QString)),
            this, SLOT(sendAlarmTemp(QString)));
}

/**
 * @name    void on_clicked(GlobalParam::ButtonType id, bool status)
 * @details 标题栏按键的响应槽
 * @param   id  触发按键的类型
 * @param   status  开关状态
 * @date    2018-12-21
**/
void SpotPropertyWnd::on_clicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
        reject();
    else if(id == GlobalParam::ButtonType::BUTTON_RIGHT)
        accept();
}

/**
 * @name    void sendAlarmTemp(QString temp)
 * @details 报警温度修改时，设置Spot的属性
 * @date    2018-12-21
**/
void SpotPropertyWnd::sendAlarmTemp(QString temp)
{
    m_spot->setAlarmTemp(temp.toFloat());
}


/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 重写按键事件，Escape键关闭窗口，Return键保存参数
 * @param   event   按键事件指针
 * @date    2018-12-21
**/
void SpotPropertyWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
        accept();
    else if(event->key() == Qt::Key_Escape)
        reject();
    else
        event->ignore();
}

/**
 * @name    void reject()
 * @details 重写reject事件，reject前回滚Spot的属性
 * @date    2018-12-21
**/
void SpotPropertyWnd::reject()
{
    m_spot->rollbackProperty();
    initStates(m_spot->_getProperty());
    QDialog::reject();
}

/**
 * @name    void exec()
 * @details 重写exec事件，exec前更新Spot的属性控件
 * @date    2018-12-21
**/
int SpotPropertyWnd::exec()
{
    initStates(m_spot->_getProperty());
    return QDialog::exec();
}

/**
 * @name    void accept()
 * @details 重写accept事件，accept前更保存修改的属性
 * @date    2018-12-21
**/
void SpotPropertyWnd::accept()
{
    m_spot->commitProperty();
    QDialog::accept();
}

/**
 * @name    void initStates(const SpotProperty spotProperty)
 * @details 更新属性控件的显示
 * @param   spotProperty    Spot属性值
 * @date    2018-12-21
**/
void SpotPropertyWnd::initStates(const SpotProperty spotProperty)
{
    displayCombobox->setCurrentIndex(spotProperty.displayMode);
    modeCombobox->setCurrentIndex(spotProperty.analysisMode);
    posShowCombobox->setCurrentIndex(spotProperty.posShowMode);
    tempShowCombobox->setCurrentIndex(spotProperty.tempShowMode);
    backgroundCombobox->setCurrentIndex(spotProperty.backgroundMode);
    alarmModeCombobox->setCurrentIndex(spotProperty.alarmMode);
    alarmTempSpinBox->setValue(spotProperty.alarmTempVal);
}
