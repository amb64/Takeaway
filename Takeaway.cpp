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

	cout << "==========Takeaway Ordering Program==========\n";
	cout << "-----Help Commands-----\n(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\n";

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
			cout << i;
		}
		cout << "finished printing out parameters";*/

		parameters.push_back("");
		string command = parameters[0];

		if (command.compare("menu") == 0) {
			cout << menu.toString();
		}
		else if (command.compare("add") == 0)
		{
			// Getting user input for the item number
			int input;
			cout << "Please enter the number of the item from the menu you would like to add.\nIf you want to add multiple items, split them with a comma like this: 1,2,3\n";

			cin >> input;

			Item* choice; // you need to instantiate this using the menu object!

			// Getting the corresponding item pointer for the selected menu object
			choice = menu.getItem(input);

			// If the pointer is not null, add it to the order and display the order
			if (choice != nullptr)
			{
				order.add(choice);

				cout << order.toString();

				cout << "item should have been added...";

				std::vector<Item*> items = menu.getItems();
				cout << items[0]->toString();
			}

			// probably also add in an explanation as to the formatting for how they would input multiple items, split by a comma, a space or whatever
			// pass the input to the add function, then in the add function split the different inputs so that you can add multiple items
			// then display the order.tostring

			// You may also wish to implement the ability to add multiple items at once!
			// e.g. add 1 5 9 
		}
		else if (command.compare("remove") == 0)
		{
			// Getting user input for the item number
			int input; 

			// Boolean for if the user selects 1. The program will crash if we do not have a special case for when the user selected the 1st item
			bool first = false;

			cout << "Please enter the number of the item from your order you would like to remove.\nIf you want to remove multiple items, split them with a comma like this: 1,2,3\n";

			cin >> input;

			if (input == 1)
			{
				first = true;
			}

			Item* choice; // you need to instantiate this using the menu object!

			// Getting the corresponding item pointer for the selected menu object
			choice = menu.getItem(input);

			// If the pointer is not null, add it to the order and display the order
			if (choice != nullptr)
			{
				order.remove(choice, first);

				cout << order.toString();
			}
		}
		else if (command.compare("checkout") == 0)
		{ 
			cout << order.checkout();
			// ask for user input, y to confirm, n to go back
		}
		else if (command.compare("help") == 0)
		{
			cout << "-----Help Commands-----\n(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\n";
			// add some dialogue here just to explain 
		}

		parameters.clear();

	}

	cout << "Press any key to quit...";
	std::getchar();

}