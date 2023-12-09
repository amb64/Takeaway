#include "Order.h"

// Constructor
Order::Order(Menu menu)
{
	// Setting items as the items vector from the menu class, which is why this get function is necessary
	// This is because child classes do inherit the parent's member variables, but as menu edits the vector, it isnt reflected in order as order inherits the empty vector.
	items = menu.getItems();

	// Variable initilisation
	savings = 0;
	total = 0;
}

// Destructor
Order::~Order()
{

}

// Function that gets the private variable total.
double Order::getTotal() const
{
	return total;
}

// Returns the size of orderItems
std::vector<Item*> Order::getOrderItems()
{
	return orderItems;
}

void Order::calculateTotal()
{
	//std::cout << "\ncalled calculate total\n";

	// Declaring variable to hold the total while it is being calculated
	double totalCalc = 0; 

	// Loops through and adds up the prices of all the items in the order
	for (auto i : orderItems)
	{
		totalCalc += i->getPrice();
	}

	// Subtracts savings
	totalCalc -= savings;

	// Sets the actual total variable
	total = totalCalc;

	// Using the private vector storing pointers to the items in the order,
	// Calculates the total while considering items eligible for a 2-4-1 discount (use the private bool for this)
	// Remember that they will only get the cheapest item free! (Will need to add to the csv so there is an appetiser with different price)
}

// ADD ABILITY TO ADD MULTIPLE ITEMS
void Order::add(Item* item)
{
	// Adding the item to the order vector
	orderItems.push_back(item);

	// Will check for the 2 for 1 deal if the item being added is an appetiser
	if (typeid(*item) == typeid(Appetiser))
	{
		checkTwoForOne();
	}

	// Calculates the new total
	calculateTotal();

	// Based on the item number given (will be from 1 instead of 0 like the list, so remember to -1!) will add to the order vector
	// If item is an appetiser, call checkTwoForOne() 
	// Then calls calculateTotal()
	
}

// ADD ABILITY TO REMOVE MULTIPLE ITEMS
void Order::remove(Item* item)
{
	// Find the pointer in the vector using an iterator, and then remove it
	auto it = std::find(orderItems.begin(), orderItems.end(), item);
	orderItems.erase(it);

	// Will check for the 2 for 1 deal if the item being removed is an appetiser
	if (typeid(*item) == typeid(Appetiser))
	{
		checkTwoForOne();
	}

	// Calculates the new total
	calculateTotal();

	// Same as order, but removes an item from the order vector
	// If the item is an appetiser, call checkTwoForOne()
	// Then calls calculateTotal()
}

void Order::checkTwoForOne()
{
	// This function works under the assumption that the 2 for 1 deal is only valid once per order.

	// Stores the amount of appetisers
	int appetiserCount = 0; 
	
	// This is done before the loop to ensure that if two appetisers are not found, no discount is applied.
	twoForOne = false; 
	savings = 0;

	// Storing pointers to the two appetisers
	Item* a1 = nullptr;
	Item* a2 = nullptr;

	// Iterates through the order vector
	for (size_t i = 0; i < orderItems.size(); i++) 
	{
		// Trying to cast the current item to appetiser type
		Appetiser* currentItem = dynamic_cast<Appetiser*>(orderItems[i]);

		// If that worked, then the current item is an appetiser
		if (currentItem)
		{
			// Storing these appetisers as we need them to calculate the savings
			if (a1 == nullptr)
			{
				a1 = currentItem;
			}
			else
			{
				a2 = currentItem;
			}

			if (currentItem->getTwoForOne())
			{
				appetiserCount++;
			}
		}
		
		// If there are two appetisers, set the bool as true and finish iterating
		if (appetiserCount == 2) 
		{
			twoForOne = true;
			calculateSavings(a1, a2);
			break;
		}
	}

	// Checks through the list if there are 2 appetisers that are valid for 2-4-1
	// Store these temporarily
	// Then sets the bool to either true or false 
	// If true, calculate the savings (compare the price attribute, the smaller one is then considered the savings amount)
}

void Order::calculateSavings(Item* a1, Item* a2)
{
	// If a1s price is bigger, the savings is set to the price of that item. Else, the opposite occurs

	if (a1->getPrice() > a2->getPrice())
	{
		savings = a2->getPrice();
	}
	else
	{
		savings = a1->getPrice();
	}
}

std::string Order::toString()
{
	// Outputs the order nice and pretty
	// Must include the total price, and the savings made
	// See brief for specifics
	
	// String that stores the text to be outputted
	std::string output;

	output += "\n===== Order =====\n";

	// Iterates through all order items, then calls the to string function for the item and adds it to the output

	if (orderItems.size() == 0)
	{
		output += "Your order is currently empty!\nIf you add an item to your order, it will show up here.\n----------";
	}
	else
	{
		for (size_t i = 0; i < orderItems.size(); i++)
		{
			output += "(" + std::to_string(i + 1) + ") " + orderItems[i]->toString();
		}

		output += "----------\n";

		// If a 241 discount is applicable, notify the user and adds the savings to the string
		if (twoForOne == true)
		{
			output += "2-4-1 discount applied! Savings: \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << savings).str() + "\n";
		}

		// Adds their total to the string
		output += "Total: \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << total).str() + "\n";
	}

	output += "\n\n";

	// Returning the string
	return output;
}

std::string Order::checkout()
{
	// Similar but slightly different to the toString function
	
	// String that stores the text to be outputted
	std::string output;

	output += "\n\n===== Checkout =====\n";

	// Iterates through all order items, then calls the to string function for the item and adds it to the output

	for (size_t i = 0; i < orderItems.size(); i++)
	{
		output += "(" + std::to_string(i + 1) + ") " + items[i]->toString();
	}

	output += "----------\n";

	// If a 241 discount is applicable, notify the user and adds the savings to the string
	if (twoForOne == true)
	{
		output += "2-4-1 discount applied! Savings: \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << savings).str() + " ";
	}

	// Adds their total to the string
	output += "Total: \x9C" + (std::ostringstream() << std::fixed << std::setprecision(2) << total).str() + "\n";

	// Adds dialogue to the string
	output += "\nDo you want to place your order?\nType 'y' to confirm, or 'n' to go back and modify it.\n\n";

	// Returning the string
	return output;

}

void Order::printReceipt()
{
	// Calls to string to get the string
	// Stores it in a text file called receipt.txt
	// See brief for specifics

	// Calling to string. Doing this instead of checkout as checkout includes additional changes
	std::string output = toString();

	std::ofstream out("receipt.txt");
	out << output;
	out.close();

	std::cout << "\nYour receipt has been successfully saved to file 'receipt.txt'!\n\n";
}
