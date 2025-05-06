//
// Created by Ioana Gavrila on 28.03.2025.
//
#include "Service.h"
#include "../Repo/Repository.h"
#include "../Domain/School.h"
#include <vector>
Service::Service() {
  ;
}

vector<School> Service::getSchools(){
  return this->repo.getSchools();
}
void Service::addSchool(School school){
  this->repo.addSchool(school);
}
void Service::RemoveSchool(School school){
  return this->repo.removeSchool(school);
}
vector<School> Service::getSchoolsBeforeDate(string date){
  return this->repo.getSchoolsBeforeDate(date);
}
vector<School> Service::getSchoolsAfterDate(string date){
  return this->repo.getSchoolsAfterDate(date);
}
School Service::getSchool(string name){
  return this->repo.getSchoolByName(name);
}