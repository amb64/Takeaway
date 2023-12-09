#include "MainCourse.h"

// Constructor
MainCourse::MainCourse(int icalories, std::string iname, double iprice) : Item(icalories, iname, iprice)
{
	// No extra parameters need to be initialised for a MainCourse object
}

// Destructor
MainCourse::~MainCourse()
{

}

std::string MainCourse::toString()
{
	// Call the base method
	std::string output = Item::toString();

	// Fixes spacing / new line issues with the other objects. Simply adds a new line to the output
	output = output + "\n";

	// Returns a string of the item
	return output;
}