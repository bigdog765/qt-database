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
    void setupPages(int number, QList<QString> *&s);
    void setSteps(int s);
    int getSteps();
public slots:
    void onPageClick();

private:
    Ui::walkthrough *ui;
    int recipeID;
    QVBoxLayout *layout;
    int numOfSteps;
};

#endif // WALKTHROUGH_H
