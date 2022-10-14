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
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating a MainWindow obj will initialize the App
    MainWindow w;

    w.show();

    return a.exec();
}
