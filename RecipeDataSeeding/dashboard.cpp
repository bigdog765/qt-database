#include "dashboard.h"
#include "ui_dashboard.h"
#include "mainwindow.h"
#include "walkthrough.h"

dashboard::dashboard(QJsonObject &Obj,int recipeID,QWidget *parent) :QMainWindow(parent),ui(new Ui::dashboard)
{
    this->recipeID = recipeID;
    steps = new QJsonArray();

    ui->setupUi(this);
    displayRecipeInfo(Obj);

}

void dashboard::displayRecipeInfo(QJsonObject &Obj)
{
    QJsonValue v;
    QString title;
    int prep;
    int serving;
    QString nutrition;
    QString ingredients;

    //nutrition{nutrients[{Calories,fat,etc.}{Calories,fat,etc.}]} Mainobj->obj->array->obj
    for(auto i = Obj.begin(); i != Obj.end();i++){ 
        if(i.key().toUtf8() == "nutrition"){ //nutrition key is an object
            QJsonObject nutrObj = i->toObject();
            nutrition = getTotalNutrients(nutrObj);
        }
        else if(i.key().toUtf8() == "extendedIngredients"){ //extended ingredient key is an array
            QJsonArray ingrArr = i->toArray();
            ingredients = getIngredients(ingrArr);
        }
        else if(i.key().toUtf8() == "analyzedInstructions"){
            QJsonArray steps = i->toArray();
            setSteps(steps);
        }
        else {

            //q is the key
            QString q = i.key().toUtf8();

            //fetch relevant keys
            if(q == "title"){
                v = Obj.value("title");
                title = v.toString();
            }
            else if(q == "servings"){

                v = Obj.value("servings");
                serving = v.toInt();

            }
            else if(q == "readyInMinutes"){
                v = Obj.value("readyInMinutes");
                prep = v.toInt();

            }
        }
    }
    ui->recipeName->setText(title);
    ui->servingSize->setText("Servings: " + QString::number(serving));
    ui->prepTime->setText("Time to Complete: " + QString::number(prep) + " min");
    ui->totalNutrition->setText(nutrition);
    ui->ingredients->setText(ingredients);
}

QString dashboard::getTotalNutrients(QJsonObject &Obj)
{
    QJsonArray nutrients;
    for(auto i = Obj.begin(); i != Obj.end();i++){

        if(i.key().toUtf8() == "nutrients"){
            qDebug() << "key is nutrients";
            nutrients = i->toArray();
            break;
        }
    }
    bool skip = true;
    double amount;
    QString unit;
    QString result = "Total Nutrients: ";

    //json file parses keys in althebetical order
    for(auto j = nutrients.begin(); j != nutrients.end();j++){

        QJsonObject f;
        f =j->toObject();
        for(auto k = f.begin(); k != f.end();k++){
            //check for certain nutritional value
            if(k.value() == "Calories"){
               skip = false;
               result.append("Calories: ");
            }
            else if(k.value() == "Fat"){
               skip = false;
               result.append("Fat: ");
            }
            else if(k.value() == "Carbohydrates"){
               skip = false;
               result.append("Carbohydrates: ");
            }
            else if(k.value() == "Protein"){
               skip = false;
               result.append("Protein: ");
            }


            //obtain specific amount plus unit
            if(k.key().toUtf8() == "amount"){
                amount = k.value().toDouble();
            }
            if(k.key().toUtf8() == "unit"){
                unit = k.value().toString().toUtf8();
            }

        }
        if(!skip){

            result.append(QString::number(amount) + unit + " ");
            skip = true;
        }
    }
    qDebug() << result;
    return result;

}

QString dashboard::getIngredients(QJsonArray &arr)
{
    QString result = "Ingredients: ";
    QString name,unit;
    double amount;
    for(auto i = arr.begin(); i != arr.end();i++){

        QJsonObject f;
        f =i->toObject();
        for(auto j = f.begin(); j != f.end();j++){
            if(j.key() == "name"){
                name = j.value().toString();

            }
            else if(j.key() == "amount"){
                amount = j.value().toDouble();
            }
            else if(j.key() == "unit"){
                unit = j.value().toString();
            }
        }
        result.append(QString::number(amount) + " " + unit + " " + name + ", ");
    }

    return result;
}

int dashboard::getRecipeID()
{
    return recipeID;
}

void dashboard::setSteps(QJsonArray &stepArr)
{
    steps = new QJsonArray(stepArr);
}

dashboard::~dashboard()
{
    delete ui;
}

void dashboard::on_start_clicked()
{

    //link new window
    walkthrough *walk = new walkthrough(*steps,recipeID);
    walk->show();
}

