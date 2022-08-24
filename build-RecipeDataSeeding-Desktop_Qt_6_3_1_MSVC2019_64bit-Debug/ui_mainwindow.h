/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *title;
    QGroupBox *groupBox;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QPushButton *pushButton4;
    QPushButton *pushButton5;
    QPushButton *pushButton6;
    QPushButton *pushButton7;
    QPushButton *pushButton8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(941, 673);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(140, 20, 303, 64));
        QFont font;
        font.setPointSize(36);
        title->setFont(font);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 90, 891, 541));
        pushButton1 = new QPushButton(groupBox);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setGeometry(QRect(10, 60, 200, 200));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        pushButton1->setFont(font1);
        pushButton1->setAutoFillBackground(false);
        pushButton1->setStyleSheet(QString::fromUtf8("border-image:url(:kalesalad.jpg);"));
        pushButton2 = new QPushButton(groupBox);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(220, 60, 200, 200));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton2->sizePolicy().hasHeightForWidth());
        pushButton2->setSizePolicy(sizePolicy);
        pushButton2->setFont(font1);
        pushButton2->setAutoFillBackground(false);
        pushButton2->setStyleSheet(QString::fromUtf8("border-image: url(:chili.jpg);\n"
"\n"
""));
        pushButton3 = new QPushButton(groupBox);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setGeometry(QRect(430, 60, 200, 200));
        sizePolicy.setHeightForWidth(pushButton3->sizePolicy().hasHeightForWidth());
        pushButton3->setSizePolicy(sizePolicy);
        pushButton3->setFont(font1);
        pushButton3->setAutoFillBackground(false);
        pushButton3->setStyleSheet(QString::fromUtf8("border-image:url(:macpasta.jpg);"));
        pushButton4 = new QPushButton(groupBox);
        pushButton4->setObjectName(QString::fromUtf8("pushButton4"));
        pushButton4->setGeometry(QRect(650, 70, 200, 200));
        pushButton4->setFont(font1);
        pushButton4->setAutoFillBackground(false);
        pushButton4->setStyleSheet(QString::fromUtf8("border-image:url(:muffin.jpg);"));
        pushButton5 = new QPushButton(groupBox);
        pushButton5->setObjectName(QString::fromUtf8("pushButton5"));
        pushButton5->setGeometry(QRect(10, 300, 200, 200));
        pushButton5->setFont(font1);
        pushButton5->setAutoFillBackground(false);
        pushButton5->setStyleSheet(QString::fromUtf8("border-image:url(:tomatosoup.jpg);"));
        pushButton6 = new QPushButton(groupBox);
        pushButton6->setObjectName(QString::fromUtf8("pushButton6"));
        pushButton6->setGeometry(QRect(220, 300, 200, 200));
        pushButton6->setFont(font1);
        pushButton6->setAutoFillBackground(false);
        pushButton6->setStyleSheet(QString::fromUtf8("border-image:url(:chickenparm.jpg);"));
        pushButton7 = new QPushButton(groupBox);
        pushButton7->setObjectName(QString::fromUtf8("pushButton7"));
        pushButton7->setGeometry(QRect(430, 300, 200, 200));
        pushButton7->setFont(font1);
        pushButton7->setAutoFillBackground(false);
        pushButton7->setStyleSheet(QString::fromUtf8("border-image:url(:ramen.jpg);"));
        pushButton8 = new QPushButton(groupBox);
        pushButton8->setObjectName(QString::fromUtf8("pushButton8"));
        pushButton8->setGeometry(QRect(650, 300, 200, 200));
        pushButton8->setFont(font1);
        pushButton8->setLayoutDirection(Qt::LeftToRight);
        pushButton8->setAutoFillBackground(false);
        pushButton8->setStyleSheet(QString::fromUtf8("border-image:url(:chickensalad.jpg);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 941, 22));
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
        title->setText(QCoreApplication::translate("MainWindow", " 8 Recipes", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton1->setText(QCoreApplication::translate("MainWindow", "Simple Kale Salad", nullptr));
        pushButton2->setText(QCoreApplication::translate("MainWindow", "Healthy Chili with Beans", nullptr));
        pushButton3->setText(QCoreApplication::translate("MainWindow", "Macaroni Pasta w/ Tomatoes, Zucchini", nullptr));
        pushButton4->setText(QCoreApplication::translate("MainWindow", "Healthy Morning Glory Muffins", nullptr));
        pushButton5->setText(QCoreApplication::translate("MainWindow", "Tomato Basil Soup", nullptr));
        pushButton6->setText(QCoreApplication::translate("MainWindow", "Chicken Parm", nullptr));
        pushButton7->setText(QCoreApplication::translate("MainWindow", "Homemade Creamy Ramen", nullptr));
        pushButton8->setText(QCoreApplication::translate("MainWindow", "Chicken Salad with Apples and Celery", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
