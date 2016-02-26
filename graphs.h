#ifndef GRAPHS_H
#define GRAPHS_H

#include <QDialog>

namespace Ui {
class graphs;
}

class graphs : public QDialog
{
    Q_OBJECT

public:
    explicit graphs(QWidget *parent = 0);
    ~graphs();

private:
    Ui::graphs *ui;
};

#endif // GRAPHS_H
