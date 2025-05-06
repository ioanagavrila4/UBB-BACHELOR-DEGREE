//
// Created by Ioana Gavrila on 28.03.2025.
//
#pragma once
#include"../Domain/School.h"
#include <iostream>
using namespace std;
#include <vector>
class Repository{
    private:
      //the list of schools
        vector <School> schools;
    public:
      //constructor
        Repository();
        void addSchool(School school);
        void removeSchool(School school);
        School getSchoolByName(string name);
        //function for having all the schools

        vector<School> getSchools();
        vector<School> sorterSchools();
        vector<School>  getSchoolsAfterDate(string date);
        vector<School> getSchoolsBeforeDate(string date);
        //destructor
      };