#ifndef WALKTHROUGH_H
#define WALKTHROUGH_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class walkthrough;
}

class walkthrough : public QMainWindow
{
    Q_OBJECT

public:
    explicit walkthrough(QJsonArray &steps,int recipeID,QVector<int> ingredients,QWidget *parent = nullptr);
    ~walkthrough();

    void setupButtons(int number);
    void setupPages(int number);
    void setSteps(int s);
    int getSteps();

    //******These functions are NOT used for manually inserted instructions
    QList<QString>* setupSteps(QJsonArray &steps);
    QList<QString>* splitInstruction(QString &s, int q);
    QList<QString>* split(QString &s);
    //*************************


    void setSubButtonsNext(QPushButton *&b);
    QList<QPushButton*> getSubButtonsNext();
    void setSubButtonsPrev(QPushButton *&b);
    QList<QPushButton*> getSubButtonsPrev();
    void setScaleButtons(QPushButton *&b);
    QList<QPushButton*> getScaleButtons();
    QVector<int> getNumberOfSubSteps();


public slots:
    void onPageClick();
    void onSubClickNext();
    void onSubClickPrev();
    void onScaleClick();

private:
    Ui::walkthrough *ui;
    int recipeID;
    QVBoxLayout *layout;
    int numOfSteps;
    QList<QPushButton*> subButtonsNext;
    QList<QPushButton*> subButtonsPrev;
    QList<QPushButton*> scaleButtons;
    QVector<int> ingr;
    QVector<int> mainAndSubPageArray = {0,0};
};

#endif // WALKTHROUGH_H
