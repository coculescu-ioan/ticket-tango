#include "InputValidation.h"
#include <iostream>
#include <limits>

int getValidIntInput(const char* promptText) {
    int value;
    while (true) {
        std::cout << promptText;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double getValidDoubleInput(const char* promptText) {
    double value;
    while (true) {
        std::cout << promptText;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid decimal number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void getValidStringInput(const char* promptText, char* buffer, int bufferSize) {
    while (true) {
        std::cout << promptText;
        std::cin.getline(buffer, bufferSize);
        bool isEmpty = true;
        for (int i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\r') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            std::cout << "Input cannot be empty. Please enter a value." << std::endl;
        } else if (std::cin.fail()) {
            std::cout << "Input too long. Please enter a shorter value (max " << bufferSize - 1 << " characters)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return;
        }
    }
}
