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

class Seat {
private:
	int number;
	bool reserved = false;

public:
	//Getter and setters
	int getNumber() {
		return this->number;
	}

	void setNumber(int num) {
		if (num < 1) {
			throw std::invalid_argument("Invalid seat number");
		}
		this->number = num;
	}

	bool isReserved() {
		return reserved;
	}

	void reserve() {
		this->reserved = true;
	}

	//Constructors
	Seat() : number(1) {}

	Seat(int num) {
		this->setNumber(num);
	}

	Seat(const Seat& other) {
		this->setNumber(other.number);
		this->reserved = other.reserved;
	}

	~Seat() {}

	//Overloaded operators
	Seat& operator=(const Seat& other) {
		if (this != &other) {
			this->setNumber(other.number);
			this->reserved = other.reserved;
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Seat& seat) {
		os << std:: endl << "Seat Number: " << seat.number << ", Reserved: " << (seat.reserved ? "Yes" : "No");
		return os;
	}

	// Generic methods for processing/displaying attributes
	//void displayDetails() const {
	//	std::cout << std::endl << *this;
	//}

	void switchReserve() {
		// toggle reservation status
		this->reserved = !this->reserved;
	}
};

class Row {
private:
	int number;
	Seat* seats = nullptr;
	int numSeats = 0;

public:
	// Getters and setters
	int getNumber() {
		return this->number;
	}

	void setNumber(int num) {
		if (num < 1) {
			throw std::invalid_argument("Invalid row number");
		}
		this->number = num;
	}

	int getNumSeats() {
		return this->numSeats;
	}

	void setNumSeats(int num) {
		if (num < 1) {
			throw std::invalid_argument("Row must have at least one seat");
		}
		this->numSeats = num;
	}

	// Constructors
	Row() : number(1), numSeats(1) {
		seats = new Seat[numSeats];
	}

	Row(int number, int numSeats) {
		this->setNumber(number);
		this->setNumSeats(numSeats);
		this->seats = new Seat[this->numSeats];

		for (int i = 0; i < this->numSeats; ++i) {
			this->seats[i] = Seat(i + 1);
		}
	}

	Row(const Row& other) : number(other.number), numSeats(other.numSeats) {
		this->seats = new Seat[this->numSeats];

		for (int i = 0; i < this->numSeats; ++i) {
			this->seats[i] = other.seats[i];
		}
	}

	~Row() {
		delete[] this->seats;
	}

	//Overloaded operators
	Row& operator=(const Row& other) {
		if (this != &other) {
			delete[] this->seats;
			this->numSeats = other.numSeats;
			this->seats = new Seat[numSeats];

			for (int i = 0; i < numSeats; ++i) {
				this->seats[i] = other.seats[i];
			}
		}
		return *this;
	}

	Seat& operator[](int index) {
		if (index < 0 || index >= this->numSeats) {
			throw std::out_of_range("Invalid seat index");
		}
		return this->seats[index];
	}

	// Generic methods for processing/displaying attributes
	void displayDetails() const {
		std::cout << std::endl << "===== Row " << this->number << " =====";
		for (int i = 0; i < this->numSeats; ++i) {
			std::cout << this->seats[i];
		}
	}

	void reserveRow() {
		// reserve all seats on a row
		for (int i = 0; i < this->numSeats; ++i) {
			this->seats[i].reserve();
		}
	}
};

class Zone {
private:
	std::string name;
	Row* rows = nullptr;
	int numRows = 0;
	static int MAX_ROWS;

public:
	//Getters and setters
	std::string getName() {
		return this->name;
	}

	void setName(std::string newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::invalid_argument("Name must start with a capital letter");
		}
		this->name = newName;
	}

	int getNumRows() {
		return this->numRows;
	}

	void setNumRows(int num) {
		if (num < 1 || num > Zone::MAX_ROWS) {
			throw std::invalid_argument("Invalid number of rows");
		}
		this->numRows = num;
	}

	// Constructors
	Zone() : name("A"), numRows(1) {
		this->rows = new Row[this->numRows];
	}

	Zone(std::string name, Row* r, int numRows) {
		this->setName(name);
		this->setNumRows(numRows);
		rows = new Row[this->numRows];

		for (int i = 0; i < this->numRows; i++) {
			rows[i] = r[i];
		}
	}

	Zone(const Zone& other) : name(other.name), numRows(other.numRows) {
		rows = new Row[this->numRows];

		for (int i = 0; i < this->numRows; ++i) {
			rows[i] = other.rows[i];
		}
	}

	~Zone() {
		delete[] this->rows;
	}

	// Overloaded operators
	Zone& operator=(const Zone& other) {
		if (this != &other) {
			delete[] rows;
			this->name = other.name;
			this->numRows = other.numRows;
			this->rows = new Row[numRows];
			for (int i = 0; i < numRows; ++i) {
				this->rows[i] = other.rows[i];
			}
		}
		return *this;
	}

	// Generic methods for processing/displaying attributes
	void displayDetails() {
		std::cout << std::endl << "===== Zone " << this->getName() << " =====";
		std::cout << std::endl << "Number of Rows : " << this->getNumRows() << std::endl;
		for (int i = 0; i < this->numRows; ++i) {
			rows[i].displayDetails();
		}
		std::cout << std::endl;
	}

};

int Zone::MAX_ROWS = 20;

class Event {
private:
	std::string name;
	char date[11] = ""; //	dd/mm/yyyy
	char time[6] = ""; //	hh:mm

public:
	// Getters and setters
	std::string getName() {
		return this->name;
	}

	void setName(std::string newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::invalid_argument("Name must start with a capital letter");
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

	// Constructors
	Event(std::string name, const char* date, const char* time) {
		this->setName(name);
		this->setDate(date);
		this->setTime(time);
	}

	Event& operator=(const Event& other) {
		if (this != &other) {
			// Copy name
			this->setName(other.name);

			// Copy date
			try {
				this->setDate(other.date);
			}
			catch (const std::exception& e) {
				std::cerr << "Error setting date: " << e.what() << std::endl;
			}

			// Copy time
			try {
				this->setTime(other.time);
			}
			catch (const std::exception& e) {
				std::cerr << "Error setting time: " << e.what() << std::endl;
			}
		}
		return *this;
	}

	//
	void displayDetails() {
		std::cout << std::endl << "===== " << this->getName() << " =====";
		std::cout << std::endl << "Date: " << this->getDate();
		std::cout << std::endl << "Time: " << this->getTime();
	}
};


