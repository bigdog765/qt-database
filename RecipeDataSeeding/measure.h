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
    explicit measure(QWidget *parent = nullptr);
    ~measure();

private:
    Ui::measure *ui;
};

#endif // MEASURE_H
