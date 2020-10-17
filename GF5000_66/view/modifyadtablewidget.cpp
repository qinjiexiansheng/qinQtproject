#include "modifyadtablewidget.h"

ModifyAdTableWidget::ModifyAdTableWidget(QWidget *parent) : QWidget(parent){
    mSatData = SatData::initance();
    mModel = mSatData->getModel();
    mView = new QTableView(this);//表格窗口
    mView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//行表头均分
    mView->verticalHeader()->hide();//竖表头隐藏
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滑条隐藏
    mView->installEventFilter(this);
    mView->setModel(mModel);
    QVBoxLayout *nLayout = new QVBoxLayout;
    int nGear = mSatData->getGearMode()==SatData::GEARONE?1:2;
    mSatTitleBar = new SatTitleBar(QString(tr("ModifyAdTable[%1]")).arg(nGear),this);
    nLayout->addWidget(mSatTitleBar);
    nLayout->addWidget(mView);
    nLayout->setMargin(1);//外边距为0
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    this->setFixedSize(250,480);//设置窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    mView->setCurrentIndex(mModel->index(0,1));//初始焦点在第一行第二列
    SatControl *nSatControl = SatControl::initance();
    connect(this,SIGNAL(operationSignal(int,QString)),nSatControl,SLOT(doService(int,QString)));
}

bool ModifyAdTableWidget::eventFilter(QObject *obj, QEvent *event){
    if(obj == mView && event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        switch (nKey->key()){
            case KEY_19:
                focusPrevious();//前一焦点
                break;
            case KEY_20:
                focusNext();//下一焦点
                break;
            case KEY_18://打开键盘修改数据
                {
                    QString nStr = mView->currentIndex().data().toString();//获取当前项的数据
                    HexadecimalKeyboard* nDialog = new HexadecimalKeyboard(nStr,this);//打开十六进制键盘
                    nDialog->move(80,80);
                    if(nDialog->exec()){
                        if(nStr.isEmpty()){
                            nStr = "0";
                        }
                        mView->model()->setData(mView->currentIndex(),nStr);
                    }
                }
                break;
            case KEY_25://返回键，将关闭窗口
                {
                    emit operationSignal(Save_Model_Data,NULL);
                    this->close();//关闭窗口
                }
            default:
                break;
           }
          return true;//拦截其他按键，不需要上层处理
    }
    return QWidget::eventFilter(obj,event);
}

void ModifyAdTableWidget::focusNext(){//下一焦点
    int i = mView->currentIndex().row();//当前的行
    int j = mView->currentIndex().column();//当前的列，其实就是第二列，因为第一列不列入焦点处理
    i++;
    if(i >= mModel->rowCount()){
        i = mModel->rowCount()-1;//不做循环
    }
    mView->setCurrentIndex(mModel->index(i,j));//设置焦点
}

void ModifyAdTableWidget::focusPrevious(){//前一焦点，同上
    int i = mView->currentIndex().row();
    int j = mView->currentIndex().column();
    i--;
    if(i < 0){
        i = 0;
    }
    mView->setCurrentIndex(mModel->index(i,j));
}

void ModifyAdTableWidget::showEvent(QShowEvent *se){
    mView->setCurrentIndex(mModel->index(0,1));
    int nGear = mSatData->getGearMode()==SatData::GEARONE?1:2;
    mSatTitleBar->setTitle(QString(tr("ModifyAdTable[%1]")).arg(nGear));
    QWidget::showEvent(se);
}

void ModifyAdTableWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}


/*================================================================================
  ================================================================================*/
ShowAdTableWidget::ShowAdTableWidget(QWidget *parent) : QWidget(parent){
    mView = new QTextBrowser(this);//文本浏览组件
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滑条隐藏
    mView->installEventFilter(this);
    QVBoxLayout *nLayout = new QVBoxLayout;
    mSatData = SatData::initance();
    int nGear = mSatData->getGearMode()==SatData::GEARONE?1:2;
    mSatTitleBar = new SatTitleBar(this);
    mSatTitleBar->setTitle(QString(tr("ShowADTable[%1]")).arg(nGear));

    nLayout->addWidget(mSatTitleBar);
    nLayout->addWidget(mView);
    nLayout->setMargin(1);//布局边框
    nLayout->setSpacing(0);
    this->setLayout(nLayout);
    this->setFixedSize(250,480);//窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
    loadFile();
}

bool ShowAdTableWidget::eventFilter(QObject *obj, QEvent *event){
    if(obj == mView && event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        switch (nKey->key()){
            case KEY_19:
                {
                    QScrollBar *nBar = mView->verticalScrollBar();
                    nBar->setSliderPosition(nBar->value()-10);//滑块上移
                }
                break;
            case KEY_20:
                {
                    QScrollBar *nBar = mView->verticalScrollBar();
                    nBar->setSliderPosition(nBar->value()+10);//滑块下移
                }
                break;
            case KEY_25:
            case KEY_18:
                this->close();//窗口关闭
                break;
            default:
                break;
           }
          return true;//其他按键不需要上层处理
    }
    return QWidget::eventFilter(obj,event);
}

void ShowAdTableWidget::loadFile(){
    QString nFileStr = mSatData->getTmpAdFile();
    if(nFileStr.isEmpty()){
        nFileStr = QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
    }
    QFile nFile(nFileStr);
    if(!nFile.open(QIODevice::ReadOnly | QIODevice::Text)){//打开文件
        return ;
    }
    QTextStream in(&nFile);
    QString nAllStr = in.readAll();//读取全部
    mView->clear();
    mView->setText(nAllStr);
    nFile.close();
    int nGear = mSatData->getGearMode()==SatData::GEARONE?1:2;
    mSatTitleBar->setTitle(QString(tr("ShowADTable[%1]")).arg(nGear));
}

void ShowAdTableWidget::showEvent(QShowEvent *event){
    loadFile();
    QWidget::showEvent(event);
}

void ShowAdTableWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen nPen;
    nPen.setColor(QColor("#888888"));
    nPen.setWidth(1);
    painter.setPen(nPen);
    painter.drawLine(0,0,0,height());//画左边线
    painter.drawLine(0,0,width(),0);//画上线
    painter.drawLine(width()-1,0,width()-1,height()-1);//画右线
    painter.drawLine(0,height()-1,width()-1,height()-1);//画下线
    QWidget::paintEvent(event);
}

