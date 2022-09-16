#include "measure.h"
#include "ui_measure.h"
#include "dashboard.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"

measure::measure(int id,QVector<int> page,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measure)
{
    ui->setupUi(this);

    recipeID = id;
    pageIndex = page;
    //in the dashboard function, create a function that returns an array of all ingredient ids
    setID();

}

void measure::setID()
{
    int INGR_ID = 0;

    //All ingredient IDs in Spoonacular
    const int kale = 11233;
    const int olive_oil = 4053;
    const int lemon_juice = 9152;
    const int bell_pepper = 10011821;
    const int avocado = 9037;
    const int red_onion = 10011282;

    const int ground_beef = 10023572;
    const int pinto_beans = 16044;
    const int canned_tomatoes = 10011693;
    const int tomato_sauce = 11549;
    const int red_kidney_beans = 10016034;
    const int celery = 11143;
    const int white_onion = 10611282;
    const int green_chiles = 31015;

    const int zucchini = 11477;
    const int tomatoes = 11529;
    const int artichokes = 11007;
    const int black_olives = 1059195;
    const int tuna = 15126;

    const int flour = 20081;
    const int brown_sugar = 93831;
    const int coconut_flakes = 12108;
    const int golden_raisins = 9297;
    const int apple = 9003;
    const int pineapple = 9354;
    const int carrots = 11124;
    const int apple_sauce = 9019;

    const int baby_tomatoes = 10411529;
    const int brown_onion = 10511282;
    const int tomato_paste = 11887;
    const int chicken_broth = 98904;
    const int apple_cider_vinegar = 2048;
    const int coconut_milk = 12118;
    const int cheddar_cheese = 1001009;

    const int vegetable_oil = 4513;
    const int chicken_breasts = 5062;
    const int red_pasta_sauce = 10011549;
    const int bread_crumbs = 18079;
    const int garlic_powder = 1022020;
    const int mozzarella_cheese = 1001028;

    const int poultry_seasoning = 2034;
    const int water = 14412;
    const int kombu = 11445;
    const int rice_milk = 93761;
    const int rice_noodles = 20133;

    const int rotisserie_chicken = 99246;
    const int green_apple = 1069003;
    const int mayo = 4025;
    const int greek_yogurt = 1011256;


    int main = pageIndex[0];
    int sub = pageIndex[1];

    //Kale Salad
    //1,1-Kale 1,3-Olive Oil 1,4-Lemon
    //2,1-Bell Pepper 2,2-Avacado 2,3-Red Onion
    if(recipeID == 660108){
        if(main == 1){
            if(sub == 1)
                INGR_ID = kale;
            if(sub == 3)
                INGR_ID = olive_oil;
            if(sub == 4)
                INGR_ID = lemon_juice;
        }
        if(main == 2){
            if(sub == 1){
                INGR_ID = bell_pepper;
            }
            if(sub == 2){
                INGR_ID = avocado;
            }
            if(sub == 3){
                INGR_ID = red_onion;
            }
        }
    }
    //Chili
    //1,2-Ground Beef
    //2,2-Pinto Beans 2,3-Tomato 2,4-Tomato Sauce 2,5-Red Kidney Beans
    //3,1-Celery 3,2-Onion 3,3-Green Chilies
    if(recipeID == 646567){
        if(main == 1){
            if(sub == 2){
                INGR_ID = ground_beef;
            }
        }
        if(main == 2){
            if(sub == 2){
                INGR_ID = pinto_beans;
            }
            if(sub == 3){
                INGR_ID = canned_tomatoes;
            }
            if(sub == 4){
                INGR_ID = tomato_sauce;
            }
            if(sub == 5){
                INGR_ID = red_kidney_beans;
            }
        }
        if(main == 3){
            if(sub == 1){
                INGR_ID = celery;
            }
            if(sub == 2){
                INGR_ID = white_onion;
            }
            if(sub == 3){
                INGR_ID = green_chiles;
            }

        }
    }

    //Mac
    //2,3-White Onion 2,5-Large Zucchini 2,6-Tomatoes 2,7-Artichokes 2,8-Black Olives 2,9-Drained Tuna
    if(recipeID == 643642){
        if(main == 2){
            if(sub == 3){
                INGR_ID = white_onion;
            }
            if(sub == 5){
                INGR_ID = zucchini;
            }
            if(sub == 6){
                INGR_ID = tomatoes;
            }
            if(sub == 7){
                INGR_ID = artichokes;
            }
            if(sub == 8){
                INGR_ID = black_olives;
            }
            if(sub == 9){
                INGR_ID = tuna;
            }
        }
    }

    //Muffins
    //2,1-Flour 2,2-Brown Sugar
    //3,1-Coconut Flakes 3,2-Golden Raisins 3,4-Apple 3,5-Pineapple w/ Juice 3,6-Carrots
    //4,2-Apple Sauce
    if(recipeID == 1096070){
        if(main == 2){
            if(sub == 1){
                INGR_ID = flour;
            }
            if(sub == 2){
                INGR_ID = brown_sugar;
            }
        }
        if(main == 3){
            if(sub == 1){
                INGR_ID = coconut_flakes;
            }
            if(sub == 2){
                INGR_ID = golden_raisins;
            }
            if(sub == 4){
                INGR_ID = apple;
            }
            if(sub == 5){
                INGR_ID = pineapple;
            }
            if(sub == 6){
                INGR_ID = carrots;
            }
        }
        if(main == 4){
            if(sub == 2){
                INGR_ID = apple_sauce;
            }
        }
    }

    //Basil Soup
    //2,1-Baby Tomatoes
    //3,1-Brown Onion
    //4,3-Tomato Paste 4,4-Chicken Broth 4,5-Apple Cider Vinegar 4,6-Coconut Milk 4,8-Cheese
    if(recipeID == 1096214){
        if(main == 2){
            if(sub == 1){
                INGR_ID = baby_tomatoes;
            }
        }
        if(main == 3){
            if(sub == 1){
                INGR_ID = brown_onion;
            }
        }
        if(main == 4){
            if(sub == 3){
                INGR_ID = tomato_paste;
            }
            if(sub == 4){
                INGR_ID = chicken_broth;
            }
            if(sub == 5){
                INGR_ID = apple_cider_vinegar;
            }
            if(sub == 6){
                INGR_ID = coconut_milk;
            }
            if(sub == 8){
                INGR_ID = cheddar_cheese;
            }
        }
    }

    //Chicken Parm
    //1,3-Vegetable Oil
    //2,1-Chicken Breasts 2,3-Flour 2,4-Pasta Sauce
    //3,2-Bread Crumbs 3,3-Garlic Powder
    //4,5-Moz Cheese
    if(recipeID == 638235){
        if(main == 1){
            if(sub == 3){
                INGR_ID = vegetable_oil;
            }
        }
        if(main == 2){
            if(sub == 1){
                INGR_ID = chicken_breasts;
            }
            if(sub == 3){
                INGR_ID = flour;
            }
            if(sub == 4){
                INGR_ID = red_pasta_sauce;
            }
        }
        if(main == 3){
            if(sub == 2){
                INGR_ID = bread_crumbs;
            }
            if(sub == 3){
                INGR_ID = garlic_powder;
            }
        }
        if(main == 4){
            if(sub == 5){
                INGR_ID = mozzarella_cheese;
            }
        }
    }

    //Ramen
    //2,2-Brown Onion 2,3-Carrots
    //3,3-Flour 3,4-Poultry Seasoning
    //4,1-Water 4,2-Kombu 4,4-Rice Milk 4,5-Rice Noodles
    if(recipeID == 646974){
        if(main == 2){
            if(sub == 2){
                INGR_ID = brown_onion;
            }
            if(sub == 3){
                INGR_ID = carrots;
            }
        }
        if(main == 3){
            if(sub == 3){
                INGR_ID = flour;
            }
            if(sub == 4){
                INGR_ID = poultry_seasoning;
            }
        }
        if(main == 4){
            if(sub == 1){
                INGR_ID = water;
            }
            if(sub == 2){
                INGR_ID = kombu;
            }
            if(sub == 4){
                INGR_ID = rice_milk;
            }
            if(sub == 5){
                INGR_ID = rice_noodles;
            }
        }
    }

    //Chicken Apple Salad
    //1,1-Chicken 1,2-Celery 1,3-Apples
    //2,1-Mayo 2,2-Yogurt 2,3-Lemon Juice
    if(recipeID == 715522){
        if(main == 1){
            if(sub == 1){
                INGR_ID = rotisserie_chicken;
            }
            if(sub == 2){
                INGR_ID = celery;
            }
            if(sub == 3){
                INGR_ID = green_apple;
            }
        }
        if(main == 2){
            if(sub == 1){
                INGR_ID = mayo;
            }
            if(sub == 2){
                INGR_ID = greek_yogurt;
            }
            if(sub == 3){
                INGR_ID = lemon_juice;
            }
        }
    }

    if(INGR_ID == 0){
        ui->measureIngredient->setText("No Ingredient to Weigh");
    }
    else showIngredient(INGR_ID);


}

