#pragma once

#include <iostream>
#include <string>

class Location {
	std::string name;
	int capacity = 0; // total number of seats
	int noRows = 0;
public:
};

class Event {
	std::string name;
	char date[11] = ""; //	dd/mm/yyyy
	char time[6] = ""; //	hh:mm
	static int NO_EVENTS;
public:
};

int Event::NO_EVENTS = 0;

class Person {
	std::string name;
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
	static int NO_TICKETS;
public:
};

int Ticket::NO_TICKETS = 0;