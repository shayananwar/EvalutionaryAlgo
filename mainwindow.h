#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <fstream>
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
            return (struct1.fitness > struct2.fitness);
        }
    };

    std::vector<data> population, newpopulation;
    QVector<double> best, avg;
    data temp;


private slots:
    void on_FPS_clicked();

    void on_RBS_clicked();

private:
    Ui::MainWindow *ui;

    int count = 20;
    int minX = -2;
    int maxX = 2;
    int minY = -5;
    int maxY = 5;
    string order = "desc";

    float randomRange(float, float);

    float getFitness(float, float);

    float TotalFitness = 0;

    float probilities[20], probilities_ranges[20];

    float offsprint_x1;
    float offsprint_y1;
    float offsprint_x2;
    float offsprint_y2;

    data generateOffspring(float val){
        int init=0;
        for(int i=0; i <= count; i++){
            if(val >= init && i!=count && val < this->probilities_ranges[i]){
                cout << "match";
                cout << this->probilities_ranges[i] << endl;
                return this->population[i];
            }else if(val == init && i==count){
                cout << "match";
                cout << this->probilities_ranges[i-1] << endl;
                return this->population[i-1];
            }else{
                init = this->probilities_ranges[i];
            }
        }
    }

    void mutation(float, float, float, float);


    void generatePopulations();
    void calc_prob_ranges();
};

#endif // MAINWINDOW_H
