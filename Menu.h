#pragma once
#include "ItemList.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Menu : public ItemList
{
public:
	Menu(std::string filePath);
	void loadFile();
	std::string toString();

private:
	std::string filePath;
};

// Additional functionality : add the ability to sort by ascending or descending menu