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

	Seat& operator!() {
		// make a seat available 
		this->reserved = false;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Seat& seat) {
		os << std:: endl << "Seat Number: " << seat.number << ", Reserved: " << (seat.reserved ? "Yes" : "No");
		return os;
	}

	//friend std::istream& operator>>(std::istream& is, Seat& seat) {
	//	std::cout << "Enter Seat Number: ";
	//	is >> seat.number;

	//	int reservedInput;
	//	std::cout << "Is the seat reserved? (1 for Yes, 0 for No): ";
	//	is >> reservedInput;
	//	seat.reserved = (reservedInput == 1);

	//	return is;
	//}

	//Generic methods for processing/displaying attributes
	void displayDetails() const {
		std::cout << std::endl << *this;
	}
};

class Row {
private:
	int number;
	Seat* seats = nullptr;
	int numSeats = 0;

public:
	// Getters and setters
	int getNumber() const {
		return this->number;
	}

	void setNumber(int num) {
		if (num < 1) {
			throw std::invalid_argument("Invalid row number");
		}
		this->number = num;
	}

	int getNumSeats() const {
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
			this->number = other.number;
			this->numSeats = other.numSeats;
			this->seats = new Seat[this->numSeats];

			for (int i = 0; i < this->numSeats; ++i) {
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

	friend std::ostream& operator<<(std::ostream& os, const Row& row) {
		os << std::endl << "===== Row " << row.number << " =====";
		for (int i = 0; i < row.numSeats; ++i) {
			os << row.seats[i];
		}
		return os;
	}

	//friend std::istream& operator>>(std::istream& is, Row& row) {
	//	std::cout << "Enter Row Number: ";
	//	is >> row.number;

	//	std::cout << "Enter the number of seats in the row: ";
	//	is >> row.numSeats;

	//	row.seats = new Seat[row.numSeats];

	//	for (int i = 0; i < row.numSeats; ++i) {
	//		std::cout << "Enter details for Seat " << i + 1 << ":";
	//		is >> row.seats[i];
	//	}

	//	return is;
	//}

	// Generic methods for processing/displaying attributes
	void displayDetails() const {
		std::cout << std::endl << "===== Row " << this->number << " =====";
		for (int i = 0; i < this->numSeats; ++i) {
			std::cout << this->seats[i];
		}
		std::cout << std::endl;
	}

	void reserveRow() {
		// reserve all seats on a row
		for (int i = 0; i < this->numSeats; ++i) {
			this->seats[i].reserve();
		}
	}

	Seat getSeat(int seatNumber) const {
		for (int i = 0; i < numSeats; ++i) {
			if (seats[i].getNumber() == seatNumber) {
				return seats[i];
			}
		}

		throw std::runtime_error("Seat not found");
	}
};

class Zone {
private:
	std::string name;
	Row* rows = nullptr;
	int numRows = 0;
	float price = 0.0; // Added price attribute
	static int MAX_ROWS;

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

	int getNumRows() const {
		return this->numRows;
	}

	void setNumRows(int num) {
		if (num < 1 || num > Zone::MAX_ROWS) {
			throw std::invalid_argument("Invalid number of rows");
		}
		this->numRows = num;
	}

	float getPrice() const {
		return this->price;
	}

	void setPrice(float newPrice) {
		if (newPrice < 0) {
			throw std::invalid_argument("Invalid price");
		}
		this->price = newPrice;
	}

	// Constructors
	Zone() : name("A"), numRows(1), price(0.0) {
		this->rows = new Row[this->numRows];
	}

	Zone(std::string name, Row* r, int numRows, float price) {
		this->setName(name);
		this->setNumRows(numRows);
		this->setPrice(price);
		rows = new Row[this->numRows];

		for (int i = 0; i < this->numRows; i++) {
			rows[i] = r[i];
		}
	}

	Zone(const Zone& other) : name(other.name), numRows(other.numRows), price(other.price) {
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
			delete[] this->rows;

			this->name = other.name;
			this->numRows = other.numRows;
			this->price = other.price;
			this->rows = new Row[this->numRows];

			for (int i = 0; i < this->numRows; ++i) {
				this->rows[i] = other.rows[i];
			}
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Zone& zone) {
		os << std::endl << "===== Zone " << zone.getName() << " =====";
		os << std::endl << "Price: $" << zone.getPrice();
		os << std::endl << "Capacity: " << zone.capacity() << std::endl;

		//for (int i = 0; i < zone.numRows; ++i) {
		//	os << zone.rows[i];
		//}
		return os;
	}

	//friend std::istream& operator>>(std::istream& is, Zone& zone) {
	//	std::cout << "Enter Zone Name: ";
	//	is >> zone.name;

	//	std::cout << "Enter the number of Rows in the Zone: ";
	//	is >> zone.numRows;

	//	std::cout << "Enter the price for the Zone: $";
	//	is >> zone.price;

	//	zone.rows = new Row[zone.numRows];

	//	for (int i = 0; i < zone.numRows; ++i) {
	//		std::cout << "Enter details for Row " << i + 1 << ":";
	//		is >> zone.rows[i];
	//	}

	//	return is;
	//}

	// Generic methods for processing/displaying attributes
	void displayDetails() const{
		std::cout << std::endl << "===== Zone " << this->getName() << " =====";
		std::cout << std::endl << "Price: $" << this->getPrice();
		std::cout << std::endl << "Capacity : " << this->capacity() << std::endl;
		for (int i = 0; i < this->numRows; ++i) {
			rows[i].displayDetails();
		}
		std::cout << std::endl;
	}

	int capacity() const {
		int totalSeats = 0;

		for (int i = 0; i < this->numRows; ++i) {
			totalSeats += rows[i].getNumSeats();
		}

		return totalSeats;
	}

	Row getRow(int rowNumber) const {
		for (int i = 0; i < numRows; ++i) {
			if (rows[i].getNumber() == rowNumber) {
				return rows[i];
			}
		}

		throw std::runtime_error("Row not found");
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
	std::string getName() const{
		return this->name;
	}

	void setName(std::string newName) {
		if (newName[0] < 'A' || newName[0] > 'Z') {
			throw std::invalid_argument("Name must start with a capital letter");
		}
		this->name = newName;
	}

	char* getDate() const{
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

	char* getTime() const{
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
	Event() {
		this->setName("A");
		this->setDate("00/00/0000");
		this->setTime("00:00");
	}

	Event(std::string name, const char* date, const char* time) {
		this->setName(name);
		this->setDate(date);
		this->setTime(time);
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
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Event& event) {
		os << std::endl << "===== " << event.getName() << " =====";
		os << std::endl << "Date: " << event.getDate();
		os << std::endl << "Time: " << event.getTime();
		os << std::endl;
		return os;
	}

	//friend std::istream& operator>>(std::istream& is, Event& event) {
	//	std::cout << "Enter Event Name: ";
	//	is >> event.name;

	//	std::cout << "Enter Event Date (dd/mm/yyyy): ";
	//	is >> event.date;

	//	std::cout << "Enter Event Time (hh:mm): ";
	//	is >> event.time;

	//	return is;
	//}

    // Generic methods for processing/displaying attributes
	void displayDetails() {
		std::cout << std::endl << "===== " << this->getName() << " =====";
		std::cout << std::endl << "Date: " << this->getDate();
		std::cout << std::endl << "Time: " << this->getTime();
		std::cout << std::endl;
	}
};

class Ticket {
private:
	const char* id;
	Event event;
	Zone zone;
	Row row;
	Seat seat;
	static int NO_TICKETS;

public:
	// Getters and setters
	const char* getID() {
		return id;
	}

	// Constructors
	Ticket(const Event& e, const Zone& z, const Row& r, const Seat& s) {
		this->event = e;
		this->zone = z;
		this->row = r;
		this->seat = s;
		this->seat.reserve();
		this->generateTicketID();
		Ticket::NO_TICKETS++;
	}

	~Ticket() {
		delete[] this->id;
		Ticket::NO_TICKETS--;
	}

	// Generic methods for processing / displaying attributes
	void displayDetails() {
		std::cout << std::endl << "===== Ticket " << this->getID() << " =====";
		event.displayDetails();
		std::cout << std::endl << zone;
		std::cout << std::endl << row;
		std::cout << std::endl << seat;
	}

private:
	void generateTicketID() {
		// For simplicity, a basic implementation using a counter is provided here.
		char* generatedID = new char[10];

		// format the ID 
		sprintf_s(generatedID, sizeof(generatedID), "T%d", NO_TICKETS);

		this->id = Util::copyString(generatedID);
	}
};

int Ticket::NO_TICKETS = 0;

class Menu {
public:
	static int selectEvent(const Event events[], int size) {
		std::cout << "Select an Event:" << std::endl;
		for (int i = 0; i < size; ++i) {
			std::cout << i + 1 << ". " << events[i] << std::endl;
		}

		int choice;
		std::cout << "Enter the number of the selected event: ";
		std::cin >> choice;
		return choice;
	}

	static int selectZone(const Zone zones[], int size) {
		std::cout << "Select a Zone:" << std::endl;
		for (int i = 0; i < size; ++i) {
			std::cout << i + 1 << ". " << zones[i] << std::endl;
		}

		int choice;
		std::cout << "Enter the number of the selected zone: ";
		std::cin >> choice;
		return choice;
	}

	static int selectRow(const Zone& zone) {
		std::cout << "Select a Row:" << std::endl;

		zone.displayDetails();

		int choice;
		std::cout << "Enter the number of the selected row: ";
		std::cin >> choice;
		return choice;
	}

	static int selectSeat(const Row& row) {
		std::cout << "Select a Seat:" << std::endl;

		row.displayDetails();

		int choice;
		std::cout << "Enter the number of the selected seat: ";
		std::cin >> choice;
		return choice;
	}
};

