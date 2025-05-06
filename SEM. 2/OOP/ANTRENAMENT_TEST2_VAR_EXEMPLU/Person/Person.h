//
// Created by Ioana Gavrila on 05.05.2025.
//

#pragma once
#include "/Users/ioanagavrila/CLionProjects/ANTRENAMENT_TEST2_VAR_EXEMPLU/Domain/Domain.h"
#include<string>
#include <vector>

using namespace std;

class Person{
  private:
    vector<Analysis*> analysis;
  public:
    Person(){
    //adding some default values
      BMI *el1 = new BMI("2025.09.20", 23.5);
      analysis.push_back(el1);
      BMI *el2 = new BMI("2025.08.01", 44.5);
      analysis.push_back(el2);

      BP *el3 = new BP("2025.08.02", 44, 56);
      analysis.push_back(el3);
      BP *el4 = new BP("2025.08.03", 29, 113);
      analysis.push_back(el4);
    }
    ~Person(){
      for(auto it: analysis){
        delete it;
      }

    }
    void addAnalysis(Analysis* analysis);
    vector<Analysis*> getAnalysisByMonth(int month);
    vector<Analysis*> getAll();
    bool isIll(int month);
    vector<Analysis*> getAnalysisBBetweenDates(string date1, string date2);
    void writeToFile(string fileName, string data1, string data2);
};
