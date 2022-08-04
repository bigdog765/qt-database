#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "box.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGroupBox *group = ui->groupBox;

    QList<QPushButton*> allPButtons = group->findChildren<QPushButton*>();
    connect(allPButtons.at(0), &QPushButton::released, this, &MainWindow::onButtonClick);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getButtons()
{






}
bool MainWindow::wasPressed(QPushButton &push){
    return true;
}


void MainWindow::onButtonClick(QPushButton &push){
    qDebug() << push.objectName();
    //pass specific button in


}

