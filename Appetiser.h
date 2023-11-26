#pragma once
#include "Item.h"

// Appetiser class
class Appetiser : public Item
{
public:
	// Constructor
	Appetiser(int icalories, std::string iname, double iprice, bool ishareable, bool itwoForOne);
	~Appetiser();

	std::string toString() override;

	// Get functions PLEASE CHECK IF THESE ARE ACTUALLY NEEDED!
	bool getShareable();
	bool getTwoForOne();

private:
	bool shareable;
	bool twoForOne;
};