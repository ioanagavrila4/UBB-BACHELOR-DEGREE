//
// Created by Ioana Gavrila on 03.05.2025.
//

#pragma once
#include "../Domain/Domain.h"
#include <stdlib.h>
#include <vector>
using namespace std;

class Controller{
  private:
    vector <Building*> buildings;

  public:
    Controller(){
      Building *neonantal1 = new Block("Str.Morii, nr 13", 2009, 23, 4);
      Building* neonantal2 = new Block("Str.Morii, nr 15", 2008, 23, 20);

      Building* surgery1 = new House("Str.Morii, nr 49", 2009, "Tudor", true);
      Building* surgery2 = new House("Str.Norocului, nr 44", 2000, "Tudor", false);

      buildings.push_back(neonantal1);
      buildings.push_back(neonantal2);
      buildings.push_back(surgery1);
      buildings.push_back(surgery2);
    }
    ~Controller(){
      for(auto building : buildings){
        delete building;
      }
    }
    void addBuilding(Building *building);
    vector <Building *> getBuildings();
    vector <Building *> getToRestore();
    vector <Building *> getToDemol();
    void saveFileRes(string file);
    void saveFileDemo(string file);
  };

