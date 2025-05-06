//
// Created by Ioana Gavrila on 01.04.2025.
//

#pragma once
#include <vector>
#include <algorithm>
#include "../Repository/Repo.h"
class Service{
  private:
    Repo repo = Repo();

  public:
    Service();
    void add_bill(Bill bill);
    vector<Bill> get_bills();
    vector<Bill> get_all_paid_bills();
    int amount_unpaid();
};
