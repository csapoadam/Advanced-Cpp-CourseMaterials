#pragma once

#include <string>
#include <vector>
#include <iostream>

enum class Regularity {
	DAILY,
	MONTHLY,
	YEARLY
};

std::string regularity_to_string(Regularity);

class Person {
	std::string name;
public:
	Person(std::string n) : name(n) {}
	std::string getName() { return name; }
};