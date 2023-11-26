#pragma once
#include <iostream>
#include "ticket.h"

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