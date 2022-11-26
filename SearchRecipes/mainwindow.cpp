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
    QJsonArray *list = new QJsonArray();
    list->append(foodName);
    QJsonObject obj;
    obj["ingredients"] = QJsonValue(*list);
    QJsonObject parent;
    parent["data"] = obj;
    QJsonDocument docJ(parent);
    QByteArray data = docJ.toJson();
    qDebug() << data;

    const QByteArray FOOD_RESULT_URL = "https://us-central1-versaware-dev.cloudfunctions.net/getIngredient?id=";

    QUrl food_url(FOOD_RESULT_URL);
    QNetworkRequest food_request(food_url);

    food_request.setRawHeader("Content-Type", "application/json");

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
            }
            else if(!i->isArray())
                qDebug() << "Json file has no arrays.";

        }

}


void MainWindow::getSearchResults(QString textQuery){

    QJsonArray *list = new QJsonArray();
    QStringList str_l = textQuery.split(',');
    foreach (QString str, str_l) {
        list->append(str);
    }
    QJsonObject obj;
    obj["ingredients"] = QJsonValue(*list);
    QJsonObject parent;
    parent["data"] = obj;
    QJsonDocument docJ(parent);
    QByteArray data = docJ.toJson();
    qDebug() << data;


   const QByteArray SEARCH_RESULT_URL = "https://us-central1-versaware-dev.cloudfunctions.net/recipeSearch";


   QUrl search_url(SEARCH_RESULT_URL);
   QNetworkRequest search_request(search_url);

   search_request.setRawHeader("Content-Type", "application/json");

        QNetworkAccessManager *manager = new QNetworkAccessManager();
       QEventLoop loop;

           QObject::connect(manager,
                            SIGNAL(finished(QNetworkReply*)),
                            &loop,
                            SLOT(quit()));

           QNetworkReply* reply = manager->post(search_request,data);
           loop.exec();

           //display raw json
           QString response = (QString)reply->readAll();
           qDebug() << "Response: " + response;


           //setup qt json libraries
           QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
           QJsonObject jObj = doc.object();


           QJsonArray result = jObj.begin()->toArray();
            populateSearchResults(result);
}

void MainWindow::populateSearchResults(QJsonArray &a){
    const int RESULT_LIMIT = 30;
    int ctr = 0;

    for(auto k = a.begin(); k != a.end(); k++){ //return all values with key title
        QJsonObject returnObject = k->toObject();
        if(returnObject.contains("title")){
            ui->listWidget->addItem(returnObject.value("title").toString());
            QListWidgetItem *p = ui->listWidget->currentItem();
           //FIX THIS

            ctr++;
        }
        if(ctr >= RESULT_LIMIT)
            break;
    }

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











