#pragma once
#include <iostream>
#include "zone.h"
#include "util.h"

class Event {
private:
    std::string name;
    char date[11] = ""; // dd/mm/yyyy
    char time[6] = ""; // hh:mm
    Zone* zones = nullptr;
    int numZones = 0;

public:
    // Getters and setters
    std::string getName() const {
        return this->name;
    }

    void setName(std::string newName) {
        if (newName[0] < 'A' || newName[0] > 'Z') {
            throw std::invalid_argument("Name must start with a capital letter");
        }
        this->name = newName;
    }

    char* getDate() const {
        return Util::copyString(this->date);
    }

    void setDate(const char* newDate) {
        if (strlen(newDate) != 10) {
            throw std::exception("Wrong date length");
        }
        if (newDate[2] != '/' || newDate[5] != '/') {
            throw std::exception("Wrong date format");
        }

        strcpy_s(this->date, newDate);
    }

    char* getTime() const {
        return Util::copyString(this->time);
    }

    void setTime(const char* newTime) {
        if (strlen(newTime) != 5) {
            throw std::exception("Wrong time length");
        }
        if (newTime[2] != ':') {
            throw std::exception("Wrong time format");
        }

        strcpy_s(this->time, newTime);
    }

    const Zone* getZones() const {
        return this->zones;
    }

    int getNumZones() const {
        return this->numZones;
    }

    void setZones(const Zone* newZones, int newNumZones) {
        // Deallocate previous zones
        delete[] this->zones;

        // Allocate and copy new zones
        this->zones = new Zone[newNumZones];
        for (int i = 0; i < newNumZones; ++i) {
            this->zones[i] = newZones[i];
        }

        this->numZones = newNumZones;
    }

    // Constructors
    Event() {
        this->setName("A");
        this->setDate("00/00/0000");
        this->setTime("00:00");
    }

    Event(std::string name, const char* date, const char* time, const Zone* zones, int numZones) {
        this->setName(name);
        this->setDate(date);
        this->setTime(time);
        this->setZones(zones, numZones);
    }

    // Destructor
    ~Event() {
        delete[] this->zones;
    }

    // Overloaded operators
    Event& operator=(const Event& other) {
        if (this != &other) {
            this->setName(other.name);

            try {
                this->setDate(other.date);
            }
            catch (const std::exception& e) {
                std::cerr << "Error setting date: " << e.what() << std::endl;
            }

            try {
                this->setTime(other.time);
            }
            catch (const std::exception& e) {
                std::cerr << "Error setting time: " << e.what() << std::endl;
            }

            this->setZones(other.zones, other.numZones);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << std::endl << "===== " << event.getName() << " =====";
        os << std::endl << "Date: " << event.getDate();
        os << std::endl << "Time: " << event.getTime();
        os << std::endl;

        //for (int i = 0; i < event.getNumZones(); ++i) {
        //    os << event.getZones()[i];
        //}

        return os;
    }

    friend std::istream& operator>>(std::istream& is, Event& event) {
        //std::cout << "Enter Event Name: ";
        is >> event.name;

        //std::cout << "Enter Event Date (dd/mm/yyyy): ";
        is >> event.date;

        //std::cout << "Enter Event Time (hh:mm): ";
        is >> event.time;

        // Input Zones
        int numZones;
        //std::cout << "Enter the number of zones: ";
        is >> numZones;

        Zone* zones = new Zone[numZones];
        for (int i = 0; i < numZones; ++i) {
            is >> zones[i];
        }

        event.setZones(zones, numZones);
        delete[] zones;

        return is;
    }

    bool operator==(const Event& other) const {
        // Check if two events happen simultaneously
        return (strcmp(this->date, other.date) == 0) &&
            (strcmp(this->time, other.time) == 0);
    }

    // Generic methods for processing/displaying attributes
    void displayDetails() {
        std::cout << std::endl << "===== " << this->getName() << " =====";
        std::cout << std::endl << "Date: " << this->getDate();
        std::cout << std::endl << "Time: " << this->getTime();
        std::cout << std::endl;

        for (int i = 0; i < this->getNumZones(); ++i) {
            std::cout << this->getZones()[i];
        }
    }
};
