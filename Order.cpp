#include "Order.h"

// Function that gets the private variable total.
float Order::getTotal()
{
	return total;
}

void Order::calculateTotal()
{
	// Using the private vector storing pointers to the items in the order,
	// Calculates the total while considering items eligible for a 2-4-1 discount (use the private bool for this)
	// Remember that they will only get the cheapest item free! (Will need to add to the csv so there is an appetiser with different price)
}

void Order::add(int itemNo)
{
	// Based on the item number given (will be from 1 instead of 0 like the list, so remember to -1!) will add to the order vector
	// If item is an appetiser, call checkTwoForOne() 
	// Then calls calculateTotal()
}

void Order::remove(int itemNo)
{
	// Same as order, but removes an item from the order vector
	// If the item is an appetiser, call checkTwoForOne()
	// Then calls calculateTotal()
}

// Is passing an Item here okay when they are pointers?
void Order::checkTwoForOne()
{
	// Checks through the list if there are 2 appetisers that are valid for 2-4-1
	// Store these temporarily
	// Then sets the bool to either true or false 
	// If true, calculate the savings (compare the price attribute, the smaller one is then considered the savings amount)
}

string Order::toString()
{
	// Outputs the order nice and pretty
	// Must include the total price, and the savings made
	// See brief for specifics

	return "";
}

void Order::printReceipt()
{
	// Calls to string to get the string
	// Stores it in a text file called receipt.txt
	// See brief for specifics
}
