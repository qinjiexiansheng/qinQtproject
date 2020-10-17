#include "slidewidget.h"
#include "slidearea.h"

/**
 * @name    SlideWidget(QWidget *parent, int H_Spacing, int V_Spacing)
 * @details 可配置为单或双滑动窗口的的Dialog对话框, 主要用于全局参数的界面等
 * @param   parent  父窗口指针
 * @param   H_Spacing   水平间隙
 * @param   V_Spacing   垂直间隙

 * @date    2018-11-15
**/
SlideWidget::SlideWidget(QWidget *parent, int H_Spacing, int V_Spacing, GlobalParam::ValueType valueType)
    : QDialog(parent)
{
    m_hSpacing = H_Spacing;
    m_vSpacing = V_Spacing;
    m_currentValueType = valueType;

    initView();
}

/**
 * @name    void initView()
 * @details 初始化控件界面

 * @date    2018-11-15
**/
void SlideWidget::initView()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    m_title = new QLabel("Title");
    m_LButton = new QPushButton("Cancel");
    m_RButton = new QPushButton("Ok");

    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFrameStyle(QFrame::StyledPanel);

    m_title->setFocusPolicy(Qt::NoFocus);
    m_LButton->setFocusPolicy(Qt::NoFocus);
    m_RButton->setFocusPolicy(Qt::NoFocus);


    //新建两个滑动窗口
    m_area1 = new SlideArea(this, m_hSpacing, m_vSpacing);
    m_area2 = new SlideArea(this, m_hSpacing, m_vSpacing);

    //滑动窗口之间的间隔
    m_dot = new QLabel("·");
    m_dot->setAlignment(Qt::AlignCenter);
    m_dot->setScaledContents(true);
    m_dot->adjustSize();
    m_dot->setFixedSize(m_dot->size());
    m_dot->setFocusPolicy(Qt::NoFocus);

    m_title->setFixedHeight(m_vSpacing);
    m_LButton->setFixedHeight(m_vSpacing);
    m_RButton->setFixedHeight(m_vSpacing);

    hide();

    connect(m_LButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(m_RButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

/**
 * @name    void adjustLayout()
 * @details 调整各个控件的大小和位置

 * @date    2018-11-15
**/
void SlideWidget::adjustLayout()
{
    //两个滑动窗口都无数据时直接退出
    if(m_area1->isEmpty() && m_area2->isEmpty())
        return;

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->setMargin(0);
    viewLayout->setSpacing(0);
    //只设置了一个窗口数据时为单滑动窗口,
    //设置了两个窗口数据时为双滑动窗口,并显示窗口的间隔文本
    if(!m_area1->isEmpty())
        viewLayout->addWidget(m_area1);
    if(!m_area1->isEmpty() && !m_area2->isEmpty())
        viewLayout->addWidget(m_dot);
    if(!m_area2->isEmpty())
        viewLayout->addWidget(m_area2);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setMargin(0);
    btnLayout->setSpacing(0);
    btnLayout->addWidget(m_LButton);
    btnLayout->addWidget(m_RButton);

    delete this->layout();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_title);
    mainLayout->addLayout(viewLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);

    setFixedSize(mainLayout->sizeHint());

    show();
}

//void LDoubleSlideWidget::addItem(QString option, int areaID)
//{
//    if(areaID == 0)
//    {
//        m_area1->addItem(option);
//    }
//    else
//    {
//        m_area2->addItem(option);
//    }
//    adjustLayout();
//}

/**
 * @name    void addItems(QStringList *options, int areaID)
 * @details 为指定的滑动窗口添加数据
 * @param   options 数据列表
 * @param   areaID  滑动窗口ID

 * @date    2018-11-15
**/
void SlideWidget::addItems(QStringList *options, int areaID)
{
    if(areaID == 0)
    {
        m_area1->addItems(options);
    }
    else
    {
        //窗口常用语显示小数,需要提供m_decimals变量
        m_area2->addItems(options);
        if(options->count() > 10)
            m_decimals = 2;
        else
            m_decimals = 1;
    }
    adjustLayout();
}

/**
 * @name    void setCurrentIndex(int index, int areaID)
 * @details 设置滑动窗口的当前索引
 * @param   index   索引值
 * @param   areaID  滑动窗口ID

 * @date    2018-11-15
**/
void SlideWidget::setCurrentIndex(int index, int areaID)
{
    if(areaID == 0)
    {
        m_area1->setCurrentIndex(index);
    }
    else
    {
        m_area2->setCurrentIndex(index);
    }
}

/**
 * @name   int getCurrentIndex(int areaID) const
 * @details 获取滑动窗口的当前数据
 * @param   areaID  滑动窗口ID
 * @return  滑动窗口的当前数据

 * @date    2018-11-15
**/
int SlideWidget::getCurrentIndex(int areaID) const
{
    if(areaID == 0)
    {
        return m_area1->getCurrentIndex();
    }
    else
    {
        return m_area2->getCurrentIndex();
    }
}

/**
 * @name    void setCurrentText(int value, int areaID)
 * @details 设置滑动窗口的当前数值
 * @param   value   数值
 * @param   areaID  滑动窗口ID

 * @date    2018-11-15
**/
void SlideWidget::setCurrentText(int value, int areaID)
{
    if(areaID == 0)
    {
        m_area1->setCurrentText(value);
    }
    else
    {
        m_area2->setCurrentText(value);
    }
}

/**
 * @name    void setCurrentText(QString text, int areaID)
 * @details 设置滑动窗口的当前文本
 * @param   text   文本字符串
 * @param   areaID  滑动窗口ID

 * @date    2018-11-15
**/
void SlideWidget::setCurrentText(QString text, int areaID)
{
    if(areaID == 0)
    {
        m_area1->setCurrentText(text);
    }
    else
    {
        m_area2->setCurrentText(text);
    }
}

/**
 * @name    QString getCurrentText(int areaID) const
 * @details 获取滑动窗口的当前数据文本
 * @param   areaID  滑动窗口ID
 * @return  滑动窗口的当前数据文本

 * @date    2018-11-15
**/
QString SlideWidget::getCurrentText(int areaID) const
{
    if(areaID == 0)
    {
        return m_area1->getCurrentText();
    }
    else
    {
        return m_area2->getCurrentText();
    }
}

/**
 * @name    QString getCurrentText(int areaID) const
 * @details 获取滑动窗口的当前数据文本
 * @param   areaID  滑动窗口ID
 * @return  滑动窗口的当前数据文本

 * @date    2018-11-15
**/
QString SlideWidget::getText(int index, int areaID) const
{
    if(areaID == 0)
    {
        return m_area1->getText(index);
    }
    else
    {
        return m_area2->getText(index);
    }
}

/**
 * @name    void keyPressEvent(QKeyEvent *e)
 * @details 自定义回车和Esc键的功能
 * @param   e  按键事件

 * @date    2018-11-15
**/
void SlideWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        reject();
    else if(e->key() == Qt::Key_Return)
        accept();
    else
        e->accept();
}

