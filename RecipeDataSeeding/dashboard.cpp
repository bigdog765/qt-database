#include "dashboard.h"
#include "ui_dashboard.h"

dashboard::dashboard(QJsonObject &Obj,QWidget *parent) :QMainWindow(parent),ui(new Ui::dashboard)
{
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
    for(auto i = Obj.begin(); i != Obj.end();i++){ 
        if(i.key().toUtf8() == "nutrition"){
            QJsonObject nutrObj = i->toObject();
            nutrition = getTotalNutrients(nutrObj);
        }
        if(i->isArray()){
            qDebug() << "Array.";
            //break array down
        }
        else if(!i->isArray()){

            //q is the key
            QString q = i.key().toUtf8();
            qDebug() << "Not array. " + q;

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

    qDebug() << "******************";
    qDebug() << nutrients.size();

    bool skip = true;
    double amount;
    QString unit;
    QString result = "Total Nutrients: ";
    for(auto j = nutrients.begin(); j != nutrients.end();j++){
        qDebug() << "hello";

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
            qDebug() << "TESTTT";
            result.append(QString::number(amount) + unit + " ");
            skip = true;
        }
    }
    qDebug() << result;
    return result;

}

dashboard::~dashboard()
{
    delete ui;
}
