/* ------------------------------------------------------
CMP2811 Applied Programming Paradigms
Driver program for "Takeaway" assignment
Autumn 2023

This file is a representative test file.
During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.
Also make sure that you don't modify the code provided here,
but instead add what you need to complete the tasks.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Order.h"
#include "Item.h"

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
	//TEMPORARY TESTING COMMANDS
	
	/*Appetiser* app;
	app = new Appetiser(500, "burger", 1.50, true, true);
	vector<Item*> items;
	items.push_back(app);
	cout << app->getTwoForOne();*/
	
	/*Menu menu = Menu("menu.csv");
	//Menu menu = Menu("menu2.csv");
	Order order = Order(menu);

	string output = menu.toString();
	cout << output;

	cout << "\nenter item to add\n";
	int itemid;
	cin >> itemid;
	order.add(itemid);

	output = order.toString();
	cout << output;

	cout << "\nenter item to remove\n";
	cin >> itemid;
	order.remove(itemid);

	output = order.toString();
	cout << output;

	cout << "\nenter item to add\n";
	itemid;
	cin >> itemid;
	order.add(itemid);

	output = order.toString();
	cout << output;

	cout << "\nenter item to add\n";
	itemid;
	cin >> itemid;
	order.add(itemid);

	output = order.toString();
	cout << output;

	cout << "\nenter item to add\n";
	itemid;
	cin >> itemid;
	order.add(itemid);

	output = order.toString();
	cout << output;

	cout << "\nenter item to add\n";
	itemid;
	cin >> itemid;
	order.add(itemid);

	output = order.toString();
	cout << output;

	order.printReceipt();*/

	// END PERSONAL TESTING COMMANDS

	string userCommand;
	vector <string> parameters;

	// Create a menu object from a CSV file
	Menu menu = Menu("menu.csv");

	// Create an order object
	Order order = Order(menu);

	cout << "==========Takeaway Ordering Program==========\n\n";
	cout << "-----Help Commands-----\nSelect an option by typing the corresponding keyword.(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n---------------------\n\n";

	while (userCommand != "exit")
	{
		getline(cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		/*for (auto i : parameters)
		{
			cout << i << endl;
		}
		cout << "finished printing out parameters";(*/

		parameters.push_back("");
		string command = parameters[0];

		if (command.compare("menu") == 0) {
			cout << menu.toString();
		}
		else if (command.compare("add") == 0)
		{
			// Iterating through the parameters vector (for each item the user wishes to add to their order)
			for (int i = 1; i < (parameters.size() - 1); i++)
			{
				if (i >= parameters.size() || parameters[i].empty() || parameters[i].find_first_not_of(" ") == std::string::npos)
				{
					//cout << "current parameter is EMPTY!!";
					continue;
				}

				// The index for the item in the menu
				int index;

				// Only continues if the input is a number
				try
				{
					// Cast the corresponding element in the vector to an int
					index = stoi(parameters[i]);
					// Pointer to the item to add to the menu
					Item* choice;

					// Getting the corresponding item pointer for the selected menu object
					choice = menu.getItem(index, false, 0);

					// If the pointer is not null, add it to the order and display the order
					if (choice != nullptr)
					{
						order.add(choice);
					}
				}
				catch(const std::invalid_argument& err)
				{
					std::cout << "\n-----\nOops!\nOne or more of your inputted numbers was invalid.\nPlease type either 'add' or 'remove' and input an item number again.\nPlease note: any valid items have been added / removed.\n-----\n\n";
				}
			}

			// Outputs their order
			cout << order.toString();

			// You may also wish to implement the ability to add multiple items at once!
			// e.g. add 1 5 9 
		}
		else if (command.compare("remove") == 0)
		{
			// Iterating through the parameters vector (for each item the user wishes to add to their order)
			for (int i = 1; i < (parameters.size()); i++)
			{
				if (i >= parameters.size() || parameters[i].empty() || parameters[i].find_first_not_of(" ") == std::string::npos)
				{
					//cout << "current parameter is EMPTY!!";
					continue;
				}

				// The index for the item in the menu
				int index;

				try
				{
					// Cast the corresponding element in the vector to an int
					index = stoi(parameters[i]);

					// Pointer to the item to remove from the order
					Item* choice;

					// Getting the size of order items to pass to get item
					int orderItemsSize = order.getOrderItemsSize();

					// Getting the corresponding item pointer for the selected order object
					choice = menu.getItem(index, true, orderItemsSize);

					// If the pointer is not null, add it to the order and display the order
					if (choice != nullptr)
					{
						order.remove(choice);
						
					}
				}
				catch (const std::invalid_argument& err)
				{
					std::cout << "\n-----\nOops!\nOne or more of your inputted numbers was invalid.\nPlease type either 'add' or 'remove' and input an item number again.\nPlease note: any valid items have been added / removed.\n-----\n\n";
				}
			}

			// Outputs their order
			cout << order.toString();
		}
		else if (command.compare("checkout") == 0)
		{ 
			cout << order.checkout();
			// ask for user input, y to confirm, n to go back
		}
		else if (command.compare("help") == 0)
		{
			cout << "\n\n-----Help Commands-----\nSelect an option by typing the corresponding keyword.(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n---------------------\n\n";
		}
		else
		{
			cout << "\n\nInvalid input.\nPlease type in a valid command.\nNeed help? Type 'help'.\n\n";
		}

		parameters.clear();

	}

	cout << "Press any key to quit...";
	std::getchar();

}