#pragma once
#include "ItemList.h"
#include "Item.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Menu : public ItemList
{
public:
	Menu(std::string filePath);
	~Menu();
	void loadFile();
	std::string toString();

	Item* getItem(int index, bool isRemoving, int orderItemsSize);

	// CAN WE MAKE THIS A FRIEND FUNCTION WITH ORDER??
	std::vector<Item*> getItems();

private:
	std::string filePath;
};

// Additional functionality : add the ability to sort by ascending or descending menu