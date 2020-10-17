#include "analysisfuncpage.h"
#include "examplepage.h"
#include "analysismanager.h"


AnalysisFuncPage::AnalysisFuncPage(QWidget *parent)
    : QDialog(parent)
{
    move(0, 0);
    setFixedSize(100, 200);

    setStyleSheet("background-color: rgb(0, 155, 155);");
    setWindowFlags(Qt::FramelessWindowHint);

    tabWidget = new QTabWidget(this);
    tabWidget->setFixedSize(100, 200);

    ExamplePage *page1 = new ExamplePage(0, "Spot");
    ExamplePage *page2 = new ExamplePage(0, "Area");
    ExamplePage *page3 = new ExamplePage(0, "Line", 1);
    ExamplePage *page4 = new ExamplePage(0, "ISO", 1);

    tabWidget->insertTab(0, page1, "Spot");
    tabWidget->insertTab(1, page2, "Area");
    tabWidget->insertTab(2, page3, "Line");
//    tabWidget->insertTab(3, page4, "ISO");

//    tabWidget->setCornerWidget(page4);


    //    tabWidget->setTabPosition(QTabWidget::West);
    //    tabWidget->setUsesScrollButtons(false);


    //    tabWidget->setCurrentIndex(1);

    analysisManager = new AnalysisManager(this);

    connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(changeTab(int)));
    connect(page1, SIGNAL(buttonClicked(int)), this, SLOT(page1Func(int)));
    connect(page2, SIGNAL(buttonClicked(int)), this, SLOT(page2Func(int)));
    connect(page3, SIGNAL(buttonClicked(int)), this, SLOT(page3Func(int)));
    connect(page4, SIGNAL(buttonClicked(int)), this, SLOT(page4Func(int)));
}

AnalysisFuncPage::~AnalysisFuncPage()
{

}

void AnalysisFuncPage::updateWidget()
{
    if(tabWidget->isHidden())
    {
        tabWidget->show();
        tabWidget->raise();
        tabWidget->tabBar()->setFocus();
    }
    else
    {
        tabWidget->hide();
    }
}

void AnalysisFuncPage::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up)
        focusPreviousChild();
    else if(e->key() == Qt::Key_Down)
        focusNextChild();
    else if(e->key() == Qt::Key_Escape)
    {
        updateWidget();
    }
    else
        e->accept();

}

void AnalysisFuncPage::mouseDoubleClickEvent(QMouseEvent *event)
{
    updateWidget();
}

void AnalysisFuncPage::changeTab(int index)
{
        //qDebug()<<index;
}

void AnalysisFuncPage::page1Func(int id)
{

    Spot *spot =  analysisManager->addSpot(/*id*/);
    if(spot->isHidden())
        spot->move(width()-spot->width(), 0);
    spot->show();
    tabWidget->hide();
}

void AnalysisFuncPage::page2Func(int id)
{
    Area *area =  analysisManager->addArea(/*id*/);
    if(area->isHidden())
        area->move(width()-area->width(), 0);
    area->show();
    tabWidget->hide();
}

void AnalysisFuncPage::page3Func(int id)
{
    Line *line =  analysisManager->addLine();
    if(line->isHidden())
        line->move(0, 240/2);
    line->show();
    tabWidget->hide();
}

void AnalysisFuncPage::page4Func(int)
{

}
