#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    bool wasPressed(QPushButton &push);
    int getRecipeId(QString name);
    QString getRecipeContent(int id);
public slots:
    void onButtonClick();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
