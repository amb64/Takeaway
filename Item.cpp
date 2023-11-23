#include "Item.h"

// Constructor
Item::Item(int icalories, string iname, float iprice)
{
	calories = icalories;
	name = iname;
	price = iprice;
}

// Desctructor
Item::~Item()
{
	
}

int Item::getCalories()
{
	return calories;
}

string Item::getName()
{
	return name;
}

float Item::getPrice()
{
	return price;
}

string Item::toString()
{
	// Prtints out info for the individual item - used for the order / receipt
	return "";
}