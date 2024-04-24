/********************************************************************************
** Form generated from reading UI file 'playernamedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERNAMEDIALOG_H
#define UI_PLAYERNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_PlayerNameDialog
{
public:

    void setupUi(QDialog *PlayerNameDialog)
    {
        if (PlayerNameDialog->objectName().isEmpty())
            PlayerNameDialog->setObjectName("PlayerNameDialog");
        PlayerNameDialog->resize(400, 300);

        retranslateUi(PlayerNameDialog);

        QMetaObject::connectSlotsByName(PlayerNameDialog);
    } // setupUi

    void retranslateUi(QDialog *PlayerNameDialog)
    {
        PlayerNameDialog->setWindowTitle(QCoreApplication::translate("PlayerNameDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerNameDialog: public Ui_PlayerNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERNAMEDIALOG_H
