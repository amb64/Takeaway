#pragma once
#include "Item.h"
#include <cstring>
#include <iostream>
using namespace std;

// Item list class (should this even be here or have its own file??)
class ItemList
{
public:
	virtual string toString() = 0;

protected:
	// Vector storing pointers to item objects
	vector<Item*> items;
};