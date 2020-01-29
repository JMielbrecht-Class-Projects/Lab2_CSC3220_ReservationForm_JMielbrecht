#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_nameInput_textChanged(const QString &arg1);

    void on_next_clicked();

    void on_diffBtn_clicked();

    void on_exit_clicked();


    void on_queenStd_toggled(bool checked);

    void on_queenAtr_toggled(bool checked);

    void on_kngStd_toggled(bool checked);

    void on_kngAtr_toggled(bool checked);

    void on_beginDate_userDateChanged(const QDate &date);

    void on_endDate_userDateChanged(const QDate &date);

    void on_needPkgChkBx_toggled(bool checked);

    void on_bktoForm_clicked();

    void on_pay_clicked();

    void on_adultCt_valueChanged(int arg1);

    void on_childCt_valueChanged(int arg1);

    void calculateCost();
    bool checkValidResInfo();
    void checkShowNext();
    void checkShowNumNights();
    bool checkValidCard(const QString&cardNum);
    void updateResValues(); //Updates values on page 2

    void on_visaRadio_toggled(bool checked);

    void on_mastcrdRadio_toggled(bool checked);

    void on_discoveryRadio_toggled(bool checked);

    void on_amExprssRadio_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QString customerName;
    int roomType;
        /*
            ==ROOM TYPE==
            1: Standard 2 Queen Room (Maximum Guests: 4)
            2: Atrium 2 Queen Room (Maximum Guests: 4)
            3: Standard 1 King Room (Maximum Guests: 3)
            4: Atrium 1 King Room (Maximum Guests: 3)
        */
    int numNights;
    int cardType;
        /*
            ==CARD TYPE==
            1: American Express
            2: Visa
            3: Mastercard
            4: Discover
        */
    QDate beginDate;
    QDate endDate;
    int numAdults = 0; //Initialized to 0
    int numKids = 0; //Initialized to 0
    int maxGuests = 0; //Changes with room type; begins at 0 to prevent invalid "next" button visibility
    bool parkingNeeded;
    double subtotal = 0; //displayed on page 1
    double taxes; //How much in taxes owed for visit
    double resortFee; //$15 per night
    double parkingFee;//$12.75 per night
    double totalDue;

};
#endif // MAINWINDOW_H
