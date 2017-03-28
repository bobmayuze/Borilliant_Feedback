#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include "Header.h"

// The biggest and the most important recursion function to find solutions.
bool find_solution(char** board, char** tmp_board, int row, int col, int* roc,
    int* coc, int* row_occupy, int* col_occupy, std::vector<battleship>& ship,
    std::vector<battleship>& used, std::vector<solution>& result, bool all_soln,
    std::vector<constraint>& cstr) {
  // End conditions.
  if (ship.size() == 0) {
    // Check whether we filled in all available locations.
    if (filled(tmp_board, row, col, row_occupy, col_occupy, roc, coc)) {
        bool unique = true;
        solution soln(tmp_board, row, col, row_occupy, col_occupy, used);
        // Check whether all constraints have been occupied by ships.
        // (Except for open water)
        if (check_cstr(cstr, tmp_board, row, col)) {
          for (unsigned int i = 0; i < result.size(); ++i) {
            // Check whether the most recent solution is same as any solutions
            // we already have.
            if (!not_same(soln.get_board(), result[i].get_board(), row, col)) {
              unique = false;
              break;
            }
          }
        }
        else return false;
        if (unique) result.push_back(soln);
    }
    else return false;
    // If we are required to find all solutions, do not end function, make it
    // keep searching.
    if (all_soln) return false;
    return true;
  }

  // Put ship from the longest to the shortest.
  used.push_back(battleship(ship[ship.size()-1].get_type()));
  ship.pop_back();

  //==================================================
  // Horizontal
  //==================================================
  for (int x = 0; x < row; ++x) {
    if (row_occupy[x] == 0) continue; // Skip that row if its capacity is 0
    for (int y = 0; y < col; ++y) {
      if (col_occupy[y] == 0) continue; // Skip that column if its capacity is 0
      int length = used[used.size()-1].get_len();
      // check_all is true only if check1 and check2 are true.
      // check1 check if there is enough available spaces to locate a ship.
      // check2 check if its perpendicular direction has enough spaces.
      bool check_all = false;
      bool check1 = true;
      bool check2 = true;
      if (y+length <= col && length <= row_occupy[x]) {
        for (int m = 0; m < length; ++m) {
          if (col_occupy[y+m] == 0) {
            check1 = false;
            break;
          }
        }
        if (check1) {
          for (int m = 0; m < length; ++m) {
            if (!available(loc(x, y+m), tmp_board, row, col)) {
              check2 = false;
              break;
            }
          }
        }
        // If the ship is ok to put on board, mark all locations occupied by it
        // with 'X'. Decrement row and column capacity.
        if (check1 && check2) {
          for (int m = 0; m < length; ++m) {
            tmp_board[x][y+m] = 'X';
            col_occupy[y+m]--;
          }
          row_occupy[x] -= length;
          used[used.size()-1].set_rot("horizontal"); // Set its direction.
          used[used.size()-1].set_loc(x,y); // Store its left most location.
          check_all = true;
        }
        // Recursively search for next available location.
        if (check_all && find_solution(board, tmp_board, row, col, roc, coc,
            row_occupy, col_occupy, ship, used, result, all_soln, cstr)) {
          return true;
        }
        // Recover game board only if the ship has been put on it.
        if (used[used.size()-1].get_rot() == "horizontal") {
          int m = used[used.size()-1].get_row();
          int n = used[used.size()-1].get_col();
          int length = used[used.size()-1].get_len();
          for (int k = 0; k < length; ++k) {
            tmp_board[m][n+k] = board[m][n+k];
            col_occupy[n+k]++;
          }
          used[used.size()-1].set_rot("");
          row_occupy[m] += length;
        }
      }
    }
  }
  //==================================================
  // Vertical
  //==================================================
  // If the ship's type is submarine, we skip the vertical searching, prevent
  // to get the repeating solutions.
  if  (used[used.size()-1].get_len() != 1) {
    for (int x = 0; x < row; ++x) {
      if (row_occupy[x] == 0) continue; // Skip that row if its capacity is 0
      for (int y = 0; y < col; ++y) {
        if (col_occupy[y] == 0) continue; // Skip that col if its capacity is 0
        // check_all is true only if check1 and check2 are true.
        // check1 check if there is enough available spaces to locate a ship.
        // check2 check if its perpendicular direction has enough spaces.
        bool check_all = false;
        bool check1 = true;
        bool check2 = true;
        int length = used[used.size()-1].get_len();
        if (x+length <= row && length <= col_occupy[y]) {
          for (int m = 0; m < length; ++m) {
            if (row_occupy[x+m] == 0) {
              check1 = false;
              break;
            }
          }
          if (check1) {
            for (int m = 0; m < length; ++m) {
              if (!available(loc(x+m, y), tmp_board, row, col)) {
                check2 = false;
                break;
              }
            }
          }
          // If the ship is ok to put on board, mark all locations occupied by
          // it with 'X'. Decrement row and column capacity.
          if (check1 && check2) {
            for (int m = 0; m < length; ++m) {
              tmp_board[x+m][y] = 'X';
              row_occupy[x+m]--;
            }
            col_occupy[y] -= length;
            used[used.size()-1].set_rot("vertical");
            used[used.size()-1].set_loc(x,y);
            check_all = true;
          }
          // Recursively search for next available location.
          if (check_all && find_solution(board, tmp_board, row, col, roc, coc,
              row_occupy, col_occupy, ship, used, result, all_soln, cstr)) {
            return true;
          }
          // Recover game board only if the ship has been put on it.
          if (used[used.size()-1].get_rot() == "vertical") {
            int m = used[used.size()-1].get_row();
            int n = used[used.size()-1].get_col();
            int length = used[used.size()-1].get_len();
            for (int k = 0; k < length; ++k) {
              tmp_board[m+k][n] = board[m+k][n];
              row_occupy[m+k]++;
            }
            used[used.size()-1].set_rot("");
            col_occupy[n] += length;
          }
        }
      }
    }
  }
  // Reset the ships have been used and have not been used.
  ship.push_back(battleship(used[used.size()-1].get_type()));
  used.pop_back();
  return false;
}

