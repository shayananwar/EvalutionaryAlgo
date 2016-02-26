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

    TotalFitness = 0;
    population.clear();
    newpopulation.clear();

    generatePopulations();

    //sort by fitness
    sort(this->population.begin(), this->population.end(), by_fitness());

    //initial graph
    graphs gr;
    gr.setModal(false);

    int k = 0;
    while(k < count){
        int j = 0;
        while(j < count){

            calc_prob_ranges();

            //offsprings
            for(int i=0; i<((count/2)/2); i++){
                float val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x1 = temp.x;
                offsprint_y1 = temp.y;

                val = randomRange(0, 1);
                temp = generateOffspring(val);

                offsprint_x2 = temp.x;
                offsprint_y2 = temp.y;

                //mutation process
                mutation(offsprint_x1, offsprint_y2, offsprint_x2, offsprint_y1);
            }

            //merge new with old population
            population.insert(population.end(), newpopulation.begin(), newpopulation.end());

            //sort by compute
            sort(population.begin(), population.end(), by_fitness());

            // erase unecessary elements/population:
            population.erase(population.begin()+count,population.end());

            cout << "population for new iteration" << endl;
            TotalFitness = 0;
            for(int i=0; i < population.size(); i++ ){
                TotalFitness = TotalFitness + population[i].fitness;
                cout << population[i].x << "," << population[i].y << "," << population[i].fitness << endl;
            }

            //best of iteration
            best.push_back(population[0].fitness);
            //avg of iteration
            avg.push_back(population[(count/2)-1].fitness);

            j++;

        }
        k++;
        gr.data.push_back({best,avg,count});
        best.clear();
        avg.clear();
    }


//    for(int i=0; i < count; i++ ){
//        gr.best.push_back({best[i].fitness});
//        gr.avg.push_back({avg[i].fitness});
//    }
//        cout << gr.best.size() << endl;

//    gr.generation = count;


    gr.makePlot(0);

    gr.exec();

}


void MainWindow::on_RBS_clicked()
{
    generatePopulations();
}


float MainWindow::randomRange(float min, float max){
//    return (min + (rand() % (int)(max - min + 1)));
    //return (min + (rand() % (max - min + 1)));
    float r3 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    return r3;
}

float MainWindow::getFitness(float x, float y){
     //float ans = fabs((2*x)+(3*y));
    float ans = (pow (x, 2))+(pow (y, 2));
    //ans = round(ans, 3);
     TotalFitness = TotalFitness + ans;
     return ans;
}

void MainWindow::mutation(float x1, float y2, float x2, float y1){

    float val;

    //for x1
    if(x1 > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+x1 > maxX)
            x1 = maxX;
        else if(val+x1 < minX)
            x1 = minX;
        else
            x1 = val+x1;
    }

    //for y2
    if(y2 > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+y2 > maxY)
            y2 = maxY;
        else if(val+y2 < minY)
            y2 = minY;
        else
            y2 = val+y2;
    }

    //for x2
    if(x2 > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+x2 > maxX)
            x2 = maxX;
        else if(val+x2 < minX)
            x2 = minX;
        else
            x2 = val+x2;
    }

    //for y1
    if(y1 > 0.2){
        val = randomRange(-0.5, 0.5);
        if(val+y1 > maxY)
            y1 = maxY;
        else if(val+y1 < minY)
            y1 = minY;
        else
            y1 = val+y1;
    }

    newpopulation.push_back({x1, y2, getFitness(x1, y2)});
    newpopulation.push_back({x2, y1, getFitness(x2, y1)});

}



void MainWindow::generatePopulations(){
    for(int i = 0; i < count; i++){
        float x = randomRange(this->minX, this->maxX);
        float y = randomRange(this->minY, this->maxY);
        this->population.push_back({x, y, getFitness(x, y)});
        cout << this->population[i].fitness << endl;
    }
}

void MainWindow::calc_prob_ranges(){
    cout << "probility & range" << endl;
    float range = 0;
    for(int i=0; i < this->count; i++ ){
        //probility
        probilities[i] = this->population[i].fitness/TotalFitness;
        //probility range
        range = range + probilities[i];
        probilities_ranges[i] = range;
        cout << range << endl;
    }
}
