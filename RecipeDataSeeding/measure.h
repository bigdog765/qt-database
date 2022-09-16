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
    explicit measure(int id,QVector<int> pages,QWidget *parent = nullptr);
    void setID();
    void showIngredient(int id);
    ~measure();

private:
    Ui::measure *ui;
    int recipeID;
    QVector<int> pageIndex = {0,0};
};

#endif // MEASURE_H
