#pragma once
#include <iostream>
#include "seat.h"

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
		//for (int i = 0; i < row.numSeats; ++i) {
		//	os << row.seats[i];
		//}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Row& row) {
		std::cout << "Enter Row Number: ";
		is >> row.number;

		std::cout << "Enter the number of seats in the row: ";
		is >> row.numSeats;

		row.seats = new Seat[row.numSeats];

		for (int i = 0; i < row.numSeats; ++i) {
			std::cout << "Enter details for Seat " << i + 1 << ":";
			is >> row.seats[i];
		}

		return is;
	}

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