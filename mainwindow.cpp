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
    ui->NUM_NIGHTS->setVisible(false); //Number of nights is not displayed until valid data parameters are set
    ui->est_cost_output->setVisible(false); //No estimate is available -- no value will be shown.
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkValidResInfo()
{
    return ((numAdults + numKids) > 0 && (numAdults + numKids) <= maxGuests && numNights > 0 && endDate > beginDate);
}
bool MainWindow::checkValidCard(const QString&cardNum)
{
    QChar firstDigit = cardNum.front();

    if(cardType == 1 && firstDigit == '3'){ //American Express
        return true;
    } else if(cardType == 2 && firstDigit == '4'){ //Visa
        return true;
    } else if(cardType == 3 && firstDigit == '5'){ //Mastercard
        return true;
    }else if(cardType == 4 && firstDigit == '6'){ //Discover
        return true;
    }else{
        return false;
    }

}
void MainWindow::checkShowNumNights()
{
    if(beginDate.daysTo(endDate) > 0){
        ui->NUM_NIGHTS->setVisible(true);
    }
}
void MainWindow::checkShowNext()
{
    //If all reservation data is valid, make the next button visible.
        ui->next->setVisible(checkValidResInfo());
}
 void MainWindow::calculateCost()
{
     double roomCost = -1;
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
           //roomCost remains -1
         break;
     }
     if(roomCost != -1){
         ui->est_cost_output->setText(QString::number(roomCost));
         ui->est_cost_output->setVisible(true);
     }
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
void MainWindow::on_beginDate_userDateChanged(const QDate &date)
{
    beginDate = date;
    numNights = beginDate.daysTo(endDate); //Gets number of days from beginDate to endDate
    calculateCost();
    checkShowNumNights();
    checkShowNext();
}
void MainWindow::on_endDate_userDateChanged(const QDate &date)
{
    endDate = date;
    numNights = beginDate.daysTo(endDate); //Gets number of days from beginDate to endDate
    checkShowNumNights();
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

void MainWindow::on_visaRadio_toggled(bool checked)
{
    if(checked){
        cardType = 2; //Visa card
    }
}

void MainWindow::on_mastcrdRadio_toggled(bool checked)
{
    if(checked){
        cardType = 3; //Mastercard
    }
}

void MainWindow::on_discoveryRadio_toggled(bool checked)
{
    if(checked){
        cardType = 4; //Discovery card
    }
}

void MainWindow::on_amExprssRadio_toggled(bool checked)
{
    if(checked){
        cardType = 1; //American Express card
    }
}
