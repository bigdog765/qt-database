#include "dashboard.h"
#include "ui_dashboard.h"
#include "mainwindow.h"
#include "walkthrough.h"

dashboard::dashboard(QJsonObject &Obj,int id,QWidget *parent) :QMainWindow(parent),ui(new Ui::dashboard)
{

    recipeID = id;
    steps = new QJsonArray();

    ui->setupUi(this);
    displayRecipeInfo(Obj);

}

void dashboard::displayRecipeInfo(QJsonObject &Obj)
{
    QJsonValue v;
    QString title;
    QString prep;
    int serving;
    QString nutrition;
    QString ingredients;
    QString equipment;
    QString micro;


    QJsonObject result = Obj.begin()->toObject();

    for(auto i = result.begin(); i != result.end();i++){
        qDebug() << i.key();
        if(i.key().toUtf8() == "nutrition"){ //nutrition key is an array

            QJsonArray nutritionArr = i->toArray();
            nutrition = getTotalNutrition(nutritionArr);

        }
        else if(i.key().toUtf8() == "nutrients"){
            QJsonArray nutrientArr = i->toArray();
            micro = getTotalNutrient(nutrientArr);
        }
        else if(i.key().toUtf8() == "ingredients"){ //extended ingredient key is an array
            QJsonArray ingrArr = i->toArray();
            ingredients = getIngredients(ingrArr);
        }
        else if(i.key().toUtf8() == "steps"){

            QJsonArray steps = i->toArray();
            equipment = getEquipment(steps);
            //passes instruction array to walkthrough
            setSteps(steps);
        }
        else {

            //q is the key
            QString q = i.key().toUtf8();

            //fetch relevant keys
            if(q == "title"){
                v = result.value("title");
                title = v.toString();
                qDebug() << "Title:" + title;
            }
            else if(q == "serves"){
                v = result.value("serves");
                serving = v.toInt();
            }
            else if(q == "cookingTime"){
                v = result.value("cookingTime");
                prep = v.toString();
            }
        }
    }
    ui->recipeName->setText(title);
    ui->servingSize->setText("Servings: " + QString::number(serving));
    ui->prepTime->setText("Time to Complete: " + prep);
    ui->totalNutrition->setText(nutrition);
    ui->extendedNutrition->setText(micro);
    ui->ingredients->setText(ingredients);
    ui->equipment->setText(equipment);
}

QString dashboard::getTotalNutrition(QJsonArray &Arr)
{
    qDebug() << "Nutrition";
    double amount;
    QString unit;
    QString result = "Total Nutrition: ";

    //json file parses keys in althebetical order
    for(auto j = Arr.begin(); j != Arr.end();j++){

        QJsonObject f;
        f =j->toObject();
        for(auto k = f.begin(); k != f.end();k++){
            //check for certain nutritional value
            if(k.value() == "Calories"){

               result.append("Calories: ");
            }
            else if(k.value() == "Fat"){

               result.append("Fat: ");
            }
            else if(k.value() == "Carbohydrates"){

               result.append("Carbohydrates: ");
            }
            else if(k.value() == "Protein"){

               result.append("Protein: ");
            }

            //obtain specific amount plus unit
            if(k.key().toUtf8() == "amount"){
                amount = k.value().toDouble();
            }
            if(k.key().toUtf8() == "amountUnit"){
                unit = k.value().toString().toUtf8();
            }
        }

        result.append(QString::number(amount) + unit + " ");
    }
    qDebug() << result;
    return result;
}
QString dashboard::getTotalNutrient(QJsonArray &Arr)
{
    qDebug() << "Nutrients";
    double amount;
    QString unit;
    QString result = "Total Micro Nutrients: ";

    //json file parses keys in althebetical order
    for(auto j = Arr.begin(); j != Arr.end();j++){

        QJsonObject f;
        f =j->toObject();
        for(auto k = f.begin(); k != f.end();k++){
            if(k.key().toUtf8() == "title")
                result.append(k.value().toString() + ": ");

            //obtain specific amount plus unit
            if(k.key().toUtf8() == "amount"){
                amount = k.value().toDouble();
            }
            if(k.key().toUtf8() == "amountUnit"){
                unit = k.value().toString().toUtf8();
            }
        }

        result.append(QString::number(amount) + unit + " ");
    }
    qDebug() << result;
    return result;
}

QString dashboard::getIngredients(QJsonArray &arr)//arr->obj->key
{
    QString result = "Ingredients: ";
    QString name,unit;
    int id;
    double amount;

    ingr = new QList<QString>;
    for(auto i = arr.begin(); i != arr.end();i++){

        QJsonObject f;
        f =i->toObject();
        for(auto j = f.begin(); j != f.end();j++){
            if(j.key() == "id"){
                id = j.value().toInt();
                setIngredientID(id);
            }
            else if(j.key() == "name"){
                name = j.value().toString(); //SAVE THIS IN AN ARRAY
                ingr->push_back(name);

            }
            else if(j.key() == "amountUS"){
                amount = j.value().toDouble();
            }
            else if(j.key() == "amountUnitUS"){
                unit = j.value().toString();
            }
        }
        result.append(QString::number(amount) + " " + unit + " " + name + ", ");
    }
    return result;
}


QString dashboard::getEquipment(QJsonArray &arr)
{
    QString result = "Equipment Needed: ";

    for(auto i = arr.begin(); i!= arr.end(); i++){
        QJsonObject a;
        a=i->toObject();
        for(auto j = a.begin(); j != a.end(); j++){
            if(j.key() == "steps"){
                QJsonArray b = j->toArray();
                for(auto k = b.begin(); k!= b.end(); k++){
                    QJsonObject c;
                    c=k->toObject();
                    for(auto l = c.begin(); l != c.end(); l++){
                        if(l.key() == "equipment"){
                            QJsonArray d = l->toArray();
                            for(auto m = d.begin(); m != d.end(); m++){
                                QJsonObject e;
                                e=m->toObject();
                                for(auto n = e.begin(); n != e.end(); n++){
                                    if(n.key() == "name"){
                                        QString newEquip = n.value().toString();
                                        if(result.contains(newEquip)){
                                            qDebug() << "already listed";
                                        }
                                        else{
                                            result.append(newEquip + ", ");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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

QVector<int> dashboard::getIngredientID()
{
    return ingrIDs;
}

void dashboard::setIngredientID(int id)
{
    ingrIDs.append(id);
}

dashboard::~dashboard()
{
    delete ui;
}

void dashboard::on_start_clicked()
{
    //test ingredient ids
    for(int i = 0; i < ingrIDs.size(); i++){
        qDebug() << ingrIDs.at(i);
    }
    //After Start Recipe clicked, link new Walkthrough of Steps
    walkthrough *walk = new walkthrough(*steps,recipeID,ingrIDs);
    walk->show();
}

