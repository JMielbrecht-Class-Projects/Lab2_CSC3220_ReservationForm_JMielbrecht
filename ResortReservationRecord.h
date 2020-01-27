#ifndef _RESORTRES_
#define _RESORTRES_

#include <string>

using namespace std;

class ResortReservationRecord {
  private:
  string customerName;
  int roomType;
  int numNights;
  bool parkingNeeded;

  public:
  string GetCustomer();
  void SetCustomerName(string name);
  int GetRoomType();
  void SetRoomType(int type);
  int GetNumNights();
  void SetNumNights(int nights);
  bool GetParkingNeeded();
  void SetParkingNeeded(bool needed);
  double CalculateCost();
  string CurrentChoice();

};
int GetPrices();

#endif //_RESORTRES_