//
// Created by Ioana Gavrila on 01.04.2025.
//

#pragma once
#include "../Service/Service.h"
#include <iostream>
using namespace std;
#include <vector>

class ui{
  private:
    Service service = Service();
  public:
    ui();
    void print_menu();
    void menu();
    void add_bill();
    void show_all_bills();
    void show_all_sorted_paid_bills();
    void get_amount_unpaid_bills();
};