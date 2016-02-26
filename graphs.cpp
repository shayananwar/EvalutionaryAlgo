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
