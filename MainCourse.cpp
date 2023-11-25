#include "MainCourse.h"

// Constructor
MainCourse::MainCourse(int icalories, std::string iname, float iprice) : Item(icalories, iname, iprice)
{
	// No extra parameters need to be initialised for a MainCourse object
}

// Destructor
MainCourse::~MainCourse()
{

}

// Fixes spacing / new line issues with the other objects. Simply adds a new line to the output
// Returns a string of the item
std::string MainCourse::toString()
{
	std::string output = Item::toString();
	output = output + "\n";

	return output;
}