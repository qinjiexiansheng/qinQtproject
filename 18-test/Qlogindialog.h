#ifndef QLOGINDIALOG_H
#define QLOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "QString"

class QLoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QLoginDialog(QWidget *parent = 0);
    QString getUser();
    QString getPwd();
    ~QLoginDialog();

private  slots:
    void canCelClicked();
    void LoginClicked();
private:
   QLabel UserLabel;
   QLabel PwdLabel;
   QLineEdit UserEdit;
   QLineEdit PwdEdit;
   QPushButton CancelBtn;
   QPushButton LOgBtn;
   QString m_user;
   QString m_pwd;

};

#endif // QLOGINDIALOG_H
