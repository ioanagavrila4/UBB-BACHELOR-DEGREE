#ifndef SERVICE_H
#define SERVICE_H

#include "../Domain/domain.h"
#include <vector>
#include <string>
#include <cmath>

class EventService {
private:
    std::vector<Event> events;
    std::vector<Person> people;
    
public:
    EventService();
    
    // File operations
    void loadEventsFromFile(const std::string& filename);
    void loadPeopleFromFile(const std::string& filename);
    void saveEventsToFile(const std::string& filename);
    
    // Event operations
    std::vector<Event> getAllEvents() const;
    std::vector<Event> getEventsForPerson(const std::string& personName) const;
    std::vector<Event> getEventsNearPerson(const std::string& personName, double maxDistance = 5.0) const;
    std::vector<Event> getPopularEvents() const;
    
    // Person operations
    std::vector<Person> getAllPeople() const;
    Person getPersonByName(const std::string& name) const;
    bool isPersonOrganiser(const std::string& name) const;
    
    // Event management
    bool addEvent(const Event& event);
    bool addPersonToEvent(const std::string& personName, const std::string& eventName);
    bool updateEventDescription(const std::string& eventName, const std::string& newDescription);
    bool updateEventDate(const std::string& eventName, const std::string& newDate);
    
    // Utility
    double calculateDistance(double lat1, double lng1, double lat2, double lng2) const;
    std::vector<Event> sortEventsByDate(const std::vector<Event>& events) const;
};

// Observer pattern for notifications
class EventObserver {
public:
    virtual ~EventObserver() = default;
    virtual void onEventUpdated() = 0;
};

#endif // SERVICE_H