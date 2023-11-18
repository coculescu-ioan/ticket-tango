#include "classes.h"

int main() {
	Location location("Arena", 100, 80);
	Event event("Festival", "08/08/2024", "20:30");
	User user("John Doe", "09/11/2001", "johndoe@gmail.com");

	location.displayDetails();
	event.displayDetails();
	user.displayDetails();

	Location anotherLocation("A", 1, 1);

	anotherLocation = location;
	anotherLocation.displayDetails();
}