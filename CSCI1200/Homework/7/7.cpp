#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

// Class: dna
// gen_ store the name of the query
// location_ store all locations of that query into a vector
// mismatch_ store all the mismatches between the genome and the query
// error_ store the allowed mismatch number of that query
class dna {
public:
  dna(std::string& gen, int error) : gen_(gen), error_(error) {}
  const std::string& get_gen() const { return gen_; }
  const std::vector<int>& get_loc() const { return location_; }
  const std::vector<int>& get_mis() const { return mismatch_; }
  unsigned int get_len() { return gen_.size(); }
  int get_err() const { return error_; }
  // When we find a new location, push it back to location vector
  void add_loc(int loc) { location_.push_back(loc); }
  // When we find a new location, push back the mismatch num to mismatch vector
  void add_mis(int mis) { mismatch_.push_back(mis); }
private:
  std::string gen_;
  std::vector<int> location_;
  std::vector<int> mismatch_;
  int error_;
};

// Helper function to store all the kmers and their locations into a map
// Whenever it get a kmer, push_back its location to that kmer's location vector
void get_kmer(std::string& file, std::map<std::string, std::vector<int> >& kmer,
  int klen) {
  std::string tmp;
  for (unsigned int i = 0; i < file.size() - klen + 1; ++i) {
    tmp = file.substr(i, klen);
    kmer[tmp].push_back(i);
  }
}

// VECTOR version
//
// Class: k_mer
// A simple class store the name of kmer and a vector of its locations
class k_mer {
public:
  k_mer(std::string& name, int loc);
  const std::string& get_name() const { return name_; }
  const std::vector<int>& get_loc() const { return location_; }
  void add_loc(int loc) { location_.push_back(loc); }
private:
  std::string name_;
  std::vector<int> location_;
};

// Constructer of k_mer
k_mer::k_mer(std::string& name, int loc) {
  name_ = name;
  location_.push_back(loc);
}

// VECTOR version
//
// Go through the kmer vector, when the kmer can't been found, add a new kmer_vec
// type and initialize its location vector with current location.
// When the kmer is found, push_back current location to that kmer.
void get_kmer_vec(std::string& file, std::vector<k_mer>& kmer_vec, int klen) {
  std::string tmp;
  for (unsigned int i = 0; i < file.size() - klen + 1; ++i) {
    tmp = file.substr(i, klen);
    bool find = false;
    for (unsigned int j = 0; j < kmer_vec.size(); ++j) {
      if (kmer_vec[j].get_name() == tmp) {
        kmer_vec[j].add_loc(i);
        find = true;
        break;
      }
    }
    if (!find) kmer_vec.push_back(k_mer(tmp, i));
  }
}

// MAP version
//
// The function find the match genome locations by iterator
bool find_loc(std::map<std::string, std::vector<int> >& kmer, dna& query,
  std::string& file, int klen) {
  bool found = false;
  // Create a temp head string as kmer
  std::string head = query.get_gen().substr(0, klen);
  std::map<std::string, std::vector<int> >::const_iterator it;
  it = kmer.find(head);
  // If the we find the kmer in the map, we check each location of that kmer
  // and its following alphabet to find the match genome
  if (it != kmer.end()) {
    int loc;
    for (unsigned int i = 0; i < it->second.size(); ++i) {
      bool find = true;
      loc = it->second[i];
      // An int mis to store the mismatch number
      // Whenever a mismatch is found, increment the mis. When the mis exceed
      // the error number, break the loop, check next possible genome
      int mis = 0;
      for (unsigned int j = klen; j < query.get_gen().size(); ++j) {
        if (file[loc + j] != query.get_gen()[j]) {
          mis++;
          if (mis > query.get_err()) {
            find = false;
            break;
          }
        }
      }
      // If we find a valid genome, add its loction to location vector, and add
      // its mismatch number to mismatch vector
      if (find) {
        query.add_loc(loc);
        query.add_mis(mis);
        found = true;
      }
    }
  }
  return found;
}

