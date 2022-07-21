#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>



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

void MainWindow::uploadUser(QString first, QString last, int age){
    ui->attempt->setText("Connecting to Database...");
    bool connected = false;
    connected = initDatabase();
    if(connected){
        ui->attempt->setText("Connected");
        QString date = QDate::currentDate().toString();
        //START SQL QUERIES

        QSqlQuery query;
            query.prepare("INSERT INTO Users (userID, first, last, age, dateOfActivation) "
                          "VALUES (?, ?, ?, ?, ?)");

            query.bindValue(1, first);
            query.bindValue(2, last);
            query.bindValue(3, age);
            query.bindValue(4, date);
            if(query.exec()){
                qDebug() << "Query Done";
            }else{

                qDebug() << "Query not executed";
                showError(query.lastError());
            }

    }
    else ui->attempt->setText("Error Connecting to Database");
}

bool MainWindow::initDatabase()
{
    const QString ADDRESS = "34.71.81.194"; //GOOGle cloud IP address
    const QString USERNAME = "root";
    const QString PASSWORD = ""; //password not working

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("demo-db");
    db.setHostName(ADDRESS);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);


    if (db.open()){
        qDebug() << "Successful Connection";
        return true;
    }
    else{
        showError(db.lastError());
        return false;
    }

}
void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}


void MainWindow::on_connect_clicked()
{
    QString first = ui->inputF->text();
    QString last = ui->inputL->text();
    int age = ui->inputA->text().toInt();
    //make sure age input is an integer


    uploadUser(first,last,age);
}

