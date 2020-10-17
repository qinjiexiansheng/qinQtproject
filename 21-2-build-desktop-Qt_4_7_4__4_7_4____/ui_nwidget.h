/********************************************************************************
** Form generated from reading UI file 'nwidget.ui'
**
** Created: Sun Dec 16 17:35:39 2018
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NWIDGET_H
#define UI_NWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nWidget
{
public:

    void setupUi(QWidget *nWidget)
    {
        if (nWidget->objectName().isEmpty())
            nWidget->setObjectName(QString::fromUtf8("nWidget"));
        nWidget->resize(400, 300);

        retranslateUi(nWidget);

        QMetaObject::connectSlotsByName(nWidget);
    } // setupUi

    void retranslateUi(QWidget *nWidget)
    {
        nWidget->setWindowTitle(QApplication::translate("nWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class nWidget: public Ui_nWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NWIDGET_H
