#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ResortReservationRecord.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //First Page
    ui->next->setVisible(false); //Next button is not displayed
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkValidResInfo()
{
    return ((numAdults + numKids) > 0 && (numAdults + numKids) <= maxGuests && numNights > 0 && endDate > beginDate);
}
void MainWindow::checkShowNext()
{
    //If all reservation data is valid, make the next button visible.
        ui->next->setVisible(checkValidResInfo());
}
 void MainWindow::calculateCost()
{
     double roomCost;
     switch(roomType){
       case 1:
         if(parkingNeeded){
           roomCost = (284 + 12.75)*numNights;
         }
         else{
           roomCost = 284*numNights;
         }
         break;
       case 2:
       if(parkingNeeded){
           roomCost = (325 + 12.75)*numNights;
         }
         else{
           roomCost = 325*numNights;
         }
         break;
       case 3:
       if(parkingNeeded){
           roomCost = (290 + 12.75)*numNights;
         }
         else{
           roomCost = 290*numNights;
         }
         break;
       case 4:
       if(parkingNeeded){
           roomCost = (350 + 12.75)*numNights;
         }
         else{
           roomCost = 350*numNights;
         }
         break;
       default:
         roomCost = -1; //ERROR
         break;
     }
     ui->est_cost_output->setText(QString::number(roomCost));
}
void MainWindow::on_next_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_diffBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_needPkgChkBx_toggled(bool checked)
{
    parkingNeeded = checked;
    calculateCost();
}

void MainWindow::on_exit_clicked() //EXIT BUTTON
{
    QApplication::quit();
}

void MainWindow::on_nameInput_textChanged(const QString &arg1)
{
    QString message = arg1;

        if (message.length() > 0){
            customerName = message;
        }
}

void MainWindow::on_queenStd_toggled(bool checked)
{
    if(checked){
        roomType = 1;
        maxGuests = 4;
    }
    calculateCost();
    checkShowNext();
}

void MainWindow::on_queenAtr_toggled(bool checked)
{
    if(checked){
        roomType = 2;
        maxGuests = 4;
    }
    calculateCost();
    checkShowNext();
}

void MainWindow::on_kngStd_toggled(bool checked)
{
    if(checked){
        roomType = 3;
        maxGuests = 3;
    }
    calculateCost();
    checkShowNext();
}

void MainWindow::on_kngAtr_toggled(bool checked)
{
    if(checked){
        roomType = 4;
        maxGuests = 3;
    }
    calculateCost();
    checkShowNext();
}

void MainWindow::on_numNights_valueChanged(int arg1)
{
    numNights = arg1;
    calculateCost();
    checkShowNext();
}

void MainWindow::on_beginDate_userDateChanged(const QDate &date)
{
    beginDate = date;
    calculateCost();
    checkShowNext();
}

void MainWindow::on_endDate_userDateChanged(const QDate &date)
{
    endDate = date;
    calculateCost();
    checkShowNext();
}

void MainWindow::on_bktoForm_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pay_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_adultCt_valueChanged(int arg1)
{
    numAdults = arg1;
    calculateCost();
    checkShowNext();
}

void MainWindow::on_childCt_valueChanged(int arg1)
{
    numKids = arg1;
    calculateCost();
    checkShowNext();
}
