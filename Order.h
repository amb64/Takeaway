#pragma once
#include "ItemList.h"
#include "Appetiser.h"
#include "Beverage.h"
#include "MainCourse.h"
#include "Menu.h"

class Order: public ItemList
{
public:
	Order();
	~Order();
	void Cleanup();

	void add(Item* item);
	void remove(Item* item);

	std::string checkout();
	void printReceipt();

	std::string toString();

	std::vector<Item*> getOrderItems();

private:
	void checkTwoForOne();
	void calculateTotal();
	void calculateSavings(Item* a1, Item* a2);

	std::vector<Item*> orderItems; // Vector that stores pointers to the items specifically added to the order
	
	bool twoForOne = false; // Preset to false
	double total; // Price of all items in the order
	double savings; // Amount of money the user has saved from 2-4-1 deal if applicable
};