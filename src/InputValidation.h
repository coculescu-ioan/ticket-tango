#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <iostream>
#include <limits> 

// Function declarations only (definitions in InputValidation.cpp)
int getValidIntInput(const char* promptText);
double getValidDoubleInput(const char* promptText);
void getValidStringInput(const char* promptText, char* buffer, int bufferSize);

#endif
