// File: hw2.cpp
// This program counts the win and lose number of matches, games and rounds, computes each type of percentages
// of tennis players and creates several tables to show the results.
// Author: Ziniu Yu

#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Tennis.h"

// Parses a string that represents a set (i.e., "6-3") by breaking the string into two substrings
// and converting those strings to integers, which are returned via call-by-reference parameters.
void parse_set(std::string &set, int &games_won, int &games_lost)
{
    int i = set.find('-');
    games_won =  atoi(set.substr(0, i).c_str());
    games_lost = atoi(set.substr(i + 1, set.size() - i - 1).c_str());
}

// This function pass the file string, the player vector and player name vector by reference to read
// information.
void read(std::vector<std::string>& allstr, std::vector<Tennis>& all_player, std::vector<std::string>& player_name)
{
    unsigned int i = 0;
    unsigned int len = allstr.size();
    while (i < len)
    {
        // First read the first name and last name for each player and store them in temporary strings.
        std::string player1_name;
        std::string player2_name;
        std::string f_name1 = allstr[i];
        std::string l_name1 = allstr[++i];
        std::string defeat = allstr[++i];
        std::string f_name2 = allstr[++i];
        std::string l_name2 = allstr[++i];
        std::string score;
        std::vector<int> left_score;
        std::vector<int> right_score;
        int lscore;
        int rscore;
        int lscore_sum = 0;
        int rscore_sum = 0;
        int left_win = 0;
        int right_win = 0;
        
        // Loop through the strings following the name strings, split them by dash, and store the former
        // to a temporary vector left_score, later to right_score. Compare two scores, then increment
        // player1's win number left_win or player2's win number right_win. Sum left and right scores up
        // and store the results to lscore_sum and rscore_sum to add towards the total win or lose number.
        // If one of the win number reaches 3, break the loop. Or if the following string does not contain
        // dash signs, just in case some player exit the match before ending because of injury or other
        // reasons.
        while (left_win < 3 && right_win < 3)
        {
            if (std::find(allstr[i+1].begin(), allstr[i+1].end(), '-') == allstr[i+1].end())
                break;
            score = allstr[++i];
            parse_set(score, lscore, rscore);
            if (lscore > rscore)
                left_win++;
            else
                right_win++;
            lscore_sum += lscore;
            rscore_sum += rscore;
            left_score.push_back(lscore);
            right_score.push_back(rscore);
        }
        
        // Concatenate first name and last name together and store them in player1/2_name. The program will
        // store them in to vector player_name latter to prevent the repeat creation of same player.
        player1_name = f_name1 + l_name1;
        player2_name = f_name2 + l_name2;
        
        // If player not found in player_name, create a new player and store the information into it.
        // If player found in player_name, modify that player's elements.
        // "player_name.size() == 0" is to prevent error when there is no element in player_name.
        if (player_name.size() == 0 || (std::find(player_name.begin(), player_name.end(), player1_name) == player_name.end()))
        {
            Tennis player1;
            player1.setfirstname(f_name1);
            player1.setlastname(l_name1);
            player1.addwingame(left_score);
            player1.addlosegame(right_score);
            player1.addwintotal(lscore_sum);
            player1.addlosetotal(rscore_sum);
            player1.addwinround(left_win);
            player1.addloseround(right_win);
            player1.win_increment();
            all_player.push_back(player1);
            player_name.push_back(player1_name);
        }
        else
        {
            int num1 = std::find(player_name.begin(), player_name.end(), player1_name) - player_name.begin();
            all_player[num1].addwingame(left_score);
            all_player[num1].addlosegame(right_score);
            all_player[num1].addwintotal(lscore_sum);
            all_player[num1].addlosetotal(rscore_sum);
            all_player[num1].addwinround(left_win);
            all_player[num1].addloseround(right_win);
            all_player[num1].win_increment();
            
        }
        if (std::find(player_name.begin(), player_name.end(), player2_name) == player_name.end())
        {
            Tennis player2;
            player2.setfirstname(f_name2);
            player2.setlastname(l_name2);
            player2.addwingame(right_score);
            player2.addlosegame(left_score);
            player2.addwintotal(rscore_sum);
            player2.addlosetotal(lscore_sum);
            player2.addwinround(right_win);
            player2.addloseround(left_win);
            player2.lose_increment();
            all_player.push_back(player2);
            player_name.push_back(player2_name);
        }
        else
        {
            int num2 = std::find(player_name.begin(), player_name.end(), player2_name) - player_name.begin();
            all_player[num2].addwingame(right_score);
            all_player[num2].addlosegame(left_score);
            all_player[num2].addwintotal(rscore_sum);
            all_player[num2].addlosetotal(lscore_sum);
            all_player[num2].addwinround(right_win);
            all_player[num2].addloseround(left_win);
            all_player[num2].lose_increment();
        }
        ++i;
    }
}

