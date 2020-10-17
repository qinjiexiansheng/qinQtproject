#ifndef AnalysisSettingPage_H
#define AnalysisSettingPage_H

#include <QDialog>

class OptionsListWidget;

class AnalysisSettingPage : public QDialog
{
    Q_OBJECT
public:
    explicit AnalysisSettingPage(QWidget *parent = 0);

signals:

private slots:
    void optionsClicked(int index);

private:
     OptionsListWidget *centralWidget;
};

#endif // AnalysisSettingPage_H
