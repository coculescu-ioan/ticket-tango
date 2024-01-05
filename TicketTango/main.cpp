#include "menu.h"
#include <fstream>

int main() {
    std::ifstream inputFile("input.txt", std::ios::in);

    if (!inputFile.is_open()) {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    int numEvents;

    inputFile >> numEvents;
    
    Event* events = new Event[numEvents];

    for (int i = 0; i < numEvents; ++i) {
        std::string eventName, date, time;
        inputFile >> eventName;
        inputFile >> date;
        inputFile >> time;

        int numZones;
        inputFile >> numZones;

        Zone* zones = new Zone[numZones];

        for (int j = 0; j < numZones; ++j) {
            std::string zoneName;
            float price;
            int zoneRows;
            inputFile >> zoneName;
            inputFile >> price;
            inputFile >> zoneRows;  

            Row* rows = new Row[zoneRows];

            for (int k = 0; k < zoneRows; ++k) {
                int numSeats;
                inputFile >> numSeats;
                rows[k] = Row(k + 1, numSeats);

            }

            zones[j] = Zone(zoneName, price, rows, zoneRows);

        }

        events[i] = Event(eventName, date.c_str(), time.c_str(), zones, numZones);

    }

    inputFile.close();  

    Ticket* tickets = new Ticket[10];
    int numTicketsIssued = 0;

    char answer;
    do {
        int selectedEventIndex = Menu::selectEvent(events, numEvents);
        const Event& selectedEvent = events[selectedEventIndex - 1];

        int selectedZoneIndex = Menu::selectZone(selectedEvent.getZones(), selectedEvent.getNumZones());
        const Zone& selectedZone = selectedEvent.getZones()[selectedZoneIndex - 1];

        int selectedRowIndex = Menu::selectRow(selectedZone);
        const Row& selectedRow = selectedZone.getRow(selectedRowIndex);

        int selectedSeatIndex = Menu::selectSeat(selectedRow);
        const Seat& selectedSeat = selectedRow.getSeat(selectedSeatIndex);

        Ticket newTicket(selectedEvent, selectedZone, selectedRow, selectedSeat);

        newTicket.displayDetails();
        
        // Store the new ticket in the array
        if (numTicketsIssued < 10) {
            tickets[numTicketsIssued++] = newTicket;
        }
        else {
            std::cout << "Maximum number of tickets reached!" << std::endl;
            break;
        }

        std::cout << std::endl << "Tickets issued: " << numTicketsIssued << std::endl;

        std::cout << "Purchase another ticket? (Y/N): ";
        std::cin >> answer;

    } while (answer == 'Y' || answer == 'y');

    for (int i = 0; i < numTicketsIssued; i++) {
        tickets[i].displayDetails();
    }
    
    return 0;
}
