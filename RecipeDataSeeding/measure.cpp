#include "measure.h"
#include "ui_measure.h"
#include "dashboard.h"

measure::measure(QVector<int> ingr,int id,QVector<int> page,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measure)
{
    ui->setupUi(this);
    ingrIds = ingr;
    recipeID = id;
    pageIndex = page;
    //in the dashboard function, create a function that returns an array of all ingredient ids
    printIngredients(ingr);

}

void measure::printIngredients(QVector<int> ingr)
{
    int INGR_ID = 0;
    //Kale
    //1,1-Kale 1,3-Olive Oil 1,4-Lemon
    //2,1-Bell Pepper 2,2-Avacado 2,3-Red Onion
    if(recipeID == 660108){
        if(pageIndex[0] == 1){
            if(pageIndex[1] == 1)
                INGR_ID = 11233; //kale
            if(pageIndex[1] == 3)
                INGR_ID = 4053; //oil
            if(pageIndex[1] == 4)
                INGR_ID = 9152; //lemon
        }
    }

    //Chili
    //1,2-Ground Beef
    //2,2-Pinto Beans 2,3-Tomato 2,4-Tomato Sauce 2,5-Red Kidney Beans
    //3,1-Celery 3,2-Onion 3,3-Green Chilies

    //Mac
    //2,3-White Onion 2,5-Large Zucchini 2,6-Tomatoes 2,7-Artichokes 2,8-Black Olives 2,9-Drained Tuna

    //Muffins
    //2,1-Flour 2,2-Brown Sugar
    //3,1-Coconut Flakes 3,2-Golden Raisins 3,4-Apple 3,5-Pineapple w/ Juice 3,6-Carrots
    //4,2-Apple Sauce

    //Basil Soup
    //2,1-Baby Tomatoes
    //3,1-Brown Onion
    //4,3-Tomato Paste 4,4-Chicken Broth 4,5-Apple Cider Vinegar 4,6-Coconut Milk 4,8-Cheese

    //Chicken Parm
    //1,3-Vegetable Oil
    //2,1-Chicken Breasts 2,3-Flour 2,4-Pasta Sauce
    //3,2-Bread Crumbs 3,3-Garlic Powder
    //4,5-Moz Cheese

    //Ramen
    //2,2-Brown Onion 2,3-Carrots
    //3,3-Flour 3,4-Poultry Seasoning
    //4,1-Water 4,2-Kombu 4,4-Rice Milk 4,5-Rice Noodles

    //Chicken Apple Salad
    //1,1-Chicken 1,2-Celery 1,3-Apples
    //2,1-Mayo 2,2-Yogurt 2,3-Lemon Juice

    for(int i = 0; i < ingr.length(); i++){
        //qDebug() << ingr.at(i);

    }
    ui->measureIngredient->setText(QString::number(INGR_ID));
}

measure::~measure()
{
    delete ui;
}