int main(int argc, char* argv[])
{
    // Open the input file and output file, check if they are opened correctly. Create a vector of Tennis class
    // to store all the player. Create a vector of string to store the player's name. Create a vector of string
    // to store the file content.
    std::ifstream in_str(argv[1]);
    std::ofstream out_str(argv[2]);
    std::vector<Tennis> allplayer;
    std::vector<std::string> player_name;
    std::vector<std::string> allstr;
    std::string line;
    if (!in_str.good())
    {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    if (!out_str.good())
    {
        std::cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    while (in_str >> line)
    {
        allstr.push_back(line);
    }
    read(allstr, allplayer, player_name);
    
    // Create max_length to store the size of longest name for formatting.
    // Create tmp_length to store the size of current player's name for comparing.
    // Calculate all percentages for all players.
    unsigned int max_length = 0;
    for (unsigned int i = 0; i < allplayer.size(); ++i)
    {
        unsigned int tmp_length;
        tmp_length = allplayer[i].firstname().size() + allplayer[i].lastname().size();
        max_length = std::max(max_length, tmp_length);
        allplayer[i].cal_easywin();
        allplayer[i].cal_toughwin();
        allplayer[i].cal_mpercent();
        allplayer[i].cal_gpercent();
        allplayer[i].cal_epercent();
        allplayer[i].cal_tpercent();
        allplayer[i].cal_rpercent();
    }
    max_length++;   // Increment the max_length because of the space inside name.
    
    // Create a header for first two tables.
    const std::string header1 = "Player" + std::string(max_length-6, ' ') + "    W    L   percentage\n";
    
    // Sort allplayer by win match percentage. Output the header and the table by certain format.
    std::sort(allplayer.begin(), allplayer.end(), matchrule);
    out_str << "MATCH STATISTICS\n" << header1;
    for (unsigned int i = 0; i < allplayer.size(); ++i)
    {
        // Create length to control the space after name.
        unsigned int length = allplayer[i].firstname().size() + allplayer[i].lastname().size() + 1;
        out_str << allplayer[i].firstname() << " " << allplayer[i].lastname() << std::string(max_length - length, ' ');
        out_str << std::setw(5) << allplayer[i].winmatch() << std::setw(5) << allplayer[i].losematch();
        out_str << std::setw(13) << std::fixed << std::setprecision(3) << allplayer[i].mpercent() << std::endl;
    }
    out_str << std::endl;
    
    // Sort allplayer by win game percentage. Output the header and the table by certain format.
    std::sort(allplayer.begin(), allplayer.end(), gamerule);
    out_str << "GAME STATISTICS\n" << header1;
    for (unsigned int i = 0; i < allplayer.size(); ++i)
    {
        unsigned int length = allplayer[i].firstname().size() + allplayer[i].lastname().size() + 1;
        out_str << allplayer[i].firstname() << " " << allplayer[i].lastname() << std::string(max_length - length, ' ');
        out_str << std::setw(5) << allplayer[i].wintotal() << std::setw(5) << allplayer[i].losetotal();
        out_str << std::setw(13) << std::fixed << std::setprecision(3) << allplayer[i].gpercent() << std::endl;
    }
    out_str << std::endl;
    
    // Create a different header for the third table.
    const std::string header2 = "Player" + std::string(max_length-6, ' ') +\
    "    W    L   percentage         easy        tough\n";
    
    // Sort allplayer by win game percentage. Output the header and the table by certain format.
    std::sort(allplayer.begin(), allplayer.end(), roundrule);
    out_str << "ROUND STATISTICS\n" << header2;
    for (unsigned int i = 0; i < allplayer.size(); ++i)
    {
        if (allplayer[i].rpercent() == 0.0)     // If the win round percent is 0, break the loop. Otherwise, the
            break;                              // easy or tough win percent will be nan (not a number) because 0/0.
        unsigned int length = allplayer[i].firstname().size() + allplayer[i].lastname().size() + 1;
        out_str << allplayer[i].firstname() << " " << allplayer[i].lastname() << std::string(max_length - length, ' ');
        out_str << std::setw(5) << allplayer[i].winround() << std::setw(5) << allplayer[i].loseround();
        out_str << std::setw(13) << std::fixed << std::setprecision(3) << allplayer[i].rpercent();
        out_str << std::setw(13) << std::fixed << std::setprecision(3) << allplayer[i].epercent();
        out_str << std::setw(13) << std::fixed << std::setprecision(3) << allplayer[i].tpercent() << std::endl;
    }
    
    out_str.close();
    return 0;
}