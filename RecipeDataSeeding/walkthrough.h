#ifndef WALKTHROUGH_H
#define WALKTHROUGH_H

#include <QMainWindow>

namespace Ui {
class walkthrough;
}

class walkthrough : public QMainWindow
{
    Q_OBJECT

public:
    explicit walkthrough(QJsonArray &steps,int recipeID,QWidget *parent = nullptr);
    ~walkthrough();
    void printSteps(QJsonArray &steps);
    void setupButtons(int number);

private:
    Ui::walkthrough *ui;
};

#endif // WALKTHROUGH_H
