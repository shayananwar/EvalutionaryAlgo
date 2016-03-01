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
    cout << data[graphno].generation << endl;
    cout << data[graphno].best.size() << endl;
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
