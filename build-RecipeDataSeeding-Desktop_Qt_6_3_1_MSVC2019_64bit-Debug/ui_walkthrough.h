/********************************************************************************
** Form generated from reading UI file 'walkthrough.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WALKTHROUGH_H
#define UI_WALKTHROUGH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_walkthrough
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *walkthrough)
    {
        if (walkthrough->objectName().isEmpty())
            walkthrough->setObjectName(QString::fromUtf8("walkthrough"));
        walkthrough->resize(800, 600);
        centralwidget = new QWidget(walkthrough);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 700, 600));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(155, 175, 155)"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        walkthrough->setCentralWidget(centralwidget);
        menubar = new QMenuBar(walkthrough);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        walkthrough->setMenuBar(menubar);
        statusbar = new QStatusBar(walkthrough);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        walkthrough->setStatusBar(statusbar);

        retranslateUi(walkthrough);

        QMetaObject::connectSlotsByName(walkthrough);
    } // setupUi

    void retranslateUi(QMainWindow *walkthrough)
    {
        walkthrough->setWindowTitle(QCoreApplication::translate("walkthrough", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class walkthrough: public Ui_walkthrough {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WALKTHROUGH_H
