//
// Created by Ioana Gavrila on 28.03.2025.
//

#pragma once
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
class School {
  private:
    string name;
    pair <float, float> address;
    string date;
    tuple<int, int, int> parseDate(const string& dateStr) const{
      istringstream iss(dateStr);
      int day, month, year;
      char delimiter;
      iss >> day>>delimiter >> month>>delimiter >> year;
      return {day, month, year};
      }
     bool was_visited;


  public:
    //constructor
    School();
    School(string name, pair <float, float> address, string date, bool is_visited);

    //destructor
    ~School();
    void setName(string name);
    void setAddress(tuple <float, float> address);
    void setDate(string date);
    void setIsVisited(bool is_visited);
    string getName();
    tuple <float, float> getAddress() const;
    string getDate() const;
    bool getIsVisited() const;
    string getDateString() const;
    string toString() const;
    bool isDateAfter(const std::string& otherDate) const {
      return parseDate(this->date) > parseDate(otherDate);
  }

    bool isDateBefore(const std::string& otherDate) const {
      return parseDate(this->date) < parseDate(otherDate);
  }
  };