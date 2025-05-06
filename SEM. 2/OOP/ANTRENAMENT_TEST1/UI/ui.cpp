//
// Created by Ioana Gavrila on 28.03.2025.
//
#include "ui.h"
#include "../Repo/Repository.h"
#include <iostream>
#include <vector>
using namespace std;


void UI::printMenu(){
  cout<<"------------Schools Manager------------"<<endl;
  cout << "YOUR CHOICES:"<<endl;
  cout << "1. Add a school"<<endl;
  cout << "2. Remove a school"<<endl;
  cout << "3. Show all schools"<<endl;
  cout<<"4. Show all schools that have the planned date of visit before a date"<<endl;
  cout<<"5. Show all schools that have the planned date of visit after a date"<<endl;
  cout << "0. EXIT"<<endl;
}
UI::UI(){
  ;
}
void UI::menu(){
  while(true){
    printMenu();
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if(choice == 0){
      exit(0);
    }
    else if(choice == 1){
      string name;
      pair <float, float> address;
      string date;
      string visitedInput;
      bool is_visited;
      cout<<"Enter the name of the school: ";
      cin.ignore(); // Add this to clear the newline character
      getline(cin, name); // Use getline instead of cin >> to read the entire line

      cout<<"Enter the address of the school: ";
      cin >> address.first>>address.second;
      cout<<"Enter the date of the school: ";
      cin>>date;
      cout << "Was the school visited? (Type 'true' or 'false'): ";
      cin >> visitedInput;

      // Convert string to boolean
      if(visitedInput == "true" || visitedInput == "True" || visitedInput == "TRUE" || visitedInput == "1") {
        is_visited = true;
      } else {
        is_visited = false;
      }

      this->service.addSchool(School(name,address,date,is_visited));
    }
    else if(choice == 2){
      string name;
      cout<<"Type the name of the school you want to remove: ";
      cin>>name;
      this->service.RemoveSchool(this->service.getSchool(name));
      cout<<"Schools have been removed."<<endl;
    }
    else if(choice == 3){
      for(int i = 0; i < this->service.getSchools().size(); i++){
        cout << this->service.getSchools()[i].toString()<<endl;
      }
    }
    else if(choice == 4){
      string date;
      cout<<"Enter a date: "<<endl;
      cin>>date;
      vector<School> schools = this->service.getSchoolsAfterDate(date);

      for(int i = 0; i < schools.size(); i++){
        cout << schools[i].toString()<<endl;
      }
    }
    else if(choice == 5){
      string date;
      cout<<"Enter a date: "<<endl;
      cin>>date;
      vector<School> schools = this->service.getSchoolsBeforeDate(date);

      for(int i = 0; i < schools.size(); i++){
        cout << schools[i].toString()<<endl;
      }
    }
    else{
      cout << "Invalid Choice!"<<endl;
    }
  }

  }
