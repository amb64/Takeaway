#pragma once
#include "Item.h"
#include <iomanip>
#include <sstream>

// Beverage class
class Beverage : public Item
{
public:
	Beverage(int icalories, std::string iname, double iprice, int ivolume, double iabv);
	~Beverage();
	std::string toString() override;
	bool isAlcoholic() const;

	// Get functions PLEASE CHECK IF THESE ARE ACTUALLY NEEDED!
	int getVolume();
	double getAbv();

private:
	int volume;
	double abv;
};


