#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <config.h>

#include <QMainWindow>


using namespace std;

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct data
    {
      float x;
      float y;
      float fitness;
    };

    struct by_fitness
    {
        inline bool operator() (const data& struct1, const data& struct2)
        {
            if(ORDER == "desc")
                    return (struct1.fitness > struct2.fitness);
                else
                    return (struct1.fitness < struct2.fitness);
        }
    };

    struct by_x
    {
        inline bool operator() (const data& struct1, const data& struct2)
        {
            if(ORDER == "desc")
                    return (struct1.x > struct2.x);
                else
                    return (struct1.x < struct2.x);
        }
    };


    std::vector<data> population, newpopulation, ais_population;
    QVector<double> best, avg, best_best, avg_avg, pso_best, pso_bb, ais_best,ais_bb, ais_avg, ais_avg_avg;
    data temp;

    struct velocity{
        float x;
        float y;
    };

    struct particles
    {
      velocity v;
      float fitness;
    };

    particles  gbest;
    std::vector<particles> particle, lbest, present;

private slots:
    void on_FPS_clicked();

    void on_RBS_clicked();

private:
    Ui::MainWindow *ui;

    float randomRange(float, float);

    float getFitness(float, float, bool);


    float TotalFitness = 0;

    float probilities[COUNT], probilities_ranges[COUNT];

    float offsprint_x1;
    float offsprint_y1;
    float offsprint_x2;
    float offsprint_y2;

    data generateOffspring(float val){
        int init=0;
        for(int i=0; i <= COUNT; i++){
            if(val >= init && i!=COUNT && val < this->probilities_ranges[i]){
//                cout << "match";
//                cout << this->probilities_ranges[i] << endl;
                return this->population[i];
            }else if(val == init && i==COUNT){
//                cout << "match";
//                cout << this->probilities_ranges[i-1] << endl;
                return this->population[i-1];
            }else{
                init = this->probilities_ranges[i];
            }
        }
    }

    void mutation(float, float, float, float, bool);


    void generatePopulations(bool);
    void calc_prob_ranges(bool);


    void pso(void);
    void ais(void);
};

#endif // MAINWINDOW_H
