#include "Item.h"
#include <iomanip>
#include <sstream>

// Constructor
Item::Item(int icalories, std::string iname, float iprice)
{
	calories = icalories;
	name = iname;
	price = iprice;
}

// Desctructor
Item::~Item()
{
	
}

// Get functions
int Item::getCalories()
{
	return calories;
}

std::string Item::getName()
{
	return name;
}

float Item::getPrice()
{
	return price;
}

std::string Item::toString()
{
	// Prints out info for the individual item - used for the order / receipt

	//std::string output = name + ": \u00A3" + std::to_string(price) + ", " + std::to_string(calories) + " cal ";

	// Creates the string and also ensures that it outputs with 2 decimal places only
	std::string output = name + ": \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << price).str() + ", " + std::to_string(calories) + " cal ";

	return output;
}