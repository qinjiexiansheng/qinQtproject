#include "spotpropertywnd.h"
#include "spot.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include "basewidget/titlebar.h"
#include "basewidget/spinbox.h"
#include "basewidget/combobox.h"


SpotPropertyWnd::SpotPropertyWnd(Spot *spot) : m_spot(spot)
{

    initView();
}

void SpotPropertyWnd::initView()
{
//    setWindowFlags(Qt::FramelessWindowHint);
    //    setAttribute(Qt::WA_DeleteOnClose,true);
    setModal(true);
    setFixedSize(280, 200);

    setStyleSheet("background-color: rgb(0, 155, 155)");
    move((SCREEN_WIDTH-width())/2+m_spot->parentWidget()->pos().x(),
         (SCREEN_HEIGHT-height())/2+m_spot->parentWidget()->pos().y());

    m_titleBar = new TitleBar(0, GlobalParam::TitleBarStyle::DOUBLE_BUTTON, 30, 280);
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
    posCombobox = new ComboBox;
    posCombobox->insertItem(0, "Off");
    posCombobox->insertItem(1, "On");

    QLabel *tempLabel = new QLabel("Temp:");
    tempCombobox = new ComboBox;
    tempCombobox->insertItem(0, "Off");
    tempCombobox->insertItem(1, "On");

    QLabel *backgroundLabel = new QLabel("Background:");
    backgroundCombobox = new ComboBox;
    backgroundCombobox->insertItem(0, "Hide");
    backgroundCombobox->insertItem(1, "Show");

    QLabel *alarmLabel = new QLabel("Alarm:");
    alarmCombobox = new ComboBox;
    alarmCombobox->insertItem(0, "Off");
    alarmCombobox->insertItem(1, "Above");
    alarmCombobox->insertItem(2, "Below");
    alarmCombobox->insertItem(3, "Equal");

    QLabel *alarmTempLabel = new QLabel("Alarm Temp:");
    alarmTempSpinBox = new SpinBox;
    alarmTempSpinBox->setAlignment(Qt::AlignCenter);
    alarmTempSpinBox->setSingleStep(0.1);
    alarmTempSpinBox->setRange(-40.0, 2000.0);
    alarmTempSpinBox->setDecimals(1);

    setStates(m_property);

    connect(displayCombobox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setDisplayState(int)));

    QGridLayout *widgetLayout = new QGridLayout(m_mainWidget);
    widgetLayout->setHorizontalSpacing(50);
    widgetLayout->setVerticalSpacing(2);
    widgetLayout->addWidget(displayLabel, 0, 0);
    widgetLayout->addWidget(displayCombobox, 0, 2);
    widgetLayout->addWidget(modeLabel, 1, 0);
    widgetLayout->addWidget(modeCombobox, 1, 2);
    widgetLayout->addWidget(tempLabel, 2, 0);
    widgetLayout->addWidget(tempCombobox, 2, 2);
    widgetLayout->addWidget(posLabel, 3, 0);
    widgetLayout->addWidget(posCombobox, 3, 2);
    widgetLayout->addWidget(backgroundLabel, 4, 0);
    widgetLayout->addWidget(backgroundCombobox, 4, 2);
    widgetLayout->addWidget(alarmLabel, 5, 0);
    widgetLayout->addWidget(alarmCombobox, 5, 2);
    widgetLayout->addWidget(alarmTempLabel, 6, 0);
    widgetLayout->addWidget(alarmTempSpinBox, 6, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(m_mainWidget);
}

void SpotPropertyWnd::on_clicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
        reject();
    else if(id == GlobalParam::ButtonType::BUTTON_RIGHT)
        accept();
}

void SpotPropertyWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
        accept();
    else if(event->key() == Qt::Key_Escape)
        reject();
    else
        event->ignore();
}

void SpotPropertyWnd::accept()
{
    QDialog::accept();
}

void SpotPropertyWnd::setStates(const SpotProperty &spotProperty)
{
    displayCombobox->setCurrentIndex(spotProperty.displayIndex);
    modeCombobox->setCurrentIndex(spotProperty.modeIndex);
    posCombobox->setCurrentIndex(spotProperty.posIndex);
    tempCombobox->setCurrentIndex(spotProperty.tempIndex);
    backgroundCombobox->setCurrentIndex(spotProperty.backgroundIndex);
    alarmCombobox->setCurrentIndex(spotProperty.alarmModeIndex);
    alarmTempSpinBox->setValue(spotProperty.alarmTempValue);

    m_property = spotProperty;
}

void SpotPropertyWnd::setDisplayState(int val)
{
//    qWarning("....");
    if(val == 0)
        m_spot->hide();
    else
        m_spot->show();
}
