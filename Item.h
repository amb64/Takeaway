#pragma once
#include <iostream>
#include <vector>
#include <string>

// Do I need: destructors, copy constructors? YES
// Do these need to be split into seperate header files? Simple fix but is it requried YES IT DOES FIX IT

// Item class, does this need a constructor considering it would never be made on its own? YES??
class Item
{
public:
	Item(int icalories, std::string iname, double iprice);
	~Item();
	std::string toString();

	// Functions to get variables PLEASE CHECK IF THESE ARE ACTUALLY NEEDED!
	int getCalories();
	std::string getName();
	double getPrice();

// Protected variables that can only be accessed by child classes
protected:
	int calories;
	std::string name;
	double price;
};
