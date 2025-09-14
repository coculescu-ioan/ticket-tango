#include "Location.h"
#include "InputValidation.h"
#include <iostream>
#include <cstring>   
#include <limits>    // For std::numeric_limits
#include <iomanip>   // For std::setw

// Initialize static member
int Location::totalLocations = 0;

// Default constructor implementation
Location::Location() : name(nullptr), numRows(0), seatsPerRow(nullptr), zones(nullptr) {
    // Allocate default values or keep null/zero
    name = new char[1];
    name[0] = '\0';
    zones = new char[1];
    zones[0] = '\0';
    totalLocations++;
}

// Parameterized constructor implementation
Location::Location(const char* name, int numRows, const int* seatsPerRow, const char* zones)
    : name(nullptr), numRows(0), seatsPerRow(nullptr), zones(nullptr) {
    totalLocations++;
    setName(name);
    setNumRows(numRows); // This will also handle seatsPerRow allocation
    setSeatsPerRow(seatsPerRow, numRows);
    setZones(zones);
}

// Copy constructor implementation (Rule of 3)
Location::Location(const Location& other)
    : name(nullptr), numRows(0), seatsPerRow(nullptr), zones(nullptr) {
    totalLocations++;
    // Deep copy for dynamically allocated members
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    numRows = other.numRows;
    if (other.seatsPerRow && other.numRows > 0) {
        seatsPerRow = new int[other.numRows];
        for (int i = 0; i < other.numRows; ++i) {
            seatsPerRow[i] = other.seatsPerRow[i];
        }
    }
    if (other.zones) {
        zones = new char[strlen(other.zones) + 1];
        strcpy(zones, other.zones);
    }
}

// Copy assignment operator implementation (Rule of 3)
Location& Location::operator=(const Location& other) {
    if (this != &other) { // Avoid self-assignment
        // 1. Deallocate old memory
        delete[] name;
        delete[] seatsPerRow;
        delete[] zones;

        // 2. Deep copy new memory
        name = nullptr;
        seatsPerRow = nullptr;
        zones = nullptr;

        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        numRows = other.numRows;
        if (other.seatsPerRow && other.numRows > 0) {
            seatsPerRow = new int[other.numRows];
            for (int i = 0; i < other.numRows; ++i) {
                seatsPerRow[i] = other.seatsPerRow[i];
            }
        }
        if (other.zones) {
            zones = new char[strlen(other.zones) + 1];
            strcpy(zones, other.zones);
        }
    }
    return *this;
}

// Destructor implementation (Rule of 3)
Location::~Location() {
    delete[] name;
    delete[] seatsPerRow;
    delete[] zones;
    totalLocations--;
}

// Accessor (Getter) methods
const char* Location::getName() const {
    return name;
}

int Location::getNumRows() const {
    return numRows;
}

const int* Location::getSeatsPerRow() const {
    return seatsPerRow;
}

const char* Location::getZones() const {
    return zones;
}

int Location::getMaxSeatsPerRow() const {
    return MAX_SEATS_PER_ROW;
}

int Location::getTotalLocations() {
    return totalLocations;
}

// Mutator (Setter) methods with validation
void Location::setName(const char* newName) {
    if (newName != nullptr && strlen(newName) > 0) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    } else {
        std::cout << "Invalid name provided. Name cannot be empty." << std::endl;
        // Optionally, set to a default empty string or throw an error
        delete[] name;
        name = new char[1];
        name[0] = '\0';
    }
}

void Location::setNumRows(int newNumRows) {
    if (newNumRows > 0) {
        // If numRows changes, seatsPerRow needs to be reallocated
        if (numRows != newNumRows) {
            delete[] seatsPerRow;
            seatsPerRow = new int[newNumRows];
            // Initialize new seatsPerRow to 0 or a default value
            for (int i = 0; i < newNumRows; ++i) {
                seatsPerRow[i] = 0; // Default to 0 seats
            }
        }
        numRows = newNumRows;
    } else {
        std::cout << "Invalid number of rows. Must be greater than 0." << std::endl;
        delete[] seatsPerRow;
        seatsPerRow = nullptr;
        numRows = 0;
    }
}

