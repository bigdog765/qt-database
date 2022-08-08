#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "box.h"
#include "dashboard.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGroupBox *group = ui->groupBox;

    QList<QPushButton*> allPButtons = group->findChildren<QPushButton*>();
    //QPushButton *B = new QPushButton(this);
    //connect(allPButtons.at(0), &QPushButton::released, this, &MainWindow::onButtonClick);

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
    QString json = getRecipeContent(id);

    //link new window
    dashboard *dash = new dashboard;
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
    //button4 = Pancakes = 646443
    else if(name.endsWith('4')){
        id = 646443;
    }
    //button5 = Tomato Soup = 1096214
    else if(name.endsWith('5')){
        id = 1096214;
    }
    //button6 = Spinach Quiche = 661249
    else if(name.endsWith('6')){
        id = 661249;
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

    const QByteArray API_KEY = "81e81ac3e7c14d2b9913ceebbbb4025a";


    QByteArray url2 = QString::number(id).toUtf8();


    const QByteArray RECIPE_URL = "https://api.spoonacular.com/recipes/";


    QUrl food_url(RECIPE_URL);
    QNetworkRequest food_request(food_url);

    food_request.setRawHeader("Content-Type", "application/json");
    //food_request.setRawHeader("apiKey", API_KEY);




    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

        QObject::connect(manager,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QByteArray dataString = "{ \"id\": \""+ url2 +"\" }";
        QNetworkReply* reply = manager->post(food_request, dataString);
        loop.exec();
        QString response = (QString)reply->readAll();
        qDebug() << "Response: " + response;
        return response;

}
