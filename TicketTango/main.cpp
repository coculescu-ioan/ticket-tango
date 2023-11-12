#include "classes.h"

int main() {
	Location location("Cluj Arena", 30201, 15);
	Event event("Untold Festival", "08/08/2024", "20:30");

	location.displayDetails();
	event.displayDetails();
}