void Location::setSeatsPerRow(const int* newSeatsPerRow, int newNumRows) {
    if (newSeatsPerRow != nullptr && newNumRows > 0 && newNumRows == numRows) {
        bool isValid = true;
        for (int i = 0; i < newNumRows; ++i) {
            if (newSeatsPerRow[i] <= 0 || newSeatsPerRow[i] > MAX_SEATS_PER_ROW) {
                isValid = false;
                std::cout << "Invalid number of seats for row " << i + 1
                          << ". Must be between 1 and " << MAX_SEATS_PER_ROW << "." << std::endl;
                break;
            }
        }
        if (isValid) {
            // Ensure seatsPerRow is already allocated with correct size by setNumRows
            if (seatsPerRow == nullptr || numRows != newNumRows) {
                 // This case should ideally be handled by calling setNumRows first
                 // For robustness, reallocate if mismatch
                delete[] seatsPerRow;
                seatsPerRow = new int[newNumRows];
                numRows = newNumRows;
            }
            for (int i = 0; i < newNumRows; ++i) {
                seatsPerRow[i] = newSeatsPerRow[i];
            }
        } else {
            // Reset seatsPerRow if invalid input
            for (int i = 0; i < numRows; ++i) {
                seatsPerRow[i] = 0;
            }
        }
    } else {
        std::cout << "Invalid seats per row data or number of rows mismatch." << std::endl;
        // Reset seatsPerRow to 0 if invalid
        if (seatsPerRow) {
            for (int i = 0; i < numRows; ++i) {
                seatsPerRow[i] = 0;
            }
        }
    }
}

void Location::setZones(const char* newZones) {
    if (newZones != nullptr && strlen(newZones) > 0) {
        delete[] zones;
        zones = new char[strlen(newZones) + 1];
        strcpy(zones, newZones);
    } else {
        std::cout << "Invalid zones provided. Zones cannot be empty." << std::endl;
        delete[] zones;
        zones = new char[1];
        zones[0] = '\0';
    }
}

// Generic methods
int Location::calculateTotalCapacity() const {
    int total = 0;
    for (int i = 0; i < numRows; ++i) {
        total += seatsPerRow[i];
    }
    return total;
}

void Location::displayLocationDetails() const {
    std::cout << "\n--- Location Details ---" << std::endl;
    std::cout << "Name: " << (name ? name : "N/A") << std::endl;
    std::cout << "Number of Rows: " << numRows << std::endl;
    std::cout << "Seats per Row: ";
    if (seatsPerRow && numRows > 0) {
        for (int i = 0; i < numRows; ++i) {
            std::cout << "Row " << i + 1 << ": " << seatsPerRow[i] << " | ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "N/A" << std::endl;
    }
    std::cout << "Zones: " << (zones ? zones : "N/A") << std::endl;
    std::cout << "Max Seats per Row (Constant): " << MAX_SEATS_PER_ROW << std::endl;
    std::cout << "Total Capacity: " << calculateTotalCapacity() << std::endl;
    std::cout << "------------------------" << std::endl;
}

// Static method
void Location::printTotalLocations() {
    std::cout << "Total number of Location objects created: " << totalLocations << std::endl;
}

// Operator overloads
// Indexing operator [] to access seats in a specific row
int Location::operator[](int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < numRows && seatsPerRow != nullptr) {
        return seatsPerRow[rowIndex];
    }
    std::cout << "Error: Invalid row index for Location." << std::endl;
    return -1; // Indicate error
}

// Stream insertion operator <<
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << "Location Name: " << (location.name ? location.name : "N/A") << std::endl;
    os << "Number of Rows: " << location.numRows << std::endl;
    os << "Seats per Row: ";
    if (location.seatsPerRow && location.numRows > 0) {
        for (int i = 0; i < location.numRows; ++i) {
            os << location.seatsPerRow[i] << (i == location.numRows - 1 ? "" : ", ");
        }
        os << std::endl;
    } else {
        os << "N/A" << std::endl;
    }
    os << "Zones: " << (location.zones ? location.zones : "N/A");
    return os;
}

// Stream extraction operator >>
std::istream& operator>>(std::istream& is, Location& location) {
    char buffer[256]; // Temporary buffer for string inputs

    std::cout << "Enter Location Name: ";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before getline
    is.getline(buffer, sizeof(buffer));
    location.setName(buffer);

    location.numRows = getValidIntInput("Enter Number of Rows: ");
    location.setNumRows(location.numRows); // Reallocate seatsPerRow based on new numRows

    if (location.numRows > 0) {
        int* tempSeatsPerRow = new int[location.numRows];
        for (int i = 0; i < location.numRows; ++i) {
            char prompt[50];
            sprintf(prompt, "Enter seats for Row %d (max %d): ", i + 1, location.MAX_SEATS_PER_ROW);
            tempSeatsPerRow[i] = getValidIntInput(prompt);
        }
        location.setSeatsPerRow(tempSeatsPerRow, location.numRows);
        delete[] tempSeatsPerRow; // Clean up temporary array
    }

    std::cout << "Enter Zones (comma-separated, e.g., VIP,Lawn,Stand1): ";
    // No need to ignore here if previous input was getline and handled by InputValidation
    is.getline(buffer, sizeof(buffer));
    location.setZones(buffer);

    return is;
}
