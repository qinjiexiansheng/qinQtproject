#ifndef UPADATEPROGRESS_H
#define UPADATEPROGRESS_H

#include <QObject>
#include <QProgressDialog>
#include <QThread>
#include <QTimer>

class UpadateProgress : public QObject
{
    Q_OBJECT
public:
    explicit UpadateProgress(QObject *parent = 0);
    void start();
    
signals:
    void UpdateSteps(int);

public slots:
    void TimeOutSlot();
    void UpadateProgressSlot();

private:
    QThread m_thread;
    QProgressDialog *m_progressDlg;
    QTimer *m_time;
    int m_steps;
    bool m_successFlag;

};

#endif // UPADATEPROGRESS_H
