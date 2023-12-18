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
	Order order = Order();

	cout << "==========Takeaway Ordering Program==========\n\n";
	cout << "-----Help Commands-----\nSelect an option by typing the corresponding keyword.\n(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) order - Displays your order. \n(5) checkout - Checkout your order.\n(6) help - Displays this menu.\n(7) exit - Exits the program.\n\nType an 'a' or 'd' after menu to sort in ascending or descending order.\nE.g menu a\n\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n\nWhen adding items, please use the corresponding number from the most recently outputted menu,\notherwise your order may not be what you expected.\n\nREMEMBER: Commands are CaSe SeNsItIvE\n---------------------\n\n";

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

		parameters.push_back("");
		string command = parameters[0];

		if (command.compare("menu") == 0) 
		{
			// Check if the user entered an additional letter after menu
			if (parameters[1].empty() || parameters[1].find_first_not_of(" ") == std::string::npos)
			{
				// Output the regular menu
				cout << menu.toString();
			}
			else if (parameters[1] == "a")
			{
				// Ascending menu
				cout << menu.toStringPlain(true);
			}
			else if (parameters[1] == "d")
			{
				// Descending menu
				cout << menu.toStringPlain(false);
			}
			else
			{
				// Invalid input message
				cout << "\nOops! Your input '" << parameters[1] << "' was invalid.\n\n";
			}
		}
		// Simply displays the user's order, added because felt it was needed
		else if (command.compare("order") == 0)
		{
			cout << order.toString();
		}
		else if (command.compare("add") == 0)
		{
			// Iterating through the parameters vector (for each item the user wishes to add to their order)
			for (int i = 1; i < (parameters.size() - 1); i++)
			{
				// Check if the parameter is empty
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
					// If the user types a decimal, it is rounded down / only the first digit is registered
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
				// If the current elemt cant be cast to an integer, it must not be a number
				catch(const invalid_argument&)
				{
					cout << "\nOops! Your input '" << parameters[i] <<  "' was invalid.";
				}
				// If the number is out of range of the limits for an integer, notify the user
				catch (const out_of_range&)
				{
					cout << "\nOops! Your input '" << parameters[i] << "' was invalid.";
				}
			}

			// Outputs their order
			cout << "\n\nYour order has been updated with any valid items!\n";
			cout << order.toString();
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
				// If the user types a decimal, it is rounded down / only the first digit is registered
				try
				{
					itemsToRemove.push_back(stoi(parameters[i]));
				}
				// If that doesnt work, the input must be invalid
				catch (const invalid_argument&)
				{
					cout << "\nOops! Your input '" << parameters[i] << "' was invalid.";
				}
				// If the number is out of range of the limits for an integer, notify the user
				catch(const out_of_range&)
				{
					cout << "\nOops! Your input '" << parameters[i] << "' was invalid.";
				}
			}
			
			// The following code works even if the user inputted "remove banana -1" or something because the itemsToRemove list would be empty, and therefore the loop would not trigger at all
			
			// Sorting the vector in ascending order and the removing duplicates
			sort(itemsToRemove.begin(), itemsToRemove.end());
			auto dupes = unique(itemsToRemove.begin(), itemsToRemove.end());
			itemsToRemove.erase(dupes, itemsToRemove.end());

			// Iterating through the items in the itemsToRemove vector- but backwards as during this the size of the orderItems vector changes.
			// So we want to always remove the last item first!
			for (int i = (itemsToRemove.size() - 1); i >= 0; i--)
			{
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
			cout << "\n\nYour order has been updated, and any valid items have been removed!\n(Duplicate inputs were not actioned)\n";
			cout << order.toString();
		}
		else if (command.compare("checkout") == 0)
		{ 
			// The receipt does NOT display £ correctly. Wanted to fix this but it is not an easy fix as Order's toString function is not where £s are added,
			// they are added in the toString methods for the Item class and its child classes.

			cout << order.checkout();

			while (true)
			{
				string choice;
				cin >> choice;

				// If they type y, print out the receipt, otherwise checkout is cancelled
				if (choice == "y" || choice == "Y")
				{
					order.printReceipt();

					// Cleanup and end program
					menu.Cleanup();
					order.Cleanup();
					return 0;
				}
				else if (choice == "n" || choice == "N")
				{
					cout << "\nCheckout cancelled.\nPlease select the checkout option once you are satisfied with the contents of your order.\n\n";
					break;
				}
				else
				{
					cout << "\nInvalid input.\nPlease type 'y' to confirm your order, or 'n' to cancel it.\n\n";
				}
			}

			// Clearing the new line character from the getline to do with the user command, ensures that the "invalid input" message in the "else" section of comparing the commands does not trigger
			cin.ignore();
		}
		else if (command.compare("help") == 0)
		{
			cout << "\n-----Help Commands-----\nSelect an option by typing the corresponding keyword.\n(1) menu - Displays the food menu.\n(2) add - Add an item to your order.\n(3) remove - Remove an item from your order.\n(4) order - Displays your order. \n(5) checkout - Checkout your order.\n(6) help - Displays this menu.\n(7) exit - Exits the program.\n\nType an 'a' or 'd' after menu to sort in ascending or descending order.\nE.g menu a\n\nTo add and remove objects, type the command and then the items you wish to add / remove seperated by a space.\nE.g: add 1 2 3\n\nWhen adding items, please use the corresponding number from the most recently outputted menu,\notherwise your order may not be what you expected.\n\nREMEMBER: Commands are CaSe SeNsItIvE\n---------------------\n\n";
		}
		// Added this, ensures that the user knows their input was invalid but also this if makes sure this message doesnt print when the user wants to exit the program
		else if (command.compare("exit") != 0)
		{
			cout << "\nInvalid input.\nPlease type in a valid command.\nRemember, commands are case sensitive.\nNeed help? Type 'help'.\n\n";
		}

		parameters.clear();
	}

	cout << "\n";
	cout << "Press any key to quit...";
	std::getchar();

	// Cleanup and end program
	menu.Cleanup();
	order.Cleanup();

}