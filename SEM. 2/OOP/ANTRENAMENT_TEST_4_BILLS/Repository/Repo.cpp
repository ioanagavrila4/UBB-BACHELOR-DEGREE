//
// Created by Ioana Gavrila on 01.04.2025.
//

#include "Repo.h"
#include <vector>
#include <algorithm>
using namespace std;
Repo::Repo(){

}
void Repo::add_bill(Bill bill){
  this->bills.push_back(bill);
}
vector<Bill> Repo::get_bills(){
  return this->bills;
}
void Repo::sort_bills(){

}
vector<Bill> Repo::get_paid_bills_sorted(){
  vector<Bill> paid_bills;
  for(int i = 0; i < this->bills.size(); i++){
    if(this->bills[i].get_is_paid() == true){
      paid_bills.push_back(this->bills[i]);

    }
  }
  sort(paid_bills.begin(), paid_bills.end(),[](Bill bill1, Bill bill2){ return bill1.get_amount() > bill2.get_amount();} );
  return paid_bills;
}

int Repo::calculate_amount_unpaid_bills(){
  int amount_unpaid_bills = 0;
  for(int i = 0; i < this->bills.size(); i++){
    if(this->bills[i].get_is_paid() == false){
      amount_unpaid_bills += this->bills[i].get_amount();
    }
  }
  return amount_unpaid_bills;
}
void Repo::add_default_bills(){
  this->bills.push_back(Bill(1, "Company 1", 200, false));
  this->bills.push_back(Bill(2, "Company 2", 300, true));
  this->bills.push_back(Bill(3, "Company 3", 250, false));
  this->bills.push_back(Bill(4, "Company 4", 240, true));
  this->bills.push_back(Bill(5, "Company 5", 400, false));
}