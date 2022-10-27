#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
  //  ui->total->setText(QString::number( ui->newprice->text().toFloat() * ui->ammount->text().toFloat() ));
   // ui->ammount->setText(QString::number(  ui->total->text().toFloat() /ui->newprice->text().toFloat()  ));
     ui->ammount->setText(QString::number(  ui->total->text().toFloat() *ui->newprice->text().toFloat()  ));

}

void MainWindow::on_pushButton_2_clicked()
{
          ui->profit->setText(QString::number(  ui->ammount->text().toFloat() - ( ui->oldprice->text().toFloat() * ui->total->text().toFloat() )  ));
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
