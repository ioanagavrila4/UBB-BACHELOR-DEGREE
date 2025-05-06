//
// Created by Ioana Gavrila on 05.05.2025.
//

#include "Domain.h"

string Analysis::toString(){
  string str = "ANALYSIS " + date + " \n";
  return str;
}

bool BMI::isResult(){
  if(value <= 25 && value >= 18.5){
    return true;
  }
  return false;
}

bool BP::isResult(){
  if(systollicValue <= 119 && systollicValue >= 90 && diastolicValue <= 79 && diastolicValue >= 60){
    return true;
  }
  return false;
}
string BMI::toString(){
  string str = "ANALYSIS of type BMI " + Analysis::toString() + ", with the value:  " + to_string(value) + "\n";
  return str;
  }
string BP::toString(){
  string str = "ANALYSIS of type BP " + Analysis::toString() + ", with the systolic value: " + to_string(systollicValue) + " and with the diastolic value: " + to_string(diastolicValue) + "\n";
  return str;

}


