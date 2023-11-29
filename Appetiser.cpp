#include "Appetiser.h"

// Constructor 
Appetiser::Appetiser(int icalories, std::string iname, double iprice, bool ishareable, bool itwoForOne) : Item(icalories, iname, iprice)
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
	// Call base method
	std::string output = Item::toString();

	// Adds shareable and 241 text only if their respective bools are true
	std::string shareableString = (shareable ? "(shareable)" : "");
	std::string twoForOneString = (twoForOne ? "(2-4-1)" : "");

	// Adds a new line for formatting purposes
	output = output + shareableString + twoForOneString + "\n";

	// Returns the string
	return output;
}