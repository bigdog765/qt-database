#include "walkthrough.h"
#include "ui_walkthrough.h"
#include "QJsonArray"
#include "QJsonObject"
#include "QPushButton"
#include "QLabel"
#include "QGroupBox"

walkthrough::walkthrough(QJsonArray &steps,int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::walkthrough)
{
    ui->setupUi(this);
    layout = ui->verticalLayout;
    recipeID = id;


    //********this was the prevous way of AUTOMATES the steps
    //QList<QString> *listOfSteps = new QList<QString>;
    //listOfSteps = setupSteps(steps);

    //********this part MANUALLY adds each step written out in a string
    QVector<int> vec = getNumberOfSubSteps();


    //this function was modified to support the manually instructions, for the second parameter it had a qlist string of steps
    setupPages(numOfSteps, vec); //parameters: number of steps, array of number of substeps for each parent step


    //below was unchanged
    setupButtons(numOfSteps);

    //make a dummy parent for the layout
    QWidget *parentL = new QWidget(ui->verticalLayoutWidget);

    //now we can display the layout
    parentL->setLayout(layout);
    parentL->show();

    //create an array of buttons from the layout so we can implement each button click
    QList<QPushButton*> listB = layout->parentWidget()->findChildren<QPushButton*>();
    qDebug() << listB.size();



    QList<QPushButton*> subList = getSubButtons();
    QList<QPushButton*> scaleList = getScaleButtons();
    qDebug() << "**************";


    //sub step button
    for(int j=0;j< numOfSteps;j++){
        qDebug() << "button found:";
           qDebug() << subList.at(j)->objectName();
        connect(subList.at(j),SIGNAL(clicked()),this,SLOT(onSubClick()));

    }
    //sub step button
    for(int j=0;j< numOfSteps;j++){
        connect(scaleList.at(j),SIGNAL(clicked()),this,SLOT(onScaleClick()));

    }


    //main step buttons
    for(int i=0;i< numOfSteps;i++){

        connect(listB.at(i),SIGNAL(clicked()),this,SLOT(onPageClick()));

    }


}

walkthrough::~walkthrough()
{
    delete ui;
}


//AUTOMATES STEPS
//for measuring part of the walkthrough, we can put each ingredient into an array of the specific recipe and scan the ingredient step to see if it has that certain ingredient
QList<QString>* walkthrough::setupSteps(QJsonArray &steps)
{
    QString totalStepsString;
    QList<QString> *listSteps = new QList<QString>;


    //get 'steps' array, stores in g
    QJsonArray g;
    for(auto i = steps.begin(); i != steps.end(); i++){
        QJsonObject f;
        f =i->toObject();
        for(auto j = f.begin(); j != f.end(); j++){
            if(j.key().toUtf8() == "steps"){
                g = j->toArray();
            }
        }
    }

    //print out each step
    int ctr = 0;
    int s;
    for(auto k = g.begin(); k != g.end(); k++){
        QJsonObject h;
        h = k->toObject();
        for(auto l = h.begin(); l != h.end(); l++){
            if(l.key().toUtf8() == "number"){
                s = l.value().toInt();
                totalStepsString.append("Step " + QString::number(s) + ": ");

                //this gets total number of steps
                ctr++;
            }
            else if(l.key().toUtf8() == "step"){
                QString txt = l.value().toString();

                //lets us know if the instruction needs to be split into two
                QList<QString> *t = splitInstruction(txt,s);

                if(!t){
                    totalStepsString.append(txt);
                    listSteps->append(txt);
                }
                else{

                    totalStepsString.append(t->at(0));
                    totalStepsString.append(t->at(1));
                    listSteps->append(t->at(0));
                    listSteps->append(t->at(1));
                    ctr++;
                }
            }
        }
    }

    setSteps(ctr);

    //this will show the whole instruction list
    qDebug() << totalStepsString;

    return listSteps;

}

//MANUAL STEPS


