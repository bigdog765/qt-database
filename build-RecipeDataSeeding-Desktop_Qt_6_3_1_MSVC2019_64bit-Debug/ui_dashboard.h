/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashboard
{
public:
    QWidget *centralwidget;
    QPushButton *start;
    QLabel *recipeName;
    QLabel *servingSize;
    QLabel *totalNutrition;
    QLabel *ingredients;
    QLabel *prepTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *dashboard)
    {
        if (dashboard->objectName().isEmpty())
            dashboard->setObjectName(QString::fromUtf8("dashboard"));
        dashboard->resize(800, 600);
        centralwidget = new QWidget(dashboard);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(50, 320, 131, 51));
        recipeName = new QLabel(centralwidget);
        recipeName->setObjectName(QString::fromUtf8("recipeName"));
        recipeName->setGeometry(QRect(50, 50, 691, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        recipeName->setFont(font);
        servingSize = new QLabel(centralwidget);
        servingSize->setObjectName(QString::fromUtf8("servingSize"));
        servingSize->setGeometry(QRect(50, 110, 181, 16));
        totalNutrition = new QLabel(centralwidget);
        totalNutrition->setObjectName(QString::fromUtf8("totalNutrition"));
        totalNutrition->setGeometry(QRect(50, 160, 49, 16));
        ingredients = new QLabel(centralwidget);
        ingredients->setObjectName(QString::fromUtf8("ingredients"));
        ingredients->setGeometry(QRect(50, 220, 49, 16));
        prepTime = new QLabel(centralwidget);
        prepTime->setObjectName(QString::fromUtf8("prepTime"));
        prepTime->setGeometry(QRect(50, 130, 161, 16));
        dashboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(dashboard);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        dashboard->setMenuBar(menubar);
        statusbar = new QStatusBar(dashboard);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        dashboard->setStatusBar(statusbar);

        retranslateUi(dashboard);

        QMetaObject::connectSlotsByName(dashboard);
    } // setupUi

    void retranslateUi(QMainWindow *dashboard)
    {
        dashboard->setWindowTitle(QCoreApplication::translate("dashboard", "MainWindow", nullptr));
        start->setText(QCoreApplication::translate("dashboard", "Start this Recipe", nullptr));
        recipeName->setText(QCoreApplication::translate("dashboard", "TextLabel", nullptr));
        servingSize->setText(QCoreApplication::translate("dashboard", "TextLabel", nullptr));
        totalNutrition->setText(QCoreApplication::translate("dashboard", "TextLabel", nullptr));
        ingredients->setText(QCoreApplication::translate("dashboard", "TextLabel", nullptr));
        prepTime->setText(QCoreApplication::translate("dashboard", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dashboard: public Ui_dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
