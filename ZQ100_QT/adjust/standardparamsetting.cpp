#include <QSizePolicy>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDebug>

#include <unistd.h>
#include <stdio.h>

#include "standardparamsetting.h"
#include "spinboxstandard.h"
#include "config.h"
#include "globalclass.h"

#if 0
static int   s_vsk   = 0;
static int   s_fid   = -45;
static int   s_gain  = 2;
static int   s_dly   = 3;
static int   s_level = 0;
static float s_span  = 1.4;
#elif 1
unsigned char   Standardparamsetting::s_vsk = 0;
unsigned char    Standardparamsetting::s_fid   = 45;
unsigned char     Standardparamsetting::s_gain  = 2;
int    Standardparamsetting::s_dly   = 3;
int    Standardparamsetting::s_level = 0;
float  Standardparamsetting::s_span  = 1.4;
#endif


Standardparamsetting::Standardparamsetting(QWidget *parent)
    :QWidget(parent = 0)
{
    layoutInit();
}

void Standardparamsetting::layoutInit(){

    setFixedWidth( 150);
    setFixedHeight( 240);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0, 0, 150, 240);

    setStyleSheet("color: rgb(255, 255, 255);\
                  background-color: rgb(0, 155, 155)");
    QGridLayout *_baseLayout = new QGridLayout(this);

    m_tempRange = new QLabel(this);
    //m_tempRange->setSizePolicy(labelPolicy);
    m_tempRange->setText( tr("Range:") );
    _baseLayout->addWidget( m_tempRange, 0, 0 );
    m_tempRangeBtn = new QLabel(this);
    m_tempRangeBtn->setText( QString(tr("0~255")));
    _baseLayout->addWidget( m_tempRangeBtn, 0, 1);

    m_vskLabel = new QLabel(this);
    m_vskLabel->setText(tr("GSK:"));
    _baseLayout->addWidget( m_vskLabel, 1, 0 );
    m_vskBtn = new SpinBoxStandard;
    m_vskBtn->setAlignment(Qt::AlignCenter);
    m_vskBtn->setSingleStep(1);
    m_vskBtn->setRange(0, 255);
    m_vskBtn->setDecimals(0);
    _baseLayout->addWidget( m_vskBtn, 1, 1 );

    m_fidLabel = new QLabel(this);
    m_fidLabel->setText(tr("FID:"));
    _baseLayout->addWidget( m_fidLabel, 2, 0 );
    m_fidBtn = new SpinBoxStandard;
    m_fidBtn->setAlignment(Qt::AlignCenter);
    m_fidBtn->setSingleStep(1);
    m_fidBtn->setRange(0, 255);
    m_fidBtn->setDecimals(0);
    _baseLayout->addWidget( m_fidBtn, 2, 1 );

    m_gainLabel = new QLabel(this);
    m_gainLabel->setText(tr("GAIN:"));
    _baseLayout->addWidget( m_gainLabel, 3, 0 );
    m_gainBtn = new SpinBoxStandard;
    m_gainBtn->setAlignment(Qt::AlignCenter);
    m_gainBtn->setSingleStep(1);
    m_gainBtn->setRange(0, 7);
    m_gainBtn->setDecimals(0);
    _baseLayout->addWidget( m_gainBtn, 3, 1 );

    _dlyLabel = new QLabel(this);
    _dlyLabel->setText(tr("DLY:"));
    _baseLayout->addWidget(_dlyLabel, 4, 0 );
    m_dlyBtn = new SpinBoxStandard;
    m_dlyBtn->setAlignment(Qt::AlignCenter);
    m_dlyBtn->setSingleStep(1);
    m_dlyBtn->setRange(0, 7);
    m_dlyBtn->setDecimals(0);
    _baseLayout->addWidget( m_dlyBtn, 4, 1 );

    _levelspanLabel = new QLabel(this);
    _levelspanLabel->setText(tr("LEVEL:"));
    _baseLayout->addWidget( _levelspanLabel, 5, 0 );
    m_levelBtn = new SpinBoxStandard;
    m_levelBtn->setAlignment(Qt::AlignCenter);
    m_levelBtn->setSingleStep(1);
    m_levelBtn->setRange(-500, 500);
    m_levelBtn->setDecimals(0);
    _baseLayout->addWidget( m_levelBtn, 5, 1 );

    _spanLabel = new QLabel(this);
    _spanLabel->setText(tr("SPAN:"));
    _baseLayout->addWidget( _spanLabel, 6, 0 );
    m_spanBtn = new SpinBoxStandard;
    m_spanBtn->setAlignment(Qt::AlignCenter);
    m_spanBtn->setSingleStep(0.01);
    m_spanBtn->setRange((float)0.5, (float)4.0);
    m_spanBtn->setDecimals(2);
    _baseLayout->addWidget( m_spanBtn, 6, 1 );

    m_adLabel = new QLabel(this);
    m_adLabel->setText( tr("AD:") );
    _baseLayout->addWidget( m_adLabel, 7, 0 );
    m_ad = new QLabel(this);
    m_ad->setText("0");
    _baseLayout->addWidget( m_ad, 7, 1 );

    m_Lens = new QLabel(this);
    m_Lens->setText(tr("Lens:"));
    _baseLayout->addWidget( m_Lens, 8, 0 );
    m_lensLaber = new QLabel(this);
    m_lensLaber->setText( QString("%1").arg(7));
    _baseLayout->addWidget( m_lensLaber, 8, 1 );

    m_okBtn = new QPushButton("OK",this);
    m_okBtn->setText(tr("Ok"));
    _baseLayout->addWidget( m_okBtn, 9, 0 );
    m_okBtn->installEventFilter(this);
    m_cancleBtn = new QPushButton("Cancle",this);
    m_cancleBtn->setText(tr("Cancle"));
    m_cancleBtn->installEventFilter(this);
    _baseLayout->addWidget( m_cancleBtn, 9, 1 );

    m_list.append( m_vskBtn );
    m_list.append( m_fidBtn );
    m_list.append( m_gainBtn );
    m_list.append( m_dlyBtn );
    m_list.append( m_levelBtn );
    m_list.append( m_spanBtn );
    m_list.append( m_okBtn);
    m_list.append( m_cancleBtn);
    m_list.first();
    focusIndex = 0;


    connect( m_vskBtn,  SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
    connect( m_fidBtn,  SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
    connect( m_gainBtn, SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
    connect( m_dlyBtn,  SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
    connect( m_levelBtn,SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
    connect( m_spanBtn, SIGNAL(textChanged(const QString )),this, SLOT(spinBoxChange(const QString ) ));
}
void Standardparamsetting::spinBoxChange( const QString &text){
    bool ok = false;
    if(m_vskBtn->hasFocus()){
        unsigned char _vskValue = text.toInt(&ok,10);

        globalClass::getFpgaInterface()->fpgaGskSet(_vskValue);

         qDebug()<<"FPGA_SET_m_vskBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_vskValue;
    }else if(m_fidBtn->hasFocus()){
        unsigned char _fidValue = text.toInt(&ok,10);

        globalClass::getFpgaInterface()->fpgaFidSet(_fidValue);

        qDebug()<<"FPGA_SET_m_fidBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_fidValue;
    }else if(m_gainBtn->hasFocus()){
        unsigned char _gainValue = text.toInt(&ok,10);

        globalClass::getFpgaInterface()->fpgaGainSet(_gainValue);

        qDebug()<<"FPGA_SET_m_gainBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_gainValue;
    }else if(m_dlyBtn->hasFocus()){
        int _dlyValue = text.toInt(&ok,10);
        qDebug()<<"FPGA_SET_m_dlyBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_dlyValue;
    }else if(m_levelBtn->hasFocus()){
        int _levelValue = text.toInt(&ok,10);
        qDebug()<<"FPGA_SET_FPGA_SET_m_levelBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_levelValue;
    }else if(m_spanBtn->hasFocus()){
        float _spanValue = text.toFloat(&ok);
        qDebug()<<"FPGA_SET_m_spanBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<_spanValue;
    }
}
bool Standardparamsetting::eventFilter(QObject *obj, QEvent *event){

    if(obj == m_okBtn){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return)
                okClicked();
         }
    }else if(obj == m_cancleBtn){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return)
                cancleClicked();
         }
    }
     return QWidget::eventFilter(obj, event);
}


