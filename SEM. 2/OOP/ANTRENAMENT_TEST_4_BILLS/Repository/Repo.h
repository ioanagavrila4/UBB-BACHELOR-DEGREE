//
// Created by Ioana Gavrila on 01.04.2025.
//

#pragma once
#include "../Domain/Bill.h"
#include <vector>
using namespace std;
class Repo{
  private:
    vector<Bill> bills;
  public:
    Repo();
    void add_default_bills();
    void add_bill(Bill bill);
    vector<Bill> get_bills();
    void sort_bills();
    vector<Bill> get_paid_bills_sorted();
    int calculate_amount_unpaid_bills();

};