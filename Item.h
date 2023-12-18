#pragma once
#include <iostream>
#include <vector>
#include <string>

class Item
{
public:
	Item(int icalories, std::string iname, double iprice);
	~Item();

	std::string virtual toString();

	double getPrice() const;

// Protected variables that can only be accessed by child classes
protected:
	int calories;
	std::string name;
	double price;
};
