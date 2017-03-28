#include <unordered_set>
#include <unordered_map>
#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>

int main() {
  std::vector<char> vec = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m','Q','W','E','R','T','Y','U','I','O','P','A','S','D','G','H','J','K','L','Z','X','C','V','B','N','M'};
  std::list<std::string> istr;
  std::string temp;

  std::unordered_set<std::string> myset;
  while (std::cin >> temp) {
    std::string cur;
    for (unsigned int i = 0; i < temp.size(); ++i) {
      if (std::find(vec.begin(), vec.end(), temp[i]) != vec.end()) {
        cur += temp[i];
      }
    }
    myset.insert(cur);
    istr.push_back(cur);
  }
  
  std::cout << "size " << istr.size() << std::endl;
  std::cout << "size " << myset.size() << std::endl;
  for (std::unordered_set<std::string>::const_iterator itr = myset.begin(); itr!= myset.end(); itr++) {
    std::cout << *itr << std::endl;
  }
  
  return 0;
}