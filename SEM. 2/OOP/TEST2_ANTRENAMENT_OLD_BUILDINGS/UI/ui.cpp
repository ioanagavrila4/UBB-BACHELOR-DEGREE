//
// Created by Ioana Gavrila on 03.05.2025.
//
#include "ui.h"
using namespace std;
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
void UI::run(){
  int option;
  while(1){
    cout << "1. SEE ALL BUILDINGS\n";
    cout <<"2. ADD A BUILDING\n";
    cout <<"3. SEE ALL BUILDINGS THAT CAN BE DEMO\n";
    cout <<"4. SEE ALL BUILDINGS THAT CAN BE REBUILD\n";
    cin >> option;
    if(option == 1){
      seeAllBuildings();
    }else if(option == 2) {
      add();
    }
    else if(option == 3) {
      seeAllDemol();
    }
    else if(option == 4) {
      seeAllres();
    }
    else {
      cout << "Invalid option passed\n";
      break;
    }

  }
}
void UI::seeAllBuildings(){
  vector<Building *> allBuildings = this->controller.getBuildings();
  for(auto building : allBuildings){
    cout << building->toString() << endl;
  }
}

void UI::seeAllDemol() {
  vector<Building *> allBuildings = this->controller.getToDemol();
  for(auto building : allBuildings) {
    cout << building->toString() << endl;
  }
}
void UI::seeAllres() {
  vector<Building *> allBuildings = this->controller.getToRestore();
  for(auto building : allBuildings) {
    cout << building->toString() << endl;
  }
}
void UI::saveAllDemol() {
  string file1, file2;
  cout << "1. File for restored";
  cin >> file1;
  cout << "2. File for demolished";
  cin >> file2;
  this->controller.saveFileRes(file1);
  this->controller.saveFileDemo(file2);
}

void UI::add() {
  int op;
  cout << "Please choose what type of building to add\n";
  cout<<"1. BLOCK\n";
  cout << "2. HOUSE\n";
  cin >> op;
  string address;
  int ContructionYear;
  cout << "Type the address of the building to add: ";

  cin >> address;
  cout<<"Type the ContructionYear of the building to add: ";
  cin >> ContructionYear;
  if(op == 1) {
    int totalApartments;
    int occupiedApartments;
    cout<<"Type the total number of apartments: \n";
    cin >> totalApartments;
    cout<<"Type the occupied number of apartments: \n";
    cin >> occupiedApartments;
    this->controller.addBuilding(new Block(address,  ContructionYear,  totalApartments,   occupiedApartments));
  }else if(op == 2) {
    string type;
    bool isHistorical;
    int intermediar;
    cout<<"Type the type of building to add: ";
    cin>>type;
    cout<<"Type the isHistorical of the building to add:1/0 ";
    cin>>intermediar;
    if (intermediar==0) isHistorical = false;
    else isHistorical = true;
    this->controller.addBuilding(new  House( address,  ContructionYear,  type,  isHistorical));
  }else {
    cout<<"Please choose what type of building to add";
  }

}