#include "wifimanagerpage.h"
#include "basewidget/titlebar.h"

#ifdef PC
#define WIFI_CONFIG_FILE "/home/osrc/lee/test.config"
#else
#define WIFI_CONFIG_FILE "/etc/hostapd.conf"
#define WIFI_START_SCRIPT "/mnt/sd/hostup.sh"
#define WIFI_STOP_SCRIPT "/mnt/sd/hostdown.sh"
#endif

/**
 * @name    WifiManagerPage(QWidget *parent)
 * @details wifi管理界面，用于设置wifi账号密码和启停wifi
 * @param   parent 父窗口指针
 * @author  lee
 * @date    2018-12-21
**/
WifiManagerPage::WifiManagerPage(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowFlags(Qt::FramelessWindowHint);

    pro = new QProcess(this);

    m_keyboard = new KeyBoard;
    m_keyboard->installEventFilter(this);
    m_keyboard->move(0+160-100+65,0+120-100+24);

    m_titleBar = new TitleBar(this, GlobalParam::TitleBarStyle::SINGLE_BUTTON, 40, SCREEN_WIDTH);
    m_titleBar->setText("Wifi Manager", "Back");
    connect(m_titleBar, SIGNAL(clicked(GlobalParam::ButtonType,bool)),
            this,SLOT(on_titleBarClicked(GlobalParam::ButtonType,bool)));

    centralWidget = new QWidget;
    centralWidget->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT-m_titleBar->height());

    m_wifiNameEdit = new QLineEdit;
    m_wifiPasswdEdit = new QLineEdit;

    m_wifiNameEdit->installEventFilter(this);
    m_wifiPasswdEdit->installEventFilter(this);
    m_wifiPasswdEdit->setEchoMode(QLineEdit::Password);

    readWifi();

    m_wifiNameEdit->setText(m_curWifiName.isEmpty() ? "PC_WIFI" : m_curWifiName);
    m_wifiPasswdEdit->setText(m_curWifiPasswd.isEmpty() ? "PC_PASSWD" : m_curWifiPasswd);

    //    connect(m_wifiNameEdit

    m_startBtn = new QPushButton("Start");
    m_stopBtn = new QPushButton("Stop");
    m_startBtn->setFixedSize(150, 30);
    m_stopBtn->setFixedSize(m_startBtn->size());
    m_startBtn->installEventFilter(this);
    m_stopBtn->installEventFilter(this);

    QButtonGroup *btnGroup = new QButtonGroup;
    btnGroup->addButton(m_startBtn, 0);
    btnGroup->addButton(m_stopBtn, 1);

    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(btnGroupClicked(int)));

    QGridLayout *widgetLayout = new QGridLayout(centralWidget);
    widgetLayout->addWidget(new QLabel("Wifi Name: "), 1, 0);
    widgetLayout->addWidget(m_wifiNameEdit, 1, 1);
    widgetLayout->addWidget(new QLabel("Wifi Key: "), 2, 0);
    widgetLayout->addWidget(m_wifiPasswdEdit, 2, 1);
    widgetLayout->addWidget(m_startBtn, 3, 1);
    widgetLayout->addWidget(m_stopBtn, 4, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(centralWidget);
}

/**
 * @name    void keyPressEvent(QKeyEvent *event)
 * @details 按键事件，保留
 * @param   event 按键事件指针
 * @author  lee
 * @date    2018-12-21
**/
void WifiManagerPage::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        reject();
        break;
        //    case Qt::Key_Up:
        //    case Qt::Key_Down:
        //        break;
        //    case Qt::Key_Left:
        //        m_wifiNameEdit->setText(m_wifiNameEdit->text()+"1");
        //        break;
        //    case Qt::Key_Right:
        //        m_wifiNameEdit->setText(m_wifiNameEdit->text().left(m_wifiNameEdit->text().length()-1));
        //        break;
    default:
        event->ignore();
        return;
    }
}

/**
 * @name    bool eventFilter(QObject *watched, QEvent *event)
 * @details 事件过滤器，自定义按键和鼠标点击事件
 * @param   watched 监测的对象
 * @param   event 事件指针
 * @author  lee
 * @date    2018-12-21
**/
bool WifiManagerPage::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == m_wifiNameEdit || watched == m_wifiPasswdEdit)
        {
            m_keyboard->setTarget(qobject_cast<QLineEdit *>(watched));
            if(m_keyboard->isHidden())
                m_keyboard->show();
            return true;
        }
    }

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = (QKeyEvent*)event;
        if(ke->key() == Qt::Key_Escape)
        {
            if(watched == m_keyboard)
                m_keyboard->hide();
            else
                reject();
            return true;
        }
        else if(ke->key() == Qt::Key_Return)
        {
            if(watched == m_wifiNameEdit || watched == m_wifiPasswdEdit)
            {
                m_keyboard->setTarget(qobject_cast<QLineEdit *>(watched));
                if(m_keyboard->isHidden())
                    m_keyboard->show();
            }
            return true;
        }
        else if(ke->key() == Qt::Key_Up)
            focusPreviousChild();
        else if(ke->key() == Qt::Key_Down)
            focusNextChild();
    }
    return QDialog::eventFilter(watched,event);
}

