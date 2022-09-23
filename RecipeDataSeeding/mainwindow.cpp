#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dashboard.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGroupBox *group = ui->groupBox;

    QList<QPushButton*> allPButtons = group->findChildren<QPushButton*>();


    for(int i=0;i< allPButtons.size();i++){
        connect(allPButtons.at(i),SIGNAL(clicked()),this,SLOT(onButtonClick()));

    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onButtonClick(){

    //get specific button from sender
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << button->objectName();
    int id = getRecipeId(button->objectName());
    QString result = getRecipeContent(id);

    //setup qt json libraries
    QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    QJsonObject jObj = doc.object();

    //link new window

    dashboard *dash = new dashboard(jObj,id);
    dash->show();

}
int MainWindow::getRecipeId(QString name){
    //manually get id from specific button
    int id;
    //button1 = Kale Salad = 660108
    if(name.endsWith('1')){
        id = 660108;
    }
    //button2 = Chili = 646567
    else if(name.endsWith('2')){
        id = 646567;
    }
    //button3 = Macaroni Pasta = 643642
    else if(name.endsWith('3')){
        id = 643642;
    }
    //button4 = Muffins = 646443
    else if(name.endsWith('4')){
        id = 1096070;
    }
    //button5 = Tomato Soup = 1096214
    else if(name.endsWith('5')){
        id = 1096214;
    }
    //button6 = Chicken Parm = 638235
    else if(name.endsWith('6')){
        id = 638235;
    }
    //button7 = Ramen = 646974
    else if(name.endsWith('7')){
        id = 646974;
    }
    //button8 = Chicken Salad = 715522
    else if(name.endsWith('8')){
        id = 715522;
    }
    else return -1;
    return id;
}
QString MainWindow::getRecipeContent(int id){
/*
 * OLD VERSION
    QByteArray RECIPE_URL = "https://api.spoonacular.com/recipes/" + QString::number(id).toUtf8() + "/information?apiKey=81e81ac3e7c14d2b9913ceebbbb4025a&includeNutrition=true";
    QUrl food_url(RECIPE_URL);
    QNetworkRequest food_request(food_url);
    food_request.setRawHeader("Content-Type", "application/json");
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;
        QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
        QNetworkReply* reply = manager->get(food_request);
        loop.exec();
        QString response = (QString)reply->readAll();
        //qDebug() << "Response: " + response;
*/
    QByteArray rID = QString::number(id).toUtf8();
    //new version with web layer URL
    QByteArray RECIPE_URL = "https://us-central1-versaware-dev.cloudfunctions.net/getRecipe?name=" + rID;

    QUrl food_url(RECIPE_URL);
    QNetworkRequest food_request(food_url);

    //food_request.setRawHeader("Content-Type", "application/json");
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QUrlQuery params;
    params.addQueryItem("name",rID);
    QByteArray p = params.query(QUrl::FullyEncoded).toUtf8();

    QEventLoop loop;
    QObject::connect(manager,
                             SIGNAL(finished(QNetworkReply*)),
                             &loop,
                             SLOT(quit()));
    QNetworkReply* reply = manager->post(food_request,p);
    loop.exec();
    QString response = (QString)reply->readAll();
    qDebug() << "Response: " + response;

    return response;
}
