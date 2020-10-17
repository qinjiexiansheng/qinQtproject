#include "ShowAdTableWidget.h"
#include <QTextStream>

ShowAdTableWidget::ShowAdTableWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(240,200);//窗口大小
    this->setGeometry(0, 0, 240, 200);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);

    nVBoxLayout =new QVBoxLayout(this);

    mView = new QTextBrowser(this);//文本浏览组件
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滑条隐藏
    mView->installEventFilter(this);

    TitleLable = new QLabel(QString("ShowADTable[%1]").arg(1) );

    nVBoxLayout->addWidget(TitleLable);
    nVBoxLayout->addWidget(mView);
    nVBoxLayout->setMargin(1);//布局边框
    nVBoxLayout->setSpacing(0);

    this->setLayout(nVBoxLayout);

    loadFile();

}

bool ShowAdTableWidget::eventFilter(QObject *obj, QEvent *event){
    if(obj == mView && event->type() == QEvent::KeyPress){
        QKeyEvent* nKey = (QKeyEvent *)event;
        switch (nKey->key()){
            case UP:
                {
                    QScrollBar *nBar = mView->verticalScrollBar();
                    nBar->setSliderPosition(nBar->value()-10);//滑块上移
                }
                break;
            case DOWN:
                {
                    QScrollBar *nBar = mView->verticalScrollBar();
                    nBar->setSliderPosition(nBar->value()+10);//滑块下移
                }
                break;
            case ESC:
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
   // QString nFileStr = mSatData->getTmpAdFile();
    QString nFileStr;
    if(nFileStr.isEmpty()){
       // nFileStr = QString("%1%2").arg(COF_DIR).arg(QString(TEMP_AD_TABLE).arg(1));
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
 //   int nGear = mSatData->getGearMode()==SatData::GEARONE?1:2;
//    mSatTitleBar->setTitle(QString(tr("ShowADTable[%1]")).arg(nGear));
}

void ShowAdTableWidget::showEvent(QShowEvent *event){
    loadFile();
    QWidget::showEvent(event);
}
