#include "walkthrough.h"
#include "ui_walkthrough.h"

walkthrough::walkthrough(QJsonArray &steps,int recipeID,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::walkthrough)
{
    ui->setupUi(this);
}

walkthrough::~walkthrough()
{
    delete ui;
}
