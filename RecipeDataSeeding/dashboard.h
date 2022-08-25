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
    dashboard(QJsonObject &Obj,int recipeID,QWidget *parent = nullptr);
    void displayRecipeInfo(QJsonObject &Obj);
    QString getTotalNutrients(QJsonObject &Obj);
    QString getIngredients(QJsonArray &arr);
    QString getEquipment(QJsonArray &arr);
    int getRecipeID();
    QString getMicroNutrients();
    void setMicroNutrients(QString &s);
    void setSteps(QJsonArray &stepArr);
    ~dashboard();


private slots:
    void on_start_clicked();

private:
    Ui::dashboard *ui;
    int recipeID;
    QJsonArray *steps; //stores all instruction strings
    QString micro; //stores all micronutrients
    QList<QString> *ingr; //stores all ingredients(this is used for the walkthrough page)

};

#endif // DASHBOARD_H