void Standardparamsetting::keyPressEvent(QKeyEvent *ke){

    switch(ke->key()){
            case KEY_PRESS_UP :
                 {
                    if(focusIndex == 0){
                        focusIndex = m_list.size()-1;
                    }else{
                        focusIndex--;
                    }
                    QWidget *currentFocus = m_list.at(focusIndex);
                    currentFocus->setFocus();
                }
                break;
            case KEY_PRESS_DOWN:
                {
                    if(focusIndex == m_list.size()-1){
                        focusIndex = 0;
                    }else{
                        focusIndex++;
                    }
                   QWidget *currentFocus = m_list.at(focusIndex);
                   currentFocus->setFocus();
                }
                break;
 /*           case KEY_PRESS_LEFT:
                break;
            case KEY_PRESS_RIGHT:
                break;
            case KEY_PRESS_ENTER:
                break;
            case KEY_PRESS_ESC:
                break;
 */
           }
}
void Standardparamsetting::okClicked(){

    saveIRParameter();
    close();
}
void Standardparamsetting::cancleClicked(){
    loadIRParameter();

    globalClass::getFpgaInterface()->fpgaGskFidSet(s_vsk, s_fid);
    globalClass::getFpgaInterface()->fpgaGainSet(s_gain);

    close();
}

void Standardparamsetting::saveIRParameter(){

    s_vsk   = m_vskBtn->text().toInt();
    s_fid   = m_fidBtn->text().toInt();
    s_gain  = m_gainBtn->text().toInt();
    s_dly   = m_dlyBtn->text().toInt();
    s_level = m_levelBtn->text().toInt();
    s_span  = m_spanBtn->text().toFloat();

    char filename[108]={'\0'};
    int len = 7;
    QString cfgFile;
    ::sprintf(filename, "/sat/opt/standard/DetectorSettings%d.conf", len);
    if(::access(filename, F_OK)) {
        cfgFile = "/sat/opt/standard/DetectorSettings.conf";
    } else {
        cfgFile = QString(filename);
    }

     Config _cfg(cfgFile);
    _cfg.setGroup("Parameter");
    _cfg.writeEntry( "VSK" , s_vsk  );
    _cfg.writeEntry( "FID" , s_fid  );
    _cfg.writeEntry( "GAIN", s_gain );
    _cfg.writeEntry( "DLY" , s_dly  );

    qDebug()<<"m_vskBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_vsk;
    qDebug()<<"m_fidBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_fid;
    qDebug()<<"m_gainBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_gain;
    qDebug()<<"m_dlyBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_dly;
}

