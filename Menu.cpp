#include "Menu.h"

// Constructor that takes the file path passed in and sets it as the filepath variable in the class. Then calls the function to load the file
Menu::Menu(std::string ifilePath)
{
	filePath = ifilePath;
	loadFile();

	// Sort the menu
	sortItems();
}

// Destructor
Menu::~Menu()
{

}

// Cleanup function to clear memory
// Menu destructor is called early, so this has to be a separate function
void Menu::Cleanup()
{
	for (Item* item : items)
	{
		delete item;
	}

	items.clear();
	ascendingItems.clear();
	descendingItems.clear();
}

void Menu::sortItems()
{
	// Making a vector for the ascending menu
	ascendingItems = items;

	// Sorting the menu by comparing the price variable of the objects
	// Need to use a lambda function here to call comparePrice on the objects to actually compare the price variables
	std::sort(ascendingItems.begin(), ascendingItems.end(), [this](Item* item1, Item* item2) {return comparePriceA(item1, item2);});

	// Repeat the same for the descending items vector
	descendingItems = items;

	std::sort(descendingItems.begin(), descendingItems.end(), [this](Item* item1, Item* item2){return comparePriceD(item1, item2);});
}

// Function that compares the price of 2 Item objects to be used to sort the menu in order
bool Menu::comparePriceA(Item* item1, Item* item2)
{
	return item1->getPrice() < item2->getPrice();
}

// The same as the above function but the operator is swapped so we can sort in descending order
bool Menu::comparePriceD(Item* item1, Item* item2)
{
	return item1->getPrice() > item2->getPrice();
}

// Returns a pointer to an item object based on an inputted integer
Item* Menu::getItem(int index, bool isRemoving, std::vector<Item*> orderItems)
{
	//std::cout << "\ncalled get item\n";

	int orderItemsSize = orderItems.size();

	Item* item;

	// If:
	// The index is less than 1
	// The user is adding and the index is larger than the size of the items vector
	// The user is removing and the index is larger than the orderItems vector
	// Then there is an error in the input

	// Furthermore, decimals are accepted but only the first digit is taken, e.g 1.7 becomes 1
	// 0.x is not accepted

	// Limits for integers

	if (index >= 1 && (!isRemoving && index <= items.size()))
	{
		// Index offset
		index--;

		// The item in the items list
		item = items[index];

		return item;
	}
	else if (index >= 1 && (isRemoving && index <= orderItemsSize))
	{
		// Index offset
		index--;

		// The item in the order items list
		item = orderItems[index];

		return item;
	}
	// Input is invalid
	else
	{
		std::cout << "\nOops! Your input '" << index << "' was invalid.";

		return nullptr;
	}
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
			}

			// Main course
			else if (itemType == "m")
			{
				// Creating a main course object and adding it to the vector
				MainCourse* a;
				a = new MainCourse(calories, itemName, price);
				items.push_back(a);
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
			}
		}

		// Free up memory
		itemList.clear();
		menuList.clear();

		// Close the file
		file.close();
	}
}

std::string Menu::toString()
{
	// Function that displays the menu nicely when printed out on the screen.
	// Organised by item type.

	// String that stores the text to be outputted
	std::string output;

	// Variable that helps to seperate the different item types in the output
	Item* previousItem = nullptr;

	output+= "\n----------Appetisers----------\n";

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

		output += "(" + std::to_string(i + 1) + ") " + items[i]->toString();
		previousItem = items[i];
	}

	output += "\n\n";

	// Returning the string
	return output;
}

// A seperate implementation of the to string function that removes the formatting as the menu has been sorted
std::string Menu::toStringPlain(bool asc) const
{
	std::vector<Item*> menu;
	std::string output;

	output += "\n----------Menu: ";

	// If the ascending bool is true, print out ascending items
	if (asc)
	{
		menu = ascendingItems;
		output += "Ascending";
	}
	// Otherwise, descending items
	else
	{
		menu = descendingItems;
		output += "Descending";
	}
	output += "----------\n";

	// Add them to the output variable
	for (size_t i = 0; i < menu.size(); i++)
	{
		output += menu[i]->toString();
	}

	output += "\n\n";

	// Return the output variable
	return output;
}