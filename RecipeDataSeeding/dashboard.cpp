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
    int prep;
    int serving;
    QString nutrition;
    QString ingredients;
    QString equipment;
    QString micro;

    //nutrition{nutrients[{Calories,fat,etc.}{Calories,fat,etc.}]} Mainobj->obj->array->obj
    for(auto i = Obj.begin(); i != Obj.end();i++){ 
        if(i.key().toUtf8() == "nutrition"){ //nutrition key is an object
            QJsonObject nutrObj = i->toObject();
            nutrition = getTotalNutrients(nutrObj,0);
            micro = getTotalNutrients(nutrObj,1);
        }
        else if(i.key().toUtf8() == "extendedIngredients"){ //extended ingredient key is an array
            QJsonArray ingrArr = i->toArray();
            ingredients = getIngredients(ingrArr);
        }
        else if(i.key().toUtf8() == "analyzedInstructions"){

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
    ui->extendedNutrition->setText(micro);
    ui->ingredients->setText(ingredients);
    ui->equipment->setText(equipment);
}

QString dashboard::getTotalNutrients(QJsonObject &Obj, bool microNut)//arr->
{
    QJsonArray nutrients;
    for(auto i = Obj.begin(); i != Obj.end();i++){

        if(i.key().toUtf8() == "nutrients"){
            qDebug() << "key is nutrients";
            nutrients = i->toArray();
            break;
        }
    }
    bool microB = true;
    double amount;
    QString unit;
    QString result = "Total Nutrients: ";
    QString micro = "Extended Nutrients: ";

    //json file parses keys in althebetical order
    for(auto j = nutrients.begin(); j != nutrients.end();j++){

        QJsonObject f;
        f =j->toObject();
        for(auto k = f.begin(); k != f.end();k++){
            //check for certain nutritional value
            if(k.value() == "Calories"){
               microB = false;
               result.append("Calories: ");
            }
            else if(k.value() == "Fat"){
               microB = false;
               result.append("Fat: ");
            }
            else if(k.value() == "Carbohydrates"){
               microB = false;
               result.append("Carbohydrates: ");
            }
            else if(k.value() == "Protein"){
               microB = false;
               result.append("Protein: ");
            }
            //micros
            else{
                if(k.key() == "name"){
                    microB = true;
                    micro.append(k.value().toString() + ": ");
                }
            }


            //obtain specific amount plus unit
            if(k.key().toUtf8() == "amount"){
                amount = k.value().toDouble();
            }
            if(k.key().toUtf8() == "unit"){
                unit = k.value().toString().toUtf8();
            }

        }
        if(!microB){

            result.append(QString::number(amount) + unit + " ");
        }
        else{
            micro.append(QString::number(amount) + unit + " ");
        }
    }
    qDebug() << result;
    qDebug() << micro;
    if(!microNut){
        return result;
    }
    else return micro;


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
    //link new window
    walkthrough *walk = new walkthrough(*steps,recipeID,ingrIDs);
    walk->show();
}

