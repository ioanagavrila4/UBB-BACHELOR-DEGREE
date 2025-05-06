//
// Created by Ioana Gavrila on 01.04.2025.
//

#pragma once
#include <string>
#include <sstream>
using namespace std;
class Bill{
  private:
    int serial_number;
    string company;
    int amount;
    bool is_paid;

  public:
    Bill();
    Bill(int serial_number, string company, int amount, bool is_paid);
    string get_company();
    int get_serial_number();
    int get_amount();
    bool get_is_paid();
    void set_serial_number(int serial_number);
    void set_company(string company);
    void set_amount(int amount);
    void set_is_paid(bool is_paid);
    void to_string();

};
