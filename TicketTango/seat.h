#pragma once
#include <iostream>

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
		os << std::endl << "Seat Number: " << seat.number << ", Reserved: " << (seat.reserved ? "Yes" : "No");
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Seat& seat) {
		std::cout << "Enter Seat Number: ";
		is >> seat.number;

		int reservedInput;
		std::cout << "Is the seat reserved? (1 for Yes, 0 for No): ";
		is >> reservedInput;
		seat.reserved = (reservedInput == 1);

		return is;
	}

	//Generic methods for processing/displaying attributes
	void displayDetails() const {
		std::cout << std::endl << *this;
	}
};