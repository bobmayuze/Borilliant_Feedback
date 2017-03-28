#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

int main(int argc, char* argv[]) {
  std::string tmp;
  std::ifstream istr(argv[1]);
  std::map<int, int> num;
  int max;

  std::map<int, int>::iterator it;
  while(istr >> tmp) {
    it = num.find(atoi(tmp.c_str()));
    if (it == num.end()) num.insert(std::make_pair(atoi(tmp.c_str()), 1));
    else it->second ++;
  }

  if (num.size() != 0){
    it = num.begin();
    max = it->second;
    for (it = num.begin(); it != num.end(); ++it) {
      if (it->second > max) max = it->second;
    }
    for (it = num.begin(); it != num.end(); ++it) {
      if (it->second == max) std::cout << it->first << std::endl;
    }
  }
  return 0;
}