//parameter vec is not used
void walkthrough::setupPages(int number, QVector<int> vec)
{

    QFont step_f("Segoe UI",15,QFont::Bold);
    for(int i =0;i < number; i++){
        qDebug() << recipeID;
        QWidget *pageWidget = new QWidget(ui->stackedWidget);
        pageWidget->setObjectName("page " + QString::number(i+1));

        QLabel *lblPage = new QLabel(pageWidget);

        lblPage->setObjectName("label" + QString::number(i+1));
        lblPage->setText("Step " + QString::number(i+1));
        lblPage->setFont(step_f);

        QPushButton *scale = new QPushButton(pageWidget);
        scale->setText("Measure");
        scale->setObjectName("measureButton");
        scale->setGeometry(50,100,75,25);
        setScaleButtons(scale);


        QStringList list1;
        QString s;

        //maunally insert all substeps
        QLabel *labelSubStep = new QLabel(pageWidget);
        if(recipeID == 660108){ //kale
            if(i == 0){
                labelSubStep->setText("Substep 1. Take and wash 1 bunch of Kale, pat dry and remove the leaves from the stems.\n"
                                      "Substep 2. Now, chop the leaves and place in a large bowl (place in VersaBowl if provided).\n"
                                      "Substep 3. Take a small container or bowl and add ⅛ cup olive oil.\n"
                                      "Substep 4. In the same container, squeeze the juice from one lemon and mix with oil until very well combined.\n"
                                      "Substep 5. Pour the lemon & olive oil mixture over the kale leaves and toss.");
                s = labelSubStep->text();

            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Take 1 bell pepper and chop to desired size. Add to the bowl.\n"
                                      "Substep 2. Take 1 avocado, remove the pit, and slice pieces to desired size. Add to the bowl.\n"
                                      "Substep 3. Take 1 red onion, remove skin, and slice pieces thinly to desired size. Add to the bowl.\n"
                                      "Substep 4. Take the bowl and toss the contents until the mixture is even.");
                s = labelSubStep->text();

            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Sprinkle desired amount of salt and pepper onto salad. Enjoy!");
                s = labelSubStep->text();
            }
        }
        else if(recipeID == 646567){ //chili
            if(i == 0){
                labelSubStep->setText("Substep 1. Take a medium saucepan and place on medium heat over the stove. (SHOW ICON OF PAN)\n"
                                      "Substep 2. Once hot, place ground beef in a sauce pan and brown 1135 grams of ground beef, breaking it into small pieces as it cooks.\n"
                                      "Substep 3. Add salt and pepper to taste while cooking.\n"
                                      "Substep 4. Remove the cooked meat from the heat, drain to remove grease.");
                s = labelSubStep->text();
            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Transfer cooked beef into a large pot and place over medium-low heat. (SHOW ICON OF PAN)\n"
                                      "Susbtep 2. Measure 425 grams of pinto beans and add to the pot.\n"
                                      "Substep 3. Measure 425 grams of diced tomatoes and add to the pot.\n"
                                      "Substep 4. Measure 225 grams of tomato sauce and add to the pot.\n"
                                      "Susbtep 5. Measure 425 grams of red kidney beans and add to the pot.");
                s = labelSubStep->text();

            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Add 50 grams of chopped celery to the pot.\n"
                                      "Substep 2. Take 1 chopped white onion and add to the pot.\n"
                                      "Substep 3. Take 113 grams of chopped green chilies and add to the pot.\n"
                                      "Substep 4. Add all desired spices, to taste, to the pot. We recommend 2 tbsp chili powder, 0.5 tbsp ground cumin, 1 tsp salt, 1 tsp black pepper, 0.5 tsp onion powder.");
                s = labelSubStep->text();

            }
            if(i == 3){
                labelSubStep->setText("Substep 1.  Stir together and cook over medium heat, bringing to a simmer.  Reduce the heat to low and continue simmering for 50-60 minutes, stirring occasionally. (SHOW ICON OF STOVE TOP COUNTDOWN TIMER).");
                s = labelSubStep->text();

            }

        }
        else if(recipeID == 643642){ //mac
            if(i == 0){
                labelSubStep->setText("Substep 1. Prepare macaroni as instructed throughout the remainder of these instructions. Move to the next step once started. (SHOW ICON OF POT COOKING).");
                s = labelSubStep->text();

            }
            if(i == 1){
                labelSubStep->setText("Substep 1.  Heat a large frying pan, or pot, over medium heat. Add a drizzle of olive oil. (SHOW ICON OF HOT PAN)\n"
                                      "Substep 2. Once hot, add 5 large cloves of chopped garlic. Don’t forget to remove the skin!\n"
                                      "Substep 3. In the same pot, add 1 unpeeled, chopped white onion\n"
                                      "Substep 4. In the same pot, add 1 bunch of chopped parsley.\n"
                                      "Substep 5. In the same pot, add 2 large, diced zucchini.\n"
                                      "Substep 6. In the same pot, add 7 ripe, diced tomatoes.\n"
                                      "Substep 7. In the same pot, add 225 grams of frozen artichokes.\n"
                                      "Substep 8. In the same pot, add 226 grams of black olives.\n"
                                      "Substep 9. In the same pot, add 1 can of drained tuna.\n"
                                      "Substep 10. Sautee mixture for 3 minutes. Dont forget to check on the macoroni! When done, proceed.");
                s = labelSubStep->text();



            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Add the seasonings to taste. We recommend 1 tsp pepper flakes, 0.5 tsp salt, 0.5 tsp pepper, and 1 tsp oregano.\n"
                                      "Substep 2. Your macaroni should now be done cooking! Strain macaroni in a colander and place cooked noodles back into the same large pot.\n"
                                      "Substep 3. Pour all of the sauteed mixture over the cooked noodles and stir. If the substance is too liquid, keep over covered medium-low heat until liquid has evaporated.\n"
                                      "Substep 4. Once ready, top with your favorite cheese and enjoy!");
                s = labelSubStep->text();

            }

        }
        else if(recipeID == 1096070){ //muffin
            qDebug() << "MUFFINS";
            if(i == 0){
                labelSubStep->setText("Substep 1. Preheat oven to 350F. (SHOW ICON OF OVEN)");
                s = labelSubStep->text();

            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Place in a large bowl 1 cup of flour.\n"
                                      "Substep 2. In the same bowl, add 1 cup of brown sugar.\n"
                                      "Substep 3. In the same bowl, add 2 tsps of cinnamon.\n"
                                      "Substep 4. In the same bowl, add 1 tsp of baking soda.\n"
                                      "Substep 5. In the same bowl, add 0.5 tsp of salt.\n"
                                      "Substep 6. Whisk ingredients together until mixed evenly.");
                s = labelSubStep->text();

            }
            if(i == 2){
                labelSubStep->setText("Substep 1. In the same bowl, add ⅓ cup unsweetened coconut flakes.\n"
                                      "Substep 2. In the same bowl, add ½ cup golden raisins.\n"
                                      "Substep 3. In the same bowl, add the zest of one orange.\n"
                                      "Substep 4. In the same bowl, add 1 small apple peeled and grated.\n"
                                      "Substep 5. In the same bowl, add 1 can of diced pineapple with juice.\n"
                                      "Substep 6. In the same bowl, add 1 cup of grated carrots.\n"
                                      "Substep 7. Stir all ingredients together until mixed evenly. Set aside");
                s = labelSubStep->text();
            }
            if(i == 3){
                labelSubStep->setText("Substep 1. In a separate bowl, add 2 large eggs.\n"
                                      "Substep 2. In the same bowl, add 1 cup of unsweetened apple sauce.\n"
                                      "Substep 3. In the same bowl. add 1.5 tsp of pure vanilla extract.\n"
                                      "Substep 4. Whisk all ingredients until mixed evenly. Once mixed, pour into the bowl with all the dry ingredients and blend well!");
                s = labelSubStep->text();

            }
            if(i == 4){
                labelSubStep->setText("Substep 1. Grab muffin oven rack and spritz a little bit of cooking spray into each cavity, ensuring to get the entire inner wall.\n"
                                      "Substep 2. Spoon the batter mixture into each muffin cavity of the oven tray. Fill 90% of each muffin cavity.\n"
                                      "Substep 3. Sprinkle coconut flakes and nuts on top of each batter-filled cavity. Place as much as desired!\n"
                                      "Substep 4. Place muffin tray in the oven and bake for 30-35 minutes. You can also check if muffins are thoroughly cooked by sticking a toothpick into each one. (SHOW ICON OF COUNTDOWN TIMER WITH OVEN)\n"
                                      "Substep 5. Remove muffin tray from oven and let cool for 10 minutes. (COOLING ICON SHOW WITH COUNTDOWN TIMER)\n"
                                      "Substep 6. Once cooled, enjoy with friends or family!");
                s = labelSubStep->text();

            }

        }
        else if(recipeID == 1096214){ //basil
            if(i == 0){
                labelSubStep->setText("Substep 1. Preheat oven to 350F. (SHOW ICON OF OVEN)\n"
                                      "Substep 2. Prepare a baking sheet onto a normal sized oven tray.\n"
                                      "Substep 3. Take out blender and set aside.");
                s = labelSubStep->text();
            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Cut 1,135 grams of baby tomatoes and place cut-side up all on the baking tray.\n"
                                      "Substep 2. Season tomatoes with 1 tsp of salt.\n"
                                      "Substep 3. Drizzle 1 tbsp of olive oil over tomatoes.\n"
                                      "Substep 4. Once oven has hit 350F, place rack of tomatoes inside for 25-30 minutes. A good indicator of readiness is by the curling and crisping of the tomato skin. Proceed to next.(SHOW ICON OF COUNTDOWN TIMER)");
                s = labelSubStep->text();

            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Chop 1 peeled brown onion, set aside.\n"
                                      "Substep 2. Mince 2 peeled garlic cloves, set aside.\n"
                                      "Substep 3. In a large saucepan over medium heat, warm 1 tbsp of olive oil. (SHOW ICON OF STOVETOP)\n"
                                      "Substep 4. Add onions to the saucepan and saute until almost translucent, then add garlic.\n"
                                      "Substep 5. Reduce heat and stir until garlic is aromatic and softened, 3 to 5 minutes. Proceed when done and turn off stove.(TURN OFF STOVETOP ICON)");
                s = labelSubStep->text();

            }
            if(i == 3){
                labelSubStep->setText("Substep 1. Transfer the roasted tomatoes, onions, and garlic to a food processor or blender and blend on high for 2 minutes.\n"
                                      "Substep 2. Return the tomato mixture to the saucepan over medium heat. (TURN ON STOVETOP ICON)\n"
                                      "Substep 3. In the same pan, add 1 tbsp of tomato paste\n"
                                      "Substep 4. In the same pan, add 2 cups of chicken broth.\n"
                                      "Substep 5. In the same pan, add 0.5 tsp of apple cider vinegar.\n"
                                      "Substep 6. In the same pan, add 0.5 cup of coconut milk.\n"
                                      "Substep 7. Stir until all the ingredients until mixed evenly and warmed throughout. Roughly 2 to 4 minutes. Once done, turn off the heat.\n"
                                      "Substep 8. Ladle tomato soup into bowls and add the desired amount of basil, black pepper, and cheese!");
                s = labelSubStep->text();

            }

        }
        else if(recipeID == 638235){ //parm
            if(i == 0){
                labelSubStep->setText("Substep 1.Preheat oven to 350F. (SHOW ICON OF OVEN)\n"
                                      "Substep 2. Place a large skillet onto the stove over medium-high heat.\n"
                                      "Substep 3. Add 2 tbsp of vegetable oil to the skillet. Proceed when done.(SHOW ICON OF PAN)");
                s = labelSubStep->text();
            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Take 2 boneless, skinless chicken breasts and cut into thin, half sections.\n"
                                      "Substep 2. Season both sides of chicken filets with a desired amount of salt and pepper.\n"
                                      "Substep 3.Coat each side of each chicken filet with a desired amount of all-purpose flour. Set aside.\n"
                                      "Substep 4. Place a small skillet over medium-low heat and add in 1 jar of red tomato pasta sauce. Proceed when done. (SHOW ICON OF SKILLET)");
                s = labelSubStep->text();
            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Take a medium sized bowl and lightly beat 1 egg.\n"
                                      "Substep 2. In another medium sized bowl, pour in 1 cup of bread crumbs\n"
                                      "Substep 3. In the same bowl of bread crumbs, pour in 1.5 tbsp of garlic powder.\n"
                                      "Substep 4. Take your floured chicken filets and dip into the egg wash, coating all over, then into the bread crumbs. Bread all four chicken breasts.\n"
                                      "Substep 5. Place each chicken filet into the skillet and cook for three minutes on each side, or until golden brown on each side. When done, proceed.");
                s = labelSubStep->text();
            }
            if(i == 3){
                labelSubStep->setText("Substep 1. Get out a large baking sheet and place each chicken filet on the sheet.\n"
                                      "Substep 2. Place the baking sheet with the chicken into the oven for 10-15 minutes. Proceed to set timer. (SHOW OVEN ICON TIMER)\n"
                                      "Substep 3. In a large pot, boil however much water is needed to cook 1 box of any type of pasta. We recommend angel hair pasta, but any type will do! Once pasta is inside the pot, proceed to next. (SHOW ICON OF POT)\n"
                                      "Substep 4. Once the timer for the oven runs out, pull the chicken out and rest on a hot plate. Do not turn off the oven. \n"
                                      "Substep 5. Top cooked chicken with 1 cup of shredded mozzarella cheese, and place back into the oven to melt the cheese for 3-5 minutes. Proceed to set timer.");
                s = labelSubStep->text();
            }
            if(i == 4){
                labelSubStep->setText("Substep 1. When the pasta is done, strain in a colander and place cooked noodles on however many plates. topped with chicken and the cover with sauce. If youre feeling zesty add a little fresh shaved Pecorino-Romano or grated Parmesan cheese!");
                s = labelSubStep->text();
            }

        }
        else if(recipeID == 646974){ //ramen
            if(i == 0){
                labelSubStep->setText("Substep 1. Take out a blender and set aside.");
                s = labelSubStep->text();
            }
            if(i == 1){
                labelSubStep->setText("Substep 1. Put 5 cloves of garlic into the blender. DO NOT TURN ON.\n"
                                      "Substep 2. Put 2 small brown onions into the same blender.\n"
                                      "Substep 3. Put 5 carrots into the same blender. Blend for 3-4 seconds until mixture is finely minced. Set aside.");
                s = labelSubStep->text();
            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Place a soup pot on the stove over medium heat. (SHOW ICON OF STOVETOP)\n"
                                      "Substep 2. Add minced vegetables mixture from blender to the pot, mixing occasionally, until just soft. Should take about 8 minutes. Proceed to next step once on the stove. (SHOW COUNTDOWN TIMER)\n"
                                      "Substep 3. Take out a medium sized bowl, add 0.5 cup of all-purpose gluten free flour.\n"
                                      "Substep 4. In the same bowl, add 2 tsp of poultry seasoning\n"
                                      "Substep 5. In the same bowl, add 1 tsp of sea salt\n"
                                      "Substep 6, In the same bowl, add a dash of celery seed.\n"
                                      "Substep 7. Stir ingredients and pour onto minced vegetable mixture after timer has run out. Stir constantly for 30 seconds, coating the vegetables well.");
                s = labelSubStep->text();
            }
            if(i == 3){
                labelSubStep->setText("Substep 1. In the same pot, pour in 4 cups of water.\n"
                                      "Substep 2. In the same pot, add  0.5 cups of kombu. If you dont have kombu, you can skip adding it. \n"
                                      "Substep 3. Bring to boil and then simmer, covered, for 30 minutes (SET TIMER).\n"
                                      "Substep 4. After 30 minutes, remove lid and pour in 0.5 cup of rice milk\n"
                                      "Substep 5. Add 113 grams of rice noodles. \n"
                                      "Substep 6. Simmer for 10 minutes on low heat, or until noodles are soft. Serve and Enjoy!");
                s = labelSubStep->text();
            }
        }
        else if(recipeID == 715522){ //chicken apple salad
            if(i == 0){
                labelSubStep->setText("Substep 1. In a large bowl, add 2.5 cups of chopped chicken\n"
                                      "Substep 2. In the same bowl, add 3 stalks of chopped celery\n"
                                      "Substep 3. In the same bowl, add 1 cup of chopped apples. We recommend granny smith!\n"
                                      "Substep 4. Mix contents together and set aside.");
                s = labelSubStep->text();

            }
            if(i == 1){
                labelSubStep->setText("Substep 1. In a small separate bowl, add 2 tbsp of mayo.\n"
                                      "Substep 2. In the same bowl, add 0.5 cup of plain yogurt.\n"
                                      "Substep 3. In the same bowl, add 2 tsp of lemon juice.\n"
                                      "Substep 4. Mix contents together well until even.");
                s = labelSubStep->text();

            }
            if(i == 2){
                labelSubStep->setText("Substep 1. Pour bowl of lemon juice mixture over large bowl of chicken mixture. Stir well until mixed well.\n"
                                      "Substep 2.  Add desired amount of salt and pepper to taste. Enjoy! ");
                s = labelSubStep->text();
            }
        }
        else{
            qDebug() << "id not regonized";
        }

        //string list of all substeps
        list1 = s.split("\n");

        //differentiate substacks

        QStackedWidget *subStack = new QStackedWidget(pageWidget);
        subStack->setObjectName("subStack"+ QString::number(i+1));
        subStack->setGeometry(50,150,570,180);
        subStack->setStyleSheet("background-color: rgb(200, 200, 200)");


        labelSubStep->setParent(subStack);


        //convert each substep string into a label and add to substep stacked widget
        for(int j = 0; j < list1.size(); j++){
            //labels
            QLabel *a = new QLabel(subStack);
            a->setText(list1.at(j));
            a->setAlignment(Qt::AlignTop);
            a->setWordWrap(true);
            a->setFixedWidth(570);
            a->setFixedHeight(180);

            subStack->insertWidget(0,a);
            qDebug() << "substack inserted";
        }
        qDebug() << "stack size:";
        qDebug() << subStack->count();


        //buttons
        //this buttons parent is the main window not the substack
        QPushButton *subButton = new QPushButton(pageWidget);
        subButton->setObjectName("subB" + QString::number(i+1));
        subButton->setText("Next");
        subButton->setGeometry(530,280,75,25);
        setSubButtons(subButton);

        //add main page to stack
        ui->stackedWidget->insertWidget(0,pageWidget);

        qDebug() << "Page inserted";

    }
}

