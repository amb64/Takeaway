#include "Appetiser.h"

// Constructor 
Appetiser::Appetiser(int icalories, string iname, float iprice, bool ishareable, bool itwoForOne)
{
	// To fix the error: call the default constructor here and then initialise appetiser specific variables afterwards
	calories = icalories;
	name = iname;
	price = iprice;
	shareable = ishareable;
	twoForOne = itwoForOne;
}

// Destructor
Appetiser::~Appetiser()
{

}

bool Appetiser::getShareable()
{
	return shareable;
}

bool Appetiser::getTwoForOne()
{
	return twoForOne;
}

string Appetiser::toString()
{
	// Overload for the appetiser
	// Call the parent's method and then add to that string with the appetiser specific ones 
	return "";
}