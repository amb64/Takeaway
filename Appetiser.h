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

	// Get function
	bool getTwoForOne() const;

private:
	bool shareable;
	bool twoForOne;
};