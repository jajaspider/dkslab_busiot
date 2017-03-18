#include "statuswindow.h"

statuswindow::statuswindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statuswindow)
{
    ui->setupUi(this);
}

statuswindow::~statuswindow()
{
    delete ui;
}
