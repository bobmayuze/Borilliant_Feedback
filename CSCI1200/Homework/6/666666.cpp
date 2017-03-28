#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>

// Simple class to record the grid location.
class loc {
public:
  loc(int r=0, int c=0) : row_(r), col_(c) {}
  int getrow() const { return row_; }
  int getcol() const { return col_; }
private:
  int row_, col_;
};

bool operator==(const loc& lhs, const loc& rhs) {
  return lhs.getrow() == rhs.getrow() && lhs.getcol() == rhs.getcol();
}

// Check if a position or its adjacent cells has already been used for some ship
bool available(const loc& pos, char** board, int row, int col) {
  if (board[pos.getrow()][pos.getcol()] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][pos.getcol()] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][pos.getcol()] == ' ' &&
      board[pos.getrow()][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[pos.getrow()][std::min(pos.getcol()+1, col-1)] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][std::min(pos.getcol()+1, col-1)] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][std::min(pos.getcol()+1, col-1)] == ' ' )
    return true;
  return false;
}

class battleship {
public:
  battleship(std::string name);
  const std::string get_type() const { return type_; }
  const std::string get_rot() const { return rotation_; }
  int get_len() const { return length_; }
  int get_row() const { return x; }
  int get_col() const { return y; }

  void set_type(std::string name) { type_ = name; }
  void set_rot(std::string rot) { rotation_ = rot; }
  void set_len(int len) { length_ = len; }
  void set_loc(int row, int col) { x = row; y = col; }
  // void change_rot();
private:
  std::string type_;
  std::string rotation_;
  int length_;
  int x, y;
};

battleship::battleship(std::string name) {
  type_ = name;
  rotation_ = "";
  if (type_ == "submarine") length_ = 1;
  else if (type_ == "destroyer") length_ = 2;
  else if (type_ == "cruiser") length_ = 3;
  else if (type_ == "battleship") length_ = 4;
  else if (type_ == "carrier") length_ = 5;
  else if (type_ == "cargo") length_ = 6;
  else if (type_ == "tanker") length_ = 7;
  // If the ship is unknown, set its length to 8 temporarily
  else if (type_ == "unknown") length_ = 8;
}

// Exchange the rotation direction
// void battleship::change_rot() {
//   if (rotation_ == "horizontal") rotation_ = "vertical";
//   else if (rotation_ == "vertical") rotation_ = "horizontal";
// }

class solution {
public:
  solution(char** board, int row, int col, std::vector<battleship> ship);
  char** get_board() const { return board_; }
  int get_row() const { return row_; }
  int get_col() const { return col_; }
  const std::vector<battleship>& get_ship() const { return ship_; }
private:
  char** board_;
  int row_, col_;
  std::vector<battleship> ship_;
};

solution::solution(char** board, int row, int col, std::vector<battleship> ship) {
  board_ = new char*[row];
  for (int i = 0; i < row; ++i) {
    board_[i] = new char[col];
    for (int j = 0; j < col; ++j) {
      board_[i][j] = board[i][j];
    }
  }
  ship_ = ship;
  row_ = row;
  col_ = col;
}

bool not_same(const solution& soln1, const solution& soln2) {
  for (int i = 0; i < soln1.get_row(); ++i) {
    for (int j = 0; j < soln1.get_col(); ++j) {
      if (soln1.get_board()[i][j] != soln2.get_board()[i][j]) return true;
    }
  }
  return false;
}

bool filled(char** board, int row, int col, int* row_occupy, int* col_occupy) {
  for (int i = 0; i < row; ++i) {
    int count = 0;
    for (int j = 0; j < col; ++j) {
      if (board[i][j] != ' ') count++;
    }
    if (count != row_occupy[i]) {
      // std::cout<<"12121"<<std::endl;
      return false;
    }
  }
  for (int j = 0; j < col; ++j) {
    int count = 0;
    for (int i = 0; i < row; ++i) {
      if (board[i][j] != ' ') count++;
    }
    if (count != col_occupy[j]) {
      // std::cout<<"34343"<<std::endl;
      return false;
    }
  }
  return true;
}

bool rule(const battleship& ship1, const battleship& ship2) {
  return ship1.get_len() < ship2.get_len();
}

