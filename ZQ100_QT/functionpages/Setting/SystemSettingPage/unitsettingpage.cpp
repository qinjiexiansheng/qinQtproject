#include "unitsettingpage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include "basewidget/switchbutton.h"
#include "globalparam.h"

UnitSettingPage::UnitSettingPage(QWidget *parent) : QDialog(parent)
{
    initView();
}

void UnitSettingPage::initView()
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    QLabel *title = new QLabel("Unit Setting");
    title->setFont(QFont(font().family(), -1, QFont::Bold));
    title->setAlignment(Qt::AlignCenter);
    title->setFocusPolicy(Qt::NoFocus);
    title->setFixedHeight(30);

    QWidget *centralWidget = new QWidget;

    m_lengthSwitch = new SwitchButton(0, "Meter", "Foot");
    m_tempSwitch = new SwitchButton(0, "°C", "°F");

    m_lengthSwitch->setFocus();

    updateLabels();

    QGridLayout *widgetLayout = new QGridLayout(centralWidget);
    widgetLayout->addWidget(new QLabel("Length: "), 0, 0);
    widgetLayout->addWidget(m_lengthSwitch, 0, 1);
    widgetLayout->addWidget(new QLabel("Temp: "), 1, 0);
    widgetLayout->addWidget(m_tempSwitch, 1, 1);

    QPushButton *btn1 = new QPushButton("Cancel");
    QPushButton *btn2 = new QPushButton("Ok");

    btn1->setFocusPolicy(Qt::NoFocus);
    btn2->setFocusPolicy(Qt::NoFocus);
    btn1->setFixedHeight(30);
    btn2->setFixedHeight(btn1->height());


    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(0);
    bottomLayout->addWidget(btn1);
    bottomLayout->addWidget(btn2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(title);
    mainLayout->addWidget(centralWidget);
    mainLayout->addLayout(bottomLayout);

    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

void UnitSettingPage::updateLabels()
{
//    //qDebug()<<GlobalParam::getLengthUnit();
//    //qDebug()<<GlobalParam::getTempUnit();

    m_lengthSwitch->setState(GlobalParam::getLengthUnit());
    m_tempSwitch->setState(GlobalParam::getTempUnit());
}

void UnitSettingPage::accept()
{
    GlobalParam::setLengthUnit(m_lengthSwitch->getState()?1:0);
    GlobalParam::setTempUnit(m_tempSwitch->getState()?1:0);

//    //qDebug()<<m_lengthSwitch->getState()<<","<<GlobalParam::getLengthUnit();
//    //qDebug()<<m_tempSwitch->getState()<<","<<GlobalParam::getTempUnit();

    GlobalParam::getParentWidget()->updateLabels();

    QDialog::accept();
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义回车和Esc键的功能
 * @param   e  按键事件
 * @author  lee
 * @date    2018-11-21
**/
void UnitSettingPage::keyPressEvent(QKeyEvent *e)
{
    qWarning("UnitSettingPage");
    if(e->key() == Qt::Key_Escape)
        reject();
    else if(e->key() == Qt::Key_Return)
        accept();
    else
        e->accept();
}
