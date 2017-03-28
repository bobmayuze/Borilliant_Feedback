//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <sstream>

#include "recipe.h"
#include "kitchen.h"
#include "ingredient.h"


// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);
void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  std::list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);
      
    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,recipes,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else if (c == 's') {
      // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE
      //   CURRENT CONTENTS OF THE KITCHEN
      recipeSuggestions(ostr,recipes,kitchen);

    } else if (c == 'd') {
      // EXTRA CREDIT: SUGGEST THE COLLECTION OF RECIPES THAT CAN BE
      // MADE TOGETHER THAT USE THE MAXIMUM NUMBER OF UNITS OF
      // INGREDIENTS
    } else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  
}

// This function read the recipe from input file.
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  int units;
  std::string name, name2;  
  istr >> name;

  // Check whether this recipe exists.
  bool find = false;
  std::list<Recipe>::iterator i = recipes.begin();
  for (; i != recipes.end(); ++i) {
    if ((*i).get_name() == name) {
      find = true;
      break;
    }
  }

  // Add the new recipe only when we haven't found it in existing list.
  if (!find) {
    // build the new recipe
    Recipe r(name);
    while (1) {
      istr >> units;
      if (units == 0) break;
      assert (units > 0);
      istr >> name2;
      r.addIngredient(name2,units);
    }
    // add it to the list
    recipes.push_back(r);
    ostr << "Recipe for " << name << " added" << std::endl;
  }

  // If the recipe has already existed, print a message, continues inputting until
  // we meet 0.
  else {
    ostr << "Recipe for " << name << " already exists" << std::endl;
    while (1) {
      istr >> units;
      if (units == 0) break;
      istr >> name;
    }
  }
}

// This function add ingredients to kitchen.
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  // Read the quantity and ingredient to be added.
  int units;
  std::string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }

  // If we only add one item to kitchen, use singular form, otherwise, plural.
  if (count == 1)
    ostr << "1 ingredient added to kitchen" << std::endl;
  else
    ostr << count << " ingredients added to kitchen" << std::endl;
}

// This function print the recipe.
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes) {
  // First check whether the target recipe is in the recipe list. As long as we
  // found it, sort its ingredients.
  std::string name;
  istr >> name;
  bool find = false;
  std::list<Ingredient> rcp_content;
  std::list<Recipe>::const_iterator i = recipes.begin();
  for (; i != recipes.end(); ++i) {
    if ((*i).get_name() == name) {
      find = true;
      rcp_content = (*i).get_ingredient();
      rcp_content.sort(rule2);
      break;
    }
  }

  // Print a message if no recipe was found.
  if (!find)
    ostr << "No recipe for " << name << std::endl;
  // Loop through the kitchen, print quantity and name for every ingredients
  // needed for the recipe. Distingush singular and plural quantities.
  else {
    ostr << "To make " << name << ", mix together:" << std::endl;
    std::list<Ingredient>::const_iterator j = rcp_content.begin();
    for (; j!= rcp_content.end(); ++j) {
      if ((*j).get_num() == 1)
        ostr << "  1 unit of " << (*j).get_name() << std::endl;
      else
        ostr << "  " << (*j).get_num() << " units of " << (*j).get_name() << std::endl;
    }
  }
}

