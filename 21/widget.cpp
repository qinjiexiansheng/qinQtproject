#include "widget.h"
#include "QGridLayout"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(50,50,100,200);
    m_fontDialogBtn = new QPushButton("Font Dialog",this);
    m_processDialogBtn = new QPushButton("Process Dialog",this);
    m_printDialogBtn = new QPushButton("Print Dialog",this);

    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(m_fontDialogBtn, 0, 0);
    gLayout->addWidget(m_processDialogBtn, 1, 0);
    gLayout->addWidget(m_printDialogBtn, 2, 0);

    connect(m_fontDialogBtn, SIGNAL(clicked()), this, SLOT(FontDialogClickedSlot()));
    connect(m_processDialogBtn, SIGNAL(clicked()), this, SLOT(ProcessDialogClickedSlot()));
    connect(m_printDialogBtn, SIGNAL(clicked()), this, SLOT(PrintDialogClickedSlot()));


}

void Widget::FontDialogClickedSlot()
{
    qDebug() << "Widget::FontDialogClickedSlot()";
}
void Widget::ProcessDialogClickedSlot()
{
    qDebug() << "Widget::ProcessDialogClickedSlot()";
    qDebug() << "ProcessDialogClickedSlot = " << QThread::currentThreadId();

   // QThread *thread = new QThread(this);
     m_pressDlg = new QProgressDialog("Operation in progress.", "Cancel", 0, 100);
     UpadateProgress *updatePross = new UpadateProgress;
    // updatePross->moveToThread(thread);

   // connect(thread,SIGNAL(started()), updatePross, SLOT(UpadateProgressSlot()));
    connect(updatePross,SIGNAL(UpdateSteps(int )), this, SLOT(GetTimeOutSlot(int )));
   // thread->start();
    updatePross->start();

    m_pressDlg->exec();

}
void Widget::PrintDialogClickedSlot()
{
    qDebug() << "Widget::PrintDialogClickedSlot()";

}



Widget::~Widget()
{
    
}

void Widget::GetTimeOutSlot(int m_steps)
{

    qDebug()<< "Widget::GetTimeOutSlot" <<m_steps ;

    m_pressDlg->setValue(m_steps);
}
