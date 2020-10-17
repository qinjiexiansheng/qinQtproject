#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{

    this->setGeometry(0, 0, 320, 240);
    this->setWindowFlags(Qt::FramelessWindowHint);

    tabDialog = new TabDialog(this);
 //   tabDialog->hide();

    this->show();


    //打开外部按键驱动
    m_fileKde = open("/dev/input/event0", O_RDONLY);
    if(m_fileKde < 0)
    {
        perror("open()");
    }

    printf("open()\r\n");
    //监听外部按键
    m_socketNotifier = new QSocketNotifier(m_fileKde, QSocketNotifier::Read, this);

    connect(m_socketNotifier, SIGNAL(activated(int)), this, SLOT(readKeyBoardData()));

    qDebug("mainWindow");

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    qDebug("void MainWindow::keyPressEvent(QKeyEvent *e)");

}


/**
 * @name    void readKeyBoardData()
 * @details 读取外部按键数据,并发送标准的按键事件
 * @author  lee
 * @date    2018-11-15
**/
void MainWindow::readKeyBoardData()
{
    struct input_event ev_key;
    QKeyEvent *keyEvent;
    Qt::Key key;

    read(m_fileKde,&ev_key,sizeof(struct input_event));

    if(ev_key.type !=0 && ev_key.value != 0)
    {
        qWarning("ev_key.code = %d", ev_key.code);

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
        keyEvent = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier);
        qApp->sendEvent(qApp->focusWidget(), keyEvent);
    }
}

MainWindow::~MainWindow()
{

}