void measure::showIngredient(int id)
{

    QByteArray RECIPE_URL = "https://api.spoonacular.com/food/ingredients/" + QString::number(id).toUtf8() + "/information?amount=1&apiKey=81e81ac3e7c14d2b9913ceebbbb4025a";

    QUrl ingr_url(RECIPE_URL);
    QNetworkRequest ingr_request(ingr_url);

    ingr_request.setRawHeader("Content-Type", "application/json");


    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

        QObject::connect(manager,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));



        QNetworkReply* reply = manager->get(ingr_request);
        loop.exec();
        QString response = (QString)reply->readAll();
        qDebug () << response;



        QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject jObj = doc.object();
        QJsonObject nutrObj;
        QJsonValue v;
        QString title;
        QString weight;
        for(auto i = jObj.begin(); i != jObj.end();i++){
            if(i.key().toUtf8() == "nutrition"){ //nutrition key is an object
                nutrObj = i->toObject();
            }
            //fetch relevant keys
            if(i.key().toUtf8() == "name"){
                v = jObj.value("name");
                title = v.toString();
            }
        }

        //static method call
        QString nutrients = dashboard::getTotalNutrients(nutrObj,0);
        QString nutrientsMicro = dashboard::getTotalNutrients(nutrObj,1);

        ui->mainNutrients->setText(nutrients);
        ui->mainNutrients->setWordWrap(true);
        ui->microNutrients->setText(nutrientsMicro);
        ui->microNutrients->setWordWrap(true);

        ui->measureIngredient->setText(title);
}

measure::~measure()
{
    delete ui;
}
