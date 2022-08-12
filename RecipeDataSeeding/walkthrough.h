#ifndef WALKTHROUGH_H
#define WALKTHROUGH_H

#include <QMainWindow>
#include <QBoxLayout>

namespace Ui {
class walkthrough;
}

class walkthrough : public QMainWindow
{
    Q_OBJECT

public:
    explicit walkthrough(QJsonArray &steps,int recipeID,QWidget *parent = nullptr);
    ~walkthrough();
    int printSteps(QJsonArray &steps);
    QVBoxLayout* setupButtons(int number);
    void setupPages(int number);
public slots:
    void onPageClick();

private:
    Ui::walkthrough *ui;
};

#endif // WALKTHROUGH_H
