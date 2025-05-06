//
// Created by Ioana Gavrila on 28.03.2025.
//

#pragma once
#include "../Repo/Repository.h"
#include "../Domain/School.h"
#include <vector>
class Service{
  private:
    Repository repo = Repository();
  public:
    Service();
    vector<School> getSchools();
    void RemoveSchool(School school);
    void addSchool(School school);
    vector<School> getSchoolsBeforeDate(string date);
    vector<School> getSchoolsAfterDate(string date);
    School getSchool(string name);




  };

