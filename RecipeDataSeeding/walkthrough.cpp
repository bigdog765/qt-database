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

    //number of steps
    int numP = printSteps(steps);


    //the layout w/ buttons
    QVBoxLayout* lay = setupButtons(numP);

    //setupPages(numP);

    //this creates a list of buttons from the layout
    QList<QPushButton*> listB = lay->parentWidget()->findChildren<QPushButton*>();
    qDebug() << listB.size();



    for(int i=0;i< numP;i++){
        qDebug() << listB.at(i)->objectName();
        connect(listB.at(i),SIGNAL(clicked()),this,SLOT(onPageClick()));

    }

}

walkthrough::~walkthrough()
{
    delete ui;
}

int walkthrough::printSteps(QJsonArray &steps)
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





    qDebug() << totalStepsString;
    //ui->steps->setText(totalStepsString);
    qDebug() << "totalStepsString";
    return ctr;

}

QVBoxLayout* walkthrough::setupButtons(int number)
{
    //create a dummy parent for the layout
    QWidget *parent = new QWidget();

    QVBoxLayout* layout = ui->verticalLayout; //this gets deleted after function return (might need to declare as member variable)

    layout->setParent(parent);


    for(int i = 1; i <= number;i++){
         QString buttonText = "Step " + QString::number(i);
         QPushButton* button = new QPushButton(buttonText, ui->verticalLayoutWidget);
         //insert buttons into the layout depending on how many steps
         layout->insertWidget(i, button);
         qDebug() << "Button added";

    }
    qDebug() << layout->count();
    for(int j = 0; j < layout->count(); j++){
        qDebug() << layout->itemAt(j);
    }

    //returns the layout with all the buttons
    return layout;

}

void walkthrough::setupPages(int number)
{
    for(int i =0;i < number; i++){
        QWidget *pageWidget = new QWidget();
        pageWidget->setObjectName("page " + QString::number(i+2));
        ui->stackedWidget->insertWidget(0,pageWidget);
    }
}

void walkthrough::onPageClick()
{
    qDebug() << "test";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << button->objectName();
}