bool find_solution(char** board, char** tmp_board, int row, int col, int* roc, int* coc,
                   int* row_occupy, int* col_occupy, std::vector<battleship>& ship,
                   std::vector<battleship>& used, std::vector<solution>& result,
                   bool all_soln) {

  if (ship.size() == 0) {
    // std::cout<<"111"<<std::endl;
    if (filled(tmp_board, row, col, roc, coc)) {
      // std::cout<<"222"<<std::endl;
      bool unique = true;
      solution soln(tmp_board, row, col, used);
      for (unsigned int i = 0; i < result.size(); ++i) {
        if (!not_same(soln, result[i])) {
          unique = false;
          break;
        }
      }
      if (unique) {
        // std::cout<<"333"<<std::endl;
        result.push_back(soln);
      }
    }
    // result.push_back(tmp_board);
    if (all_soln) return false;
    return true;
  }

  // Put ship from the longest
  used.push_back(battleship(ship[ship.size()-1].get_type()));
  ship.pop_back();

  //////////////////////////////////////////////////
  //////////////////////////////////////////////////
  // Horizontal
  for (int x = 0; x < row; ++x) {
    if (row_occupy[x] == 0) continue; // Skip that row if its capacity is 0
    for (int y = 0; y < col; ++y) {
      if (col_occupy[y] == 0) continue; // Skip that column if its capacity is 0
      int length = used[used.size()-1].get_len();

      // check_all is true only if check1 and check2 are true
      // check1 check if there is enough spaces and available spaces to locate a ship
      // check2 check if its perpendicular direction has enough space
      bool check_all = false;
      bool check1 = true;
      bool check2 = true;

      // check1
      if (y+length <= col && length <= row_occupy[x]) {
        for (int m = 0; m < length; ++m) {
          if (col_occupy[y+m] == 0) {
            check1 = false;
            break;
          }
        }
        // for (int m = 0; m < length; ++m) {
        //   if (!available(loc(x, y+m), tmp_board, row, col)) {
        //     check1 = false;
        //     break;
        //   }
        // }
        // check2
        if (check1) {
          for (int m = 0; m < length; ++m) {
            if (!available(loc(x, y+m), tmp_board, row, col)) {
              check2 = false;
              break;
            }
          }
          // for (int m = 0; m < length; ++m) {
          //   if (col_occupy[y+m] == 0) {
          //     check2 = false;
          //     break;
          //   }
          // }
        }
        // put the ship on game board, mark its location with 'X'
        // decrement row and column capacity
        if (check1 && check2) {
          for (int m = 0; m < length; ++m) {
            tmp_board[x][y+m] = 'X';
            col_occupy[y+m]--;
          }
          row_occupy[x] -= length;
          if (used[used.size()-1].get_type() == "submarine") used[used.size()-1].set_rot("center");
          else used[used.size()-1].set_rot("horizontal"); // Set its direction
          used[used.size()-1].set_loc(x,y); // Store its left up most location
          check_all = true;
        }

        if (check_all && find_solution(board, tmp_board, row, col, roc, coc,
                                       row_occupy, col_occupy, ship, used, result, all_soln)) {
          return true;
        }
        // Recover game board only if the ship has been put on it
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
        else if (used[used.size()-1].get_rot() == "center") {
          int m = used[used.size()-1].get_row();
          int n = used[used.size()-1].get_col();
          tmp_board[m][n] = board[m][n];
          col_occupy[n]++;
          used[used.size()-1].set_rot("");
          row_occupy[m] ++;
        }
      }
    }
  }

  //////////////////////////////////////////////////
  //////////////////////////////////////////////////
  // Vertical
  if  (used[used.size()-1].get_type() != "submarine") {
    for (int x = 0; x < row; ++x) {
      if (row_occupy[x] == 0) continue;
      for (int y = 0; y < col; ++y) {
        if (col_occupy[y] == 0) continue;
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
          // for (int m = 0; m < length; ++m) {
          //   if (!available(loc(x+m, y), tmp_board, row, col)) {
          //     check1 = false;
          //     break;
          //   }
          // }
          if (check1) {
            for (int m = 0; m < length; ++m) {
              if (!available(loc(x+m, y), tmp_board, row, col)) {
                check2 = false;
                break;
              }
            }
            // for (int m = 0; m < length; ++m) {
            //   if (row_occupy[x+m] == 0) {
            //     check2 = false;
            //     break;
            //   }
            // }
          }
          if (check1 && check2) {
            for (int m = 0; m < length; ++m) {
              tmp_board[x+m][y] = 'X';
              row_occupy[x+m]--;
            }
            col_occupy[y] -= length;
            // if (used[used.size()-1].get_type() == "submarine") used[used.size()-1].set_rot("center");
            used[used.size()-1].set_rot("vertical");
            used[used.size()-1].set_loc(x,y);
            check_all = true;
          }

          if (check_all && find_solution(board, tmp_board, row, col, roc, coc,
                                         row_occupy, col_occupy, ship, used, result, all_soln)) {
            return true;
          }
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

  // reset the ships have been used and have not been used
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

  // tmp for input
  // row = row number; col = col number
  // used = all ships have been put on the board
  std::string tmp;
  int row, col;
  bool found = false;
  bool all_soln = false;
  std::vector<battleship> used;
  std::vector<solution> result;

  if (argc == 3) {
    if (std::string(argv[2]) == std::string("find_all_solutions")) {
      all_soln = true;
    }
    else std::cerr << "Unknown command\n";
  }

  // Store row and column number of board
  istr >> tmp;
  if (tmp != "board") std::cerr << "Unknown command\n";
  istr >> tmp;
  row = atoi(tmp.c_str());
  istr >> tmp;
  col = atoi(tmp.c_str());

  // Store the number occupy by ship of each row and column twice
  // One for output result, one for find the result
  // roc = row_occupy; coc = col_occupy
  istr >> tmp;
  if (tmp != "rows") std::cerr << "Unknown command\n";
  int roc[row], row_oc[row];
  for (int i = 0; i < row; ++i) {
    istr >> tmp;
    if (tmp == "?") {
      roc[i] = -1;
      row_oc[i] = -1;
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
      col_oc[i] = -1;
    }
    else {
      coc[i] = atoi(tmp.c_str());
      col_oc[i] = atoi(tmp.c_str());
    }
  }

  // Store all ship information into a vector
  std::vector<battleship> ship;
  while (istr >> tmp) {
    if (tmp == "constraint") break;
    ship.push_back(battleship(tmp));
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

  if (find_solution(bd, tmp_bd, row, col, roc, coc, row_oc, col_oc, ship, used, result, all_soln))
    found = true;

  // If no result has been found, print message
  if (result.size() == 0) {
    std::cout << "No solutions" << std::endl;
    return 0;
  }

  // Print the position of each ship
  for (unsigned int k = 0; k < result.size(); ++k) {

  std::cout << "Solution:" << std::endl;
  for (unsigned int i = 0; i <result[k].get_ship().size(); ++i) {
    std::cout << std::left << std::setw(10) << result[k].get_ship()[i].get_type();
    std::cout << ' ' << result[k].get_ship()[i].get_row() << ' ' << result[k].get_ship()[i].get_col();
    if (result[k].get_ship()[i].get_type() != "submarine")
      std::cout << ' ' << result[k].get_ship()[i].get_rot();
    std::cout << std::endl;
  }

  // Print the game board
  std::cout << '+' << std::string(col,'-') << '+' <<std::endl;
  for (int i = 0; i < row; ++i) {
    std::cout<< '|';
    for (int j = 0; j < col; ++j) std::cout << result[k].get_board()[i][j];
    std::cout<< '|' << roc[i]<< std::endl;
  }
  std::cout << '+' << std::string(col,'-') << '+' <<std::endl;
  std::cout << ' ';
  for (int i = 0; i < col; ++i) std::cout<< coc[i];
  std::cout<< ' ' << std::endl;
}
  std::cout<<"find "<<result.size()<<std::endl;

  for (int i = 0; i < row; ++i) delete[] bd[i];
  delete[] bd;
  for (int i = 0; i < row; ++i) delete[] tmp_bd[i];
  delete[] tmp_bd;

  return 0;
}
