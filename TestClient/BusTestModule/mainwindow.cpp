#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_tem_cb_clicked()
{
    if(ui->tem_cb->isChecked()){
        ui->tem_min->setEnabled(true);
        ui->tem_max->setEnabled(true);
    }
    else{
        ui->tem_min->setEnabled(false);
        ui->tem_max->setEnabled(false);
    }
}

void MainWindow::on_hum_cb_clicked()
{
    if(ui->hum_cb->isChecked()){
        ui->hum_min->setEnabled(true);
        ui->hum_max->setEnabled(true);
    }
    else{
        ui->hum_min->setEnabled(false);
        ui->hum_max->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgbox;
    msgbox.setText("carCount : "+ui->carcount->text()+", Cycle : "+ui->cycle->text()+" seconds\ntemperature : "+ui->tem_min->text()+" ~ "+ui->tem_max->text()+", humidity : "+ui->hum_min->text()+" ~ "+ui->hum_max->text());
    msgbox.exec();


}
