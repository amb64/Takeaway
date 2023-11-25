#include "Appetiser.h"

// Constructor 
Appetiser::Appetiser(int icalories, std::string iname, float iprice, bool ishareable, bool itwoForOne) : Item(icalories, iname, iprice)
{
	// First call the parent constructor, then initialise Appetiser class specific parameters
	shareable = ishareable;
	twoForOne = itwoForOne;
}

// Destructor
Appetiser::~Appetiser()
{

}

// Get functions
bool Appetiser::getShareable()
{
	return shareable;
}

bool Appetiser::getTwoForOne()
{
	return twoForOne;
}

// Returns a string of the item
std::string Appetiser::toString()
{
	// Override for the appetiser
	std::string output = Item::toString();

	std::string shareableString = (shareable ? "(shareable)" : "");
	std::string twoForOneString = (twoForOne ? "(2-4-1)" : "");

	output = output + shareableString + twoForOneString + "\n";

	return output;
}