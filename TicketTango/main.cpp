#include "menu.h"

int main() {
 
    const int numEvents = 2;
    Event events[numEvents] = {
        Event("Concert", "01/12/2023", "20:00"),
        Event("Festival", "23/12/2023", "21:00")
    };

    //if (events[0] == events[1]) {
    //    std::cout << "Events have the same date and time." << std::endl;
    //}
    //else {
    //    std::cout << "Events have different date and time." << std::endl;
    //}

    Row rows1[] = {
        Row(1, 10),
        Row(2, 10),
        Row(3, 10),
        Row(4, 10),
        Row(5, 10)
    };

    Row rows2[] = {
        Row(1, 7),
        Row(2, 8),
        Row(3, 8),
        Row(4, 9),
        Row(5, 5)
    };

    //Zone zona("Peluza Nord", rows1, 5, 35);
    //std::cout << std::endl << zona + 5;

    const int numZones = 2;
    Zone zones[numZones] = {
        Zone("Basic", rows1, 5, 20.0),
        Zone("VIP", rows2, 5, 40.0)
    };

    //std::cout << std::endl << !zones[0];
    //std::cout << std::endl << (zona == zones[1] ?
    //    "Same number of rows and price" :
    //    "Different number of rows and price");

    char answer;
    do {
        int selectedEventIndex = Menu::selectEvent(events, numEvents);
        const Event& selectedEvent = events[selectedEventIndex - 1];

        int selectedZoneIndex = Menu::selectZone(zones, numZones);
        const Zone& selectedZone = zones[selectedZoneIndex - 1];

        int selectedRowIndex = Menu::selectRow(selectedZone);
        const Row& selectedRow = selectedZone.getRow(selectedRowIndex);

        int selectedSeatIndex = Menu::selectSeat(selectedRow);
        const Seat& selectedSeat = selectedRow.getSeat(selectedSeatIndex);

        Ticket newTicket(selectedEvent, selectedZone, selectedRow, selectedSeat);
        newTicket.displayDetails();

        std::cout << std::endl << "Tickets issued: " << Ticket::getNoTickets() << std::endl;

        std::cout << "Purchase another ticket? (Y/N): ";
        std::cin >> answer;

    } while (answer == 'Y' || answer == 'y');

    return 0;
}
