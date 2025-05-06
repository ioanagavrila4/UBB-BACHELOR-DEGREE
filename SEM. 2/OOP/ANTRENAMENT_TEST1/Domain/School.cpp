//
// Created by Ioana Gavrila on 28.03.2025.
//
#import "School.h"
#include <sstream>
using namespace std;

School::School(string name, pair <float, float> address, string date, bool is_visited){
  this->name = name;
  this->address = address;
  this->date = date;
  this->was_visited = is_visited;
}
void  School::setName(string name){
  this->name = name;
  }
void School::setAddress(tuple <float, float> address){
  this->address = address;
  }
void School::setDate(string date){
  this->date = date;
  }
void School::setIsVisited(bool is_visited){
  this->was_visited = is_visited;
  }
School::~School() {
  ;
}
string School::getName(){
  return this->name;
  }
tuple <float, float> School::getAddress() const{
  return this->address;
  }
string School::getDate() const{
  return this->date;
  }
bool School::getIsVisited() const{
  return this->was_visited;
  }

string School::toString() const{
  stringstream ss;
  ss << "School: " << name << " Location: " << address.first << " " << address.second <<"Data: " << date << " School was visited: "<< was_visited;
  return ss.str();
  }
//bool School::SchoolAfterDate(string date){
//
//  }
//bool School::SchoolBeforeDate(string date)
//      {
//  }
