//
// Created by Ioana Gavrila on 01.04.2025.
//
#include "Bill.h"

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

Bill::Bill(int serial_number, string company, int amount, bool is_paid){
  this->serial_number = serial_number;
  this->company = company;
  this->amount = amount;
  this->is_paid = is_paid;

}
string Bill::get_company(){
  return this->company;
}
int Bill::get_serial_number(){
  return this->serial_number;
}
int Bill::get_amount(){
  return this->amount;
}
bool Bill::get_is_paid(){
  return this->is_paid;
}
void Bill::set_serial_number(int serial_number){
  this->serial_number = serial_number;
}
void Bill::set_company(string company){
  this->company = company;
}
void Bill::set_amount(int amount){
  this->amount = amount;
}
void Bill::set_is_paid(bool is_paid){
  this->is_paid = is_paid;
}
void Bill::to_string(){
  cout << "SERIAL NUMBER: " << this->serial_number << " COMPANY: "<< this->company << " AMOUNT: " << this->amount << " IS_PAID: " << this->is_paid << endl;

}