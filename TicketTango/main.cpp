#include "classes.h"

int main() {
    Seat seat1(1);
    Seat seat2(2);

    std::cout << seat1;
    std::cout << seat2;

    seat1.reserve();

    //seat1.displayDetails();
    //seat2.displayDetails();

    std::cout << seat1;
    std::cout << seat2;

    seat2.switchReserve();

    std::cout << seat1;
    std::cout << seat2;

    Row row1(1, 5);
    Row row2(2, 6);

    row1.displayDetails();
    row2.displayDetails();

    row1.reserveRow();

    row1.displayDetails();

    row2 = row1;

    row2.displayDetails();

    std::cout << row1[3]; //Displays seat number 4 (index from 0 to n-1)

    Row a(1, 3);
    Row b(2, 4);
    Row c(3, 5);
    Row d(4, 6);

    Row r1[] = { a, b };
    Row r2[] = { c, d };

    //rows[0].displayDetails();
    //rows[1].displayDetails();

    Zone zone1("Parter", r1, 2);
    Zone zone2("Balcon", r2, 2);

    zone1.displayDetails();
    zone2.displayDetails();

    Event event1("Concert", "03/12/2023", "21:30");

    event1.displayDetails();
}