// This function make a particular recipe and modify the quantity in kitchen.
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;
  istr >> name;
  bool find = false;      // Whether we find the recipe in recipe list.
  bool item_find = false; // Whether we find ingredient in the kitchen.
  bool sufficient = true; // Whether the quantity of ingredient is sufficient.
  bool header = false;    // Whether we have print the error message's header.
  std::list<Ingredient> rcp_content;
  std::list<Ingredient> kch_content = kitchen.get_item();
  std::list<Recipe>::const_iterator i = recipes.begin();

  // Find the recipe in recipe list.
  for (; i != recipes.end(); ++i) {
    if ((*i).get_name() == name) {
      find = true;
      rcp_content = (*i).get_ingredient();
      rcp_content.sort(rule2);
      break;
    }
  }
  // Print a message if we didn't find the recipe.
  if (!find)
    ostr << "Don't know how to make " << name << std::endl;
  // Check whether there are sufficient ingredients to make that recipe.
  else {
    std::list<Ingredient>::iterator j = rcp_content.begin();
    std::list<Ingredient>::iterator k = kch_content.begin();
    for (; j != rcp_content.end(); ++j) {
      item_find = false;
      for (; k != kch_content.end(); ++k) {
        if ((*j).get_name() == (*k).get_name()) {
          item_find = true;
          if ((*j).get_num() > (*k).get_num()) {

            // Print the header for error message, only once.
            // Print the following error message.
            if (!header) {
              ostr << "Cannot make " << name << ", need to buy:\n";
              header = true;
            }
            if ((*j).get_num() - (*k).get_num() == 1)
              ostr << "  1 unit of " << (*j).get_name() << std::endl;
            else
              ostr << "  " << ((*j).get_num() - (*k).get_num()) << " units of " << (*j).get_name() << std::endl;
            sufficient = false;
          }
          k = kch_content.begin();
          break; 
        }
      }
      if (!item_find){
        sufficient = false;
        // Print the header for error message, only once.
        // Print the following error message.
        if (!header) {
          ostr << "Cannot make " << name << ", need to buy:\n";
          header = true;
        }
        if ((*j).get_num() == 1)
          ostr << "  1 unit of " << (*j).get_name() << std::endl;
        else
          ostr << "  " << (*j).get_num() << " units of " << (*j).get_name() << std::endl;
        sufficient = false;
        // Set the iterator back to the beginning position for next loop.
        k = kch_content.begin();
      }
    }
    // If everything is sufficient, modify corresponding ingredients' quantities
    // and print a message.
    if (sufficient) {
      j = rcp_content.begin();
      for (;j != rcp_content.end(); ++j)
        kitchen.useIngredient((*j).get_name(), (*j).get_num());
      ostr << "Made " << name << std::endl; 
    }
  }
}

void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, const Kitchen &kitchen) {
  std::list<std::string> available;    // List to store all available recipes.
  std::list<std::string>::iterator p;
  std::list<Ingredient> rcp_content;
  std::list<Ingredient> kch_content = kitchen.get_item();
  std::list<Ingredient>::iterator j = kch_content.begin();
  std::list<Ingredient>::iterator k;
  std::list<Recipe>::const_iterator i = recipes.begin();

  bool find = false;    // Whether a ingredient is in kitchen.
  bool temp_available;  // Whether a ingredient is sufficient.
  for (; i != recipes.end(); ++i) {
    rcp_content = (*i).get_ingredient();
    k = rcp_content.begin();
    temp_available = true;

    // Check whether a ingredient is in kitchen and whether it is isufficient.
    for (; k != rcp_content.end(); ++k) {
      find = false;
      for (; j != kch_content.end(); ++j) {
        if ((*k).get_name() == (*j).get_name()) {
          find = true;
          if ((*k).get_num() > (*j).get_num()) {
            temp_available = false;
            break;
          }
        }
      }
      if (!find) {
        temp_available = false;
        j = kch_content.begin();
        break;
      }
      j = kch_content.begin();
    }
    // Store the recipe to list if all requirements are met.
    if (temp_available) 
      available.push_back((*i).get_name());
  }

  // The list has no recipes.
  if (available.size() == 0)
    ostr << "No recipes can be prepared" << std::endl;
  // Distinguish the singular and plural recipes.
  else if (available.size() == 1) {
    p = available.begin();
    ostr << "Recipe that can be prepared:\n  " << (*p) << std::endl;
  }
  // Print all recipes in alphabetical order.
  else {
    available.sort();
    ostr << "Recipes that can be prepared:" << std::endl;
    p = available.begin();
    for (; p != available.end(); ++p)
      ostr << "  " << (*p) << std::endl;  
  }
}
