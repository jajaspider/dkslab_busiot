/********************************************************************************
** Form generated from reading UI file 'statuswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWINDOW_H
#define UI_STATUSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLabel *cpustatus;
    QLabel *label_3;
    QLabel *bandwidth;
    QLabel *label_5;
    QLabel *clientcount;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(232, 138);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 91, 17));
        cpustatus = new QLabel(Dialog);
        cpustatus->setObjectName(QStringLiteral("cpustatus"));
        cpustatus->setGeometry(QRect(120, 30, 67, 17));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 60, 101, 17));
        bandwidth = new QLabel(Dialog);
        bandwidth->setObjectName(QStringLiteral("bandwidth"));
        bandwidth->setGeometry(QRect(120, 60, 67, 17));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 90, 141, 17));
        clientcount = new QLabel(Dialog);
        clientcount->setObjectName(QStringLiteral("clientcount"));
        clientcount->setGeometry(QRect(160, 90, 67, 17));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "cpu status : ", Q_NULLPTR));
        cpustatus->setText(QApplication::translate("Dialog", "0%", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "bandwidth :", Q_NULLPTR));
        bandwidth->setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "connection client :", Q_NULLPTR));
        clientcount->setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWINDOW_H
