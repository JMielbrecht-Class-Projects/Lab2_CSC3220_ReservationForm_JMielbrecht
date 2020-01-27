#include "ResortReservationRecord.h"
#include <string>
#include <sstream>

 string ResortReservationRecord::GetCustomer(){
   return customerName;
 }

 void ResortReservationRecord::SetCustomerName(string name){
   customerName = name;
 }
  int ResortReservationRecord::GetRoomType(){
    return roomType;
  }
  void ResortReservationRecord::SetRoomType(int type){
    roomType = type;
  }
  
  int ResortReservationRecord::GetNumNights(){
    return numNights;
  }
   void ResortReservationRecord::SetNumNights(int nights){
     numNights = nights;
   }

  bool ResortReservationRecord::GetParkingNeeded(){
    return parkingNeeded;
  }
  void ResortReservationRecord::SetParkingNeeded(bool needed){
    parkingNeeded = needed;
  }

  double ResortReservationRecord::CalculateCost(){
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
    
    return roomCost;
  };

string ResortReservationRecord::CurrentChoice(){
  stringstream strang;
  string parkNeed;
  if(GetParkingNeeded()){
      parkNeed = "Yes";
    }else{
      parkNeed = "No";
    }
    
  strang << "===Current reservation choices===" <<'\n' 
        << "Name of customer: " << GetCustomer() <<  '\n' 
        << "Number of Nights Stayed: " << GetNumNights() << '\n'
  << "Room Type: " << GetRoomType() << '\n'
  << "Parking needed? " << parkNeed << '\n' << '\n';

  return strang.str();
}
