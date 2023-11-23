#pragma once
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Do I need: destructors, copy constructors? YES
// Do these need to be split into seperate header files? Simple fix but is it requried YES IT DOES FIX IT

// Item class, does this need a constructor considering it would never be made on its own? YES??
class Item
{
public:
	Item(int icalories, string iname, float iprice);
	~Item();
	string toString();

	// Functions to get variables
	int getCalories();
	string getName();
	float getPrice();

// Protected variables that can only be accessed by child classes
protected:
	int calories;
	string name;
	float price;
};
