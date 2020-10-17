#include "globalparampage.h"
#include <QFrame>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QMessageBox>
#include "basewidget/combobox.h"
#include "basewidget/spinbox.h"
#include <QFocusEvent>
#include "globalparam.h"
#include "basewidget/slidewidget.h"

/**
 * @name    GlobalParamPage(QWidget *parent)
 * @details 全局参数界面,实现了参数的修改和保存
 * @param   parent  父窗口
 * @author  lee
 * @date    2018-11-15
**/
GlobalParamPage::GlobalParamPage(QWidget *parent) :
    QDialog(parent)
{
    initView();
}

/**
 * @name    void initView()
 * @details 初始化界面显示
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParamPage::initView()
{
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setStyleSheet("color: rgb(255, 255, 255);\
                  background-color: rgb(0, 155, 155)");

                  m_title = new QLabel("Global Param.", this);
            m_leftBtn = new QPushButton("Back", m_title);
    m_rightBtn = new QPushButton("Save", m_title);
    m_leftBtn->setObjectName("leftBtn");
    m_rightBtn->setObjectName("rightBtn");
    m_title->setFocusPolicy(Qt::NoFocus);
    m_leftBtn->setFocusPolicy(Qt::NoFocus);
    m_rightBtn->setFocusPolicy(Qt::NoFocus);

    m_title->resize(SCREEN_WIDTH, 30);
    m_leftBtn->resize(60, 30);
    m_rightBtn->resize(m_leftBtn->size());
    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_rightBtn->move(SCREEN_WIDTH-m_rightBtn->width(), pos().y());

    QWidget *centralWidget = new QWidget(this);
    centralWidget->resize(SCREEN_WIDTH, 190);
    centralWidget->move(0, 30);

    m_emissSpinBox = new SpinBox;
    //    m_emissSpinBox->setFocus();
    m_emissSpinBox->setAlignment(Qt::AlignCenter);
    m_emissSpinBox->setSingleStep(0.01);
    m_emissSpinBox->setRange(0.01, 1.00);
    m_emissSpinBox->setDecimals(2);
    m_emissSpinBox->setValue(GlobalParam::getEmissivity());

    m_distSpinBox = new SpinBox;
    m_distSpinBox->setAlignment(Qt::AlignCenter);
    m_distSpinBox->setSingleStep(0.5);
    m_distSpinBox->setRange(0.5, 500.0);
    m_distSpinBox->setSuffix("m");
    m_distSpinBox->setDecimals(1);
    m_distSpinBox->setValue(GlobalParam::getDistance());

    m_ambiTSpinBox = new SpinBox;
    m_ambiTSpinBox->setAlignment(Qt::AlignCenter);
    m_ambiTSpinBox->setSingleStep(0.1);
    m_ambiTSpinBox->setRange(-40.0, 125.0);
    m_ambiTSpinBox->setSuffix("°C");
    m_ambiTSpinBox->setDecimals(1);
    m_ambiTSpinBox->setValue(GlobalParam::getAmbiTemp());

    m_reflTSpinBox = new SpinBox;
    m_reflTSpinBox->setAlignment(Qt::AlignCenter);
    m_reflTSpinBox->setSingleStep(0.1);
    m_reflTSpinBox->setRange(-40.0, 2000.0);
    m_reflTSpinBox->setSuffix("°C");
    m_reflTSpinBox->setDecimals(1);
    m_reflTSpinBox->setValue(GlobalParam::getReflTemp());


    m_humiSpinBox = new SpinBox;
    m_humiSpinBox->setAlignment(Qt::AlignCenter);
    m_humiSpinBox->setSingleStep(1);
    m_humiSpinBox->setRange(1, 99);
    m_humiSpinBox->setSuffix("%");
    m_humiSpinBox->setDecimals(0);
    m_humiSpinBox->setValue(GlobalParam::getHumidity());


    m_offsetSpinBox = new SpinBox;
    m_offsetSpinBox->setAlignment(Qt::AlignCenter);
    m_offsetSpinBox->setSingleStep(0.1);
    m_offsetSpinBox->setRange(-100.0, 100.0);
    m_offsetSpinBox->setSuffix("°C");
    m_offsetSpinBox->setDecimals(1);
    m_offsetSpinBox->setValue(GlobalParam::getOffset());


    m_backgroundComboBox = new ComboBox;
    m_backgroundComboBox->addItem("Hide");
    m_backgroundComboBox->addItem("Show");
    m_backgroundComboBox->setCurrentIndex(GlobalParam::getBackground());

    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->setHorizontalSpacing(50);
    mainLayout->setVerticalSpacing(2);
    mainLayout->addWidget(new QLabel("Emissivity: "), 0, 0);
    mainLayout->addWidget(m_emissSpinBox, 0, 2);\
    mainLayout->addWidget(new QLabel("Distance: "), 1, 0);
    mainLayout->addWidget(m_distSpinBox, 1, 2);
    mainLayout->addWidget(new QLabel("Ambi.Temp: "), 2, 0);
    mainLayout->addWidget(m_ambiTSpinBox, 2, 2);
    mainLayout->addWidget(new QLabel("Refl.Temp: "), 3, 0);
    mainLayout->addWidget(m_reflTSpinBox, 3, 2);
    mainLayout->addWidget(new QLabel("Humidity: "), 4, 0);
    mainLayout->addWidget(m_humiSpinBox, 4, 2);
    mainLayout->addWidget(new QLabel("Offset: "), 5, 0);
    mainLayout->addWidget(m_offsetSpinBox, 5, 2);
    mainLayout->addWidget(new QLabel("Background: "), 6, 0);

    mainLayout->addWidget(m_backgroundComboBox, 6, 2);

    connect(m_leftBtn, SIGNAL(clicked(bool)), this, SLOT(processEvent()));
    connect(m_rightBtn, SIGNAL(clicked(bool)), this, SLOT(processEvent()));

    connect(m_emissSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
    connect(m_distSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
    connect(m_ambiTSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
    connect(m_reflTSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
    connect(m_humiSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
    connect(m_offsetSpinBox, SIGNAL(clicked(SpinBox*)), this, SLOT(createSlideWindow(SpinBox*)));
}

/**
 * @name    void processEvent()
 * @details 处理标题栏按键事件
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParamPage::processEvent()
{
    QString objName = sender()->objectName();
    if(objName == "leftBtn")
        close();
    else if(objName == "rightBtn")
    {
        if(QMessageBox::Ok == QMessageBox::information(this, "Information", "Save ?", QMessageBox::Cancel, QMessageBox::Ok))
        {
            applyValue();
        }
    }
}

/**
 * @name    void createSlideWindow(SpinBox *p)
 * @details 创建滑动窗口进行参数设置
 * @param   点击的spinbox的控件指针
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParamPage::createSlideWindow(SpinBox *p)
{
    //读取当前spinbox的数值,并获取其取值范围
    int integerMin = p->minimum();
    int integerMax = p->maximum();
    //分割浮点数为整数部分和小数部分
    QString tmp = QString::number(p->value(), 'f', p->decimals()?p->decimals():1);
    QStringList splitList = tmp.split(".");
    int integerValue = splitList[0].toInt();
    int decimalValue = splitList[1].toInt();
    QStringList integerList;
    QStringList decimalsList;
    //为整数值时只使用一个滑动窗口
    int decimalsNum = p->decimals() ? (p->decimals() > 1 ? 99 : 9) : -1;

    for(int i=integerMin; i<=integerMax;i++)
        integerList<<QString::number(i);
    for(int i=0; i<=decimalsNum;i++)
        decimalsList<<QString("%1").arg(i, p->decimals(), 10, QChar('0'));
    //创建滑动窗口
    SlideWidget *w = new SlideWidget(0, 30, 30, GlobalParam::ValueType::VALUE);
    w->setStyleSheet("background-color: rgb(0, 155, 155)");
    w->setTitle("Change Value");
    w->setLButton("Cancel");
    w->setRButton("Ok");
    //添加整数滑动窗口和小数滑动窗口
    w->addItems(&integerList);
    w->addItems(&decimalsList, 1);
    //设置滑动窗口的当前数值
    w->setCurrentText(integerValue);
    w->setCurrentText(decimalValue, 1);
    w->move(this->pos().x()+(width()-w->width())/2, this->pos().y()+(height() - w->height())/2);
    if(w->exec() == QDialog::Accepted)
    {
        p->setValue(GlobalParam::getParamSettingValue());
    }
}

/**
 * @name    void applyValue()
 * @details 更新全局参数
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParamPage::applyValue()
{
    //            qWarning("Ok");
    GlobalParam::setEmissivity(m_emissSpinBox->value());
    GlobalParam::setDistance(m_distSpinBox->value());
    GlobalParam::setAmbiTemp(m_ambiTSpinBox->value());
    GlobalParam::setReflTemp(m_reflTSpinBox->value());
    GlobalParam::setHumidity(m_humiSpinBox->value());
    GlobalParam::setOffset(m_offsetSpinBox->value());
    GlobalParam::setBackground((GlobalParam::Background)m_backgroundComboBox->currentIndex());

    GlobalParam::getParentWidget()->updateLabels();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义Esc和回车键的功能
 * @param   e   按键事件
 * @author  lee
 * @date    2018-11-15
**/
void GlobalParamPage::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        m_leftBtn->click();
    else if(e->key() == Qt::Key_Return)
        m_rightBtn->click();
    else
        QDialog::keyPressEvent(e);
}


