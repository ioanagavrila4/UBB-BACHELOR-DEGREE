//
// Created by Ioana Gavrila on 03.05.2025.
//

#pragma once
#include "../Controller/Controller.h"
class UI{
  private:
    Controller controller;
  public:
    UI() {};
    ~UI() {};
    void run();
    void seeAllBuildings();
    void seeAllDemol();
    void seeAllres();
    void add();
    void saveAllDemol();
    void saveAllres();
};
