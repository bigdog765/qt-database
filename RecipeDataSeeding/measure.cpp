#include "measure.h"
#include "ui_measure.h"
#include "dashboard.h"

measure::measure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measure)
{
    ui->setupUi(this);
    //in the dashboard function, create a function that returns an array of all ingredient ids
}

measure::~measure()
{
    delete ui;
}
