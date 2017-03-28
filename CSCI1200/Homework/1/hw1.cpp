// File: hw1.cpp
// This program simulates the algorithms that modify the borders between neighboring clusters of
// similarly colored pixels. The four operations are replace, diilation, erosion and floodfill.
// Auther: Ziniu Yu

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

// This function passes the file by reference and changes all certain characters to a different one.
// It goes through line by line and character by character, and change the character immediately as
// long as it is same as certain character.
void replace(std::vector<std::string> &file, char former, char later)
{
    for (unsigned int i = 0; i < file.size(); ++i)
    {
        for (unsigned int j = 0; j < file[i].size(); ++j)
        {
            if (file[i][j] == former)
                file[i][j] = later;
        }
    }
}

// This function passes the file by reference. It first store all the locations that need to be dilate
// and change them all at a time in the very end.
// If 1: Current character is same as given one; 2: The characters neighbor to current one are different
// the program then store the neighbors' locations to a vector called "change".
void dilation(std::vector<std::string> & file, char symbol)
{
    std::vector<int> change; // The int vector to store the locations need to be change
    for (unsigned int i = 0; i < file.size(); ++i)
    {
        for (unsigned int j = 0; j < file[i].size(); ++j)
        {
            if (i == 0) // The first line
            {
                if (j == 0) // Up left corner. Check the charactors right to it and below it.
                {
                    if (((file[i][j+1] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i); // First store the line number.
                        change.push_back(j); // Then the location in that line.
                    }
                }
                else if (j == file[i].size() - 1) // Up right corner. Check the charactors left to it and below it.
                {
                    if (((file[i][j-1] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Up boundary. Check the charactors left and right to it and below it.
                {
                    if (((file[i][j-1] == symbol) or (file[i][j+1] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else if (i == file.size() - 1) // The last line
            {
                if (j == 0) // Bottom left corner. Check the charactors right to it and above it.
                {
                    if (((file[i][j+1] == symbol) or (file[i-1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Bottom right corner. Check the charactors left to it and above it.
                {
                    if (((file[i][j-1] == symbol) or (file[i-1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Bottom boundary. Check the charactors left and right to it and above it.
                {
                    if (((file[i][j-1] == symbol) or (file[i][j+1] == symbol) or (file[i-1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else // Lines in the middle
            {
                if (j == 0) // Left boundary. Check the charactors above and below it and right to it.
                {
                    if (((file[i][j+1] == symbol) or (file[i-1][j] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Right boundary. Check the charactors above and below it and left to it.
                {
                    if (((file[i][j-1] == symbol) or (file[i-1][j] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Center. Check the charactors above and below it and left and right to it.
                {
                    if (((file[i][j-1] == symbol) or (file[i][j+1] == symbol) or (file[i-1][j] == symbol) or (file[i+1][j] == symbol)) and file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i < change.size(); i+=2)   // Read two values at a time, one for the line number
    {                                                   // and the other for the location in that line.
        file[change[i]][change[i+1]] = symbol;
    }
}

// This function passes the file by reference. It first store all the locations that need to be erase
// and change them all at a time in the very end.
// If 1: Current character is same as given one; 2: The characters neighbor to current one are different
// the program then store the current location to a vector called "change".
void erosion(std::vector<std::string> &file, char former, char later)
{
    std::vector<int> change; // The int vector to store the locations need to be change
    for (unsigned int i = 0; i < file.size(); ++i)
    {
        for (unsigned int j = 0; j < file[i].size(); ++j)
        {
            if (i == 0) // The first line
            {
                if (j == 0) // Up left corner. Check the charactors right to it and below it.
                {
                    if (((file[i][j+1] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Up right corner. Up right corner. Check the charactors left to it and below it.
                {
                    if (((file[i][j-1] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Up boundary. Check the charactors left and right to it and below it.
                {
                    if (((file[i][j-1] != former) or (file[i][j+1] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else if (i == file.size() - 1) // The last line
            {
                if (j == 0) // Bottom left corner. Check the charactors right to it and above it.
                {
                    if (((file[i][j+1] != former) or (file[i-1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Bottom right corner. Check the charactors left to it and above it.
                {
                    if (((file[i][j-1] != former) or (file[i-1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Bottom boundary. Check the charactors left and right to it and above it.
                {
                    if (((file[i][j-1] != former) or (file[i][j+1] != former) or (file[i-1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else // Lines in the middle
            {
                if (j == 0) // Left boundary. Check the charactors above and below it and right to it.
                {
                    if (((file[i][j+1] != former) or (file[i-1][j] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Right boundary. Check the charactors above and below it and left to it.
                {
                    if (((file[i][j-1] != former) or (file[i-1][j] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Center. Check the charactors above and below it and left and right to it.
                {
                    if (((file[i][j-1] != former) or (file[i][j+1] != former) or (file[i-1][j] != former) or (file[i+1][j] != former)) and file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i < change.size(); i+=2)   // Read two values at a time, one for the line number
    {                                                   // and the other for the location in that line.
        file[change[i]][change[i+1]] = later;
    }
}

// This function passes the file by reference. It is a recursion.
// It first change the current character (given charactor) to a certain one and then check the neighbor characters.
// If the neighbor charactors are same as given charactor, then set the location to the neighbor's location and
// call the function it self (recursion).
void floodfill(std::vector<std::string> &file, unsigned int x, unsigned int y, char former, char later)
{
    file[x][y] = later; // Change to certain charactor
    if (x == 0) // The first line
    {
        if (y == 0) // Up left corner. Check the charactors right to it and below it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
        else if (y == file[x].size() - 1) // Up right corner. Check the charactors left to it and below it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
        else // Up boundary. Check the charactors left and right to it and below it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
    }
    else if (x == file.size() - 1) // The last line
    {
        if (y == 0) // Bottom left corner. Check the charactors right to it and above it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
        }
        else if (y == file[x].size() - 1) // Bottom right corner. Check the charactors left to it and above it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
        }
        else // Bottom boundary. Check the charactors left and right to it and above it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
        }
    }
    else // Lines in the middle
    {
        if (y == 0) // Left boundary. Check the charactors above and below it and right to it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
        else if (y == file[x].size() - 1) // Right boundary. Check the charactors above and below it and left to it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
        else // Center. Check the charactors above and below it and left and right to it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later);
        }
    }
}

int main(int argc, char* argv[])
{
    std::ifstream file(argv[1]);
    std::vector<std::string> allstr;
    std::string line;
    while (file >> line)
    {
        allstr.push_back(line);
    }
    if (std::string(argv[3]) == std::string("replace"))
    {
        char former = std::string(argv[4])[0];
        char later = std::string(argv[5])[0];
        replace(allstr, former, later);
    }
    else if (std::string(argv[3]) == std::string("dilation"))
    {
        char symbol = std::string(argv[4])[0];
        dilation(allstr, symbol);
    }
    else if (std::string(argv[3]) == std::string("erosion"))
    {
        char former = std::string(argv[4])[0];
        char later = std::string(argv[5])[0];
        erosion(allstr, former, later);
    }
    else if (std::string(argv[3]) == std::string("floodfill"))
    {
        unsigned int x = atoi(std::string(argv[4]).c_str());
        unsigned int y = atoi(std::string(argv[5]).c_str());
        char former = allstr[x][y];
        char later = std::string(argv[6])[0];
        floodfill(allstr, x, y, former, later);
    }
    std::ofstream fileout(argv[2]);
    for (unsigned int i = 0; i < allstr.size(); ++i)
    {
        fileout << allstr[i] << std::endl;
    }
    fileout.close();
    return 0;
}