//
// Created by Ioana Gavrila on 05.05.2025.
//

#pragma once
#include <string>
using namespace std;
class Analysis{

public:
  string date;
  Analysis():date{" "} {};
  Analysis(string date) : date{date}{};
  virtual bool isResult() { return false; };
  virtual string toString();
};

class BMI : public Analysis{
  public:
    double value;
    BMI(string date, double value) : Analysis{date}, value{value}{};
     bool isResult();
     string toString();
};

class BP : public Analysis{
  public:
    int systollicValue;
    int diastolicValue;
    BP(string date, int systollicValue, int diastolicValue) : Analysis{date}, systollicValue{systollicValue}, diastolicValue{diastolicValue}{};
     bool isResult();
     string toString();
};