#pragma once
#include "Item.h"

// Main course class
class MainCourse : public Item
{
public:
	MainCourse(int icalories, std::string iname, double iprice);
	~MainCourse();

	// Additional implementation of toString to fix spacing / new line issues in the output.
	std::string toString() override;
};