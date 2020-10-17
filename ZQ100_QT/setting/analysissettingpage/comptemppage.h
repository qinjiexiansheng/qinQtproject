#ifndef COMPTEMPPAGE_H
#define COMPTEMPPAGE_H

#include "globalparam.h"
#include "basewidget/titlebar.h"

class SlideArea;

class CompTempPage : public QDialog
{
    Q_OBJECT
public:
    CompTempPage(QWidget *parent = 0);

protected:
        void keyPressEvent(QKeyEvent *e);

private slots:
        void on_clicked(GlobalParam::ButtonType id, bool status);

private:
        void initView();
        void showView(bool show);

private:
    QWidget *m_mainWidget;
    TitleBar *m_titleBar;

//    SlideArea *slideArea1;
//    SlideArea *slideArea2;
};

#endif // COMPTEMPPAGE_H
