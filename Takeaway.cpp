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
#include <algorithm>

using namespace std;


int main()
{
	string userCommand;
	vector <string> parameters;

	// Create a menu object from a CSV file
	Menu menu = Menu("menu.csv");

	// Create an order object
	Order order = Order(menu);

	cout << "==========Takeaway Ordering Program==========\n\n";
	cout << "-----Help Commands-----\nSelect an option by typing the corresponding keyword.(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\n\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n---------------------\n\n";

	while (userCommand != "exit")
	{
		cout << "Enter a command...\n\n-> ";

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

					// Required as a vector must be passed in. But, we dont actually need anything in this vector as we are adding items not removing them
					vector<Item*> emptyVector;

					// Getting the corresponding item pointer for the selected menu object
					choice = menu.getItem(index, false, emptyVector);

					// If the pointer is not null, add it to the order and display the order
					if (choice != nullptr)
					{
						order.add(choice);
					}
				}
				catch(const invalid_argument&)
				{
					cout << "\nOops! Your input '" << parameters[i] <<  "' was invalid.";
				}
			}

			// Outputs their order
			cout << "\n\nYour order has been updated with any valid items!\n";
			cout << order.toString();

			// You may also wish to implement the ability to add multiple items at once!
			// e.g. add 1 5 9 
		}
		else if (command.compare("remove") == 0)
		{
			// Vector to store the set of items to remove
			vector<int> itemsToRemove;

			// Iterating through the parameters vector (for each item the user wishes to add to their order)
			for (int i = 1; i < (parameters.size() - 1); i++)
			{
				if (i >= parameters.size() || parameters[i].empty() || parameters[i].find_first_not_of(" ") == std::string::npos)
				{
					//cout << "current parameter is EMPTY!!";
					continue;
				}

				// Try adding them to the vector as integers
				try
				{
					itemsToRemove.push_back(stoi(parameters[i]));
				}
				// If that doesnt work, the input must be invalid
				catch (const exception& e)
				{
					// put this back at the normal exception like the one in add?
					//cout << "exception: " << e.what();
					//cout << "\nInvalid parameter: " << parameters[i] << endl;
					cout << "\nOops! Your input '" << parameters[i] << "' was invalid.";
				}
			}
			
			// Sorting the vector in ascending order
			sort(itemsToRemove.begin(), itemsToRemove.end());

			/*for (auto num : itemsToRemove)
			{
				cout << "\nitem to remove: " << num << endl;
			}

			cout << "thats all\n";*/

			// Iterating through the items in the itemsToRemove vector- but backwards as during this the size of the orderItems vector changes.
			// So we want to always remove the last item first!
			for (int i = (itemsToRemove.size() - 1); i >= 0; i--)
			{
				//cout << "\nitem to remove: " << itemsToRemove[i] << endl;

				//cout << "\ncurrent iteration is: " << i << endl;

				//cout << "\nindex's value is: " << itemToRemove << endl;

				// Pointer to the item to remove from the order
				Item* choice;

				// Getting order items to pass to get item
				vector<Item*> orderItems = order.getOrderItems();

				// Getting the corresponding item pointer for the selected order object
				choice = menu.getItem(itemsToRemove[i], true, orderItems);

				// If the pointer is not null, add it to the order and display the order
				if (choice != nullptr)
				{
					order.remove(choice);
				}
			}

			// Outputs their order
			cout << "\n\nYour order has been updated with any valid items!\n";
			cout << order.toString();
		}
		else if (command.compare("checkout") == 0)
		{ 
			string choice;

			cout << order.checkout();
			cin >> choice;

			if (choice == "y" || choice == "Y")
			{
				order.printReceipt();
			}
			else
			{
				cout << "\n\nCheckout cancelled.\nPlease select the checkout option once you are content with the contents of your order.\n\n";
			}

			// Clearing the new line character from the getline to do with the user command, ensures that the "invalid input" message in the "else" section of comparing the commands does not trigger
			cin.ignore();

			// ask for user input, y to confirm, n to go back
		}
		else if (command.compare("help") == 0)
		{
			cout << "\n\n-----Help Commands-----\nSelect an option by typing the corresponding keyword.(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) checkout - Checkout your order.\n(5) help - Displays this menu.\n(6) exit - Exits the program.\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n---------------------\n\n";
		}
		// Added this, ensures that the user knows their input was invalid but also this if makes sure this message doesnt print when the user wants to exit the program
		else if (command.compare("exit") == 1)
		{
			cout << "\n\nInvalid input.\nPlease type in a valid command.\nNeed help? Type 'help'.\n\n";
		}

		parameters.clear();

	}

	cout << "\n";
	cout << "Press any key to quit...";
	std::getchar();
}