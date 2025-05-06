//
// Created by Ioana Gavrila on 05.05.2025.
//

#pragma once

#include "../Domain/domain.h"
#include <vector>
using namespace std;
class Service
    {
  private:
    vector<Appliance*> applies;
  public:
    Service(){
      //add some default 2 refrig and 2 dishwashers
      Refrigerator *el1= new Refrigerator("1", "A", true);
      Refrigerator *el2= new Refrigerator("2", "A++", false);
      applies.push_back(el1);
      applies.push_back(el2);
      DishWasher *el3= new DishWasher("3", 12.3);
      applies.push_back(el3);
      DishWasher *el4= new DishWasher("4", 44.4);
      applies.push_back(el4);
    }
    ~Service(){
      for(auto el:applies){
        delete el;
      }
    }
  vector<Appliance*> getAll();
  vector<Appliance*> getAllWithConsumedElectricityThan(double maxElectricity);
  void writeToFile(string filename);
  void addAppliance(Appliance *el);
    };
