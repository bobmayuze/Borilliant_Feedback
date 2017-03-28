#include "ingredient.h"

// Sort the ingredients first by their quantities, then by their names.
bool rule1(Ingredient& item1, Ingredient& item2) {
	if (item1.get_num() < item2.get_num())
		return true;
	else if (item1.get_num() == item2.get_num())
		return item1.get_name() < item2.get_name();
	else
		return false;
}

// Sort the ingredients by their names.
bool rule2(Ingredient& item1, Ingredient& item2) {
	return item1.get_name() < item2.get_name();
}