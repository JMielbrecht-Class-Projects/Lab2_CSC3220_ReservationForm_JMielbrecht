#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ResortReservationRecord.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //First Page
    ui->next->setVisible(false); //Next button is not displayed
    ui->NUM_NIGHTS->setVisible(false); //Number of nights is not displayed until valid data parameters are set
    ui->est_cost_output->setVisible(false); //No estimate is available -- no value will be shown.

    loadImage();

    ui->AtriumRoomImage->setPixmap(imageAtrium);
    ui->StandardRoomImage->setPixmap(imageStandard);
    ui->CreditCardImage->setPixmap(imageCreditCard);
    ui->QuestionImage->setPixmap(imageQuestion);
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
        ui->NUM_NIGHTS->setNum(numNights);
        ui->totalNumNight->setNum(numNights);
    }
}
void MainWindow::checkShowNext()
{
    //If all reservation data is valid, make the next button visible.
        ui->next->setVisible(checkValidResInfo());
}
 void MainWindow::calculateCost()
{
     switch(roomType){
       case 1:
         if(parkingNeeded){
          subtotal = (284 + 12.75)*numNights;
         }
         else{
           subtotal = 284*numNights;
         }
         break;
       case 2:
       if(parkingNeeded){
           subtotal = (325 + 12.75)*numNights;
         }
         else{
           subtotal = 325*numNights;
         }
         break;
       case 3:
       if(parkingNeeded){
           subtotal = (290 + 12.75)*numNights;
         }
         else{
           subtotal = 290*numNights;
         }
         break;
       case 4:
       if(parkingNeeded){
           subtotal = (350 + 12.75)*numNights;
         }
         else{
           subtotal = 350*numNights;
         }
         break;
       default:
           //subtotal remains 0
         break;
     }
     if(subtotal != 0){
         ui->est_cost_output->setText(QString::number(subtotal));
         ui->est_cost_output->setVisible(true);

     }
}
void MainWindow::updateResValues()
{
 //Updates room type, taxes, resort fee, parking fee, total due
    switch(roomType){
      case 1:
           taxes = 0.15*284;
           ui->taxOutput->setNum((taxes));
           ui->roomSelection->setText("Standard 2 Queen Room");
        break;
      case 2:
           taxes = 0.15*325;
           ui->taxOutput->setNum((taxes));
           ui->roomSelection->setText("Atrium 2 Queen Room");
        break;
      case 3:
           taxes = 0.15*290;
           ui->taxOutput->setNum((taxes));
           ui->roomSelection->setText("Standard 1 King Room");
        break;
      case 4:
           taxes = 0.15*350;
           ui->taxOutput->setNum((taxes));
           ui->roomSelection->setText("Atrium 1 King Room");
        break;
      default:
          taxes = -1; //INVALID
        break;
    }

    resortFee = numNights*15;
    parkingFee = numNights*12.75;
    totalDue = resortFee + subtotal; //Parking fee included in subtotal (calculated with calculateCost()
    ui->resFeeOutput->setNum(resortFee);
    ui->totalDueOutput->setNum(totalDue);
    ui->totalCost->setNum(totalDue);
}
 void MainWindow::on_next_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
     updateResValues();
}
void MainWindow::on_diffBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_needPkgChkBx_toggled(bool checked)
{
    parkingNeeded = checked;
    calculateCost();
    ui->pkgFeeOutput->setNum(parkingFee);
    ui->parkingIncluded->setText("Yes");
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
        ui->rmTypeOutput->setText("Standard 2 Queen Room");
        maxGuests = 4;
    }
    calculateCost();
    checkShowNext();
    updateResValues();
}
void MainWindow::on_queenAtr_toggled(bool checked)
{
    if(checked){
        roomType = 2;
        maxGuests = 4;
        ui->rmTypeOutput->setText("Atrium 2 Queen Room");
    }
    calculateCost();
    checkShowNext();
}
void MainWindow::on_kngStd_toggled(bool checked)
{
    if(checked){
        roomType = 3;
        maxGuests = 3;
        ui->rmTypeOutput->setText("Standard 1 King Room");
    }
    calculateCost();
    checkShowNext();
}
void MainWindow::on_kngAtr_toggled(bool checked)
{
    if(checked){
        roomType = 4;
        maxGuests = 3;
        ui->rmTypeOutput->setText("Atrium 1 King Room");
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
    ui->numAdults->setNum(numAdults);
}
void MainWindow::on_childCt_valueChanged(int arg1)
{
    numKids = arg1;
    calculateCost();
    checkShowNext();
    ui->numKids->setNum(numKids);
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
void MainWindow::loadImage(){
    QString atriumFile = ":/Images/Atrium.jpg";
    QString standardFile = ":/Images/Standard.jpg";
    QString creditCardFile = ":/Images/creditCardNumber.jpg";
    QString questionFile = ":/Images/Question.jpg";


    if(imageAtrium.load(atriumFile)){
        std::cout << "Atrium Image loaded" << std::endl;
        imageAtrium = imageAtrium.scaled(ui->AtriumRoomImage->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageStandard.load(standardFile)){
        std::cout << "Standard Image loaded" << std::endl;
        imageStandard = imageStandard.scaled(ui->StandardRoomImage->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageCreditCard.load(creditCardFile)){
        std::cout << "Credit Card Image loaded" << std::endl;
        imageCreditCard = imageCreditCard.scaled(ui->CreditCardImage->size(), Qt::KeepAspectRatioByExpanding);
    }
    if(imageQuestion.load(questionFile)){
        std::cout << "Question Image loaded" << std::endl;
        imageQuestion = imageQuestion.scaled(ui->QuestionImage->size(), Qt::KeepAspectRatio);
    }

}


void MainWindow::on_nextButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
