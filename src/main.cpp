#include <iostream> 
#include <vector>
#include <cstring>
#include "Location.h"
#include "Event.h"
#include "Ticket.h"
#include "InputValidation.h"

// Function prototypes
void displayMainMenu();
void manageLocations(Location& currentLoc);
void manageEvents(Event& currentEvent, Location& currentLoc);
void manageTickets(Ticket& currentTicket, Event& currentEvent);
void displayAllObjects(const Location& loc, const Event& event, const Ticket& ticket);

int main() {
    // Initialize objects for demonstration.
    // In a real application, these might be loaded from files or managed in collections.
    Location myLocation;
    Event myEvent;
    Ticket myTicket;

    int choice;
    do {
        displayMainMenu();
        choice = getValidIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                manageLocations(myLocation);
                break;
            case 2:
                manageEvents(myEvent, myLocation);
                break;
            case 3:
                manageTickets(myTicket, myEvent);
                break;
            case 4:
                displayAllObjects(myLocation, myEvent, myTicket);
                break;
            case 0:
                std::cout << "Exiting application. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::cout << "\n"; // Add a newline for better readability between menu loops
    } while (choice != 0);

    return 0;
}

// Displays the main menu options to the user.
void displayMainMenu() {
    std::cout << "--- Ticketing Application Main Menu ---" << std::endl;
    std::cout << "1. Manage Location Characteristics" << std::endl;
    std::cout << "2. Manage Event Characteristics" << std::endl;
    std::cout << "3. Generate/Validate Tickets" << std::endl;
    std::cout << "4. Display All Current Object Details" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

// Manages location-related functionalities.
void manageLocations(Location& currentLoc) {
    int locChoice;
    do {
        std::cout << "\n--- Manage Location Menu ---" << std::endl;
        std::cout << "1. Enter New Location Details" << std::endl;
        std::cout << "2. Display Current Location Details" << std::endl;
        std::cout << "3. Calculate Total Capacity" << std::endl;
        std::cout << "4. Check Seats in a Specific Row (using [])" << std::endl;
        std::cout << "5. Print Total Number of Locations (Static Method)" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "----------------------------" << std::endl;
        locChoice = getValidIntInput("Enter your choice: ");

        switch (locChoice) {
            case 1: {
                std::cout << "Entering new location details:\n";
                std::cin >> currentLoc; // Use overloaded >> operator
                std::cout << "Location details updated successfully.\n";
                break;
            }
            case 2:
                currentLoc.displayLocationDetails(); // Use generic method
                std::cout << currentLoc << std::endl; // Use overloaded << operator
                break;
            case 3:
                std::cout << "Total Capacity of Location: " << currentLoc.calculateTotalCapacity() << std::endl;
                break;
            case 4: {
                if (currentLoc.getNumRows() > 0) {
                    int rowIndex = getValidIntInput("Enter row index to check (0-based): ");
                    int seats = currentLoc[rowIndex]; // Use overloaded [] operator
                    if (seats != -1) { // -1 indicates error from operator[]
                        std::cout << "Seats in Row " << rowIndex << ": " << seats << std::endl;
                    }
                } else {
                    std::cout << "No rows defined for this location yet." << std::endl;
                }
                break;
            }
            case 5:
                Location::printTotalLocations(); // Call static method
                break;
            case 0:
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (locChoice != 0);
}

// Manages event-related functionalities.
void manageEvents(Event& currentEvent, Location& currentLoc) {
    int eventChoice;
    do {
        std::cout << "\n--- Manage Event Menu ---" << std::endl;
        std::cout << "1. Enter New Event Details" << std::endl;
        std::cout << "2. Display Current Event Details" << std::endl;
        std::cout << "3. Check if Event is Upcoming" << std::endl;
        std::cout << "4. Check Event Validity (using ! operator)" << std::endl;
        std::cout << "5. Print Total Number of Events (Static Method)" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "-------------------------" << std::endl;
        eventChoice = getValidIntInput("Enter your choice: ");

        switch (eventChoice) {
            case 1: {
                std::cout << "Entering new event details:\n";
                // Before entering event, ensure location is set if it's new
                if (currentLoc.getName() == nullptr || strlen(currentLoc.getName()) == 0) {
                    std::cout << "Please define a location first for the event.\n";
                    manageLocations(currentLoc); // Accepts const Location&
                }
                std::cin >> currentEvent; // Use overloaded >> operator
                // Ensure the event's location is correctly set to the currentLoc object
                currentEvent.setEventLocation(currentLoc);
                std::cout << "Event details updated successfully.\n";
                break;
            }
            case 2:
                currentEvent.displayEventDetails(); // Use generic method
                std::cout << currentEvent << std::endl; // Use overloaded << operator
                break;
            case 3:
                if (currentEvent.isEventUpcoming()) { // Use generic method
                    std::cout << "The event is upcoming." << std::endl;
                } else {
                    std::cout << "The event is not upcoming or has invalid date/time." << std::endl;
                }
                break;
            case 4:
                if (!currentEvent) { // Use overloaded ! operator
                    std::cout << "Event is considered invalid or cancelled." << std::endl;
                } else {
                    std::cout << "Event is valid." << std::endl;
                }
                break;
            case 5:
                Event::printEventCount(); // Call static method
                break;
            case 0:
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (eventChoice != 0);
}

// Manages ticket-related functionalities.
void manageTickets(Ticket& currentTicket, Event& currentEvent) {
    int ticketChoice;
    do {
        std::cout << "\n--- Manage Tickets Menu ---" << std::endl;
        std::cout << "1. Generate New Ticket" << std::endl;
        std::cout << "2. Display Current Ticket Details" << std::endl;
        std::cout << "3. Validate Ticket" << std::endl;
        std::cout << "4. Calculate Ticket Price" << std::endl;
        std::cout << "5. Compare Tickets (using == operator)" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "---------------------------" << std::endl;
        ticketChoice = getValidIntInput("Enter your choice: ");

        switch (ticketChoice) {
            case 1: {
                std::cout << "Generating new ticket:\n";
                // Ensure event is set for the ticket
                if (currentEvent.getEventName() == nullptr || strlen(currentEvent.getEventName()) == 0) {
                    std::cout << "Please define an event first for the ticket.\n";
                    // Fix: Instead of passing a const Location, pass the application's main Location object.
                    // Use a temporary Location object if needed, or restructure to avoid extern
                    Location tempLoc;
                    manageEvents(currentEvent, tempLoc); // User will be prompted to enter location details
                }
                std::cin >> currentTicket; // Use overloaded >> operator
                currentTicket.setTicketEvent(currentEvent); // Ensure ticket is linked to current event
                std::cout << "Ticket generated successfully with ID: " << currentTicket.getTicketID() << std::endl;
                break;
            }
            case 2:
                std::cout << currentTicket << std::endl; // Use overloaded << operator
                break;
            case 3:
                currentTicket.validateTicket(); // Use generic method
                break;
            case 4: {
                char categoryBuffer[50];
                getValidStringInput("Enter ticket category (e.g., VIP, Normal, Box, Lawn): ", categoryBuffer, sizeof(categoryBuffer));
                double price = currentTicket.calculateTicketPrice(categoryBuffer); // Use generic method
                std::cout << "Calculated price for " << categoryBuffer << " ticket: " << price << std::endl;
                break;
            }
            case 5: {
                std::cout << "To compare, you need another ticket's ID.\n";
                char compareIDBuffer[20];
                getValidStringInput("Enter Ticket ID to compare with: ", compareIDBuffer, sizeof(compareIDBuffer));
                Ticket tempTicket; // Create a temporary ticket for comparison
                tempTicket.setTicketID(compareIDBuffer);

                if (currentTicket == tempTicket) { // Use overloaded == operator
                    std::cout << "The current ticket ID matches the entered ID." << std::endl;
                } else {
                    std::cout << "The current ticket ID does NOT match the entered ID." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (ticketChoice != 0);
}

// Displays details of all currently managed objects.
void displayAllObjects(const Location& loc, const Event& event, const Ticket& ticket) {
    std::cout << "\n--- Current Application State ---" << std::endl;
    std::cout << "\n--- Location Object ---" << std::endl;
    std::cout << loc << std::endl;
    Location::printTotalLocations(); // Static method call

    std::cout << "\n--- Event Object ---" << std::endl;
    std::cout << event << std::endl;
    Event::printEventCount(); // Static method call

    std::cout << "\n--- Ticket Object ---" << std::endl;
    std::cout << ticket << std::endl;
    std::cout << "---------------------------------" << std::endl;
}
