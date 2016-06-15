#ifndef GRAPHS_H
#define GRAPHS_H

#include <config.h>
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
        QVector<double> best, avg, pso_best, ais_best, ais_avg;
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
