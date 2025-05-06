//
// Created by Ioana Gavrila on 01.04.2025.
//
#include "Service.h"
#include <vector>
#include <algorithm>
using namespace std;
Service::Service(){
  this->repo.add_default_bills();
}
void Service::add_bill(Bill bill){
  this->repo.add_bill(bill);
}
vector<Bill> Service::get_bills(){
  return this->repo.get_bills();
}
vector<Bill> Service::get_all_paid_bills(){
  return this->repo.get_paid_bills_sorted();
}
int Service::amount_unpaid(){
  return this->repo.calculate_amount_unpaid_bills();
}
