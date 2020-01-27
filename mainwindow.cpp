#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ResortReservationRecord.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //First Page
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{

}

void MainWindow::on_queen_clicked()
{

}

void MainWindow::on_king_clicked()
{

}

void MainWindow::on_standard_clicked()
{

}

void MainWindow::on_atrium_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
