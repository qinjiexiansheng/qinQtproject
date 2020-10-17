#ifndef QLOGINDIALOG_H
#define QLOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QString>

class QLoginDialog : public QDialog
{
    Q_OBJECT
    
private:
    QLabel UserLabel;
    QLabel PwdLabel;
    QLineEdit UserLineEdit;
    QLineEdit PwdLineEdit;
    QPushButton nButtonOk;
    QPushButton nButtonCancel;
    QGridLayout nGridLayout;
    QString mUser;
    QString mPwd;

private slots:
    void mynButtonOk_Clicked();
    void mynButtonCancel_Clicked();


public:
    explicit QLoginDialog(QWidget *parent = 0);
    QString getUser();
    QString getPwd();
    ~QLoginDialog();

};

#endif // QLOGINDIALOG_H
