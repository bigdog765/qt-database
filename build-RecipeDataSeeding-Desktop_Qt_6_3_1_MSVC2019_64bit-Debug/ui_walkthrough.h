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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_walkthrough
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *walkthrough)
    {
        if (walkthrough->objectName().isEmpty())
            walkthrough->setObjectName(QString::fromUtf8("walkthrough"));
        walkthrough->resize(866, 565);
        centralwidget = new QWidget(walkthrough);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 701, 600));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 136, 136)"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(710, 20, 131, 491));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        walkthrough->setCentralWidget(centralwidget);
        menubar = new QMenuBar(walkthrough);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 866, 22));
        walkthrough->setMenuBar(menubar);
        statusbar = new QStatusBar(walkthrough);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        walkthrough->setStatusBar(statusbar);

        retranslateUi(walkthrough);

        stackedWidget->setCurrentIndex(-1);


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
