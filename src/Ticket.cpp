#include "Ticket.h"
#include "InputValidation.h"
#include <iostream>
#include <cstring>   
#include <cstdlib>   // For rand(), srand()
#include <ctime>     // For time()

// Helper static method for generating random ID components
char* Ticket::generateRandomIDComponent(int length) {
    char* id = new char[length + 1];
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int charsetSize = sizeof(charset) - 1; // Exclude null terminator

    for (int i = 0; i < length; ++i) {
        id[i] = charset[rand() % charsetSize];
    }
    id[length] = '\0';
    return id;
}

// Default constructor implementation
Ticket::Ticket() : ticketID(nullptr), ticketEvent(), seatInfo(nullptr), isValid(true) {
    ticketID = new char[1];
    ticketID[0] = '\0';
    seatInfo = new char[1];
    seatInfo[0] = '\0';
    // Seed random number generator once for the program
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }
}

// Parameterized constructor implementation
Ticket::Ticket(const Event& event, const char* seatInfo)
    : ticketID(nullptr), ticketEvent(event), isValid(true) {
    // Seed random number generator once for the program
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }
    setSeatInfo(seatInfo);
    generateTicketID(); // Generate ID upon construction
}

// Copy constructor implementation (Rule of 3)
Ticket::Ticket(const Ticket& other)
    : ticketID(nullptr), ticketEvent(other.ticketEvent), isValid(other.isValid) {
    if (other.ticketID) {
        ticketID = new char[strlen(other.ticketID) + 1];
        strcpy(ticketID, other.ticketID);
    }
    if (other.seatInfo) {
        seatInfo = new char[strlen(other.seatInfo) + 1];
        strcpy(seatInfo, other.seatInfo);
    }
}

// Copy assignment operator implementation (Rule of 3)
Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) { // Avoid self-assignment
        // 1. Deallocate old memory
        delete[] ticketID;
        delete[] seatInfo;

        // 2. Deep copy new memory
        ticketID = nullptr;
        seatInfo = nullptr;

        if (other.ticketID) {
            ticketID = new char[strlen(other.ticketID) + 1];
            strcpy(ticketID, other.ticketID);
        }
        ticketEvent = other.ticketEvent; // Uses Event's assignment operator
        if (other.seatInfo) {
            seatInfo = new char[strlen(other.seatInfo) + 1];
            strcpy(seatInfo, other.seatInfo);
        }
        isValid = other.isValid;
    }
    return *this;
}

// Destructor implementation (Rule of 3)
Ticket::~Ticket() {
    delete[] ticketID;
    delete[] seatInfo;
}

// Accessor (Getter) methods
const char* Ticket::getTicketID() const {
    return ticketID;
}

const Event& Ticket::getTicketEvent() const {
    return ticketEvent;
}

const char* Ticket::getSeatInfo() const {
    return seatInfo;
}

bool Ticket::getIsValid() const {
    return isValid;
}

double Ticket::getBasePrice() const {
    return BASE_PRICE;
}

// Mutator (Setter) methods with validation
void Ticket::setTicketID(const char* newID) {
    if (newID != nullptr && strlen(newID) > 0) {
        delete[] ticketID;
        ticketID = new char[strlen(newID) + 1];
        strcpy(ticketID, newID);
    } else {
        std::cout << "Invalid ticket ID. Cannot be empty." << std::endl;
        delete[] ticketID;
        ticketID = new char[1];
        ticketID[0] = '\0';
    }
}

void Ticket::setTicketEvent(const Event& newEvent) {
    ticketEvent = newEvent; // Uses Event's copy assignment operator
}

void Ticket::setSeatInfo(const char* newSeatInfo) {
    if (newSeatInfo != nullptr && strlen(newSeatInfo) > 0) {
        delete[] seatInfo;
        seatInfo = new char[strlen(newSeatInfo) + 1];
        strcpy(seatInfo, newSeatInfo);
    } else {
        std::cout << "Invalid seat info. Cannot be empty." << std::endl;
        delete[] seatInfo;
        seatInfo = new char[1];
        seatInfo[0] = '\0';
    }
}

void Ticket::setIsValid(bool status) {
    isValid = status;
}

// Generic methods
void Ticket::generateTicketID() {
    // Generate a unique ID using a combination of random characters and time.
    // For Phase 1, without STL containers like std::set, we rely on the
    // high probability of uniqueness for a sufficiently long random string.
    // In Phase 2, a lookup structure (e.g., std::unordered_set) would be used
    // to guarantee uniqueness across all generated IDs for an event.
    char* part1 = generateRandomIDComponent(8);
    char* part2 = generateRandomIDComponent(8);

    char tempID[20]; // Sufficient buffer for "XXXXXXXX-XXXXXXXX\0"
    sprintf(tempID, "%s-%s", part1, part2);
    setTicketID(tempID);

    delete[] part1;
    delete[] part2;
}

void Ticket::validateTicket() {
    if (isValid) {
        isValid = false;
        std::cout << "Ticket ID " << (ticketID ? ticketID : "N/A") << " has been validated and marked as used." << std::endl;
    } else {
        std::cout << "Ticket ID " << (ticketID ? ticketID : "N/A") << " is already invalid or used." << std::endl;
    }
}

double Ticket::calculateTicketPrice(const char* category) const {
    double price = BASE_PRICE;
    if (category != nullptr) {
        if (strcmp(category, "VIP") == 0) {
            price *= 2.0; // Double price for VIP
        } else if (strcmp(category, "Box") == 0) {
            price *= 1.5; // 50% increase for Box
        } else if (strcmp(category, "Lawn") == 0) {
            price *= 0.75; // 25% discount for Lawn
        }
        // Add more category-based pricing as needed
    }
    return price;
}

// Operator overloads
// Stream insertion operator <<
std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "--- Ticket Details ---" << std::endl;
    os << "Ticket ID: " << (ticket.ticketID ? ticket.ticketID : "N/A") << std::endl;
    os << "Seat Info: " << (ticket.seatInfo ? ticket.seatInfo : "N/A") << std::endl;
    os << "Validity: " << (ticket.isValid ? "Valid" : "Used/Invalid") << std::endl;
    os << "Base Price (Constant): " << ticket.BASE_PRICE << std::endl;
    os << "--- Event Details for this Ticket ---" << std::endl;
    os << ticket.ticketEvent; // Use Event's stream insertion operator
    os << "\n----------------------" << std::endl;
    return os;
}

// Stream extraction operator >>
std::istream& operator>>(std::istream& is, Ticket& ticket) {
    char buffer[256]; // Temporary buffer for string inputs

    // Note: Ticket ID is generated, not read.
    // Validity is initially true.
    // Base price is constant.

    std::cout << "Enter Event details for this Ticket:\n";
    is >> ticket.ticketEvent; // Use Event's stream extraction operator

    std::cout << "Enter Seat Info (e.g., Row 5, Seat 12, VIP Zone): ";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before getline
    is.getline(buffer, sizeof(buffer));
    ticket.setSeatInfo(buffer);

    ticket.generateTicketID(); // Generate the ID after event and seat info are set
    ticket.setIsValid(true); // New tickets are valid

    return is;
}

// Relational operator == (to compare ticket IDs)
bool Ticket::operator==(const Ticket& other) const {
    if (ticketID == nullptr || other.ticketID == nullptr) {
        return false; // Cannot compare if IDs are null
    }
    return strcmp(ticketID, other.ticketID) == 0;
}
