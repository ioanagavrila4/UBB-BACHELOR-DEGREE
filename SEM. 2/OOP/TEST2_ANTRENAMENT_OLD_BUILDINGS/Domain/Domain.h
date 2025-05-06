//
// Created by Ioana Gavrila on 03.05.2025.
//

#pragma once
#include <string>
using namespace std;
class Building{

  public:
    string address;
    int ContructionYear;
    Building():address{""},ContructionYear{0} {};
    Building(string address, int ContructionYear): address{address}, ContructionYear{ContructionYear} {};

    virtual bool mustBeRestored(){return false;};
    virtual bool mustBeDemol(){return false;};
    virtual string toString();
};

class Block : public Building{
  public:
    int totalApartments;
    int occupiedApartments;

    Block(string address, int ContructionYear, int totalApartments,  int occupiedApartments):Building{address, ContructionYear}, totalApartments{totalApartments}, occupiedApartments{occupiedApartments} {};
    string toString();
    bool mustBeRestored();
    bool mustBeDemol();

};

class House : public Building{
  public:
    string type;
    bool isHistorical;
    House(string address, int ContructionYear, string type, bool isHistorical):Building{address, ContructionYear},  type{type}, isHistorical{isHistorical} {};
    string toString();
    bool mustBeRestored();
    bool mustBeDemol();
};


