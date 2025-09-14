#include "Event.h"
#include "InputValidation.h" 
#include <iostream>
#include <cstring>   
#include <ctime>     // For time_t, tm, localtime, mktime
#include <iomanip>   // For std::put_time

// Initialize static member
int Event::eventCounter = 0;

// Default constructor implementation
Event::Event() : eventName(nullptr), date(nullptr), time(nullptr), eventLocation() {
    eventName = new char[1];
    eventName[0] = '\0';
    date = new char[1];
    date[0] = '\0';
    time = new char[1];
    time[0] = '\0';
    eventCounter++;
}

// Parameterized constructor implementation
Event::Event(const char* eventName, const char* date, const char* time, const Location& location)
    : eventName(nullptr), date(nullptr), time(nullptr), eventLocation(location) {
    eventCounter++;
    setEventName(eventName);
    setDate(date);
    setTime(time);
}

// Copy constructor implementation (Rule of 3)
Event::Event(const Event& other)
    : eventName(nullptr), date(nullptr), time(nullptr), eventLocation(other.eventLocation) {
    eventCounter++;
    if (other.eventName) {
        eventName = new char[strlen(other.eventName) + 1];
        strcpy(eventName, other.eventName);
    }
    if (other.date) {
        date = new char[strlen(other.date) + 1];
        strcpy(date, other.date);
    }
    if (other.time) {
        time = new char[strlen(other.time) + 1];
        strcpy(time, other.time);
    }
}

// Copy assignment operator implementation (Rule of 3)
Event& Event::operator=(const Event& other) {
    if (this != &other) { // Avoid self-assignment
        // 1. Deallocate old memory
        delete[] eventName;
        delete[] date;
        delete[] time;

        // 2. Deep copy new memory
        eventName = nullptr;
        date = nullptr;
        time = nullptr;

        if (other.eventName) {
            eventName = new char[strlen(other.eventName) + 1];
            strcpy(eventName, other.eventName);
        }
        if (other.date) {
            date = new char[strlen(other.date) + 1];
            strcpy(date, other.date);
        }
        if (other.time) {
            time = new char[strlen(other.time) + 1];
            strcpy(time, other.time);
        }
        eventLocation = other.eventLocation; // Use Location's assignment operator
    }
    return *this;
}

// Destructor implementation (Rule of 3)
Event::~Event() {
    delete[] eventName;
    delete[] date;
    delete[] time;
    eventCounter--;
}

// Accessor (Getter) methods
const char* Event::getEventName() const {
    return eventName;
}

const char* Event::getDate() const {
    return date;
}

const char* Event::getTime() const {
    return time;
}

const Location& Event::getEventLocation() const {
    return eventLocation;
}

int Event::getEventCounter() {
    return eventCounter;
}

// Mutator (Setter) methods with validation
void Event::setEventName(const char* newName) {
    if (newName != nullptr && strlen(newName) > 0) {
        delete[] eventName;
        eventName = new char[strlen(newName) + 1];
        strcpy(eventName, newName);
    } else {
        std::cout << "Invalid event name. Cannot be empty." << std::endl;
        delete[] eventName;
        eventName = new char[1];
        eventName[0] = '\0';
    }
}

void Event::setDate(const char* newDate) {
    // Basic validation: Check length and format (YYYY-MM-DD)
    if (newDate != nullptr && strlen(newDate) == 10 &&
        newDate[4] == '-' && newDate[7] == '-') {
        delete[] date;
        date = new char[strlen(newDate) + 1];
        strcpy(date, newDate);
    } else {
        std::cout << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
        delete[] date;
        date = new char[1];
        date[0] = '\0';
    }
}

void Event::setTime(const char* newTime) {
    // Basic validation: Check length and format (HH:MM)
    if (newTime != nullptr && strlen(newTime) == 5 && newTime[2] == ':') {
        delete[] time;
        time = new char[strlen(newTime) + 1];
        strcpy(time, newTime);
    } else {
        std::cout << "Invalid time format. Please use HH:MM." << std::endl;
        delete[] time;
        time = new char[1];
        time[0] = '\0';
    }
}

void Event::setEventLocation(const Location& newLocation) {
    eventLocation = newLocation; // Uses Location's copy assignment operator
}

// Generic methods
void Event::displayEventDetails() const {
    std::cout << "\n--- Event Details ---" << std::endl;
    std::cout << "Event Name: " << (eventName ? eventName : "N/A") << std::endl;
    std::cout << "Date: " << (date ? date : "N/A") << std::endl;
    std::cout << "Time: " << (time ? time : "N/A") << std::endl;
    std::cout << "--- Associated Location ---" << std::endl;
    eventLocation.displayLocationDetails();
    std::cout << "-------------------------" << std::endl;
}

bool Event::isEventUpcoming() const {
    if (!date || !time || strlen(date) == 0 || strlen(time) == 0) {
        return false; // Cannot determine if date/time is invalid
    }

    // Get current time
    time_t now = std::time(0);
    struct tm* ltm = localtime(&now);

    // Parse event date and time
    struct tm eventTm = {0};
    // Assuming YYYY-MM-DD and HH:MM
    sscanf(date, "%d-%d-%d", &eventTm.tm_year, &eventTm.tm_mon, &eventTm.tm_mday);
    sscanf(time, "%d:%d", &eventTm.tm_hour, &eventTm.tm_min);

    eventTm.tm_year -= 1900; // Years since 1900
    eventTm.tm_mon -= 1;     // Months since January (0-11)

    time_t eventTime = mktime(&eventTm);

    if (eventTime == (time_t)-1) {
        // Error converting event time
        return false;
    }

    return (eventTime > now);
}

// Static method
void Event::printEventCount() {
    std::cout << "Total number of Event objects created: " << eventCounter << std::endl;
}

// Operator overloads
// Stream insertion operator <<
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << "Event Name: " << (event.eventName ? event.eventName : "N/A") << std::endl;
    os << "Date: " << (event.date ? event.date : "N/A") << std::endl;
    os << "Time: " << (event.time ? event.time : "N/A") << std::endl;
    os << "Location: " << event.eventLocation.getName(); // Just print location name for brevity
    return os;
}

// Stream extraction operator >>
std::istream& operator>>(std::istream& is, Event& event) {
    char buffer[256]; // Temporary buffer for string inputs

    std::cout << "Enter Event Name: ";
    // Ensure buffer is clear from previous inputs
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    is.getline(buffer, sizeof(buffer));
    event.setEventName(buffer);

    std::cout << "Enter Date (YYYY-MM-DD): ";
    is.getline(buffer, sizeof(buffer));
    event.setDate(buffer);

    std::cout << "Enter Time (HH:MM): ";
    is.getline(buffer, sizeof(buffer));
    event.setTime(buffer);

    std::cout << "Enter Location details for this Event:\n";
    is >> event.eventLocation; // Use Location's stream extraction operator

    return is;
}

// Negation operator ! (e.g., !event could mean event is invalid/cancelled)
bool Event::operator!() const {
    // An event is considered "invalid" if its name, date, or time is empty/null
    // or if its associated location is invalid (e.g., 0 capacity).
    return (eventName == nullptr || strlen(eventName) == 0 ||
            date == nullptr || strlen(date) == 0 ||
            time == nullptr || strlen(time) == 0 ||
            eventLocation.calculateTotalCapacity() <= 0);
}
