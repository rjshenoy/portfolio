/********************************************************************************
** Form generated from reading UI file 'announcewinnerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNOUNCEWINNERDIALOG_H
#define UI_ANNOUNCEWINNERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AnnounceWinnerDialog
{
public:

    void setupUi(QDialog *AnnounceWinnerDialog)
    {
        if (AnnounceWinnerDialog->objectName().isEmpty())
            AnnounceWinnerDialog->setObjectName("AnnounceWinnerDialog");
        AnnounceWinnerDialog->resize(400, 300);

        retranslateUi(AnnounceWinnerDialog);

        QMetaObject::connectSlotsByName(AnnounceWinnerDialog);
    } // setupUi

    void retranslateUi(QDialog *AnnounceWinnerDialog)
    {
        AnnounceWinnerDialog->setWindowTitle(QCoreApplication::translate("AnnounceWinnerDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnnounceWinnerDialog: public Ui_AnnounceWinnerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNOUNCEWINNERDIALOG_H
