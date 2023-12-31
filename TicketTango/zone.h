#pragma once
#include <iostream>
#include "row.h"

class Zone {
private:
	std::string name;
	float price = 0.0;
	Row* rows = nullptr;
	int numRows = 0;
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
	Zone() : name("A"), price(0.0), numRows(1) {
		this->rows = new Row[this->numRows];
	}

	Zone(std::string name, float price, Row* r, int numRows) {
		this->setName(name);
		this->setPrice(price);
		this->setNumRows(numRows);

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

		return os;
	}

	friend std::istream& operator>>(std::istream& is, Zone& zone) {
		//std::cout << "Enter Zone Name: ";
		is >> zone.name;

		//std::cout << "Enter the price for the Zone: $";
		is >> zone.price;

		//std::cout << "Enter the number of Rows in the Zone: ";
		is >> zone.numRows;

		zone.rows = new Row[zone.numRows];

		for (int i = 0; i < zone.numRows; ++i) {
			//std::cout << "Enter details for Row " << i + 1 << ":";
			is >> zone.rows[i];
		}

		return is;
	}

	Row& operator[](int index) {
		if (index < 0 || index >= numRows) {
			throw std::out_of_range("Index out of bounds");
		}
		return rows[index];
	}

	Zone& operator+(float value) {
		// increase the price of the zone
		this->price += value;
		return *this;
	}

	bool operator!() const {
		return price == 0;
	}

	bool operator<(const Zone& other) const {
		return price < other.price;
	}

	bool operator>(const Zone& other) const {
		return price > other.price;
	}

	bool operator==(const Zone& other) const {
		return ((numRows == other.numRows) && (price == other.price));
	}

	// Generic methods for processing/displaying attributes
	void displayDetails() const {
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

	Row* getRows() const {
		return rows;
	}
};

int Zone::MAX_ROWS = 20;