#include "measure.h"
#include "ui_measure.h"
#include "dashboard.h"

measure::measure(QVector<int> ingr,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measure)
{
    ui->setupUi(this);
    //in the dashboard function, create a function that returns an array of all ingredient ids
    printIngredients(ingr);
}

void measure::printIngredients(QVector<int> ingr)
{
    for(int i = 0; i < ingr.length(); i++){
        qDebug() << ingr.at(i);
        qDebug() << " ";
    }
}

measure::~measure()
{
    delete ui;
}
