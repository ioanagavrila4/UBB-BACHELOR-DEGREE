//
// Created by Ioana Gavrila on 05.05.2025.
//
#include "domain.h"
#include <string>
using namespace std;
double Appliance::consumedElectricity(){
  return 0;
}
string Appliance::toString(){
  string str = "APPLIANCE: " + id + "\n";
  return str;
}

double Refrigerator::consumedElectricity(){
  double result = 0;
  if(electricityUsageClass == "A"){
    result = 90;
  }
  else if(electricityUsageClass == "A++"){
    result = 60;
  }
  if (hasFreezer == true) {
    result = result +20;
  }
  return result;
}
string Refrigerator::toString(){
  string have;
  if(hasFreezer){
    have = "having";

  }else{
    have = "not having";
  }
  string str = "Refrigerator: " + Appliance::toString() + " with the electricity usage class: " + electricityUsageClass + " and " + have + " a freezer " + "\n";
  return str;
}


double DishWasher::consumedElectricity(){
  double result = 0;
  result = consumedElectricityForOneHour * 20;
  return result;
}
string DishWasher::toString(){
  string have;

  string str = "Refrigerator: " + Appliance::toString() + " with the consumed electricty in one hour: " + to_string(consumedElectricityForOneHour) +"\n";
  return str;
}


