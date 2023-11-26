#include "Beverage.h"
#include <iomanip>
#include <sstream>

// Constructor
Beverage::Beverage(int icalories, std::string iname, double iprice, int ivolume, double iabv) : Item(icalories, iname, iprice)
{
	// First call the parent constructor, then initialise Beverage class specific parameters
	volume = ivolume;
	abv = iabv;
}

// Destructor
Beverage::~Beverage()
{

}

// Returns true or false based on whether the drink has abv or not
bool Beverage::isAlcoholic() const
{
	// Checks whether is alcoholic
	if (abv > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Get functions
int Beverage::getVolume()
{
	return volume;
}

double Beverage::getAbv()
{
	return abv;
}

std::string Beverage::toString()
{
	// Override for the beverage
	std::string output = Item::toString();

	output = output + "(" + std::to_string(volume) + "ml";

	if (Beverage::isAlcoholic())
	{
		//output = output + "," + std::to_string(abv) + "% abv)\n";

		// Creates the string and also ensures that it outputs with 1 decimal place only
		output = output + ", " + (std::ostringstream() << std::fixed << std::setprecision(1) << abv).str() + "% abv)\n";
	}
	else
	{
		output = output + ")\n";
	}
	
	return output;
}