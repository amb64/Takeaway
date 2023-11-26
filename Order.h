#pragma once
#include "ItemList.h"

class Order: public ItemList
{
public:
	Order();
	~Order();
	void calculateTotal();
	void printReceipt();
	void add(int itemNo);
	void remove(int itemNo);
	void checkTwoForOne();

	std::string toString();
	double getTotal();

private:
	std::vector<Item*> orderItems; // Vector that stores pointers to the items specifically added to the order
	bool twoForOne = false; // Preset to false
	double total; // Price of all items in the order
	double savings; // Amount of money the user has saved from 2-4-1 deal if applicable
};