#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <string>
#include <iostream>

class Superhero {
public:
  Superhero(const std::string& name, const std::string& identity, const std::string& power) :
  good_(true), name_(name), identity_(identity), power_(power) {}
  
  const std::string& getName() const { return name_; }
  const std::string& getPower() const { return power_; }
  bool isGood() const { return good_; }

  bool operator==(const Superhero& hero) { return name_ == hero.getName(); }
  bool operator==(const std::string& identity) { return identity_ == identity; }
  bool operator!=(const std::string& identity) { return identity_ != identity; }
  void operator-() {
    good_ = !good_;
  }
  
  
  const std::string& getTrueIdentity() const { return identity_; }
  
private:
  bool good_;
  
  std::string name_;
  std::string identity_;
  std::string power_;
};

std::ostream& operator<<(std::ostream& ostr, const Superhero& hero) {
  if (hero.isGood()) ostr << "Superhero ";
  else ostr << "SuperVillain ";
  ostr << hero.getName() << " has power " << hero.getPower() << std::endl;
  return ostr;
}

bool operator>(const Superhero& hero1, const Superhero& hero2) {
  if (hero1.getPower() == "Fire" && hero2.getPower() == "Wood") return true;
  else if (hero1.getPower() == "Wood" && hero2.getPower() == "Water") return true;
  else if (hero1.getPower() == "Water" && hero2.getPower() == "Fire") return true;
  else if (hero1.getPower() == "Invisible" && hero2.getPower() == "Laser") return true;
  else if (hero1.getPower() == "Laser" && hero2.getPower() == "Flexible") return true;
  else if (hero1.getPower() == "Flexible" && hero2.getPower() == "Flying") return true;
  else if (hero1.getPower() == "Flying" && hero2.getPower() == "Fire") return true;
  else if (hero1.getPower() == "Fire" && hero2.getPower() == "Invisible") return true;
  else if (hero1.getPower() == "Speed" && hero2.getPower() == "Flying") return true;
  else if (hero1.getPower() == "Wood" && hero2.getPower() == "Laser") return true;
  else return false;
}

#endif
