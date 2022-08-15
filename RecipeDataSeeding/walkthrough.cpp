#include "walkthrough.h"
#include "ui_walkthrough.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QPushButton"
#include "QLabel"

walkthrough::walkthrough(QJsonArray &steps,int recipeID,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::walkthrough)
{
    ui->setupUi(this);
    layout = ui->verticalLayout;
    recipeID = this->recipeID;

    QList<QString> *listOfSteps = new QList<QString>;
    listOfSteps = setupSteps(steps);


    setupPages(numOfSteps, listOfSteps);
    setupButtons(numOfSteps);

    //make a dummy parent for the layout
    QWidget *parentL = new QWidget(ui->verticalLayoutWidget);

    //now we can display the layout
    parentL->setLayout(layout);
    parentL->show();

    //create an array of buttons from the layout so we can implement each button click
    QList<QPushButton*> listB = layout->parentWidget()->findChildren<QPushButton*>();
    qDebug() << listB.size();



    for(int i=0;i< numOfSteps;i++){
        qDebug() << (*listB.at(i)).objectName();
        connect(listB.at(i),SIGNAL(clicked()),this,SLOT(onPageClick()));

    }

}

walkthrough::~walkthrough()
{
    delete ui;
}

QList<QString>* walkthrough::setupSteps(QJsonArray &steps)
{
    QString totalStepsString;
    QList<QString> *listSteps = new QList<QString>;


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

                //this gets total number of steps
                ctr++;
            }
            else if(l.key().toUtf8() == "step"){
                QString txt = l.value().toString();
                totalStepsString.append(txt);

                //inserts each step into a string list
                listSteps->append(txt);
            }
        }
    }

    setSteps(ctr);

    //this will show the whole instruction list
    qDebug() << totalStepsString;

    return listSteps;

}

void walkthrough::setupButtons(int number)
{

    for(int i = 1; i <= number;i++){
         QString buttonText = "Step " + QString::number(number - i + 1);
         QPushButton* button = new QPushButton(buttonText, ui->verticalLayoutWidget);
         button->setObjectName("step" + QString::number(i));
         //insert buttons into the layout depending on how many steps
         layout->insertWidget(0, button);
         qDebug() << "Button added";

    }
}

void walkthrough::setupPages(int number, QList<QString> *&s)
{

    for(int i =0;i < number; i++){
        QWidget *pageWidget = new QWidget(ui->stackedWidget);
        pageWidget->setObjectName("page " + QString::number(i+1));

        QLabel *lblPage = new QLabel(pageWidget);
        QLabel *lblStep = new QLabel(pageWidget);
        lblPage->setObjectName("label" + QString::number(i+1));
        lblPage->setText("Page " + QString::number(i+1));

        lblStep->setObjectName("step " + QString::number(i+1));
        //get specific step index and insert into page label
        lblStep->setText(s->at(i));
        lblStep->setGeometry(50,150,570,280);
        lblStep->setAlignment(Qt::AlignTop);
        lblStep->setWordWrap(true);

        //add specific page to stack
        ui->stackedWidget->insertWidget(0,pageWidget);

        qDebug() << "Page inserted";

    }
}

void walkthrough::setSteps(int s)
{
    numOfSteps = s;
}

int walkthrough::getSteps()
{
    return numOfSteps;
}

void walkthrough::onPageClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << button->objectName();
    QChar number = button->objectName().back();
    int a = number.digitValue();
    ui->stackedWidget->setCurrentIndex(a-1);


}
