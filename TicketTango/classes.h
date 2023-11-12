#pragma once

#include <iostream>
#include <string>

class Util {
public:
	static char* copyString(const char* source) {
		if (source == nullptr)
			return nullptr;

		char* value = new char[strlen(source) + 1];
		strcpy_s(value, strlen(source) + 1, source);

		return value;
	}
};

class Location {
	std::string name;
	int capacity = 0; // total number of seats
	int noRows = 0;
public:
	std::string getName() {
		return this->name;
	}

	void setName(std::string newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::exception("Name must start with a capital letter");
		}
		this->name = newName;
	}

	int getCapacity() {
		return this->capacity;
	}

	void setCapacity(int c) {
		if (c <= 0) {
			throw std::exception("Capacity must be strictly positive");
		}
		this->capacity = c;
	}

	int getNoRows() {
		return this->noRows;
	}

	void setNoRows(int r) {
		if (r <= 0) {
			throw std::exception("Number of rows must be strictly positive");
		}
		this->noRows = r;
	}

	void displayDetails() {
		std::cout << std::endl << "Location Name: " << this->getName();
		std::cout << std::endl << "Capacity: " << this->getCapacity();
		std::cout << std::endl << "Number of Rows: " << this->getNoRows();
	}

	Location(std::string name, int capacity, int rows) {
		this->setName(name);
		this->setCapacity(capacity);
		this->setNoRows(rows);
	}
};

class Event {
	std::string name;
	char date[11] = ""; //	dd/mm/yyyy
	char time[6] = ""; //	hh:mm
	static int NO_EVENTS;
public:
	std::string getName() {
		return this->name;
	}

	void setName(std::string newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::exception("Name must start with a capital letter");
		}
		this->name = newName;
	}

	char* getDate() {
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

	char* getTime() {
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

	static int getNoEvents() {
		return Event::NO_EVENTS;
	}

	void displayDetails() {
		std::cout << std::endl << "Event Name: " << this->getName();
		std::cout << std::endl << "Date: " << this->getDate();
		std::cout << std::endl << "Time: " << this->getTime();
	}

	Event(std::string name, const char* date, const char* time) {
		this->setName(name);
		this->setDate(date);
		this->setTime(time);
		Event::NO_EVENTS += 1;
	}
};

int Event::NO_EVENTS = 0;

class Person {
	const char* name;
	const char dateOfBirth[11]; //	dd/mm/yyyy
	char gender;
	std::string* email = nullptr;
public:
};

class Ticket {
	const char* id;
	const Event& event;
	const Location& location;
	const Person& person;
	float price = 0;
	static int NO_TICKETS;
public:
};

int Ticket::NO_TICKETS = 0;