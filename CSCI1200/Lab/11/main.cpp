#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

int main() {
  
  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!
  
  assert(set1.sanity_check());
  assert (set1.size() == 7);
  
  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));
  
  p = set1.find( "foo" );
  assert (p == set1.end());
  
  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");
  
  std::cout << "Here is the tree, printed sideways.\n"
  << "The indentation is proportional to the depth of the node\n"
  << "so that the value stored at the root is the only value printed\n"
  << "without indentation.  Also, for each node, the right subtree\n"
  << "can be found above where the node is printed and indented\n"
  << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  
  ds_set<std::string>::iterator itt;
  for ( itt = set1.begin(); itt != set1.end(); itt ++ ){
    std::cout << " print: " << * itt << std::endl;
  }
  
  
  std::string acc = "";
  set1.accumulate(acc);
  std::cout << "\naccumulate result: " << acc << std::endl << std::endl;;
  
  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  
  
  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);
  
  
  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);
  
  
  // Test the iterators!
  
  ds_set<int> set3;
  set3.insert(8);
  set3.insert(4);
  set3.insert(12);
  set3.insert(2);
  set3.insert(6);
  set3.insert(10);
  set3.insert(14);
  set3.insert(1);
  set3.insert(3);
  set3.insert(5);
  set3.insert(7);
  set3.insert(9);
  set3.insert(11);
  set3.insert(13);
  set3.insert(15);
  
  std::cout << "\nAfter inserting stuff:\n";
  set3.print_as_sideways_tree( std::cout );

  ds_set<int>::iterator it;
  for ( it = set3.begin(); it != set3.end(); it ++ ){
    std::cout << " print: " << * it << std::endl;
  }
  
  for ( it = set3.end(); it != set3.begin(); ){
    it --;
    std::cout << " decrement test: " << *it << std::endl;
  }
  
  int accumu = 0;
  set3.accumulate(accumu);
  
  std::cout << "accumulate result: " << accumu << std::endl;

  
  
  
  ds_set<int> set4;
  
  for ( int i = 1; i <= 10; i ++ ){
    set4.insert(i);
  }
  std::cout << "\nAfter inserting stuff:\n";
  set4.print_as_sideways_tree( std::cout );

  ds_set<int>::iterator itr;
  for ( itr = set4.begin(); itr != set4.end(); itr ++ ){
    std::cout << " print: " << * itr << std::endl;
  }
  
  
  itr = set4.end();
  for ( itr = set4.end(); itr != set4.begin(); ){
    itr --;
    std::cout << " decrement test: " << *itr << std::endl;
  }
  
  int accumulate = 0;
  set4.accumulate(accumulate);
  
  std::cout << "accumulate result: " << accumulate << std::endl;
  
  return 0;
}