/**
 * @name    void btnGroupClicked(int id)
 * @details Pushbutton点击事件， 启停wifi
 * @param   id 按键的id
 * @author  lee
 * @date    2018-12-21
**/
void WifiManagerPage::btnGroupClicked(int id)
{
    switch (id) {
    case 0:
    {
        if(m_wifiNameEdit->text().isEmpty() || m_wifiPasswdEdit->text().isEmpty())
        {
            QMessageBox::warning(0, "Warning!",
                                 QString("Please input %1 !")
                                 .arg(m_wifiNameEdit->text().isEmpty()?"wifiname":"wifipasswd"));
            break;
        }
        qDebug()<<"Start wifi.."<<m_wifiNameEdit->text()<<"+"<<m_wifiPasswdEdit->text();
        setWifi();

#ifdef ARM
        pro->execute(WIFI_START_SCRIPT);
#endif
        break;
    }
    case 1:
    {
        qDebug()<<"Stop wifi..";
#ifdef ARM
        pro->execute(WIFI_STOP_SCRIPT);
#endif
        break;
    }
    default:
        break;
    }
}

/**
 * @name    void on_titleBarClicked(GlobalParam::ButtonType id, bool status)
 * @details 标题栏点击事件
 * @param   id 标题栏触发的按键类型
 * @param   status  开关状态
 * @author  lee
 * @date    2018-12-21
**/
void WifiManagerPage::on_titleBarClicked(GlobalParam::ButtonType id, bool status)
{
    if(id == GlobalParam::ButtonType::BUTTON_LEFT)
    {
        //关闭
        close();
    }
}

/**
 * @name    void readWifi()
 * @details 从配置文件读取wifi配置，并刷新输入框内容
 * @author  lee
 * @date    2018-12-21
**/
void WifiManagerPage::readWifi()
{
    QFile Ncfile(WIFI_CONFIG_FILE);
    Ncfile.open(QIODevice::ReadOnly);

    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        QString sep = "=";
        QString wifiNameKey = "ssid=";
        QString wifiPasswdKey = "wpa_passphrase=";
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.contains(wifiNameKey) && strtemp.startsWith(wifiNameKey))
            {
                m_curWifiName = strtemp.split(sep).at(1);
            }
            if(strtemp.contains(wifiPasswdKey) && strtemp.startsWith(wifiPasswdKey))
            {
                m_curWifiPasswd = strtemp.split(sep).at(1);
            }
        }
        Ncfile.close();
    }
}

/**
 * @name    void setWifi()
 * @details 修改wifi配置文件
 * @author  lee
 * @date    2018-12-21
**/
void WifiManagerPage::setWifi()
{
    QFile Ncfile(WIFI_CONFIG_FILE);
    Ncfile.open(QIODevice::ReadOnly);

    if (Ncfile.isOpen())
    {
        QString strtemp;
        QTextStream NctextStream(&Ncfile);
        QString wifiNameKey = "ssid=";
        QString wifiPasswdKey = "wpa_passphrase=";
        QString Alltemp;
        while(!NctextStream.atEnd())
        {
            strtemp = NctextStream.readLine();
            if(strtemp.contains(wifiNameKey))
            {
                m_curWifiName = m_wifiNameEdit->text();
                Alltemp = Alltemp + wifiNameKey.toLatin1() + m_curWifiName.toLatin1();
                Alltemp += QString('\n').toLatin1();
            }
            else if(strtemp.contains(wifiPasswdKey))
            {
                m_curWifiPasswd = m_wifiPasswdEdit->text();
                Alltemp = Alltemp + wifiPasswdKey.toLatin1() + m_curWifiPasswd.toLatin1();
                Alltemp += QString('\n').toLatin1();
            }
            else
            {
                Alltemp += strtemp.toLatin1();
                Alltemp += QString('\n').toLatin1();
            }
        }
        Ncfile.close();

        //        qDebug()<<Alltemp;

        Ncfile.open(QIODevice::WriteOnly);

        QTextStream in(&Ncfile);
        in <<Alltemp;
        Ncfile.close();
    }
}
