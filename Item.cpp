#include "Item.h"
#include <iomanip>
#include <sstream>

// Constructor
Item::Item(int icalories, std::string iname, double iprice)
{
	calories = icalories;
	name = iname;
	price = iprice;
}

// Desctructor
Item::~Item()
{
	
}

double Item::getPrice() const
{
	return price;
}

std::string Item::toString()
{
	std::string output;

	// Prints out info for the individual item - used for the order / receipt

	// Creates the string and also ensures that it outputs with 2 decimal places only
	output = name + ": \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << price).str() + ", " + std::to_string(calories) + " cal ";

	// Returns the string
	return output;
}