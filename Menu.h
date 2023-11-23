#pragma once
#include "ItemList.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Menu : public ItemList
{
public:
	Menu(string filePath);
	void loadFile();
	string toString();

private:
	string filePath;
};

// Additional functionality : add the ability to sort by ascending or descending menu