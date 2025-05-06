//
// Created by Ioana Gavrila on 05.05.2025.
//

#pragma once
#include <string>
using namespace std;
class Appliance{

    public:
      string id;
      Appliance():id{" "} {};
      Appliance(string id_):id{id_}{};
      virtual double consumedElectricity();
      virtual string toString();

};
class Refrigerator: public Appliance{
  public:
    string electricityUsageClass;
    bool hasFreezer;
    Refrigerator(string id, string electricityUsageClass, bool hasFreezer):Appliance{id}, electricityUsageClass{electricityUsageClass}, hasFreezer{hasFreezer}{};
    double consumedElectricity();
    string toString();
};

class DishWasher: public Appliance{

  public:
    double consumedElectricityForOneHour;
    DishWasher(string id, double consumedElectricityForOneHour):Appliance{id}, consumedElectricityForOneHour{consumedElectricityForOneHour} {};
    double consumedElectricity();
    string toString();
};