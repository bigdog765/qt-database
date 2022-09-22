/********************************************************************************
** Form generated from reading UI file 'measure.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURE_H
#define UI_MEASURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_measure
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *measureIngredient;
    QLabel *mainNutrients;
    QLabel *microNutrients;

    void setupUi(QDialog *measure)
    {
        if (measure->objectName().isEmpty())
            measure->setObjectName(QString::fromUtf8("measure"));
        measure->resize(646, 375);
        buttonBox = new QDialogButtonBox(measure);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(250, 310, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        measureIngredient = new QLabel(measure);
        measureIngredient->setObjectName(QString::fromUtf8("measureIngredient"));
        measureIngredient->setGeometry(QRect(10, 40, 221, 71));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        measureIngredient->setFont(font);
        mainNutrients = new QLabel(measure);
        mainNutrients->setObjectName(QString::fromUtf8("mainNutrients"));
        mainNutrients->setGeometry(QRect(250, 40, 361, 51));
        microNutrients = new QLabel(measure);
        microNutrients->setObjectName(QString::fromUtf8("microNutrients"));
        microNutrients->setGeometry(QRect(250, 100, 351, 161));

        retranslateUi(measure);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, measure, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, measure, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(measure);
    } // setupUi

    void retranslateUi(QDialog *measure)
    {
        measure->setWindowTitle(QCoreApplication::translate("measure", "Dialog", nullptr));
        measureIngredient->setText(QCoreApplication::translate("measure", "TextLabel", nullptr));
        mainNutrients->setText(QCoreApplication::translate("measure", "TextLabel", nullptr));
        microNutrients->setText(QCoreApplication::translate("measure", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class measure: public Ui_measure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_H
