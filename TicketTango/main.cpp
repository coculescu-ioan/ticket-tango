#include "menu.h"

int main() {
 
    const int numEvents = 2;
    Event events[numEvents] = {
        Event("Concert", "01/12/2023", "20:00"),
        Event("Festival", "23/12/2023", "21:00")
    };

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

    const int numZones = 2;
    Zone zones[numZones] = {
        Zone("Basic", rows1, 5, 20.0),
        Zone("VIP", rows2, 5, 40.0)
    };

    int selectedEventIndex = Menu::selectEvent(events, numEvents);
    const Event& selectedEvent = events[selectedEventIndex - 1];
    //std::cout << selectedEvent;

    int selectedZoneIndex = Menu::selectZone(zones, numZones);
    const Zone& selectedZone = zones[selectedZoneIndex - 1];
    //std::cout << selectedZone;

    int selectedRowIndex = Menu::selectRow(selectedZone);
    const Row& selectedRow = selectedZone.getRow(selectedRowIndex);
    //std::cout << selectedRow;

    int selectedSeatIndex = Menu::selectSeat(selectedRow);
    const Seat& selectedSeat = selectedRow.getSeat(selectedSeatIndex);
    //std::cout << selectedSeat;

    Ticket newTicket(selectedEvent, selectedZone, selectedRow, selectedSeat);
    newTicket.displayDetails();

    return 0;
}
