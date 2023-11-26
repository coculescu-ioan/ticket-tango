#pragma once
#include <iostream>
#include "seat.h"
#include "row.h"
#include "zone.h"
#include "event.h"

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
		std::cout << std::endl << "~~~~~~~ Ticket " << this->getID() << " ~~~~~~~";
		event.displayDetails();
		std::cout << zone;
		std::cout << row;
		std::cout << seat;
		std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~";
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
