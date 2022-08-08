#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit dashboard(QJsonObject &Obj,QWidget *parent = nullptr);
    void displayRecipeInfo(QJsonObject &Obj);
    ~dashboard();

private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
