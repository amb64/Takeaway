#pragma once
#include "ItemList.h"
#include "Item.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Menu : public ItemList
{
public:
	Menu(std::string filePath);
	~Menu();
	void Cleanup();

	void loadFile();

	// Functions for printing out the menu
	std::string toString();
	std::string toStringPlain(bool asc);

	Item* getItem(int index, bool isRemoving, std::vector<Item*> orderItems);

private:
	void sortItems();
	bool comparePriceA(Item* item1, Item* item2);
	bool comparePriceD(Item* item1, Item* item2);

	std::string filePath;

	std::vector<Item*> ascendingItems;
	std::vector<Item*> descendingItems;

	// Int that represents the current menu type.
	// 0 - normal , 1 - ascending , 2 - descending
	int menuType;
};