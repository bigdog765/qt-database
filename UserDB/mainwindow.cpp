#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>



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
    ui->attempt->setText("Attempting to Connect...");
    if(initDatabase()){
        //START SQL QUERIES
    }
}

bool MainWindow::initDatabase()
{
    const QString ADDRESS = "34.71.81.194"; //GOOGle cloud IP address
    const QString USERNAME = "root";
    const QString PASSWORD = "Hf~GHaPFppN3U'x/";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //db.setDatabaseName("User");
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

