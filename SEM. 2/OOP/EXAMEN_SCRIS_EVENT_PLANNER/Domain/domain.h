#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>

struct Event {
    std::string organiser;
    std::string name;
    std::string description;
    double latitude;
    double longitude;
    std::string date;
    std::vector<std::string> attendees;
    
    Event() : latitude(0.0), longitude(0.0) {}
    
    Event(const std::string& org, const std::string& n, const std::string& desc, 
          double lat, double lng, const std::string& d)
        : organiser(org), name(n), description(desc), 
          latitude(lat), longitude(lng), date(d) {}
};

struct Person {
    std::string name;
    double latitude;
    double longitude;
    bool isOrganiser;
    
    Person() : latitude(0.0), longitude(0.0), isOrganiser(false) {}
    
    Person(const std::string& n, double lat, double lng, bool org)
        : name(n), latitude(lat), longitude(lng), isOrganiser(org) {}
};

#endif // DOMAIN_H