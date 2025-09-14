#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <cstring> 
#include <iomanip>  // Required for std::setw

// Forward declaration for operator overloads
class Location;
std::ostream& operator<<(std::ostream& os, const Location& location);
std::istream& operator>>(std::istream& is, Location& location);

class Location {
private:
    char* name;             // Dynamically allocated char array for location name
    int numRows;            // Number of rows in the location
    int* seatsPerRow;       // Dynamically allocated int array for seats per row
    char* zones;            // Dynamically allocated char array for zones (e.g., "VIP,Lawn,Stand1")
    const int MAX_SEATS_PER_ROW = 100; // Constant field: Maximum seats allowed in a single row
    static int totalLocations; // Static field: Counts the total number of Location objects created

public:
    // Default constructor
    Location();

    // Parameterized constructor
    Location(const char* name, int numRows, const int* seatsPerRow, const char* zones);

    // Copy constructor (Rule of 3)
    Location(const Location& other);

    // Copy assignment operator (Rule of 3)
    Location& operator=(const Location& other);

    // Destructor (Rule of 3)
    ~Location();

    // Accessor (Getter) methods
    const char* getName() const;
    int getNumRows() const;
    const int* getSeatsPerRow() const;
    const char* getZones() const;
    int getMaxSeatsPerRow() const;
    static int getTotalLocations();

    // Mutator (Setter) methods with validation
    void setName(const char* newName);
    void setNumRows(int newNumRows);
    void setSeatsPerRow(const int* newSeatsPerRow, int newNumRows);
    void setZones(const char* newZones);

    // Generic methods
    int calculateTotalCapacity() const; // Calculates the total number of seats in the location
    void displayLocationDetails() const; // Displays all details of the location

    // Static method
    static void printTotalLocations(); // Prints the total number of Location objects

    // Operator overloads
    // Indexing operator [] to access seats in a specific row
    int operator[](int rowIndex) const;

    // Stream insertion operator <<
    friend std::ostream& operator<<(std::ostream& os, const Location& location);

    // Stream extraction operator >>
    friend std::istream& operator>>(std::istream& is, Location& location);
};

#endif
