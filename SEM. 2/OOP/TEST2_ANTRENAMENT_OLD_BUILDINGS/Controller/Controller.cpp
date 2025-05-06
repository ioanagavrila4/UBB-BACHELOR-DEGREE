//
// Created by Ioana Gavrila on 03.05.2025.
//
#include "Controller.h"
#include <fstream>
void Controller::addBuilding(Building *building){
  buildings.push_back(building);
}
vector <Building *> Controller::getBuildings(){
  return buildings;
}
vector <Building *> Controller::getToRestore() {
  vector <Building *> toRestore = this->getToRestore();
  return toRestore;
}
vector <Building *> Controller::getToDemol() {
  vector <Building *> toDemol = this->getToDemol();
  return toDemol;
}

void Controller::saveFileRes(string file) {
  ofstream fout(file);
  for (auto building : this->getToRestore()) {
    fout<<building->toString()<<endl;
  }
}
void Controller::saveFileDemo(string file) {
  ofstream fout(file);
  for (auto building : this->getToDemol()) {
    fout<<building->toString()<<endl;
  }
}