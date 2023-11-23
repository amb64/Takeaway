#pragma once
#include "Item.h"

// Beverage class
class Beverage : public Item
{
public:
	Beverage();
	~Beverage();
	string toString();
	void isAlcoholic();

	// Get functions
	int getVolume();
	float getAbv();

private:
	int volume;
	float abv;
};

string Beverage::toString()
{
	// Overload for the beverage
	// Calls the parents method and then add to that strng with beverage specific stuff
	return "";
}
