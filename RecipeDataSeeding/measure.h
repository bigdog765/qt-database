#ifndef MEASURE_H
#define MEASURE_H

#include <QDialog>

namespace Ui {
class measure;
}

class measure : public QDialog
{
    Q_OBJECT

public:
    explicit measure(QVector<int> ingr,int id,QVector<int> pages,QWidget *parent = nullptr);
    void printIngredients(QVector<int> ingr);
    ~measure();

private:
    Ui::measure *ui;
    QVector<int> ingrIds;
    int recipeID;
    QVector<int> pageIndex = {0,0};
};

#endif // MEASURE_H
