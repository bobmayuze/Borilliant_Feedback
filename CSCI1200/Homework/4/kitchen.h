#include <list>
#include <string>
#include "ingredient.h"

#ifndef kitchen_h
#define kitchen_h

class Kitchen {
public:
	Kitchen() : kch_item() {}
	const std::list<Ingredient>& get_item() const { return kch_item; }
	void addIngredient(std::string& name, unsigned int num);
	void useIngredient(const std::string& name, unsigned int num);
	void printIngredients(std::ofstream& ostr);
private:
	std::list<Ingredient> kch_item;
};

#endif /* kitchen_h */