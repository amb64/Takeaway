#include "Menu.h"
#include "Item.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"

// Constructor that takes the file path passed in and sets it as the filepath variable in the class. Then calls the function to load the file
Menu::Menu(std::string ifilePath)
{
	filePath = ifilePath;
	loadFile();
}

void Menu::loadFile()
{
	std::ifstream file(filePath, std::ios::in); // Opening the file
	std::string line; // The curent line being checked (entry in the csv file)
	
	std::vector<std::string> itemList; // Vector to store the current menu item's info
	std::vector<std::vector<std::string>> menuList; // 2D vector to store all menu item info

	if (file.is_open())
	{
		while (getline(file, line)) // Checking each line 
		{
			std::stringstream ss(line);
			std::string item; // The current string being checked

			while (getline(ss, item, ',')) // Checking the current string
			{
				// If the string is not empty then add it into the list for the current menu item
				if (!item.empty() && item.find_first_not_of(" ") != std::string::npos)
				{
					itemList.push_back(item);
				}
			}

			/*for (auto i : itemList)
			{
				cout << i << endl;
			}
			cout << "end" << endl;*/
			// print out individual list to check it recognises each object

			// Adding the data for the current menu item into the 2d vector
			menuList.push_back(itemList);
			// Using a temporary vector to clear and release the old vector from memory
			std::vector<std::string>().swap(itemList);
		}

		for (const auto& item : menuList)
		{
			// Setting shared variables
			const std::string itemType = item[0];
			std::string itemName = item[1];
			double price = stod(item[2]);
			int calories = stoi(item[3]);
			
			if (itemType == "a")
			{
				bool isShareable;

				if (item[4] == "y")
				{
					isShareable = true;
				}
				else
				{
					isShareable = false;
				}

				bool isTwoForOne;

				if (item[5] == "y")
				{
					isTwoForOne = true;
				}
				else
				{
					isTwoForOne = false;
				}

				Appetiser* a;
				a = new Appetiser(calories, itemName, price, isShareable, isTwoForOne);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

				//delete a;
			}
			else if (itemType == "m")
			{
				MainCourse* a;
				a = new MainCourse(calories, itemName, price);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

				//delete a;
			}
			else if (itemType == "b")
			{
				int volume = stoi(item[4]);
				double abv = stod(item[5]);

				Beverage* a;
				a = new Beverage(calories, itemName, price, volume, abv);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

				//delete a;
			}
		}

		file.close();

		//std::cout << items[0]->toString();
		//std::cout << items[0]->getName();

		/*for (auto i : menuList)
		{
			for (auto j : i)
			{
				cout << j << endl;
			}
		}*/
	}



	// Need to open the csv file
	// Iterate through each line and get each part of the data in that line
	// Store that data temporarily in a list
	// Determine which kind of item object needs to be created
	// Create the object
	// When done reading from the file, close it and delete the variable for the file as well as the list used
}

std::string Menu::toString()
{
	// Function that displays the menu nicely when printed out on the screen.
	// Organised by item type.
	// See brief for specifics

	std::string output;
	//int counter = 1;
	Item* previousItem = nullptr;

	//output = output + "----------Appetisers----------";
	output+= "----------Appetisers----------\n";

	// Loop that goes through the list of items. When it hits an item with a type different to the previous item, check whether the new item is a main course or beverage.
	// Then it displays the next message and continues through the loop.
	// This is done under the assumption that the menu.csv file will always be ordered appetisers -> main courses -> beverages

	//std::cout << items[0]->toString();

	for (size_t i = 0; i < items.size(); i++)
	{
		if (i > 0 && typeid(*items[i]) != typeid(*previousItem))
		{
			if (typeid(*items[i]) == typeid(MainCourse))
			{
				output += "----------Main Dishes----------\n";
			}
			else if (typeid(*items[i]) == typeid(Beverage))
			{
				output += "----------Beverages----------\n";
			}
		}

		//output = output + std::to_string(counter) + i->toString() + "\n";
		output += "(" + std::to_string(i + 1) + ") " + items[i]->toString();
		previousItem = items[i];
		//counter++;
	}

	return output;
}
