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
    for(auto i = Obj.begin(); i != Obj.end();i++){
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
}

dashboard::~dashboard()
{
    delete ui;
}
