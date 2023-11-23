#pragma once
#include "ItemList.h"
#include <cstring>

class Order: public ItemList
{
public:
	Order();
	void calculateTotal();
	void printReceipt();
	void add(int itemNo);
	void remove(int itemNo);
	void checkTwoForOne();

	string toString();
	float getTotal();

private:
	vector<Item*> orderItems; // Vector that stores pointers to the items specifically added to the order
	bool twoForOne = false; // Preset to false
	float total; // Price of all items in the order
	float savings; // Amount of money the user has saved from 2-4-1 deal if applicable
};