int main(int argc, char* argv[]) {
  if (argc != 2 && argc != 3) {
    std::cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Couldn't open " << argv[1] << '\n';
    return 1;
  }

  std::string tmp; // Store the input string.
  int row, col; // Row number and column number.
  bool found = false;
  bool all_soln = false;  // Whether we are going to find all solutions.
  std::vector<battleship> ship; // Store all ships.
  std::vector<battleship> used; // Store all used ships.
  std::vector<solution> result; // Store all solutions.
  std::vector<constraint> cstr; // Store all constraints.

  if (argc == 3) {
    if (std::string(argv[2]) == std::string("find_all_solutions")) {
      all_soln = true;
    }
    else std::cerr << "Unknown command\n";
  }

  // Store row and column number of board.
  istr >> tmp;
  if (tmp != "board") std::cerr << "Unknown command\n";
  istr >> tmp;
  row = atoi(tmp.c_str());
  istr >> tmp;
  col = atoi(tmp.c_str());
  // Store the number occupied by ship of each row and column twice. One for
  // output solutions, one for find solutions. Do some basic error checking.
  // If some row_occupy and col_occupy are unknown, set them to the maximum
  // possible value.
  istr >> tmp;
  if (tmp != "rows") std::cerr << "Unknown command\n";
  int roc[row], row_oc[row];
  for (int i = 0; i < row; ++i) {
    istr >> tmp;
    if (tmp == "?") {
      roc[i] = -1;
      row_oc[i] = col;
    }
    else {
      roc[i] = atoi(tmp.c_str());
      row_oc[i] = atoi(tmp.c_str());
    }
  }
  istr >> tmp;
  if (tmp != "cols") std::cerr << "Unknown command\n";
  int coc[col], col_oc[col];
  for (int i = 0; i < col; ++i) {
    istr >> tmp;
    if (tmp == "?") {
      coc[i] = -1;
      col_oc[i] = row;
    }
    else {
      coc[i] = atoi(tmp.c_str());
      col_oc[i] = atoi(tmp.c_str());
    }
  }
  // Store all ship information into a vector
  while (istr >> tmp) {
    if (tmp == "constraint") break;
    ship.push_back(battleship(tmp));
  }
  // Several temporary string to store the constraint information.
  std::string p;
  std::string q;
  std::string x;
  while (istr >> p >> q >> x) {
    cstr.push_back(constraint(loc(atoi(p.c_str()), atoi(q.c_str())), x));
    istr >> tmp;
  }
  // Sort all ships from the longest to the shortest for easy recursion
  std::sort(ship.begin(), ship.end(), rule);
  // Initialize two board with whitespace, one for attempting to put ship on it
  // The other for correct the wrong attempt
  char** bd = new char*[row];
  for (int i = 0; i < row; ++i) {
    bd[i] = new char[col];
    for (int j = 0; j < col; ++j) bd[i][j] = ' ';
  }
  char** tmp_bd = new char*[row];
  for (int i = 0; i < row; ++i) {
    tmp_bd[i] = new char[col];
    for (int j = 0; j < col; ++j) tmp_bd[i][j] = bd[i][j];
  }

  if (find_solution(bd, tmp_bd, row, col, roc, coc, row_oc, col_oc, ship,
      used, result, all_soln, cstr))
    found = true;

  // If no result has been found, print message, exit the program.
  if (result.size() == 0) {
    std::cout << "No solutions" << std::endl;
    return 0;
  }
  // Print the position of each ship
  for (unsigned int k = 0; k < result.size(); ++k)
    result[k].print_soln();
  // Print message for "find_all_solutions" command.
  if (all_soln)
    std::cout<< "Found " << result.size() << " solution(s)" << std::endl;

  for (int i = 0; i < row; ++i) delete[] bd[i];
  delete[] bd;
  for (int i = 0; i < row; ++i) delete[] tmp_bd[i];
  delete[] tmp_bd;
  return 0;
}
