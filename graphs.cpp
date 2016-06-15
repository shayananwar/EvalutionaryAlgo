#include "graphs.h"
#include "ui_graphs.h"

graphs::graphs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphs)
{
    ui->setupUi(this);

}

graphs::~graphs()
{
    delete ui;
}

void graphs::makePlot(int graphno){

    // generate some data:
    QVector<double> generations(20);
    for (int i=0; i< data[graphno].generation; i++)
    {
      generations[i] = i+1; // generations
    }

    //clear previous graphs
    ui->customPlot->clearGraphs();

    // create graph and assign data to it:
    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->axisRect()->outerRect();
    ui->customPlot->addGraph();
//    if(graphno == 10)
//        ui->customPlot->graph(0)->setData(generations, generations);
//    else
        ui->customPlot->graph(0)->setData(generations, data[graphno].best);

    ui->customPlot->graph(0)->setName("Best");

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(generations, data[graphno].avg);
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));

    ui->customPlot->graph(1)->setName("Average");

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setData(generations, data[graphno].pso_best);
    ui->customPlot->graph(2)->setPen(QPen(Qt::yellow));
    ui->customPlot->graph(2)->setName("pso-best");

    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setData(generations, data[graphno].ais_best);
    ui->customPlot->graph(3)->setPen(QPen(Qt::green));
    ui->customPlot->graph(3)->setName("ais-best");

    ui->customPlot->addGraph();
    ui->customPlot->graph(4)->setData(generations, data[graphno].ais_avg);
    ui->customPlot->graph(4)->setPen(QPen(QColor(255, 100, 0)));
    ui->customPlot->graph(4)->setName("ais-avg");

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("generatons");
    ui->customPlot->yAxis->setLabel("fitness");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 20);
    ui->customPlot->yAxis->setRange(0, 100);
    //ui->customPlot->rescaleAxes();
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes();
    ui->customPlot->replot();

}


void graphs::on_graphNo_valueChanged(double arg1)
{
    if(arg1 <= COUNT)
        makePlot(arg1);
}
