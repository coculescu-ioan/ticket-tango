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
	int noRows = 0;
	int noSeatsPerRow = 0;
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

	int getNoRows() {
		return this->noRows;
	}

	void setNoRows(int r) {
		if (r <= 0) {
			throw std::exception("Number of rows must be strictly positive");
		}
		this->noRows = r;
	}

	int getNoSeatsPerRow() {
		return this->noSeatsPerRow;
	}

	void setNoSeatsPerRow(int s) {
		if (s <= 0) {
			throw std::exception("Number of rows must be strictly positive");
		}
		this->noSeatsPerRow = s;
	}

	void displayDetails() {
		std::cout << std::endl << "=====================";
		std::cout << std::endl << "Location Name: " << this->getName();
		std::cout << std::endl << "Capacity: " << (this->getNoRows() * this->getNoSeatsPerRow());
	}

	Location(std::string name, int rows, int seats) {
		this->setName(name);
		this->setNoRows(rows);
		this->setNoSeatsPerRow(seats);
	}

	Location(const Location& loc) {
		this->setName(loc.name);
		this->setNoRows(loc.noRows);
		this->setNoSeatsPerRow(loc.noSeatsPerRow);
	}

	void operator=(const Location& loc) {
		if (&loc == this) {
			return;
		}
		this->setName(loc.name);
		this->setNoRows(loc.noRows);
		this->setNoSeatsPerRow(loc.noSeatsPerRow);
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
		std::cout << std::endl << "=====================";
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

class User {
	const char* name;
	char dateOfBirth[11]; //	dd/mm/yyyy
	char* email = nullptr;
public:
	const char* getName() {
		return Util::copyString(this->name);
	}

	void setName(const char* newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::exception("Name must start with a capital letter");
		}
		this->name = newName;
	}

	char* getDateOfBirth() {
		return Util::copyString(this->dateOfBirth);
	}

	void setDateOfBirth(const char* bday) {
		if (strlen(bday) != 10) {
			throw std::exception("Wrong date length");
		}
		if (bday[2] != '/' || bday[5] != '/') {
			throw std::exception("Wrong date format");
		}

		strcpy_s(this->dateOfBirth, bday);
	}

	char* getEmail() {
		char* copy = Util::copyString(this->email);
		return copy;
	}

	void setEmail(const char* newEmail) {
		this->email = Util::copyString(newEmail);
		if (strchr(this->email, '@') == NULL) {
			throw std::exception("Wrong email format");
		}
	}

	void displayDetails() {
		std::cout << std::endl << "=====================";
		std::cout << std::endl << "Name: " << this->getName();
		std::cout << std::endl << "Date of birth: " << this->getDateOfBirth();
		std::cout << std::endl << "Email: " << this->getEmail();
	}

	User(const char* name, const char* bday, const char* email) {
		this->setName(name);
		this->setDateOfBirth(bday);
		this->setEmail(email);
	}

	~User() {
		delete[] this->email;
	}
};

class Ticket {
	const char* id;
	const Event& event;
	const Location& location;
	const User& user;
	float price = 0;
	static int NO_TICKETS;
public:
};

int Ticket::NO_TICKETS = 0;