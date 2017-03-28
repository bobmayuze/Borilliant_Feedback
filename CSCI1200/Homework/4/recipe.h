#include <list>
#include <string>
#include "ingredient.h"

#ifndef recipe_h
#define recipe_h

class Recipe {
public:
	Recipe(std::string the_name) : rcp_name(the_name), rcp_item() {}
	const std::string& get_name() const { return rcp_name; }
	const std::list<Ingredient>& get_ingredient() const { return rcp_item; }
	void addIngredient(std::string name, unsigned int num)
		{ rcp_item.push_back(Ingredient(name, num)); }
private:
	std::string rcp_name;
	std::list<Ingredient> rcp_item;
};

#endif /* recipe_h */