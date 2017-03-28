// File: Tennis.cpp
// Author: Ziniu Yu

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Tennis.h"

Tennis::Tennis()    // Default constructor.
{
    std::string fname;
    std::string lname;
    std::vector<int> wingame_;
    std::vector<int> losegame_;
    winround_ = 0;
    loseround_ = 0;
    winmatch_ = 0;
    losematch_ = 0;
    wintotal_ = 0;
    losetotal_ = 0;
    easywin_ = 0;
    toughwin_ = 0;
    mpercent_ = 0.0;
    gpercent_ = 0.0;
    epercent_ = 0.0;
    tpercent_ = 0.0;
    rpercent_ = 0.0;
}

// Set first name to certain string.
void Tennis::setfirstname(std::string f_name)
{
    fname = f_name;
}

// Set last name to certain string.
void Tennis::setlastname(std::string l_name)
{
    lname = l_name;
}

// Append the vector by scores won in each round.
void Tennis::addwingame(std::vector<int> wingame)
{
    for (unsigned int i = 0; i < wingame.size(); ++i)
        wingame_.push_back(wingame[i]);
}

// Append the vector by scores lost in each round.
void Tennis::addlosegame(std::vector<int> losegame)
{
    for (unsigned int i = 0; i < losegame.size(); ++i)
        losegame_.push_back(losegame[i]);
}

// Add the number of win rounds in each match.
void Tennis::addwinround(int winround)
{
    winround_ += winround;
}

// Add the number of lose rounds in each match.
void Tennis::addloseround(int loseround)
{
    loseround_ += loseround;
}

// Add the number of win games in each match.
void Tennis::addwintotal(int wintotal)
{
    wintotal_ += wintotal;
}

// Add the number of lose games in each match.
void Tennis::addlosetotal(int losetotal)
{
    losetotal_ += losetotal;
}

// Calculate the easy win number.
// If player wins the round by three or more scores, it count as one easy win.
void Tennis::cal_easywin()
{
    for (unsigned int i = 0; i < wingame_.size(); i++)
    {
        if (wingame_[i] - losegame_[i] > 2)
            easywin_ ++;
    }
}

// Calculate the tough win number.
// If player wins the round by two or less scores, it count as one tough win.
void Tennis::cal_toughwin()
{
    for (unsigned int i = 0; i < wingame_.size(); i++)
    {
        if (wingame_[i] > losegame_[i] && wingame_[i] - losegame_[i] <= 2)
            toughwin_ ++;
    }
}

// Calculate the win matches percent.
void Tennis::cal_mpercent()
{
    mpercent_ = double(winmatch_) / (winmatch_ + losematch_);
}

// Calculate the lose matches percent.
void Tennis::cal_gpercent()
{
    gpercent_ = double(wintotal_) / (wintotal_ + losetotal_);
}

// Calculate the easy win percent.
void Tennis::cal_epercent()
{
    epercent_ = double(easywin_) / winround_;
}

// Calculate the tough win percent.
void Tennis::cal_tpercent()
{
    tpercent_ = double(toughwin_) / winround_;
}

// Calculate the win rounds percent.
void Tennis::cal_rpercent()
{
    rpercent_ = double(winround_) / (winround_ + loseround_);
}

// Increment the win matches number.
void Tennis::win_increment()
{
    winmatch_ ++;
}

// Increment the lose matches number.
void Tennis::lose_increment()
{
    losematch_ ++;
}

// Determine players order by match percent.
// First determined by whoever has greater match percent.
// If two player have same match percent, then determined by last name and finally first name.
bool matchrule(const Tennis& player1, const Tennis& player2)
{
    if (player1.mpercent() > player2.mpercent())
        return true;
    else if (player1.mpercent() == player2.mpercent())
    {
        return player1.lastname() < player2.lastname() ||\
        (player1.lastname() == player2.lastname() && player1.firstname() < player2.firstname());
    }
    else
        return false;
}

// Determine players order by game percent.
// First determined by whoever has greater game percent.
// If two player have same game percent, then determined by last name and finally first name.
bool gamerule(const Tennis& player1, const Tennis& player2)
{
    if (player1.gpercent() > player2.gpercent())
        return true;
    else if (player1.gpercent() == player2.gpercent())
    {
        return player1.lastname() < player2.lastname() ||\
        (player1.lastname() == player2.lastname() && player1.firstname() < player2.firstname());
    }
    else
        return false;
}

// Determine players order by round percent.
// First determined by whoever has greater round percent.
// If two player have same round percent, then determined by last name and finally first name.
bool roundrule(const Tennis& player1, const Tennis& player2)
{
    if (player1.rpercent() > player2.rpercent())
        return true;
    else if (player1.rpercent() == player2.rpercent())
    {
        return player1.lastname() < player2.lastname() ||\
        (player1.lastname() == player2.lastname() && player1.firstname() < player2.firstname());
    }
    else
        return false;
}