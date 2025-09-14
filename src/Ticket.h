#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <cstring>  
#include "Event.h"  // A Ticket is for an Event

// Forward declaration for operator overloads
class Ticket;
std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
std::istream& operator>>(std::istream& is, Ticket& ticket);

class Ticket {
private:
    char* ticketID;     // Dynamically allocated char array for unique ID
    Event ticketEvent;  // Composition: A Ticket is for an Event
    char* seatInfo;     // Dynamically allocated char array for seat details (e.g., "Row 5, Seat 12, VIP Zone")
    bool isValid;       // Status of the ticket (true if valid, false if used/invalid)
    const double BASE_PRICE = 50.0; // Constant field: Base price for a ticket

    // Helper static method for generating random ID components
    static char* generateRandomIDComponent(int length);

public:
    // Default constructor
    Ticket();

    // Parameterized constructor
    Ticket(const Event& event, const char* seatInfo);

    // Copy constructor (Rule of 3)
    Ticket(const Ticket& other);

    // Copy assignment operator (Rule of 3)
    Ticket& operator=(const Ticket& other);

    // Destructor (Rule of 3)
    ~Ticket();

    // Accessor (Getter) methods
    const char* getTicketID() const;
    const Event& getTicketEvent() const;
    const char* getSeatInfo() const;
    bool getIsValid() const;
    double getBasePrice() const;

    // Mutator (Setter) methods with validation
    void setTicketID(const char* newID); // For setting a pre-generated ID
    void setTicketEvent(const Event& newEvent);
    void setSeatInfo(const char* newSeatInfo);
    void setIsValid(bool status);

    // Generic methods
    void generateTicketID();    // Generates a unique, random ID for the ticket
    void validateTicket();      // Marks the ticket as used/invalid
    double calculateTicketPrice(const char* category) const; // Calculates price based on category

    // Operator overloads
    // Stream insertion operator <<
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);

    // Stream extraction operator >>
    friend std::istream& operator>>(std::istream& is, Ticket& ticket);

    // Relational operator == (to compare ticket IDs)
    bool operator==(const Ticket& other) const;
};

#endif // TICKET_H
