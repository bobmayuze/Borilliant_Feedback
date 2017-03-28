// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"

void ProvidedTests();
void StudentTests();
void MyTest1();
void MyTest2();
void MyTest3();

// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false

template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename std::list<T>::const_iterator a_itr = a.begin();
  typename std::list<T>::const_iterator b_itr = b.begin();
  while (a_itr != a.end()) {
    if (*a_itr != *b_itr) return false;
    a_itr++;
    b_itr++;
  }
  return true;
}

// ================================================================================
// This program stress tests the templated MultiLL container class

int main() {
  ProvidedTests();
  StudentTests();
}

// ================================================================================
// ================================================================================

void ProvidedTests() {

  std::cout << "Begin ProvidedTests..." << std::endl;

  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();

  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());

  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));

  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<std::string> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));

  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));

  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));

  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "hound dog");
  itr = my_list.erase(itr);
  assert (*itr == "poker face");
  assert (my_list.size() == 9);
  std::cout << "erased: hound dog" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { itr++; }
  assert (*itr == "stairway to heaven");
  itr = my_list.erase(itr);
  assert (*itr == "walk like an egyptian");
  assert (my_list.size() == 8);
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  std::cout << "Finished ProvidedTests." << std::endl;
}

// ================================================================================
// ================================================================================

void StudentTests() {

  std::cout << "Begin StudentTests..." << std::endl;

  // ---------------------------
  // ADD YOUR OWN TEST CASES BELOW

  // be sure to test:
  //   copy constructor -> done!
  //   assignment operator -> done!
  //   destructor -> done!
  //   all corner cases of erase -> done!
  //   decrement operator for the chronological & sorted iterators -> done!
  //   pre vs. post increment & decrement operations for iterators -> done!
  //   MultiLL containing types other than std::string -> done!
  //   anything else that is necessary

  MyTest1();
  MyTest2();
  MyTest3();
  std::cout << "Finished StudentTests." << std::endl;
}

// ================================================================================
// This test case test copy constructor, assignment operator, destructor,
// decrement operator for the chronological & sorted iterators and
// pre vs. post increment & decrement operations for iterators

void MyTest1() {
  // The test data (stored in STL lists)
  // Musics are from billboard the hot 100 of the week of march 19, 2016
  std::list<std::string> songs;
  songs.push_back("Work");
  songs.push_back("Love Yourself");
  songs.push_back("Stressed Out");
  songs.push_back("My House");
  songs.push_back("Sorry");
  songs.push_back("Pillowtalk");
  songs.push_back("Me, Myself and I");
  songs.push_back("Piece By Piece");
  songs.push_back("Seven Years");
  songs.push_back("Cake By The Ocean");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();

  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());

  // -------------------
  // copy constructor test
  MultiLL<std::string> list_copy(my_list);

  // -------------------
  // assignment operator test
  MultiLL<std::string> list_assign = my_list;

  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  // use copied Lists and pre-increment
  std::cout << "chronological order forwards" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = list_copy.begin_chronological();
  while (itr != list_copy.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    ++itr;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));

  // test the chronological iterator (backwards)
  // use copied Lists and post-decrement
  std::cout << "chronological order backwards" << std::endl;
  itr = list_copy.end_chronological();
  while (itr != list_copy.begin_chronological()) {
    itr--;
    std::cout << "  " << *itr << std::endl;
  }
  std::cout << std::endl;

  // test the sorted order iterator (forwards)
  // use assigned list and post-increment
  std::cout << "sorted order forwards" << std::endl;
  std::list<std::string> sorted_order;
  itr = list_assign.begin_sorted();
  while (itr != list_assign.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));

  // test the sorted order iterator (backwards)
  // use assigned list and post-decrement
  std::cout << "sorted order backwards" << std::endl;
  itr = list_assign.end_sorted();
  while (itr != list_assign.begin_sorted()) {
    --itr;
    std::cout << "  " << *itr << std::endl;
  }
  std::cout << std::endl;

  // test the random order iterator
  // use post-increment
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));

  // test the re-randomization by creating a new random iterator
  // use pre-increment
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); ++i,++itr) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));

  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "Work");
  itr = my_list.erase(itr);
  assert (*itr == "Love Yourself");
  assert (my_list.size() == 9);
  std::cout << "erased: Work" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { itr++; }
  assert (*itr == "Sorry");
  itr = my_list.erase(itr);
  assert (*itr == "Stressed Out");
  assert (my_list.size() == 8);
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;
}

