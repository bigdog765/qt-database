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

    void setupUi(QDialog *measure)
    {
        if (measure->objectName().isEmpty())
            measure->setObjectName(QString::fromUtf8("measure"));
        measure->resize(400, 300);
        buttonBox = new QDialogButtonBox(measure);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        measureIngredient = new QLabel(measure);
        measureIngredient->setObjectName(QString::fromUtf8("measureIngredient"));
        measureIngredient->setGeometry(QRect(150, 110, 49, 16));

        retranslateUi(measure);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, measure, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, measure, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(measure);
    } // setupUi

    void retranslateUi(QDialog *measure)
    {
        measure->setWindowTitle(QCoreApplication::translate("measure", "Dialog", nullptr));
        measureIngredient->setText(QCoreApplication::translate("measure", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class measure: public Ui_measure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_H
