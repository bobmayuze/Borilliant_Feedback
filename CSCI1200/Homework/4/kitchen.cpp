#include <list>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

#include "kitchen.h"

// This member function add ingredients to kitchen.
// If it found the ingredient already exist in the kitchen, modify its quantity.
// If not, add a new ingredient to kitchen and set its quantity to certain number.
void Kitchen::addIngredient(std::string& name, unsigned int num) {
	std::list<Ingredient>::iterator i = kch_item.begin();
	bool find = false;

	for (; i != kch_item.end(); ++i) {
		if ((*i).get_name() == name) {
			(*i).add_num(num);
			find = true;
			break;
		}
	}
	if (!find) kch_item.push_back(Ingredient(name, num));
}

// This member function reduce the quantity of some ingredients in kitchen.
// It first go through the list of kitchen, modify the quantity when find that
// ingredient and break the loop.
void Kitchen::useIngredient(const std::string& name, unsigned int num) {
	std::list<Ingredient>::iterator i = kch_item.begin();
	for (; i != kch_item.end(); ++i) {
		if ((*i).get_name() == name) {
			(*i).minus_num(num);
			break;
		}
	}
}

// This member function print all the ingredients in the kitchen by some order.
void Kitchen::printIngredients(std::ofstream& ostr) {
	ostr << "In the kitchen:\n";
	kch_item.sort(rule1);

	// Go through the list, print each ingredient's quantity and name.
	std::list<Ingredient>::iterator i = kch_item.begin();
	for (; i != kch_item.end(); ++i) {

		// If the quantities of any ingredient are 0, ignore them.
		// If the quantities of any ingredient are 1, use singular unit, otherwise units.
		if ((*i).get_num() != 0) {
			if ((*i).get_num() == 1)
				ostr << "  1 unit of " << (*i).get_name() << std::endl;
			else
				ostr << "  " << (*i).get_num() << " units of " << (*i).get_name() << std::endl;
		}
	}
}