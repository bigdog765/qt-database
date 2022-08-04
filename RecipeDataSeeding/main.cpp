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
    MainWindow w;
    w.show();
    w.getButtons();
    return a.exec();
}