void walkthrough::setupButtons(int number)
{

    for(int i = 1; i <= number;i++){
         QString buttonText = "Step " + QString::number(number - i + 1);
         QPushButton* button = new QPushButton(buttonText, ui->verticalLayoutWidget);
         button->setObjectName("step" + QString::number(i));
         //insert buttons into the layout depending on how many steps
         layout->insertWidget(0, button);
         qDebug() << "Button added";

    }
}



void walkthrough::setSteps(int s)
{
    numOfSteps = s;
}

int walkthrough::getSteps()
{
    return numOfSteps;
}



void walkthrough::onPageClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << button->objectName();
    QChar number = button->objectName().back();
    int a = number.digitValue();
    ui->stackedWidget->setCurrentIndex(a-1);

    /*
    if(a == 1){ //last page
        qDebug() << "last page";
        QPushButton *clear = new QPushButton();
        clear->setText("clear page");
        ui->stackedWidget->insertWidget(0,clear); //fix this, this button should be created at the same time as the labels

    }
    */

}

void walkthrough::onSubClick()
{
    qDebug() << "SUB CALLED!!!!!!!";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    qDebug() << button->objectName();
    QChar number = button->objectName().back();
    int a = number.digitValue();
    QStackedWidget *w = ui->stackedWidget->findChild<QStackedWidget*>("subStack"+ QString::number(a));
    qDebug() << w->objectName();

    int ind = w->currentIndex();

    qDebug() << ind;
    int p = ind - 1;
    w->setCurrentIndex(p);

}