/**
 * @name    void accept()
 * @details 重写accept事件,保存滑动窗口的数值

 * @date    2018-11-15
**/
void SlideWidget::accept()
{
    switch (m_currentValueType) {
    case GlobalParam::ValueType::VALUE:
    {
        QString value = QString("%1.%2")
                .arg(m_area1->getCurrentText().toInt())
                .arg(m_area2->getCurrentText().toInt(), m_decimals, 10, QChar('0'));
        //临时存储滑动窗口的数值
        GlobalParam::setParamSettingValue(value.toFloat());

        break;
    }
    case GlobalParam::ValueType::TIME:
    {
        int h = m_area1->getCurrentText().toInt();
        int m = m_area2->getCurrentText().toInt();
        QString time = QTime(h, m).toString("hh:mm:ss");
#ifdef PC
        QString cmd = QString("date -s %1")
                .arg(time);
#else
        QString cmd = QString("/mnt/sd/busybox date -s %1")
                .arg(time);
#endif

        QProcess *pro = new QProcess(this);
        pro->execute(cmd);
#ifdef PC
        pro->execute("hwclock -w");
#else
        pro->execute("/mnt/sd/busybox hwclock -w");
#endif


        break;
    }
    case GlobalParam::ValueType::TIMEZONE:
    {
        QString cmd = QString("timedatectl set-timezone %1")
                .arg(m_area1->getCurrentText());
        QProcess *pro = new QProcess(this);
        pro->execute(cmd);
        GlobalParam::setTimeZoneTemp(m_area1->getCurrentText());
        break;
    }
    case GlobalParam::ValueType::SCREENSAVER:
    {
        GlobalParam::setScreenSaver(m_area1->getCurrentText());
        //设置ScreenSaverd...
        break;
    }
    case GlobalParam::ValueType::POWEROFF:
    {
        GlobalParam::setPowerOff(m_area1->getCurrentText());
        //设置poweroff...
        break;
    }
    case GlobalParam::ValueType::TVOUTMODE:
    {
        //临时存储滑动窗口的数值
        GlobalParam::setTVOutMode(m_area1->getCurrentText());
        break;
    }
    case GlobalParam::ValueType::USBMODE:
    {
        //临时存储滑动窗口的数值
        GlobalParam::setUSBMode(m_area1->getCurrentText());
        break;
    }
    case GlobalParam::ValueType::MULTIFUNCKEY:
    {
        //临时存储滑动窗口的数值
        GlobalParam::setMultifuncKey(m_area1->getCurrentText());
        break;
    }
    default:
    {
        //临时存储滑动窗口的数值
        GlobalParam::setCurrentIndex(m_area1->getCurrentIndex());
        break;
    }
    }
    QDialog::accept();
}

/**
 * @name    void setTitle(QString str)
 * @details 设置标题文本
 * @param   str 显示文本

 * @date    2018-11-15
**/
void SlideWidget::setTitle(QString str)
{
    m_title->setText(str);
}

/**
 * @name    void setLButton(QString str)
 * @details 设置左按键文本
 * @param   str 显示文本

 * @date    2018-11-15
**/
void SlideWidget::setLButton(QString str)
{
    m_LButton->setText(str);
}

/**
 * @name    void setRButton(QString str)
 * @details 设置右按键文本
 * @param   str 显示文本

 * @date    2018-11-15
**/
void SlideWidget::setRButton(QString str)
{
    m_RButton->setText(str);
}

/**
 * @name    void setSeparatorText(QString str)
 * @details 设置分隔符的符号
 * @param   str 符号

 * @date    2018-11-15
**/
void SlideWidget::setSeparatorText(QString str)
{
    m_dot->setText(str);
}

/**
 * @name    void setValueType(GlobalParam::ValueType valueType)
 * @details 设置滑动窗口操作的数据类型
 * @param   valueType 操作的数据类型

 * @date    2018-11-15
**/
void SlideWidget::setValueType(GlobalParam::ValueType valueType)
{
    m_currentValueType = valueType;
}

/**
 * @name    void show()
 * @details 当未设置数据时,不显示窗口

 * @date    2018-11-15
**/
void SlideWidget::show()
{
    if(m_area1->isEmpty() && m_area2->isEmpty())
    {
        qWarning("Empty!");
        return;
    }
    QDialog::show();
}