void Standardparamsetting::loadIRParameter(){
    char filename[108]={'\0'};
    int len = 7;
    QString cfgFile;
    ::sprintf(filename, "/sat/opt/standard/DetectorSettings%d.conf", len);
    if(::access(filename, F_OK)) {
        cfgFile ="/sat/opt/standard/DetectorSettings.conf";// "/opt/DetectorSettings.conf";
    } else {
        cfgFile = QString(filename);
    }

     Config _cfg(cfgFile);
    _cfg.setGroup("Parameter");
    s_vsk  = _cfg.readNumEntry( "VSK" , 0xf0);
    s_fid  = _cfg.readNumEntry( "FID" , 0xb0);
    s_gain = _cfg.readNumEntry( "GAIN", 0 );
    s_dly  = _cfg.readNumEntry( "DLY" , 0 );
    qDebug()<<"FPGA_SET_m_vskBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_vsk;
    qDebug()<<"FPGA_SET_m_fidBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_fid;
    qDebug()<<"FPGA_SET_m_gainBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_gain;
    qDebug()<<"FPGA_SET_m_dlyBtn:"<<__FILE__<<"====LINE:"<<__LINE__<<"----FUNC----------"<<__FUNCTION__<<s_dly;
}

void Standardparamsetting::showEvent( QShowEvent *se ){
    loadIRParameter();
    m_vskBtn->setValue(s_vsk);
    m_fidBtn->setValue(s_fid);
    m_gainBtn->setValue(s_gain);
    m_dlyBtn->setValue(s_dly);
}
unsigned char Standardparamsetting::getStandardparamsVsk()
{
    return s_vsk;
}
unsigned char Standardparamsetting::getStandardparamsFid()
{
    return s_fid;
}
unsigned char Standardparamsetting::getStandardparamsGain()
{
    return s_gain;
}

Standardparamsetting::~Standardparamsetting()
{

}
