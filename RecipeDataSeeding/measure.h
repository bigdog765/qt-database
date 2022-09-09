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
    explicit measure(QVector<int> ingr,QWidget *parent = nullptr);
    void printIngredients(QVector<int> ingr);
    ~measure();

private:
    Ui::measure *ui;
};

#endif // MEASURE_H
