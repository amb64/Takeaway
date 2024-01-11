#include "Order.h"

// Constructor
Order::Order()
{
	// Variable initilisation
	savings = 0;
	total = 0;
}

// Destructor
Order::~Order()
{

}

// Cleanup function to clear memory
// Order destructor is called early, so this has to be a separate function
void Order::Cleanup()
{
	orderItems.clear();
	items.clear();
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
}

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
}

void Order::remove(Item* item)
{
	// Find the pointer in the vector using an iterator, and then remove it
	// We must go backwards through the vector because if we delete the first item found from the start, it will change the indexes
	// Basically we go from back to front to prevent issues if the user added multiple of the same item into their order
	auto it = std::find(orderItems.rbegin(), orderItems.rend(), item);
	auto foundItem = it.base() - 1;
	orderItems.erase(foundItem);

	// Will check for the 2 for 1 deal if the item being removed is an appetiser
	if (typeid(*item) == typeid(Appetiser))
	{
		checkTwoForOne();
	}

	// Calculates the new total
	calculateTotal();
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
	auto size = orderItems.size();
	for (size_t i = 0; i < size; i++) 
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
}

void Order::calculateSavings(Item* a1, Item* a2)
{
	// If a1s price is bigger, the savings is set to the price of that item. Else, the opposite occurs
	auto price1 = a1->getPrice();
	auto price2 = a2->getPrice();

	if (price1 > price2)
	{
		savings = price2;
	}
	else
	{
		savings = price1;
	}
}

std::string Order::toString()
{	
	// String that stores the text to be outputted
	std::string output;

	output += "\n===== Order =====\n";

	// Iterates through all order items, then calls the to string function for the item and adds it to the output
	auto size = orderItems.size();

	if (size == 0)
	{
		output += "Your order is currently empty!\nIf you add an item to your order, it will show up here.\n----------";
	}
	else
	{
		for (size_t i = 0; i < size; i++)
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
	auto size = orderItems.size();

	// Only if there are items in the order
	if (size > 0)
	{
		// Similar but slightly different to the toString function

		// String that stores the text to be outputted
		std::string output;

		output += "\n\n===== Checkout =====\n";

		// Iterates through all order items, then calls the to string function for the item and adds it to the output

		for (size_t i = 0; i < size; i++)
		{
			output += "(" + std::to_string(i + 1) + ") " + orderItems[i]->toString();
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
	// If the order is empty display a message
	else
	{
		return "\n\nYour order is currently empty!\nPlease type 'n' to cancel your order so you can add items to it.\n\n";
	}
}

void Order::printReceipt()
{
	// Doing this instead of the checkout function as checkout includes additional changes

	// The £ symbol wont display correctly in the receipt since the text file encoding is different
	std::ofstream out("receipt.txt");
	out << std::hex;
	out << toString();
	out.close();

	std::cout << "\nYour receipt has been successfully saved to file 'receipt.txt'!\n\n";
}
