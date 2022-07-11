#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"



#include <QApplication>

#include <QGuiApplication>


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QEvent>
#include <QDebug>
#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QString>
#include <QStringList>



MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::on_pushButton_clicked()
{

   QString queryIn = ui->in1->text();
   ui->listWidget->clear();
   getSearchResults(queryIn);


}
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //implement SPECIFIC ingredient nutritional info
    QString name = item->text();
    ui->titleFood->setText("Nutrition Preview of " + name);
    qDebug() << "\n\n\n\n\n";
    getFoodNutrients(name);
}
void MainWindow::getFoodNutrients(QString foodName){
    const QByteArray APP_ID = "3a3bcc0b";
    const QByteArray API_KEY = "9fd8be4795a30b3146947c62eaf3795f";
    const QByteArray FOOD_RESULT_URL = "https://trackapi.nutritionix.com/v2/natural/nutrients";

    QUrl food_url(FOOD_RESULT_URL);
    QNetworkRequest food_request(food_url);

    food_request.setRawHeader("Content-Type", "application/json");
    food_request.setRawHeader("x-app-id", APP_ID);
    food_request.setRawHeader("x-app-key", API_KEY);

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

        QObject::connect(manager,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QByteArray dataString = "{ \"query\": \""+ foodName.toUtf8() +"\" }";
        QNetworkReply* reply = manager->post(food_request, dataString);
        loop.exec();
        QString response = (QString)reply->readAll();
        qDebug() << "Response: " + response;

        QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject jObj = doc.object();
        //get serving_qty, serving_unit, serving_weight_grams,calories,fat,carbs,protein.(Preview)
        for(auto i = jObj.begin(); i != jObj.end();i++){
            if(i->isArray()){
                QJsonArray jArr = i->toArray();
                checkArray(jArr,true);
            }
            else if(!i->isArray())
                qDebug() << "Json file has no arrays.";

        }

}


void MainWindow::getSearchResults(QString textQuery){

   const QByteArray APP_ID = "3a3bcc0b";
   const QByteArray API_KEY = "9fd8be4795a30b3146947c62eaf3795f";
   const QByteArray SEARCH_RESULT_URL = "https://trackapi.nutritionix.com/v2/search/instant?query=";


   QUrl search_url(SEARCH_RESULT_URL + textQuery + "");
       QNetworkRequest search_request(search_url);

       search_request.setRawHeader("Content-Type", "application/json");
       search_request.setRawHeader("x-app-id", APP_ID);
       search_request.setRawHeader("x-app-key", API_KEY);



       QNetworkAccessManager *manager = new QNetworkAccessManager();
       QEventLoop loop;

           QObject::connect(manager,
                            SIGNAL(finished(QNetworkReply*)),
                            &loop,
                            SLOT(quit()));

           QNetworkReply* reply = manager->get(search_request);
           loop.exec();

           //display raw json
           QString response = (QString)reply->readAll();
           qDebug() << "Response: " + response;


           //setup qt json libraries
           QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
           QJsonObject jObj = doc.object();


           for(auto i = jObj.begin(); i != jObj.end();i++){
               bool branded;
               branded = i.key().toStdString() == "branded";

               if(i->isArray() && !branded){ //change this if we want to display branded ingredients
                   QJsonArray jArr = i->toArray();
                   checkArray(jArr,false);
               }
               else if(!i->isArray())
                   qDebug() << "Json file has no arrays.";

           }

}
void MainWindow::checkArray(QJsonArray &a, bool nutr){
   auto i = a.begin();

   if(i->isArray()){ //check for nested arrays
        QJsonArray b = i->toArray();
        qDebug() << "nested array";
       checkArray(b,nutr); //recursive call
   }
   else{
       if(nutr)
           showNutrients(a);
       else populateSearchResults(a);
       return;
   }
}
void MainWindow::populateSearchResults(QJsonArray &a){
    const int RESULT_LIMIT = 30;
    bool empty = true;
    int ctr = 0;

    for(auto k = a.begin(); k != a.end(); k++){ //return all values with key food_name
        QJsonObject returnObject = k->toObject();
        if(returnObject.contains("food_name")){
            ui->listWidget->addItem(returnObject.value("food_name").toString());
            empty = false;
            ctr++;
        }

        if(ctr >= RESULT_LIMIT)
            break;
    }
    if(empty)
        qDebug() << "No results.";
}

//this is just the preview of nutritional information
void MainWindow::showNutrients(QJsonArray &a){
    bool empty = false;
    QString nutrResult;
    //return all values with key serving_qty, serving_unit, serving_weight_grams,calories,fat,carbs,protein

        auto k = a.begin(); //first array named "foods"

        QJsonObject rObject = k->toObject();
        double d;
        QJsonValue r;
        if(rObject.isEmpty())
            empty = true;
        if(rObject.contains("serving_qty")){
            r = rObject.value("serving_qty");
            d = r.toDouble();
            nutrResult.append("Serving Quantity: " + QString::number(d) +"   ");
        }
        if(rObject.contains("serving_unit")){
            r = rObject.value("serving_unit");
            nutrResult.append("Serving Unit: " + r.toString()+"   ");
        }
        if(rObject.contains("serving_weight_grams")){
            r = rObject.value("serving_weight_grams");
            d = r.toDouble();
            nutrResult.append("Weight(g): " + QString::number(d)+"   ");
        }
        if(rObject.contains("nf_calories")){
            r = rObject.value("nf_calories");
            d = r.toDouble();
            nutrResult.append("Calories: " + QString::number(d)+"   ");
        }
        if(rObject.contains("nf_total_fat")){
            r = rObject.value("nf_total_fat");
            d = r.toDouble();
            nutrResult.append("Fat: " + QString::number(d)+"   ");
        }
        if(rObject.contains("nf_total_carbohydrate")){
            r = rObject.value("nf_total_carbohydrate");
            d = r.toDouble();
            nutrResult.append("Carbs: " + QString::number(d)+"   ");
        }
        if(rObject.contains("nf_protein")){
            r = rObject.value("nf_protein");
            d = r.toDouble();
            nutrResult.append("Protein: " + QString::number(d)+"   ");
        }

    if(empty)
        qDebug() << "No results.";
    else{
        qDebug() << nutrResult;
        ui->nutritionFood->setText(nutrResult);
    }
}











