/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *carcount;
    QLabel *label_2;
    QLineEdit *cycle;
    QLabel *label_3;
    QCheckBox *tem_cb;
    QCheckBox *hum_cb;
    QCheckBox *cou_cb;
    QLineEdit *tem_min;
    QLabel *label_4;
    QLineEdit *tem_max;
    QLineEdit *hum_max;
    QLabel *label_5;
    QLineEdit *hum_min;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(363, 308);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 75, 17));
        carcount = new QLineEdit(centralWidget);
        carcount->setObjectName(QStringLiteral("carcount"));
        carcount->setGeometry(QRect(111, 30, 41, 25));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 30, 67, 17));
        cycle = new QLineEdit(centralWidget);
        cycle->setObjectName(QStringLiteral("cycle"));
        cycle->setGeometry(QRect(220, 30, 41, 25));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 30, 67, 17));
        tem_cb = new QCheckBox(centralWidget);
        tem_cb->setObjectName(QStringLiteral("tem_cb"));
        tem_cb->setGeometry(QRect(30, 90, 111, 23));
        hum_cb = new QCheckBox(centralWidget);
        hum_cb->setObjectName(QStringLiteral("hum_cb"));
        hum_cb->setGeometry(QRect(30, 120, 92, 23));
        cou_cb = new QCheckBox(centralWidget);
        cou_cb->setObjectName(QStringLiteral("cou_cb"));
        cou_cb->setGeometry(QRect(30, 150, 92, 23));
        tem_min = new QLineEdit(centralWidget);
        tem_min->setObjectName(QStringLiteral("tem_min"));
        tem_min->setEnabled(false);
        tem_min->setGeometry(QRect(180, 90, 41, 25));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 90, 67, 17));
        tem_max = new QLineEdit(centralWidget);
        tem_max->setObjectName(QStringLiteral("tem_max"));
        tem_max->setEnabled(false);
        tem_max->setGeometry(QRect(250, 90, 41, 25));
        hum_max = new QLineEdit(centralWidget);
        hum_max->setObjectName(QStringLiteral("hum_max"));
        hum_max->setEnabled(false);
        hum_max->setGeometry(QRect(250, 120, 41, 25));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setEnabled(false);
        label_5->setGeometry(QRect(230, 120, 67, 17));
        hum_min = new QLineEdit(centralWidget);
        hum_min->setObjectName(QStringLiteral("hum_min"));
        hum_min->setEnabled(false);
        hum_min->setGeometry(QRect(180, 120, 41, 25));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 220, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 363, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "CarCount : ", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Cycle : ", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Seconds", Q_NULLPTR));
        tem_cb->setText(QApplication::translate("MainWindow", "Temperature", Q_NULLPTR));
        hum_cb->setText(QApplication::translate("MainWindow", "Humidity", Q_NULLPTR));
        cou_cb->setText(QApplication::translate("MainWindow", "Count", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "~", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "~", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Summit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
