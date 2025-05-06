//
// Created by Ioana Gavrila on 03.05.2025.
//

#include "Domain.h"
#include <string>
using namespace std;
string Building::toString(){
  string name = "Building" + address + "\n Construction Year:  " + to_string(ContructionYear) + "\n";
  return name;
}

string Block::toString(){
  string name = "Block " + Building::toString() +  "\nTotal no of apartments: " + to_string(totalApartments) + "\nOccupied appartments " + to_string(occupiedApartments) + "\n";
  return name;
}
//100% ... total number
//80*totalnumber/100
bool Block::mustBeRestored() {
  int no_of_years = 2025 - Building::ContructionYear;
  int percentage = (80*this->totalApartments)/100;

  if (no_of_years > 40 && this->occupiedApartments > percentage) {
    return true;
  }
  return false;
}
bool House::mustBeRestored() {
  if (this->isHistorical) {
    return false;
  }
  int no_of_years = 2025 - Building::ContructionYear;
  if (no_of_years > 100) {
    return true;
  }
  return false;
}
bool Block::mustBeDemol() {
  int percentage = (80*this->totalApartments)/100;
  if (percentage < 5) {
    return true;
  }
  return false;
}
bool House::mustBeDemol() {
  if (this->isHistorical) {
    return false;
  }
  return true;
}
string House::toString(){
  string name = "House " + Building::toString() + "\nType: " + type + "\n is it historical: " + "\n";
  return name;
}

