//
// Created by Ioana Gavrila on 05.05.2025.
//
#include "ui.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
void ui::run(){
  while(1){
    int option;
    cout << "YOUR MENU:" << endl;
    cout << "1. Add Element" << endl;
    cout << "2. Show All" << endl;
    cout << "3. Show all inefficient applies" << endl;
    cout << "4. Save to file" << endl;
    cout << "0. Exit" << endl;
    cout << "Your option: ";
    cin >> option;
    if(option == 1){
      addElem();
    }else if(option == 2){
      showAll();
    }else if(option == 3){
      showInef();
    }else if(option == 4){
      saveToFile();
    }else if(option == 0){
      exit(1);
    }

  }
}
void ui::addElem(){
  string id;

  int op;
  cout << "ID : ";
  cin >> id;
  cout << "WHAT TYPE OF APPLIANCE DO YOU WANT??" <<endl;
  cout << "1. REFRIGERATOR" << endl;
  cout << "2. DISHWASHER" << endl;
  cout << "Your choice: " << endl;
  cin >> op;
  if(op == 1){
    string elecClass;
    bool hasFrezeer;
    cout << "TYPE THE USAGE CLASS (A/A++) : \n";
    cin >> elecClass;
    int op2;
    cout << "DOES THE REFRIGERATOR HAS A FREEZER? 1/0" << endl;
    cin>>op2;
    if(op2 == 1){
      hasFrezeer = true;
    }else if(op2 == 0){
      hasFrezeer = false;
    }

    Refrigerator *el = new Refrigerator(id, elecClass, hasFrezeer);
    this->service.addAppliance(el);
  }
  else if(op == 2){
    double consumed;
    cout << "PLEASE TYPE THE CONSUMED ELECTRICITY FOR ONE HOUR: \n";
    cin >> consumed;
    DishWasher *el2 = new DishWasher(id, consumed);
    this->service.addAppliance(el2);
  }
  cout << "THE ELEMENT WAS ADDED";
}
void ui::showAll(){
  for(auto el: this->service.getAll()){
    cout << el->toString() << endl;
  }
}
void ui::showInef(){
  vector<Appliance*> copy_applies = this->service.getAllWithConsumedElectricityThan(100);
  for(auto el: copy_applies){
    cout << el->toString() << endl;
  }
}
void ui::saveToFile(){
  string FileName;
  cout << "Please type the file path: \n";
  cin>>FileName;
  this->service.writeToFile(FileName);
}