#include "service.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

EventService::EventService() {}

void EventService::loadEventsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open events file: " << filename << std::endl;
        return;
    }
    
    events.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string organiser, name, description, date;
        double latitude, longitude;
        
        if (std::getline(ss, organiser, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, description, ',') &&
            ss >> latitude && ss.ignore() &&
            ss >> longitude && ss.ignore() &&
            std::getline(ss, date)) {
            
            events.push_back(Event(organiser, name, description, latitude, longitude, date));
        }
    }
    file.close();
}

void EventService::loadPeopleFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open people file: " << filename << std::endl;
        return;
    }
    
    people.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, organiserStr;
        double latitude, longitude;
        bool isOrganiser;
        
        if (std::getline(ss, name, ',') &&
            ss >> latitude && ss.ignore() &&
            ss >> longitude && ss.ignore() &&
            std::getline(ss, organiserStr)) {
            
            isOrganiser = (organiserStr == "true" || organiserStr == "1");
            people.push_back(Person(name, latitude, longitude, isOrganiser));
        }
    }
    file.close();
}

void EventService::saveEventsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot save to events file: " << filename << std::endl;
        return;
    }
    
    for (const auto& event : events) {
        file << event.organiser << "," << event.name << "," << event.description << ","
             << event.latitude << "," << event.longitude << "," << event.date;
        
        // Save attendees
        for (const auto& attendee : event.attendees) {
            file << "," << attendee;
        }
        file << std::endl;
    }
    file.close();
}

std::vector<Event> EventService::getAllEvents() const {
    return sortEventsByDate(events);
}

std::vector<Event> EventService::getEventsForPerson(const std::string& personName) const {
    std::vector<Event> result;
    for (const auto& event : events) {
        if (event.organiser == personName || 
            std::find(event.attendees.begin(), event.attendees.end(), personName) != event.attendees.end()) {
            result.push_back(event);
        }
    }
    return sortEventsByDate(result);
}

std::vector<Event> EventService::getEventsNearPerson(const std::string& personName, double maxDistance) const {
    Person person = getPersonByName(personName);
    if (person.name.empty()) {
        return {};
    }
    
    std::vector<Event> result;
    for (const auto& event : events) {
        double distance = calculateDistance(person.latitude, person.longitude, 
                                          event.latitude, event.longitude);
        if (distance <= maxDistance) {
            result.push_back(event);
        }
    }
    return sortEventsByDate(result);
}

std::vector<Event> EventService::getPopularEvents() const {
    std::vector<Event> sorted = events;
    std::sort(sorted.begin(), sorted.end(), 
        [](const Event& a, const Event& b) {
            return a.attendees.size() > b.attendees.size();
        });
    return sorted;
}

std::vector<Person> EventService::getAllPeople() const {
    return people;
}

Person EventService::getPersonByName(const std::string& name) const {
    for (const auto& person : people) {
        if (person.name == name) {
            return person;
        }
    }
    return Person(); // Return empty person if not found
}

bool EventService::isPersonOrganiser(const std::string& name) const {
    Person person = getPersonByName(name);
    return person.isOrganiser;
}

bool EventService::addEvent(const Event& event) {
    // Check if event with same name and location already exists
    for (const auto& e : events) {
        if (e.name == event.name && e.latitude == event.latitude && e.longitude == event.longitude) {
            return false; // Event already exists
        }
    }
    events.push_back(event);
    return true;
}

bool EventService::addPersonToEvent(const std::string& personName, const std::string& eventName) {
    for (auto& event : events) {
        if (event.name == eventName) {
            // Check if person is already attending
            if (std::find(event.attendees.begin(), event.attendees.end(), personName) == event.attendees.end()) {
                event.attendees.push_back(personName);
                return true;
            }
        }
    }
    return false;
}

bool EventService::updateEventDescription(const std::string& eventName, const std::string& newDescription) {
    for (auto& event : events) {
        if (event.name == eventName) {
            event.description = newDescription;
            return true;
        }
    }
    return false;
}

bool EventService::updateEventDate(const std::string& eventName, const std::string& newDate) {
    for (auto& event : events) {
        if (event.name == eventName) {
            event.date = newDate;
            return true;
        }
    }
    return false;
}

double EventService::calculateDistance(double lat1, double lng1, double lat2, double lng2) const {
    // Simple Euclidean distance for simplicity
    double deltaLat = lat2 - lat1;
    double deltaLng = lng2 - lng1;
    return std::sqrt(deltaLat * deltaLat + deltaLng * deltaLng);
}

std::vector<Event> EventService::sortEventsByDate(const std::vector<Event>& events) const {
    std::vector<Event> sorted = events;
    std::sort(sorted.begin(), sorted.end(), 
        [](const Event& a, const Event& b) {
            return a.date < b.date;
        });
    return sorted;
}