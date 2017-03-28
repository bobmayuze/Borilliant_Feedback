// File: hw1.cpp
// This program simulates the algorithms that modify the borders between neighboring clusters of
// similarly colored pixels. The four operations are replace, diilation, erosion && floodfill.
// Auther: Ziniu Yu

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

// This function passes the file by reference && changes all certain characters to a different one.
// It goes through line by line && character by character, && change the character immediately as
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
// && change them all at a time in the very end.
// If 1: Current character is same as given one; 2: The characters neighbor to current one are different
// the program then store the neighbors' locations to a vector called "change".
void dilation(std::vector<std::string> & file, char symbol, bool large)
{
    std::vector<int> change; // The int vector to store the locations need to be change
    for (unsigned int i = 0; i < file.size(); ++i)
    {
        for (unsigned int j = 0; j < file[i].size(); ++j)
        {
            if (i == 0) // The first line
            {
                if (j == 0) // Up left corner. Check the charactors right to it && below it.
                {
                    if ((file[i][j+1] == symbol || file[i+1][j] == symbol || (file[i+1][j+1] == symbol && large))\
                         && file[i][j] != symbol)
                    {
                        change.push_back(i); // First store the line number.
                        change.push_back(j); // Then the location in that line.
                    }
                }
                else if (j == file[i].size() - 1) // Up right corner. Check the charactors left to it && below it.
                {
                    if ((file[i][j-1] == symbol || file[i+1][j] == symbol || (file[i+1][j-1] == symbol && large))\
                         && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Up boundary. Check the charactors left && right to it && below it.
                {
                    if ((file[i][j-1] == symbol || file[i][j+1] == symbol || file[i+1][j] == symbol ||\
                         ((file[i+1][j-1] == symbol || file[i+1][j+1] == symbol) && large)) && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else if (i == file.size() - 1) // The last line
            {
                if (j == 0) // Bottom left corner. Check the charactors right to it && above it.
                {
                    if ((file[i][j+1] == symbol || file[i-1][j] == symbol || (file[i-1][j+1] == symbol && large))\
                         && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Bottom right corner. Check the charactors left to it && above it.
                {
                    if ((file[i][j-1] == symbol || file[i-1][j] == symbol || (file[i-1][j-1] == symbol && large))\
                         && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Bottom boundary. Check the charactors left && right to it && above it.
                {
                    if ((file[i][j-1] == symbol || file[i][j+1] == symbol || file[i-1][j] == symbol ||\
                         ((file[i-1][j-1] == symbol || file[i-1][j+1] == symbol) && large)) && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else // Lines in the middle
            {
                if (j == 0) // Left boundary. Check the charactors above && below it && right to it.
                {
                    if ((file[i][j+1] == symbol || file[i-1][j] == symbol || file[i+1][j] == symbol ||\
                         ((file[i-1][j+1] == symbol || file[i+1][j+1] == symbol) && large)) && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Right boundary. Check the charactors above && below it && left to it.
                {
                    if ((file[i][j-1] == symbol || file[i-1][j] == symbol || file[i+1][j] == symbol ||\
                         ((file[i-1][j-1] == symbol || file[i+1][j-1] == symbol) && large)) && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Center. Check the charactors above && below it && left && right to it.
                {
                    if ((file[i][j-1] == symbol || file[i][j+1] == symbol || file[i-1][j] == symbol || file[i+1][j] == symbol\
                         || ((file[i-1][j-1] == symbol || file[i-1][j+1] == symbol || file[i+1][j-1] == symbol ||\
                             file[i+1][j+1] == symbol) && large)) && file[i][j] != symbol)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i < change.size(); i+=2)   // Read two values at a time, one for the line number
    {                                                   // && the other for the location in that line.
        file[change[i]][change[i+1]] = symbol;
    }
}

// This function passes the file by reference. It first store all the locations that need to be erase
// && change them all at a time in the very end.
// If 1: Current character is same as given one; 2: The characters neighbor to current one are different
// the program then store the current location to a vector called "change".
void erosion(std::vector<std::string> &file, char former, char later, bool large)
{
    std::vector<int> change; // The int vector to store the locations need to be change
    for (unsigned int i = 0; i < file.size(); ++i)
    {
        for (unsigned int j = 0; j < file[i].size(); ++j)
        {
            if (i == 0) // The first line
            {
                if (j == 0) // Up left corner. Check the charactors right to it && below it.
                {
                    if ((file[i][j+1] != former || file[i+1][j] != former || (file[i+1][j+1] != former && large))\
                         && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Up right corner. Up right corner. Check the charactors left to it && below it.
                {
                    if ((file[i][j-1] != former || file[i+1][j] != former || (file[i+1][j-1] != former && large))\
                        && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Up boundary. Check the charactors left && right to it && below it.
                {
                    if ((file[i][j-1] != former || file[i][j+1] != former || file[i+1][j] != former ||\
                         ((file[i+1][j-1] != former || file[i+1][j+1] != former) && large)) && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
            }
            else if (i == file.size() - 1) // The last line
            {
                if (j == 0) // Bottom left corner. Check the charactors right to it && above it.
                {
                    if ((file[i][j+1] != former || file[i-1][j] != former || (file[i-1][j+1] != former && large))\
                        && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Bottom right corner. Check the charactors left to it && above it.
                {
                    if ((file[i][j-1] != former || file[i-1][j] != former || (file[i-1][j-1] != former && large))\
                        && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Bottom boundary. Check the charactors left and right to it and above it.
                {
                    if ((file[i][j-1] != former || file[i][j+1] != former || file[i-1][j] != former ||\
                         ((file[i-1][j-1] != former && file[i-1][j+1] != former) && large)) && file[i][j] == former)
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
                    if ((file[i][j+1] != former || file[i-1][j] != former || file[i+1][j] != former ||\
                         ((file[i-1][j+1] != former || file[i+1][j+1] != former) && large)) && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else if (j == file[i].size() - 1) // Right boundary. Check the charactors above and below it and left to it.
                {
                    if ((file[i][j-1] != former || file[i-1][j] != former || file[i+1][j] != former ||\
                         ((file[i-1][j-1] != former || file[i+1][j-1] != former) && large)) && file[i][j] == former)
                    {
                        change.push_back(i);
                        change.push_back(j);
                    }
                }
                else // Center. Check the charactors above and below it and left and right to it.
                {
                    if ((file[i][j-1] != former || file[i][j+1] != former || file[i-1][j] != former || file[i+1][j] != former\
                         || ((file[i-1][j-1] != former || file[i-1][j+1] != former || file[i+1][j-1] != former ||\
                              file[i+1][j+1] != former) && large)) && file[i][j] == former)
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
void floodfill(std::vector<std::string> &file, unsigned int x, unsigned int y, char former, char later, bool large)
{
    file[x][y] = later; // Change to certain charactor
    if (x == 0) // The first line
    {
        if (y == 0) // Up left corner. Check the charactors right to it and below it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x+1][y+1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
        }
        else if (y == file[x].size() - 1) // Up right corner. Check the charactors left to it and below it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x+1][y-1] == former && large)
                floodfill(file, x+1, y-1, former, later, large);
        }
        else // Up boundary. Check the charactors left and right to it and below it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x+1][y-1] == former && large)
                floodfill(file, x+1, y-1, former, later, large);
            if (file[x+1][y+1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
        }
    }
    else if (x == file.size() - 1) // The last line
    {
        if (y == 0) // Bottom left corner. Check the charactors right to it and above it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x-1][y+1] == former && large)
                floodfill(file, x-1, y+1, former, later, large);
        }
        else if (y == file[x].size() - 1) // Bottom right corner. Check the charactors left to it and above it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x-1][y-1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
        }
        else // Bottom boundary. Check the charactors left and right to it and above it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x-1][y+1] == former && large)
                floodfill(file, x-1, y+1, former, later, large);
            if (file[x-1][y-1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
        }
    }
    else // Lines in the middle
    {
        if (y == 0) // Left boundary. Check the charactors above and below it and right to it.
        {
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x-1][y+1] == former && large)
                floodfill(file, x-1, y+1, former, later, large);
            if (file[x+1][y+1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
        }
        else if (y == file[x].size() - 1) // Right boundary. Check the charactors above and below it and left to it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x-1][y-1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
            if (file[x+1][y-1] == former && large)
                floodfill(file, x+1, y-1, former, later, large);
        }
        else // Center. Check the charactors above and below it and left and right to it.
        {
            if (file[x][y-1] == former)
                floodfill(file, x, y-1, former, later, large);
            if (file[x][y+1] == former)
                floodfill(file, x, y+1, former, later, large);
            if (file[x-1][y] == former)
                floodfill(file, x-1, y, former, later, large);
            if (file[x+1][y] == former)
                floodfill(file, x+1, y, former, later, large);
            if (file[x-1][y+1] == former && large)
                floodfill(file, x-1, y+1, former, later, large);
            if (file[x+1][y+1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
            if (file[x-1][y-1] == former && large)
                floodfill(file, x+1, y+1, former, later, large);
            if (file[x+1][y-1] == former && large)
                floodfill(file, x+1, y-1, former, later, large);
        }
    }
}

// Main function here.
int main(int argc, char* argv[])
{
    std::ifstream file(argv[1]);
    std::vector<std::string> allstr;
    std::string line;
    if (!file.good())
    {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    bool large = false;
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
        if (std::string(argv[argc-1]) == std::string("large"))  // check if the last argument is "large"
            large = true;
        char symbol = std::string(argv[4])[0];
        dilation(allstr, symbol, large);
    }
    else if (std::string(argv[3]) == std::string("erosion"))
    {
        if (std::string(argv[argc-1]) == std::string("large"))  // check if the last argument is "large"
            large = true;
        char former = std::string(argv[4])[0];
        char later = std::string(argv[5])[0];
        erosion(allstr, former, later, large);
    }
    else if (std::string(argv[3]) == std::string("floodfill"))
    {
        if (std::string(argv[argc-1]) == std::string("large"))  // check if the last argument is "large"
            large = true;
        unsigned int x = atoi(std::string(argv[4]).c_str());    // set start point x coordinate
        unsigned int y = atoi(std::string(argv[5]).c_str());    // set start point y coordinate
        char former = allstr[x][y];                             // find character to be changed
        char later = std::string(argv[6])[0];                   // find character to be changed to
        floodfill(allstr, x, y, former, later, large);
    }
    std::ofstream fileout(argv[2]);
    for (unsigned int i = 0; i < allstr.size(); ++i)
    {
        fileout << allstr[i] << std::endl;
    }
    fileout.close();
    return 0;
}