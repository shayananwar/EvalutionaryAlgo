#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FPS_clicked()
{


    //initial graph
    graphs gr;
    gr.setModal(true);

    int k = 0;
    while(k < COUNT){

        TotalFitness = 0;
        population.clear();
        newpopulation.clear();

        generatePopulations(false);

        //sort by fitness
        sort(this->population.begin(), this->population.end(), by_fitness());

        int j = 0;
        while(j < COUNT){

            calc_prob_ranges(false);

            //offsprings
            for(int i=0; i<((COUNT/2)/2); i++){
                float val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x1 = temp.x;
                offsprint_y1 = temp.y;

                val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x2 = temp.x;
                offsprint_y2 = temp.y;

                //mutation process
                mutation(offsprint_x1, offsprint_y2, offsprint_x2, offsprint_y1, false);
            }

            //merge new with old population
            population.insert(population.end(), newpopulation.begin(), newpopulation.end());

            //clear new population
            newpopulation.clear();

            //sort by compute
            sort(population.begin(), population.end(), by_fitness());

            // erase unecessary elements/population:
            population.erase(population.begin()+COUNT,population.end());

            cout << "population for new iteration" << endl;
            TotalFitness = 0;
            for(int i=0; i < population.size(); i++ ){
                TotalFitness = TotalFitness + population[i].fitness;
                //cout << population[i].x << "," << population[i].y << "," << population[i].fitness << endl;
            }

            //best of iteration
            best.push_back(population[0].fitness);
            //avg of iteration
            avg.push_back(population[(COUNT/2)-1].fitness);

            j++;

        }
        k++;
        gr.data.push_back({best,avg,COUNT});
        reverse(best.begin(), best.end());
        reverse(avg.begin(), avg.end());
        best_best.push_back(best[0]);
        avg_avg.push_back(avg[0]);
        best.clear();
        avg.clear();
    }

    gr.data.push_back({best_best,avg_avg,COUNT});
    best_best.clear();
    avg_avg.clear();

//    for(int i=0; i < COUNT; i++ ){
//        gr.best.push_back({best[i].fitness});
//        gr.avg.push_back({avg[i].fitness});
//    }
//        cout << gr.best.size() << endl;

//    gr.generation = COUNT;


    gr.makePlot(0);

    gr.exec();

}


void MainWindow::on_RBS_clicked()
{


    //initial graph
    graphs gr;
    gr.setModal(true);

    int k = 0;
    while(k < COUNT){

        TotalFitness = 0;
        population.clear();
        newpopulation.clear();

        generatePopulations(true);

        //sort by fitness
        sort(this->population.begin(), this->population.end(), by_x());

        int j = 0;
        while(j < COUNT){

            calc_prob_ranges(true);

            //offsprings
            for(int i=0; i<((COUNT/2)/2); i++){
                float val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x1 = temp.x;
                offsprint_y1 = temp.y;

                val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x2 = temp.x;
                offsprint_y2 = temp.y;

                //mutation process
                mutation(offsprint_x1, offsprint_y2, offsprint_x2, offsprint_y1, true);
            }

            //merge new with old population
            population.insert(population.end(), newpopulation.begin(), newpopulation.end());

            //clear new population
            newpopulation.clear();

            //sort by compute
            sort(population.begin(), population.end(), by_fitness());

            // erase unecessary elements/population:
            population.erase(population.begin()+COUNT,population.end());

            cout << "population for new iteration" << endl;
            TotalFitness = 0;
            for(int i=0; i < population.size(); i++ ){
                TotalFitness = TotalFitness + population[i].x;
                //cout << population[i].x << "," << population[i].y << "," << population[i].fitness << endl;
            }

            //best of iteration
            best.push_back(population[0].fitness);
            //avg of iteration
            avg.push_back(population[(COUNT/2)-1].fitness);

            j++;

        }
        k++;
        gr.data.push_back({best,avg,COUNT});
        reverse(best.begin(), best.end());
        reverse(avg.begin(), avg.end());
        best_best.push_back(best[0]);
        avg_avg.push_back(avg[0]);
        best.clear();
        avg.clear();
    }

    gr.data.push_back({best_best,avg_avg,COUNT});
    best_best.clear();
    avg_avg.clear();

//    for(int i=0; i < COUNT; i++ ){
//        gr.best.push_back({best[i].fitness});
//        gr.avg.push_back({avg[i].fitness});
//    }
//        cout << gr.best.size() << endl;

//    gr.generation = COUNT;


    gr.makePlot(0);

    gr.exec();
}


float MainWindow::randomRange(float min, float max){
//    return (min + (rand() % (int)(max - min + 1)));
    //return (min + (rand() % (max - min + 1)));
    float r3 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    return r3;
}

float MainWindow::getFitness(float x, float y, bool isRBS){
     //float ans = fabs((2*x)+(3*y));
    float ans = (pow (x, 2))+(pow (y, 2));
    //ans = round(ans, 3);
    if(isRBS)
     TotalFitness = TotalFitness + x;
    else
     TotalFitness = TotalFitness + ans;

     return ans;
}


void MainWindow::mutation(float x1, float y2, float x2, float y1, bool isRBS){

    float val, fit1, fit2;

    fit1 = getFitness(x1, y2, isRBS);
    fit2 = getFitness(x2, y1, isRBS);

    //for x1
    if(x1 > 0.2){
//    val = randomRange(0, 1);
//    if(val > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+x1 > MAXX)
            x1 = MAXX;
        else if(val+x1 MINX)
            x1 MINX;
        else
            x1 = val+x1;
    }

    //for y2
    if(y2 > 0.2){
//    val = randomRange(0, 1);
//    if(val > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+y2 > MAXY)
            y2 = MAXY;
        else if(val+y2 < MINY)
            y2 = MINY;
        else
            y2 = val+y2;
    }

    //for x2
    if(x2 > 0.2){
//    val = randomRange(0, 1);
//    if(val > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+x2 > MAXX)
            x2 = MAXX;
        else if(val+x2 MINX)
            x2 MINX;
        else
            x2 = val+x2;
    }

    //for y1
    if(y1 > 0.2){
//    val = randomRange(0, 1);
//    if(val > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+y1 > MAXY)
            y1 = MAXY;
        else if(val+y1 < MINY)
            y1 = MINY;
        else
            y1 = val+y1;
    }

//    newpopulation.push_back({x1, y2, fit1});
//    newpopulation.push_back({x2, y1, fit2});

    newpopulation.push_back({x1, y2, getFitness(x1, y2, isRBS)});
    newpopulation.push_back({x2, y1, getFitness(x2, y1, isRBS)});

}



void MainWindow::generatePopulations(bool isRBS){
    for(int i = 0; i < COUNT; i++){
        float x = randomRange(MINX, MAXX);
        float y = randomRange(MINY, MAXY);
        this->population.push_back({x, y, getFitness(x, y, isRBS)});
        //cout << this->population[i].fitness << endl;
    }
}

void MainWindow::calc_prob_ranges(bool isRBS){
    cout << "probility & range" << endl;
    float range = 0;
    for(int i=0; i < COUNT; i++ ){
        //probility
        if(isRBS)
            probilities[i] = this->population[i].x/TotalFitness;
        else
            probilities[i] = this->population[i].fitness/TotalFitness;
        //probility range
        range = range + probilities[i];
        probilities_ranges[i] = range;
        cout << range << endl;
    }
}

