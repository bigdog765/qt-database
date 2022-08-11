#include "walkthrough.h"
#include "ui_walkthrough.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QPushButton"

walkthrough::walkthrough(QJsonArray &steps,int recipeID,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::walkthrough)
{
    ui->setupUi(this);
    printSteps(steps);
}

walkthrough::~walkthrough()
{
    delete ui;
}

void walkthrough::printSteps(QJsonArray &steps)
{
    QString totalStepsString;
    //get 'steps' array, stores in g
    QJsonArray g;
    for(auto i = steps.begin(); i != steps.end(); i++){
        QJsonObject f;
        f =i->toObject();
        for(auto j = f.begin(); j != f.end(); j++){
            if(j.key().toUtf8() == "steps"){
                g = j->toArray();
            }
        }
    }

    //print out each step
    int ctr = 0;
    for(auto k = g.begin(); k != g.end(); k++){
        QJsonObject h;
        h = k->toObject();
        for(auto l = h.begin(); l != h.end(); l++){
            if(l.key().toUtf8() == "number"){
                int s = l.value().toInt();
                totalStepsString.append("Step " + QString::number(s) + ": ");
                ctr++;
            }
            else if(l.key().toUtf8() == "step"){
                QString txt = l.value().toString();
                totalStepsString.append(txt);
            }
        }
    }
    setupButtons(ctr);
    ui->steps->setText(totalStepsString);

}

void walkthrough::setupButtons(int number)
{
    QVBoxLayout* layout = ui->verticalLayout;

    for(int i = 1; i <= number;i++){
         QString buttonText = "Step " + QString::number(i);
         QPushButton* button = new QPushButton(buttonText, ui->verticalLayoutWidget);
         layout->insertWidget(i, button);

    }

}
