//
// Created by Ioana Gavrila on 05.05.2025.
//

#include "Person.h"
#include <fstream>
vector<Analysis*> Person::getAll(){
  vector<Analysis*> all = this->analysis;
  return all;
}
void Person::addAnalysis(Analysis* analysis) {
  this->analysis.push_back(analysis);
}
vector<Analysis*> Person::getAnalysisByMonth(int month) {
  vector<Analysis*> all;
  for (auto an: this->analysis) {
    int month_n = stoi(an->date.substr(5, 2));
    if (month_n > month) {
      all.push_back(an);
    }
  }
  return all;
}

bool Person::isIll(int month) {
  vector<Analysis*> all;
  for (auto an: this->analysis) {
    int month_n = stoi(an->date.substr(5, 2));
    if (month_n == month) {
      if (!an->isResult()) {
        return false;
      }
    }
  }
  return true;
}
vector<Analysis*> Person::getAnalysisBBetweenDates(string date1, string date2) {
  vector<Analysis*> all;
  int month_1 = stoi(date1.substr(5, 2));
  int month_2 = stoi(date2.substr(5, 2));
  int day_1 = stoi(date1.substr(8, 2));
  int day_2 = stoi(date2.substr(8, 2));
  int year_1 = stoi(date1.substr(0, 4));
  int year_2 = stoi(date2.substr(0, 4));
  for (auto an: this->analysis) {
    int month_n = stoi(an->date.substr(5, 2));
    int day_n = stoi(an->date.substr(8, 2));
    int year_n = stoi(an->date.substr(0, 4));
    bool isAfterOrEqualStartDate = (year_n > year_1) ||
                                   (year_n == year_1 && month_n > month_1) ||
                                   (year_n == year_1 && month_n == month_1 && day_n >= day_1);

    bool isBeforeOrEqualEndDate = (year_n < year_2) ||
                                 (year_n == year_2 && month_n < month_2) ||
                                 (year_n == year_2 && month_n == month_2 && day_n <= day_2);

    if (isAfterOrEqualStartDate && isBeforeOrEqualEndDate) {
      all.push_back(an);
    }

  }
  return all;
}
void Person::writeToFile(string fileName, string data1, string data2) {
  ofstream fout(fileName);
  vector<Analysis*> all = getAnalysisBBetweenDates(data1, data2);
  for (auto an: all) {
    fout << an->toString() << endl;
  }
}