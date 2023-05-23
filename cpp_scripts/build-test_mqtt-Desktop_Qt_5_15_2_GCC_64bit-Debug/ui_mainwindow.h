/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *leAboTopic;
    QPushButton *pbAbo;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *leAdresse;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPushButton *pbConnect;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *leEnvoiMessage;
    QLabel *label_5;
    QLineEdit *leEnvoiTopic;
    QPushButton *pbEnvoi;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *leUser;
    QLabel *label_7;
    QLineEdit *lePassword;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(742, 638);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        leAboTopic = new QLineEdit(centralwidget);
        leAboTopic->setObjectName(QString::fromUtf8("leAboTopic"));

        horizontalLayout->addWidget(leAboTopic);

        pbAbo = new QPushButton(centralwidget);
        pbAbo->setObjectName(QString::fromUtf8("pbAbo"));

        horizontalLayout->addWidget(pbAbo);


        gridLayout->addLayout(horizontalLayout, 2, 2, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 4, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        leAdresse = new QLineEdit(centralwidget);
        leAdresse->setObjectName(QString::fromUtf8("leAdresse"));

        horizontalLayout_2->addWidget(leAdresse);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(65000);
        spinBox->setValue(1883);

        horizontalLayout_2->addWidget(spinBox);

        pbConnect = new QPushButton(centralwidget);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));

        horizontalLayout_2->addWidget(pbConnect);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        leEnvoiMessage = new QLineEdit(centralwidget);
        leEnvoiMessage->setObjectName(QString::fromUtf8("leEnvoiMessage"));

        horizontalLayout_3->addWidget(leEnvoiMessage);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        leEnvoiTopic = new QLineEdit(centralwidget);
        leEnvoiTopic->setObjectName(QString::fromUtf8("leEnvoiTopic"));

        horizontalLayout_3->addWidget(leEnvoiTopic);

        pbEnvoi = new QPushButton(centralwidget);
        pbEnvoi->setObjectName(QString::fromUtf8("pbEnvoi"));

        horizontalLayout_3->addWidget(pbEnvoi);


        gridLayout->addLayout(horizontalLayout_3, 3, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        leUser = new QLineEdit(centralwidget);
        leUser->setObjectName(QString::fromUtf8("leUser"));

        horizontalLayout_4->addWidget(leUser);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        lePassword = new QLineEdit(centralwidget);
        lePassword->setObjectName(QString::fromUtf8("lePassword"));

        horizontalLayout_4->addWidget(lePassword);


        gridLayout->addLayout(horizontalLayout_4, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 742, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Topic", nullptr));
        pbAbo->setText(QCoreApplication::translate("MainWindow", "Abonnement", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        leAdresse->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        pbConnect->setText(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Topic", nullptr));
        pbEnvoi->setText(QCoreApplication::translate("MainWindow", "Envoi", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "User :", nullptr));
        leUser->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Password :", nullptr));
        lePassword->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