void walkthrough::onScaleClick()
{
    qDebug() << "Scale Clicked";
}

//this function will manually split certain instruction strings that are too long
//instructions that need to be split:
//kale 1,2
//chili 4
//mac 4
//muffin 3
//basil 2,5
//quiche 2
QList<QString>* walkthrough::splitInstruction(QString &s, int q)
{
    //ids of 6 recipes that need to be split
    int idArr[6] = {660108,646567,643642,1096070,1096214,661249};
    bool tooLong = false;

    int i;
    for(i=0; i < 6; i++){
        if(recipeID == idArr[i]){
            tooLong = true;
            break;
        }
    }
    if(!tooLong)
        return nullptr;
    else{
        if(i == 0){ //kale salad
            qDebug() << q;
            if(q == 1 || q == 2){
                 return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 1){ //chili
            if(q == 4){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 2){ //mac
            if(q == 4){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 3){ //muffin
            if(q == 3){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 4){ //basil
            if(q == 2 || q == 5){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        if(i == 5){ //quiche
            if(q == 2){
                return split(s);
            }
            else{
                return nullptr;
            }
        }
        else{
            return nullptr;
        }

    }
}
QList<QString>* walkthrough::split(QString &s){
    QString per = ".";
    QList<QString> *splitStrings = new QList<QString>(2);
    int mid = s.length() /2;

    //find the closest period to the middle of the string
    int f = s.indexOf(per,mid);
    int b = s.lastIndexOf(per,mid);
    if(f == -1 && b == -1){
        qDebug() << "No period found";
        return 0;
    }
    int indForward = f + 1 - mid;
    int indBackward = mid - b;
    qDebug() << "INDEXES::::";
    qDebug() << indForward;
    qDebug() << indBackward;
    int closest = 0;
    if(indForward <= indBackward)
        closest = s.indexOf(per,mid) + 1;
    else
        closest = s.lastIndexOf(per,mid) + 1;


    QString one = s.left(closest);
    int last = s.length() - closest;
    QString two = s.right(last);
    qDebug() << "****SPLIT STRING:::" + one + "***********"+ two;
    splitStrings->insert(0,one);
    splitStrings->insert(1, two);
    return splitStrings;
}

void walkthrough::setSubButtons(QPushButton *&b)
{
    subButtons.push_back(b);
}

QList<QPushButton*> walkthrough::getSubButtons()
{
    return subButtons;
}

void walkthrough::setScaleButtons(QPushButton *&b)
{
    scaleButtons.push_back(b);
}

QList<QPushButton *> walkthrough::getScaleButtons()
{
    return scaleButtons;
}


QVector<int> walkthrough::getNumberOfSubSteps()
{
    if(recipeID == 660108){ //kale
        QVector<int> arr = {5,4,1};
        numOfSteps = 3;
        return arr;
    }
    else if(recipeID == 646567){ //chili
        QVector<int> arr = {4,5,4,1};
        numOfSteps = 4;
        return arr;
    }
    else if(recipeID == 643642){ //mac
        QVector<int> arr = {1,10,4};
        numOfSteps = 3;
        return arr;
    }
    else if(recipeID == 1096070){ //muffin
        QVector<int> arr = {1,6,7,4,6};
        numOfSteps = 5;
        return arr;
    }
    else if(recipeID == 1096214){ //basil
        QVector<int> arr = {3,4,5,8};
        numOfSteps = 4;
        return arr;
    }
    else if(recipeID == 638235){ //parm
        QVector<int> arr = {3,4,5,5,1};
        numOfSteps = 5;
        return arr;
    }
    else if(recipeID == 646974){ //ramen
        QVector<int> arr = {1,3,7,6};
        numOfSteps = 4;
        return arr;
    }
    else if(recipeID == 715522){ //chicken apple salad
        QVector<int> arr = {4,4,2};
        numOfSteps = 3;
        return arr;
    }
    else{
        qDebug() << "id not defined";
        QVector<int> arr;
        return arr;
    }



}



