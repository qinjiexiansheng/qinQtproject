#include "tabdialog.h"

TabDialog::TabDialog(QWidget *parent) : QDialog(parent){
    //加载样式
    QString nQssStr = QString("%1SatGF5000.qss").arg(QSS_DIR);
    QFile nQss(nQssStr);
    nQss.open(QFile::ReadOnly);
    this->setStyleSheet(nQss.readAll());
    nQss.close();
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    this->setGeometry(0,0,250,480);



    mTabWidget = new QTabWidget(this);//创建标签窗口
    //QTabBar *nTabBar = mTabWidget->tabBar();
    //connect(mTabWidget,SIGNAL(currentChanged(int)),mTabWidget,SLOT(setCurrentIndex(int)));
    //信息标签页
    TabPageOne *nTabPageOne = new TabPageOne(this);
    //nTabPageOne->installEventFilter(this);
    mTabWidget->addTab(nTabPageOne,tr("KTable"));

//    QScrollArea *nScroll = new QScrollArea(this);
//    nScroll->setStyleSheet("QScrollArea{background:transparent;}"
//                              "QScrollBar::vertical{background:#35A739;border:-5px solid grey;margin:-2px 0px 0px 0px;width:8px;}"
//                              "QScrollBar::horizontal{background:#35A739;border:0px solid #126691;height:10px;}"
//                              "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#D3D3D3;}"
//                              );

//    nScroll->setFrameShape(QFrame::NoFrame);
//    nScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    nScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    nScroll->setFocusPolicy(Qt::NoFocus);
//    QWidget *nW = new QWidget(this);
//    nW->setStyleSheet("background:transparent;");
//    nScroll->setWidget(nW);


//    TabPageTwo *nTabPageTwo = new TabPageTwo(nW);
//    nTabPageTwo->installEventFilter(this);
//    mTabWidget->addTab(nW,tr("Setting"));

    //设置标签页
    TabPageTwo *nTabPageTwo = new TabPageTwo(this);
    //nTabPageTwo->installEventFilter(this);
    mTabWidget->addTab(nTabPageTwo,tr("Setting"));


    //其他标签页
    TabPageThree *nTabPageThree = new TabPageThree(this);
    //nTabPageThree->installEventFilter(this);
    mTabWidget->addTab(nTabPageThree,tr("TempAD"));

    //设置标签页
    TabPageFour *nTabPageFour = new TabPageFour(this);
    //nTabPageFour->installEventFilter(this);
    mTabWidget->addTab(nTabPageFour,tr("Other"));

    TabPageFive *nTabPageFive = new TabPageFive(this);
    //nTabPageFive->installEventFilter(this);
    mTabWidget->addTab(nTabPageFive,tr("Test"));


    mTabWidget->installEventFilter(this);

    SatTitleBar *nTitleBar = new SatTitleBar(tr("Calibration"),this);

    QVBoxLayout *nLayout = new QVBoxLayout;
    nLayout->addWidget(nTitleBar);
    nLayout->addWidget(mTabWidget);
    nLayout->setMargin(1);//设置外边框
    nLayout->setSpacing(0);//设置内边框
    this->setLayout(nLayout);
    mMaxIndex = 5;
    mTabWidget->setCurrentIndex(0);


    SatControl *nSat = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSat,SLOT(doService(int,QString)));//连接控制类
}

void TabDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(5);
    painter.setPen(nPen);
    //painter.setBrush(QColor(Qt::yellow));
    painter.drawLine(0,0,0,this->height());
    painter.drawLine(0,0,width(),0);
    painter.drawLine(width()-2,0,width()-2,height()-1);
    painter.drawLine(0,height()-1,width()-1,height()-1);
    QDialog::paintEvent(event);
}

bool TabDialog::eventFilter(QObject *obj, QEvent *ev){
    if(ev->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)ev;
        if(nKey->isAutoRepeat()){
            return true;
        }
        switch(nKey->key()){
            case KEY_21:
                prevTab();
                break;
            case KEY_22:
                nextTab();
                break;
            case KEY_25:
                this->close();
                break;
            case KEY_26:
            case KEY_23:
                emit operationSignal(Manual_Play,NULL);
                break;
        }
        return true;
    }else if(ev->type() == QEvent::KeyRelease){
        return true;
    }
    return QDialog::eventFilter(obj,ev);
}

void TabDialog::showEvent(QShowEvent *se){
    int nIndex = mTabWidget->currentIndex();
    mTabWidget->setCurrentIndex(nIndex);
    QDialog::showEvent(se);
}

void TabDialog::nextTab(){
    int nIndex = mTabWidget->currentIndex();
    nIndex++;
    if(nIndex >= mMaxIndex){
        nIndex = 0;
    }
    mTabWidget->setCurrentIndex(nIndex);
}

void TabDialog::prevTab(){
    int nIndex = mTabWidget->currentIndex();
    nIndex--;
    if(nIndex < 0){
        nIndex = mMaxIndex - 1;
    }
    mTabWidget->setCurrentIndex(nIndex);
}







