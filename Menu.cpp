#include "Menu.h"

// Constructor that takes the file path passed in and sets it as the filepath variable in the class. Then calls the function to load the file
Menu::Menu(string ifilePath)
{
	filePath = ifilePath;
	loadFile();
}

void Menu::loadFile()
{
	ifstream file(filePath, ios::in); // Opening the file
	string line; // The curent line being checked (entry in the csv file)
	
	vector<string> itemList; // Vector to store the current menu item's info
	vector<vector<string>> menuList; // 2D vector to store all menu item info

	if (file.is_open())
	{
		while (getline(file, line)) // Checking each line 
		{
			stringstream ss(line);
			string item; // The current string being checked

			while (getline(ss, item, ',')) // Checking the current string
			{
				// If the string is not empty then add it into the list for the current menu item
				if (!item.empty() && item.find_first_not_of(" ") != string::npos)
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
			vector<string>().swap(itemList); 
		}

		for (const auto& item : menuList)
		{
			// Setting shared variables
			const string itemType = item[0];
			string itemName = item[1];
			float price = stof(item[2]);
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
				delete a;
			}
			else if (itemType == "m")
			{

			}
			else if (itemType == "b")
			{

			}


		}

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

string Menu::toString()
{
	// Function that displays the menu nicely when printed out on the screen.
	// Organised by item type.
	// See brief for specifics

	return "";
}
