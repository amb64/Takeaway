#pragma once
#include "Item.h"
#include <string>
#include <iostream>

// Item list class (should this even be here or have its own file??)
class ItemList
{
public:
	virtual std::string toString() = 0;

protected:
	// Vector storing pointers to item objects
	std::vector<Item*> items;
};