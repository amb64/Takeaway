#pragma once
#include "Item.h"

// Beverage class
class Beverage : public Item
{
public:
	Beverage(int icalories, std::string iname, float iprice, int ivolume, float iabv);
	~Beverage();
	std::string toString();
	bool isAlcoholic() const;

	// Get functions PLEASE CHECK IF THESE ARE ACTUALLY NEEDED!
	int getVolume();
	float getAbv();

private:
	int volume;
	float abv;
};


