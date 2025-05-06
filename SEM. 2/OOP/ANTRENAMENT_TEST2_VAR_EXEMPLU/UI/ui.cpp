//
// Created by Ioana Gavrila on 05.05.2025.
//

#include <iostream>
#include <string>
#include <vector>
#include "/Users/ioanagavrila/CLionProjects/ANTRENAMENT_TEST2_VAR_EXEMPLU/Domain/Domain.h"
#include "ui.h"

#include <optional>
using namespace std;

void ui::run(){
  while(1){
    int option;
    cout << "YOUR OPTIONS:\n";
    cout<<"1. Show All\n";
    cout <<"2. Add an analysis\n";
    cout<<"3. Show if you are ill\n";
    cout<<"4. Write to a File the data\n";
    cout<<"0. Exit\n";
    cout<<"YOUR OPTION AGAIN:\n";
    cin>>option;
    if(option == 1){
      showAll();
    }else if(option == 0){
      exit(1);
    }
    else if(option == 2) {
      addAnalysis();
    }
    else if(option == 3) {
      shoyIll();
    }
    else if(option == 4) {
      writeFile();
    }
  }
}
void ui::showAll(){
  for(auto an: this->service.getAll()){
    cout << an->toString() << endl;

  }
}
void ui::addAnalysis() {
  string data ;
  cout << "PLEASE TYPE A DATE: \n";
  cin>>data;
  int option ;
  cout <<"\nPLEASE CHOOSE WHAT TYPE OF ANALYSIS DO YOU WANT TO ADD: \n1. BMI\n2.BP\n";
  cin >> option;
  if (option == 1) {
    double value;
    cout << "PLEASE PUT THE VALUE FOR BMI: \n";
    cin >> value;
    BMI *el = new BMI(data, value);
    this->service.addAnalysis(el);
    cout << "The element was added!!";

  }
  else if (option == 2) {
    int systolic,diastolic;
    cout << "PLEASE PUT THE VALUE FOR SYSTOLIC BP: \n";
    cin >> systolic;
    cout <<"PLEASE PUT THE VALUE FOR DIASTOLIC BP: \n";
    cin >> diastolic;
    BP *el2 = new BP(data, systolic, diastolic);
    this->service.addAnalysis(el2);
    cout << "The element was added!!";
  }
}

void ui::shoyIll() {
  int data ;
  cout << "PLEASE TYPE A MONTH: \n";
  cin>>data;
  int is_ill = 0;
  if (this->service.isIll(data)) {
    cout << "THE PERSON IS ILL\n";
  }
  cout << "THE PERSON IS NOT ILL\n";


}

void ui::writeFile() {
    string fileName;
    cout << "PLEASE TYPE A FILE NAME: \n";
    cin >> fileName;
    string data1, data2;
    cout << "PLEASE TYPE A DATA 1: \n";
    cin>>data1;
    cout << "PLEASE TYPE A DATA 2: \n";
    cin>>data2;
    this->service.writeToFile(fileName, data1, data2);


}