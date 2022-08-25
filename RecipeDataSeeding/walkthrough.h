#ifndef WALKTHROUGH_H
#define WALKTHROUGH_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class walkthrough;
}

class walkthrough : public QMainWindow
{
    Q_OBJECT

public:
    explicit walkthrough(QJsonArray &steps,int recipeID,QWidget *parent = nullptr);
    ~walkthrough();
    QList<QString>* setupSteps(QJsonArray &steps);
    void setupButtons(int number);
    void setupPages(int number,  QVector<int> vec);
    void setSteps(int s);
    int getSteps();
    QList<QString>* splitInstruction(QString &s, int q);
    QList<QString>* split(QString &s);


    QVector<int> getNumberOfSubSteps();

    //we need a function to measure each ingredient in the instructions

public slots:
    void onPageClick();

private:
    Ui::walkthrough *ui;
    int recipeID;
    QVBoxLayout *layout;
    int numOfSteps;
    QList<QString> *measureArray; //this array is used to compare the ingredients to the ingredient in the intruction string, so we can place it in the portioning string
};

#endif // WALKTHROUGH_H
