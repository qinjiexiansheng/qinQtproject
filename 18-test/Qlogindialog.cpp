#include "Qlogindialog.h"

QLoginDialog::QLoginDialog(QWidget *parent) :
    QDialog(parent),
    UserLabel(this), PwdLabel(this), UserEdit(this), PwdEdit(this), LOgBtn(this), CancelBtn(this)
{
   UserLabel.move(20,30);
   UserLabel.setText("User ID:");
   PwdLabel.move(20,60);
   PwdLabel.setText("PassWord:");

   UserEdit.move(80,20);
   UserEdit.setFixedSize(170,20);
   PwdEdit.move(80,60);
   PwdEdit.setFixedSize(170,20);

   CancelBtn.move(80, 100);
   CancelBtn.setText("Cancel");
   LOgBtn.move(180,100);
   LOgBtn.setText("Login");

   setGeometry(100,100,285,150);

   connect(&CancelBtn, SIGNAL(clicked()), this, SLOT(canCelClicked()));
   connect(&LOgBtn, SIGNAL(clicked()), this, SLOT(LoginClicked()));


}

void QLoginDialog::canCelClicked()
{
    qWarning("=====QLoginDialog::canCelClicked()=======");

     done(Rejected);
}
void QLoginDialog::LoginClicked()
{


     qWarning("=====LoginClicked()=======");
     m_user = UserEdit.text().trimmed();
     m_pwd = PwdEdit.text();

     done(Accepted);

      qWarning("=====canCelClicked()=======  end end ");

}
QString QLoginDialog::getUser()
{
    return m_user;
}
QString QLoginDialog::getPwd()
{
    return m_pwd;
}
QLoginDialog::~QLoginDialog()
{

}