// VECTOR version
//
// The function find the match genome locations
bool find_loc_vec(std::vector<k_mer>& kmer_vec, dna& query, std::string& file,
  int klen) {
  bool found = false;
  // Create a temp head string as kmer
  std::string head = query.get_gen().substr(0, klen);
  for (unsigned int i = 0; i < kmer_vec.size(); ++i) {
    if (kmer_vec[i].get_name() == head) {
      // If the we find the kmer in the map, we check each location of that kmer
      // and its following alphabet to find the match genome
      int loc;
      for (unsigned int j = 0; j < kmer_vec[i].get_loc().size(); ++j) {
        bool find = true;
        loc = kmer_vec[i].get_loc()[j];
        // An int mis to store the mismatch number
        // Whenever a mismatch is found, increment the mis. When the mis exceed
        // the error number, break the loop, check next possible genome
        int mis = 0;
        for (unsigned int k = klen; k < query.get_gen().size(); ++k) {
          if (file[loc + k] != query.get_gen()[k]) {
            mis++;
            if (mis > query.get_err()) {
              find = false;
              break;
            }
          }
        }
        // If we find a valid genome, add its loction to location vector, and add
        // its mismatch number to mismatch vector
        if (find) {
          query.add_loc(loc);
          query.add_mis(mis);
          found = true;
        }
      }
      break;
    }
  }
  // If we can't find the kmer, just return false
  return found;
}

int main() {
  // Create a map kmer to store the kmer information
  // A vector kmer_vec to store the kmer information
  // A temp string to store the file content
  // Some temp string for std::cin
  // An int klen to store the length of kmer
  // An int error to store the allowed mismatch number
  // A boolean to decide which type to use
  std::map<std::string, std::vector<int> > kmer;
  std::vector<k_mer> kmer_vec;
  std::string file = "";
  std::string tmp;
  std::string qstr;
  std::string num;
  std::string head;
  int klen;
  int error;
  bool vec = false;

  // Read all the file content to file string
  std::cin >> tmp;
  std::cin >> tmp;
  std::ifstream istr(tmp.c_str());
  if (!istr) {
    std::cerr << "Couldn't open " << tmp << '\n';
    return 1;
  }
  while (istr >> tmp) file += tmp;

  // If the third string is vector, use vector type
  std::cin >> tmp;
  if (tmp == "vector") {
    vec = true;
    std::cin >> tmp;
  }

  // Store the length of kmer
  // Store all kmers information based on types
  std::cin >> tmp;
  klen = atoi(tmp.c_str());
  if (vec) get_kmer_vec(file, kmer_vec, klen);
  else get_kmer(file, kmer, klen);

  // MAP version
  std::cin >> tmp;
  if (!vec) {
    while (std::cin >> num >> qstr >> tmp) {
      // Store the allowed error number of that Query
      error = atoi(num.c_str());
      // Create a dna class to store the information of that query
      dna query(qstr, error);
      std::cout << "Query: " << qstr << std::endl;
      // Print all match genomes when any of them are found
      if (find_loc(kmer, query, file, klen)) {
        for (unsigned int i = 0; i < query.get_loc().size(); ++i) {
          std::cout << query.get_loc()[i] << " " << query.get_mis()[i] << " ";
          for (unsigned int j = 0; j < query.get_len(); ++j) {
            std::cout << file[query.get_loc()[i]+j];
          }
          std::cout << std::endl;
        }
      }
      // Or print a message when no genome is found
      else std::cout << "No Match" << std::endl;
      // End this program when a quit command is given
      if (tmp == "quit") return 0;
    }
  }
  // VECTOR version
  else {
    while (std::cin >> num >> qstr >> tmp) {
      // Store the allowed error number of that Query
      error = atoi(num.c_str());
      // Create a dna class to store the information of that query
      dna query(qstr, error);
      std::cout << "Query: " << qstr << std::endl;
      // Print all match genomes when any of them are found
      if (find_loc_vec(kmer_vec, query, file, klen)) {
        for (unsigned int i = 0; i < query.get_loc().size(); ++i) {
          std::cout << query.get_loc()[i] << " " << query.get_mis()[i] << " ";
          for (unsigned int j = 0; j < query.get_len(); ++j) {
            std::cout << file[query.get_loc()[i]+j];
          }
          std::cout << std::endl;
        }
      }
      // Or print a message when no genome is found
      else std::cout << "No Match" << std::endl;
      // Print all match genomes when any of them are found
      if (tmp == "quit") return 0;
    }
  }
  return 0;
}
