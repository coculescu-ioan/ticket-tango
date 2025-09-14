#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <cstring>  
#include "Location.h" // Event has a Location

// Forward declaration for operator overloads
class Event;
std::ostream& operator<<(std::ostream& os, const Event& event);
std::istream& operator>>(std::istream& is, Event& event);

class Event {
private:
    char* eventName;    // Dynamically allocated char array for event name
    char* date;         // Date of the event (e.g., "YYYY-MM-DD")
    char* time;         // Time of the event (e.g., "HH:MM")
    Location eventLocation; // Composition: An Event has a Location
    static int eventCounter; // Static field: Counts the total number of Event objects created

public:
    // Default constructor
    Event();

    // Parameterized constructor
    Event(const char* eventName, const char* date, const char* time, const Location& location);

    // Copy constructor (Rule of 3)
    Event(const Event& other);

    // Copy assignment operator (Rule of 3)
    Event& operator=(const Event& other);

    // Destructor (Rule of 3)
    ~Event();

    // Accessor (Getter) methods
    const char* getEventName() const;
    const char* getDate() const;
    const char* getTime() const;
    const Location& getEventLocation() const;
    static int getEventCounter();

    // Mutator (Setter) methods with validation
    void setEventName(const char* newName);
    void setDate(const char* newDate); // Basic format validation
    void setTime(const char* newTime); // Basic format validation
    void setEventLocation(const Location& newLocation);

    // Generic methods
    void displayEventDetails() const; // Displays all details of the event and its location
    bool isEventUpcoming() const;     // Checks if the event date/time is in the future (simple check)

    // Static method
    static void printEventCount(); // Prints the total number of Event objects

    // Operator overloads
    // Stream insertion operator <<
    friend std::ostream& operator<<(std::ostream& os, const Event& event);

    // Stream extraction operator >>
    friend std::istream& operator>>(std::istream& is, Event& event);

    // Negation operator ! (e.g., !event could mean event is invalid/cancelled)
    bool operator!() const;
};

#endif
