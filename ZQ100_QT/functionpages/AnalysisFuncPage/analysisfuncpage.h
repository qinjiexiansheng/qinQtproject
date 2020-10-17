#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QMouseEvent>

class QTabWidget;
class AnalysisManager;

class AnalysisFuncPage : public QDialog
{
    Q_OBJECT

public:
    AnalysisFuncPage(QWidget *parent = 0);
    ~AnalysisFuncPage();

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void changeTab(int);
    void page1Func(int);
    void page2Func(int);
    void page3Func(int);
    void page4Func(int);

private slots:
    void updateWidget();

private:
    QTabWidget *tabWidget;
    AnalysisManager * analysisManager;
};

#endif // DIALOG_H
