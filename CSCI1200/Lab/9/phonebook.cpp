// A simple "caller ID" program

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED")
    cout << "unknown caller!" << endl;
  else
    cout << phonebook[number] << " is calling!" << endl;
}

void addmap(map<int, string>& pbmap, int num, string const& name) {
  pbmap[num] = name;
}

void idmap(const map<int, string>& pbmap, int num) {
  map<int, string>::const_iterator it;
  it = pbmap.find(num);
  if (it == pbmap.end()) cout << "Unknown" << endl;
  else cout << it->second << " is calling!" << endl;
}

int main() {
  map<int, string> pbmap;
  //
  // // create the phonebook; initially all numbers are unassigned
  // vector<string> phonebook(1000000, "UNASSIGNED");
  //
  // // add several names to the phonebook
  // add(phonebook, 1111, "fred");
  // add(phonebook, 2222, "sally");
  // add(phonebook, 3333, "george");
  // add(phonebook, 4444, "sam");
  //
  // // test the phonebook
  // identify(phonebook, 2222);
  // identify(phonebook, 4444);
  // identify(phonebook, 5555);

  // construct: N
  // memory used: N
  // add: n
  // 7 digit: 10 000 000
  // 10 digit: 10 000 000 000
  //
  addmap(pbmap, 1111, "fred");
  addmap(pbmap, 2222, "sally");
  addmap(pbmap, 3333, "george");
  addmap(pbmap, 4444, "sam");

  idmap(pbmap, 2222);
  idmap(pbmap, 4444);
  idmap(pbmap, 5555);

}
