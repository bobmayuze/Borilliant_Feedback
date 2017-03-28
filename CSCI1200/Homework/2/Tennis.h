// File: Tennis.h
// Author: Ziniu Yu

#include <string>
#include <iostream>
#include <vector>

#ifndef Tennis_h
#define Tennis_h

class Tennis
{
public:
    Tennis();
    
    // ACCESSORS
    const std::string& firstname() const { return fname; }
    const std::string& lastname() const { return lname; }
    int winround() const { return winround_; }
    int loseround() const { return loseround_; }
    int winmatch() const { return winmatch_; }
    int losematch() const { return losematch_; }
    int wintotal() const { return wintotal_; }
    int losetotal() const { return losetotal_; }
    double mpercent() const { return mpercent_; }
    double gpercent() const { return gpercent_; }
    double epercent() const { return epercent_; }
    double tpercent() const { return tpercent_; }
    double rpercent() const { return rpercent_; }
    
    // MODIFIERS
    // The detailed descriptions are in the implementation file.
    void setfirstname(std::string f_name);
    void setlastname(std::string l_name);
    void addwingame(std::vector<int> wingame);
    void addlosegame(std::vector<int> losegame);
    void addwintotal(int wintotal);
    void addlosetotal(int losetotal);
    void addwinround(int winround);
    void addloseround(int loseround);
    void win_increment();
    void lose_increment();
    void cal_easywin();
    void cal_toughwin();
    void cal_mpercent();
    void cal_gpercent();
    void cal_epercent();
    void cal_tpercent();
    void cal_rpercent();
    
private:
    std::string fname;              // First name.
    std::string lname;              // Last name.
    std::vector<int> wingame_;      // Vector stores the scores of player in each turn.
    std::vector<int> losegame_;     // Vector stores the scores of competitor in each turn.
    int winround_;                  // Count the number of win rounds.
    int loseround_;                 // Count the number of lose rounds.
    int winmatch_;                  // Count the number of win matches.
    int losematch_;                 // Count the number of lose matches.
    int wintotal_;                  // Count the number of win games.
    int losetotal_;                 // Count the number of lose games.
    int easywin_;                   // Count the number of easy win rounds.
    int toughwin_;                  // Count the number of tough win rounds.
    double mpercent_;               // The percent of win matches.
    double gpercent_;               // The percent of win games.
    double epercent_;               // The percent of easy win rounds.
    double tpercent_;               // The percent of tough win rounds.
    double rpercent_;               // The percent of win rounds.
};

bool matchrule(const Tennis& player1, const Tennis& player2);   // Determine orders by match percent.
bool gamerule(const Tennis& player1, const Tennis& player2);    // Determine orders by game percent.
bool roundrule(const Tennis& player1, const Tennis& player2);   // Determine orders by round percent.
#endif /* Tennis_h */
