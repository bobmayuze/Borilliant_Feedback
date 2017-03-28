#include <string>

#ifndef ingredient_h
#define ingredient_h

class Ingredient {
public:
	Ingredient(std::string the_name, int the_num) : name(the_name), num(the_num) {}
	const std::string& get_name() const { return name; }
	unsigned int get_num() const { return num; }
	void add_num(unsigned int number) { num+= number; }
	void minus_num(unsigned int number) { num-= number; }
private:
	std::string name;
	unsigned int num;
};

bool rule1(Ingredient& item1, Ingredient& item2);
bool rule2(Ingredient& item1, Ingredient& item2);

#endif /* ingredient_h */