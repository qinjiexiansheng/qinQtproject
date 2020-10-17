#include "QloginDialog.h"

QLoginDialog::QLoginDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowCloseButtonHint), UserLabel(this), PwdLabel(this), UserLineEdit(this),
    PwdLineEdit(this),nButtonOk(this), nButtonCancel(this)
 {
/*
    QLabel UserLabel;
    QLabel PwdLabel;
    QLineEdit UserLineEdit;
    QLineEdit PwdLineEdit;
    QPushButton nButtonOk;
    QPushButton nButtonCancel;
    QGridLayout nGridLayout;
*/

    UserLabel.setText("user :");
    PwdLabel.setText("pwd :");

    nButtonOk.setText("ok");
    nButtonCancel.setText("Cancel");

    PwdLineEdit.setEchoMode(QLineEdit::Password);


    setFixedSize(285, 170);


    nGridLayout.addWidget(&UserLabel, 0, 0);
    nGridLayout.addWidget(&UserLineEdit, 0, 1);

    nGridLayout.addWidget(&PwdLabel, 1, 0);
    nGridLayout.addWidget(&PwdLineEdit, 1, 1);

    nGridLayout.addWidget(&nButtonOk, 2, 1);
    nGridLayout.addWidget(&nButtonCancel, 2, 0);
    this->setLayout(&nGridLayout);

    connect(&nButtonOk, SIGNAL(clicked()), this,  SLOT(mynButtonOk_Clicked()) );
    connect(&nButtonCancel, SIGNAL(clicked()), this, SLOT(mynButtonCancel_Clicked()) );


}

QLoginDialog::~QLoginDialog()
{
}

void QLoginDialog::mynButtonOk_Clicked()
{
    qDebug(" QLoginDialog::mynButtonOk_Clicked");

    mUser = UserLineEdit.text().trimmed();
    mPwd  = PwdLineEdit.text();

    done(Accepted);



}
void QLoginDialog::mynButtonCancel_Clicked()
{

}

QString QLoginDialog::getUser()
{
    return mUser;
}

QString QLoginDialog::getPwd()
{
    return mPwd;
}


