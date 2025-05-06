//
// Created by Ioana Gavrila on 28.03.2025.
//

#include "Repository.h"
#include <algorithm>

Repository::Repository() {
    this->schools.push_back(School("Avram Iancu", {46.33, 45.33}, "15.04.2022", false));
    this->schools.push_back(School("Mihai Viteazul", { 46.33, 45.33 }, "16.04.2022", false));
    this->schools.push_back(School("Gheorghe Sincai", { 46.33, 45.33 }, "17.04.2022", false));
    this->schools.push_back(School("Gheorghe Lazar", { 46.33, 45.33 }, "18.04.2022", false));
    this->schools.push_back(School("Gheorghe Asachi", { 46.33, 45.33 }, "19.04.2022", false));
}

void Repository::addSchool(School school){
  this->schools.push_back(school);
}
void Repository::removeSchool(School school){
    bool is_in_vector = false;
    int position = -1;
    for(int i = 0; i < this->schools.size(); i++){
      if(this->schools[i].getName() == school.getName()){
        is_in_vector = true;
        position = i;
      }
    }
    if(is_in_vector){
      this->schools.erase(this->schools.begin() + position);

    }
}
School Repository::getSchoolByName(string name){
    bool is_in_vector = false;
    int position = -1;
    for(int i = 0; i < this->schools.size(); i++){
        if(this->schools[i].getName() == name){
            return this->schools[i];
        }
    }


}
//function for having all the schools

vector<School> Repository::getSchools(){
    return this->schools;
}
vector<School> Repository::sorterSchools(){
    vector<School> copy = this->schools;
    sort(copy.begin(), copy.end(), [](School school1, School school2){ return school1.getName() < school2.getName();});
    return copy;
}
vector<School>  Repository::getSchoolsAfterDate(string date){
    vector<School> copy = this->schools;
    vector<School> result;
    for(int i = 0; i < copy.size(); i++){
      if(copy[i].isDateAfter(date)){
        result.push_back(copy[i]);
      }
    }
    return result;
}
vector<School> Repository::getSchoolsBeforeDate(string date){
    vector<School> copy = this->schools;
    vector<School> result;
    for(int i = 0; i < copy.size(); i++){
        if(copy[i].isDateBefore(date)){
            result.push_back(copy[i]);
        }
    }

    return result;
}