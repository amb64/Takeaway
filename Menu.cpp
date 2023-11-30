#include "Menu.h"

// Constructor that takes the file path passed in and sets it as the filepath variable in the class. Then calls the function to load the file
Menu::Menu(std::string ifilePath)
{
	filePath = ifilePath;
	loadFile();
}

// Destructor
Menu::~Menu()
{

}

std::vector<Item*> Menu::getItems()
{
	return items;
}


void Menu::loadFile()
{
	// Opening the file
	std::ifstream file(filePath, std::ios::in); 

	// The curent line being checked (entry in the csv file)
	std::string line; 
	
	// Vector to store the current menu item's info
	std::vector<std::string> itemList; 

	// 2D vector to store all menu item info
	std::vector<std::vector<std::string>> menuList; 

	if (file.is_open())
	{
		// Checking each line 
		while (getline(file, line)) 
		{
			std::stringstream ss(line);

			// The current string being checked
			std::string item; 

			// Checking the current string
			while (getline(ss, item, ',')) 
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

		// Loops through all items in the newly created menu list
		for (const auto& item : menuList)
		{
			// Setting shared variables
			const std::string itemType = item[0];
			std::string itemName = item[1];
			double price = stod(item[2]);
			int calories = stoi(item[3]);
			
			// Appetiser
			if (itemType == "a")
			{
				// Setting the unique variables first
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

				// Creating an appetiser object and adding it to the vector
				Appetiser* a;
				a = new Appetiser(calories, itemName, price, isShareable, isTwoForOne);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

			}

			// Main course
			else if (itemType == "m")
			{
				// Creating a main course object and adding it to the vector
				MainCourse* a;
				a = new MainCourse(calories, itemName, price);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

			}

			// Beverage
			else if (itemType == "b")
			{
				// Setting the beverage specific variables
				int volume = stoi(item[4]);
				double abv = stod(item[5]);

				// Creating a beverage object and adding it to the vector
				Beverage* a;
				a = new Beverage(calories, itemName, price, volume, abv);
				items.push_back(a);

				//Testing
				/*std::string output = a->toString();
				std::cout << output;*/

			}
		}

		// Close the file
		file.close();

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

	//std::cout << "\nMenu.cpp after making objects, items size is: " << items.size();
}

// NEED TO BE ABLE TO SORT MENU IN ASCENDING AND DESCENDING ORDER
std::string Menu::toString()
{
	// Function that displays the menu nicely when printed out on the screen.
	// Organised by item type.
	// See brief for specifics

	// String that stores the text to be outputted
	std::string output;

	// Variable that helps to seperate the different item types in the output
	Item* previousItem = nullptr;

	output+= "----------Appetisers----------\n";

	// Loop that goes through the list of items. When it hits an item with a type different to the previous item, check whether the new item is a main course or beverage.
	// Then it displays the next message and continues through the loop.
	// This is done under the assumption that the menu.csv file will always be ordered appetisers -> main courses -> beverages

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

		output += "(" + std::to_string(i + 1) + ") " + items[i]->toString() + "\n";
		previousItem = items[i];
	}

	// Returning the string
	return output;
}