// ================================================================================
// This test case test MultiLL containing types other than std::string
void MyTest2() {
  // The test data (stored in STL lists)
  // type: float
  std::list<float> numbers;
  numbers.push_back(-9.87);
  numbers.push_back(9.87);
  numbers.push_back(-7.65);
  numbers.push_back(7.65);
  numbers.push_back(-5.43);
  numbers.push_back(5.43);
  numbers.push_back(-3.21);
  numbers.push_back(3.21);
  numbers.push_back(0);
  // the same data, sorted!
  std::list<float> sorted_numbers(numbers);
  sorted_numbers.sort();

  // create an empty multi-linked list and fill it with the test data
  MultiLL<float> my_list;
  for (std::list<float>::iterator itr = numbers.begin(); itr != numbers.end(); itr++) {
    my_list.add(*itr);
  }
  assert (numbers.size() == my_list.size());

  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<float> chrono_order;
  MultiLL<float>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(numbers,chrono_order));

  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<float> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_numbers,sorted_order));

  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<float> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<float>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<float> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_numbers,random_order_check));

  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<float> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));

  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  itr = my_list.erase(itr);
  assert (my_list.size() == 8);
  std::cout << "erased: -9.87" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 6; i++) { itr++; }
  itr = my_list.erase(itr);
  assert (my_list.size() == 7);
  std::cout << "erased: 5.43" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  float tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 6);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;
}

// ================================================================================
// This test case test all corner cases of erase
void MyTest3() {
  // -------------------
  // only one element
  std::list<std::string> songs1;
  songs1.push_back("hound dog");
  // the same data, sorted!
  MultiLL<std::string> my_list1;
  for (std::list<std::string>::iterator itr1 = songs1.begin(); itr1 != songs1.end(); itr1++) {
    my_list1.add(*itr1);
  }
  assert (songs1.size() == my_list1.size());
  MultiLL<std::string>::iterator itr1 = my_list1.begin_chronological();
  itr1 = my_list1.erase(itr1);
  assert (my_list1.size() == 0);
  std::cout << "erased: hound dog" << std::endl;
  my_list1.clear();
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  // -------------------
  // all the same elements
  std::list<std::string> songs2;
  songs2.push_back("hound dog");
  songs2.push_back("hound dog");
  // the same data, sorted!
  std::list<std::string> sorted_songs2(songs2);
  sorted_songs2.sort();
  MultiLL<std::string> my_list2;
  for (std::list<std::string>::iterator itr2 = songs2.begin(); itr2 != songs2.end(); itr2++) {
    my_list2.add(*itr2);
  }
  assert (songs2.size() == my_list2.size());
  MultiLL<std::string>::iterator itr2 = my_list2.begin_sorted();
  itr2 = my_list2.erase(itr2);
  assert (my_list2.size() == 1);
  assert (*itr2 == "hound dog");
  std::cout << "erased: hound dog" << std::endl;
  my_list2.clear();
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  // -------------------
  // erase the last element
  std::list<std::string> songs3;
  songs3.push_back("hound dog");
  songs3.push_back("poker face");
  songs3.push_back("brown eyed girl");
  // the same data, sorted!
  std::list<std::string> sorted_songs3(songs3);
  sorted_songs3.sort();
  MultiLL<std::string> my_list3;
  for (std::list<std::string>::iterator itr3 = songs3.begin(); itr3 != songs3.end(); itr3++) {
    my_list3.add(*itr3);
  }
  assert (songs3.size() == my_list3.size());
  MultiLL<std::string>::iterator itr3 = my_list3.end_chronological();
  itr3--; // point to the last element
  itr3 = my_list3.erase(itr3);
  assert (my_list3.size() == 2);
  std::cout << "erased: brown eyed girl" << std::endl;
  my_list3.clear();
  std::cout << "cleared the whole list!" << std::endl << std::endl;
}

// ================================================================================
