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

	// Functions for printing out the menu
	std::string toString();
	std::string toStringA();
	std::string toStringD();

	Item* getItem(int index, bool isRemoving, std::vector<Item*> orderItems);

	std::vector<Item*> getItems();

private:
	std::string filePath;
};