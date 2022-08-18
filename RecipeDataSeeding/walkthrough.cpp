#include "walkthrough.h"
#include "ui_walkthrough.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QPushButton"
#include "QLabel"

walkthrough::walkthrough(QJsonArray &steps,int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::walkthrough)
{
    ui->setupUi(this);
    layout = ui->verticalLayout;
    recipeID = id;

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


//for measuring part of the walkthrough, we can put each ingredient into an array of the specific recipe and scan the ingredient step to see if it has that certain ingredient
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
    int s;
    for(auto k = g.begin(); k != g.end(); k++){
        QJsonObject h;
        h = k->toObject();
        for(auto l = h.begin(); l != h.end(); l++){
            if(l.key().toUtf8() == "number"){
                s = l.value().toInt();
                totalStepsString.append("Step " + QString::number(s) + ": ");

                //this gets total number of steps
                ctr++;
            }
            else if(l.key().toUtf8() == "step"){
                QString txt = l.value().toString();

                //lets us know if the instruction needs to be split into two
                QList<QString> *t = splitInstruction(txt,s);

                if(!t){
                    totalStepsString.append(txt);
                    listSteps->append(txt);
                }
                else{

                    totalStepsString.append(t->at(0));
                    totalStepsString.append(t->at(1));
                    listSteps->append(t->at(0));
                    listSteps->append(t->at(1));
                    ctr++;
                }
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
        QLabel *lblMeasure = new QLabel(pageWidget);
        lblPage->setObjectName("label" + QString::number(i+1));
        lblPage->setText("Step " + QString::number(i+1));

        lblStep->setObjectName("step " + QString::number(i+1));
        lblMeasure->setObjectName("measureLabel" + QString::number(i+1));
        lblMeasure->setText("Measure: ");

        //get specific step index and insert into page label
        lblStep->setText(s->at(i));
        lblStep->setGeometry(50,150,570,280);
        lblStep->setAlignment(Qt::AlignTop);
        lblStep->setWordWrap(true);

        lblMeasure->setGeometry(50,75,570,50);
        lblMeasure->setAlignment(Qt::AlignTop);
        lblMeasure->setWordWrap(true);

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

//this function will manually split certain instruction strings that are too long
//instructions that need to be split:
//kale 1,2
//chili 4
//mac 4
//muffin 3
//basil 2,5
//quiche 2
QList<QString>* walkthrough::splitInstruction(QString &s, int q)
{
    //ids of 6 recipes that need to be split
    int idArr[6] = {660108,646567,643642,1096070,1096214,661249};
    bool tooLong = false;

    int i;
    for(i=0; i < 6; i++){
        if(recipeID == idArr[i]){
            tooLong = true;
            break;
        }
    }
    if(!tooLong)
        return nullptr;
    else{
        if(i == 0){ //kale salad
            qDebug() << q;
            if(q == 1 || q == 2){
                 return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 1){ //chili
            if(q == 4){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 2){ //mac
            if(q == 4){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 3){ //muffin
            if(q == 3){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 4){ //basil
            if(q == 2 || q == 5){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 5){ //quiche
            if(q == 2){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        else{
            return nullptr;
        }

    }
}
QList<QString>* walkthrough::split(QString &s){
    QString per = ".";
    QList<QString> *splitStrings = new QList<QString>(2);
    int mid = s.length() /2;

    //find the closest period to the middle of the string
    int f = s.indexOf(per,mid);
    int b = s.lastIndexOf(per,mid);
    if(f == -1 && b == -1){
        qDebug() << "No period found";
        return 0;
    }
    int indForward = f + 1 - mid;
    int indBackward = mid - b;
    qDebug() << "INDEXES::::";
    qDebug() << indForward;
    qDebug() << indBackward;
    int closest = 0;
    if(indForward <= indBackward)
        closest = s.indexOf(per,mid) + 1;
    else
        closest = s.lastIndexOf(per,mid) + 1;


    QString one = s.left(closest);
    int last = s.length() - closest;
    QString two = s.right(last);
    qDebug() << "****SPLIT STRING:::" + one + "***********"+ two;
    splitStrings->insert(0,one);
    splitStrings->insert(1, two);
    return splitStrings;
}



