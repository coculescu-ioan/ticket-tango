#pragma once
#include <iostream>

class Util {
public:
	static char* copyString(const char* source) {
		if (source == nullptr)
			return nullptr;

		char* value = new char[strlen(source) + 1];
		strcpy_s(value, strlen(source) + 1, source);

		return value;
	}
};