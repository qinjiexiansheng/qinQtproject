/********************************************************************************
** Form generated from reading UI file 'qlogindialog.ui'
**
** Created: Sat Dec 15 23:00:11 2018
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLOGINDIALOG_H
#define UI_QLOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QLoginDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QLoginDialog)
    {
        if (QLoginDialog->objectName().isEmpty())
            QLoginDialog->setObjectName(QString::fromUtf8("QLoginDialog"));
        QLoginDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(QLoginDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(QLoginDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), QLoginDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QLoginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QLoginDialog);
    } // setupUi

    void retranslateUi(QDialog *QLoginDialog)
    {
        QLoginDialog->setWindowTitle(QApplication::translate("QLoginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QLoginDialog: public Ui_QLoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLOGINDIALOG_H
