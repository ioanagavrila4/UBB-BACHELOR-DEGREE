//
// Created by Ioana Gavrila on 05.05.2025.
//
#include "controller.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
vector<Appliance*> Service::getAll(){
  return applies;
}
vector<Appliance*> Service::getAllWithConsumedElectricityThan(double maxElectricity){
  vector<Appliance*> copy_applies = applies;
  vector<Appliance*> result;
  for(auto el: copy_applies){
    if(el->consumedElectricity() > maxElectricity){
      result.push_back(el);

    }
  }
  return result;
}
void Service::writeToFile(string filename){
  ofstream fout(filename);
  for(auto el: applies){
    fout << el->toString() << endl;
  }
}
void Service::addAppliance(Appliance *el){
  applies.push_back(el);
}