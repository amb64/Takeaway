#pragma once
#include "Item.h"

// Appetiser class
class Appetiser : public Item
{
public:
	// Constructor
	Appetiser(int icalories, string iname, float iprice, bool ishareable, bool itwoForOne);
	~Appetiser();

	string toString();

	// Get functions
	bool getShareable();
	bool getTwoForOne();

private:
	bool shareable;
	bool twoForOne;
};