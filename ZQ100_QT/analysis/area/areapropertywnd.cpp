#include "areapropertywnd.h"
#include "area.h"
#include "basewidget/titlebar.h"
#include "basewidget/combobox.h"

#define PROPERTYWND_WIDTH    280
#define PROPERTYWND_HEIGHT   150
#define PROPERTYWND_SIZE     QSize(PROPERTYWND_WIDTH, PROPERTYWND_HEIGHT)

/**
 * @name    AreaPropertyWnd(Area *area)
 * @details 获取Area的指针，并初始化窗口的显示和功能

 * @date    2018-12-21
**/
AreaPropertyWnd::AreaPropertyWnd(Area *area) : m_area(area)
{
    initView();
}

/**
 * @name    void initView()
 * @details 初始化窗口的显示和功能

 * @date    2018-12-21
**/
void AreaPropertyWnd::initView()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(true);
    setFixedSize(PROPERTYWND_SIZE);

    setStyleSheet(CHILDPAGE_STYLESHEET);
    move((SCREEN_WIDTH-width())/2+m_area->parentWidget()->pos().x(),
         (SCREEN_HEIGHT-height())/2+m_area->parentWidget()->pos().y());

    m_titleBar = new TitleBar(0, GlobalParam::TitleBarStyle::DOUBLE_BUTTON, 30, PROPERTYWND_WIDTH);
    m_titleBar->setText(QString("Area %1").arg(m_area->id()), "Back", "Save");

    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)), this, SLOT(on_clicked(GlobalParam::ButtonType,bool)));

    m_mainWidget = new QWidget;

    QLabel *displayLabel = new QLabel("Display:");
    displayCombobox = new ComboBox;
    displayCombobox->insertItem(0, "Hide");
    displayCombobox->insertItem(1, "Show");

    QLabel *maxShowLabel = new QLabel("Max:");
    maxShowCombobox = new ComboBox;
    maxShowCombobox->insertItem(0, "Off");
    maxShowCombobox->insertItem(1, "On");

    QLabel *minShowLabel = new QLabel("Min:");
    minShowCombobox = new ComboBox;
    minShowCombobox->insertItem(0, "Off");
    minShowCombobox->insertItem(1, "On");

    QLabel *avgShowLabel = new QLabel("Avg:");
    avgShowCombobox = new ComboBox;
    avgShowCombobox->insertItem(0, "Off");
    avgShowCombobox->insertItem(1, "On");

    QGridLayout *widgetLayout = new QGridLayout(m_mainWidget);
    widgetLayout->setHorizontalSpacing(50);
    widgetLayout->setVerticalSpacing(2);
    widgetLayout->addWidget(displayLabel, 0, 0);
    widgetLayout->addWidget(displayCombobox, 0, 2);
    widgetLayout->addWidget(maxShowLabel, 1, 0);
    widgetLayout->addWidget(maxShowCombobox, 1, 2);
    widgetLayout->addWidget(minShowLabel, 2, 0);
    widgetLayout->addWidget(minShowCombobox, 2, 2);
    widgetLayout->addWidget(avgShowLabel, 3, 0);
    widgetLayout->addWidget(avgShowCombobox, 3, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(m_mainWidget);

    connect(displayCombobox, SIGNAL(currentIndexChanged(int)),
            m_area, SLOT(setDisplay(int)));
    connect(maxShowCombobox, SIGNAL(currentIndexChanged(int)),
            m_area, SLOT(setMaxShow(int)));
    connect(minShowCombobox, SIGNAL(currentIndexChanged(int)),
            m_area, SLOT(setMinShow(int)));
    connect(avgShowCombobox, SIGNAL(currentIndexChanged(int)),
            m_area, SLOT(setAvgShow(int)));
}

/**
 * @name    void initStates(const AreaProperty areaProperty)
 * @details 更新属性控件的显示
 * @param   areaProperty    Area属性值
 * @date    2018-12-21
**/
void AreaPropertyWnd::initStates(const AreaProperty areaProperty)
{
    displayCombobox->setCurrentIndex(areaProperty.displayMode);
    maxShowCombobox->setCurrentIndex(areaProperty.maxShowMode);
    minShowCombobox->setCurrentIndex(areaProperty.minShowMode);
    avgShowCombobox->setCurrentIndex(areaProperty.avgShowMode);
}

/**
 * @name    void accept()
 * @details 重写accept事件，accept前更保存修改的属性
 * @date    2018-12-21
**/
void AreaPropertyWnd::accept()
{
    m_area->commitProperty();
    QDialog::accept();
}

/**
 * @name    void reject()
 * @details 重写reject事件，reject前回滚Area的属性
 * @date    2018-12-21
**/
void AreaPropertyWnd::reject()
{
    m_area->rollbackProperty();
    initStates(m_area->_getProperty());
    QDialog::reject();
}

/**
 * @name    void exec()
 * @details 重写exec事件，exec前更新Area的属性控件
 * @date    2018-12-21
**/
int AreaPropertyWnd::exec()
{
    initStates(m_area->_getProperty());
    return QDialog::exec();
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 重写按键事件，Escape键关闭窗口，Return键保存参数
 * @param   event   按键事件指针
 * @date    2018-12-21
**/
void AreaPropertyWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
        accept();
    else if(event->key() == Qt::Key_Escape)
        reject();
    else
        event->ignore();
}

/**
 * @name    void on_clicked(GlobalParam::ButtonType id, bool status)
 * @details 标题栏按键的响应槽
 * @param   id  触发按键的类型
 * @param   status  开关状态
 * @date    2018-12-21
**/
void AreaPropertyWnd::on_clicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
        reject();
    else if(id == GlobalParam::ButtonType::BUTTON_RIGHT)
        accept();
}

