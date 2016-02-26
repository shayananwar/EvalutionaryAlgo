#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <QDialog>

using namespace std;

namespace Ui {
class graphs;
}

class graphs : public QDialog
{
    Q_OBJECT

public:
    explicit graphs(QWidget *parent = 0);
    ~graphs();

    struct plots
    {
        QVector<double> best, avg;
        int generation;
    };

    std::vector<plots> data;


public slots:
    void makePlot(int);

private slots:
    void on_graphNo_valueChanged(double arg1);

private:
    Ui::graphs *ui;
};

#endif // GRAPHS_H
