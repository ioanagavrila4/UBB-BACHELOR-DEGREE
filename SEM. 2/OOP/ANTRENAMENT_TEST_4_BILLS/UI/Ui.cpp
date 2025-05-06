//
// Created by Ioana Gavrila on 01.04.2025.
//
#include "Ui.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include "../Domain/Bill.h"
ui::ui(){
  ;
}
void ui::print_menu(){
  cout<<"-----------------BILLS MANAGER-----------------"<<endl;
  cout<<"1. Add a bill"<<endl;
  cout<<"2. Show all bills"<<endl;
  cout<<"3. Show all paid bills"<<endl;
  cout<<"4. Get the amount of unpaid bills"<<endl;
  cout<<"0. Exit"<<endl;
}
void ui::menu(){
  int choice = 0;
  while(true){
    print_menu();
    cout << "CHOICE: ";
    cin >> choice;
    if(choice == 0){
      cout << "EXISTING THE PROGRAM..." << endl;
      exit(0);
    }
    else if(choice == 1){
      add_bill();
    }
    else if(choice == 2){
      show_all_bills();

    }
    else if(choice == 3){
      show_all_sorted_paid_bills();
    }
    else if(choice == 4){
      get_amount_unpaid_bills();
    }
  }
}
void ui::add_bill(){
  int serial_number;
  string company;
  int amount;
  bool is_paid;
  int paid_status;
  cout << "Type the serial number: ";
  cin >> serial_number;
  cout <<endl;
  cout << "Type the company: ";
  cin >> company;
  cout <<endl;
  cout << "Type the amount: ";
  cin >> amount;
  cout <<endl;
  cout << "Type the paid status following the next " <<endl << "1 - IS PAID"<<endl<< "2 - IS UNPAID"<<endl;
  cin >> paid_status;
  cout <<endl;
  if(paid_status == 1){
    is_paid = true;
  }
  else{
    is_paid = false;
  }
  this->service.add_bill(Bill(serial_number, company, amount, is_paid));
  
}
void ui::show_all_bills(){
  for(int i = 0; i < this->service.get_bills().size(); i++){
    this->service.get_bills()[i].to_string();
  }
}
void ui::show_all_sorted_paid_bills(){
  for(int i = 0; i < this->service.get_all_paid_bills().size(); i++){
    this->service.get_all_paid_bills()[i].to_string();
  }
}
void ui::get_amount_unpaid_bills(){
  cout << "Total amount of unpaid bills: ";
  cout << this->service.amount_unpaid() << endl;
}