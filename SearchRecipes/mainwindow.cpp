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

struct recipe {
    QString name;
    int id;
};

QVector<recipe> recList;

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

    int id = 0;
    for (int i = 0; i < recList.size(); ++i) {
        if (recList.at(i).name == foodName)
            id = recList.at(i).id;
    }
    QString idS = QString::number(id);
    qDebug() << idS;



    QJsonObject obj;
        obj["id"] = QJsonValue(idS);
        QJsonObject parent;
        parent["data"] = obj;
        QJsonDocument docJ(parent);
        QByteArray data = docJ.toJson();
        qDebug() << data;

    const QByteArray FOOD_RESULT_URL = "https://us-central1-versaware-dev.cloudfunctions.net/getRecipe";

    qDebug() << FOOD_RESULT_URL;
    QUrl food_url(FOOD_RESULT_URL);
    QNetworkRequest food_request(food_url);

    food_request.setRawHeader("Content-Type", "application/json");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

        QObject::connect(manager,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));


        QNetworkReply* reply = manager->post(food_request,data);
        loop.exec();
        QString response = (QString)reply->readAll();
        qDebug() << "Response: " + response;

        QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject jObj = doc.object();
        QJsonObject result = jObj.begin()->toObject();
        showNutrients(result);

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
    const int RESULT_LIMIT = 40;
    int ctr = 0;
    recList.clear();

    for(auto k = a.begin(); k != a.end(); k++){ //return all values with key title
        QJsonObject returnObject = k->toObject();
        if(returnObject.contains("title")){
            QString title = returnObject.value("title").toString();
            ui->listWidget->addItem(title);
            if(returnObject.contains("id")){
                QString idS = returnObject.value("id").toString();
                int id = idS.toInt();
                recList.append({title,id});
            }
            ctr++;
        }
        if(ctr >= RESULT_LIMIT)
            break;
    }

}

//this is just the preview of nutritional information
void MainWindow::showNutrients(QJsonObject &obj){

    QString nutrResult;
    QJsonArray nutrition;
    //return all values with key serving_qty, serving_unit, serving_weight_grams,calories,fat,carbs,protein
        for(auto i = obj.begin(); i !=obj.end(); i++){
            if(i.key() == "nutrition"){
                nutrition = i.value().toArray();
                qDebug() << "Nutrition found";
                break;
            }
        }
        for(auto j = nutrition.begin(); j !=nutrition.end(); j++){

            QJsonObject v = j->toObject();
            for (auto m = v.begin(); m != v.end(); ++m) {
                if(m.value() == "Calories"){
                    nutrResult.append("Calories: ");
                }
                else if(m.value() == "Protein"){
                    nutrResult.append("Protein: ");
                }
                else if(m.value() == "Carbohydrates"){
                    nutrResult.append("Protein: ");
                }
                else if(m.value() == "Fat"){
                    nutrResult.append("Fat: ");
                }

                if(m.key() == "amount"){
                    double b = m.value().toDouble();
                    nutrResult.append(QString::number(b));
                }
                if(m.key() == "amountUnit"){
                    nutrResult.append(m.value().toString());
                }
            }

        }
        qDebug() << "Nutrition result:" + nutrResult;
        ui->nutritionFood->setText(nutrResult);

}











