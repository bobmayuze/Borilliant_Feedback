#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

// Simple class to record the grid location.
class loc {
public:
  loc(int r=0, int c=0) : row_(r), col_(c) {}
  int getrow() const { return row_; }
  int getcol() const { return col_; }
private:
  int row_, col_;
};

bool operator== (const loc& lhs, const loc& rhs) {
  return lhs.getrow() == rhs.getrow() && lhs.getcol() == rhs.getcol();
}

// Check if a position or its adjacent cells has already been used for some ship
bool available(loc pos, char** board, int row, int col) {
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
  void change_rot();
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
void battleship::change_rot() {
  if (rotation_ == "horizontal") rotation_ = "vertical";
  else if (rotation_ == "vertical") rotation_ = "horizontal";
}

bool rule(const battleship& ship1, const battleship& ship2) {
  return ship1.get_len() < ship2.get_len();
}

bool find_solution(int r, int c, char** board, char** tmp_board, int row, int col,
                   int* row_occupied, int* col_occupied, std::vector<battleship>& ship,
                   std::vector<battleship>& used, std::vector<char**>& result,
                   bool all_soln) {
  std::cout << r<< ' ' <<c<<std::endl;
  
  if (ship.size() == 0) {
    // bool finish = true;
    // delete some codes here
    result.push_back(tmp_board);
    std::cout<<'0'<<std::endl;
    if (all_soln) {
      if (used[used.size()-1].get_rot() == "horizontal") {
        int m = used[used.size()-1].get_row();
        int n = used[used.size()-1].get_col();
        int length = used[used.size()-1].get_len();
        for (int k = 0; k < length; ++k) {
          tmp_board[m][n+k] = board[m][n+k];
          col_occupied[n+k]++;
        }
        row_occupied[m] += length;
        std::cout<<"Hout ";
      }
      else if (used[used.size()-1].get_rot() == "vertical") {
        int m = used[used.size()-1].get_row();
        int n = used[used.size()-1].get_col();
        int length = used[used.size()-1].get_len();
        for (int k = 0; k < length; ++k) {
          tmp_board[m+k][n] = board[m+k][n];
          row_occupied[m+k]++;
        }
        col_occupied[n] += length;
        std::cout<<"Vout ";
      }
      // std::cout<<"388"<<std::endl;
      std::cout<<used[used.size()-1].get_type();
      std::cout<<used[used.size()-1].get_row()<<' '<<used[used.size()-1].get_col()<<std::endl;
      ship.push_back(battleship(used[used.size()-1].get_type()));
      std::cout<<'4'<<std::endl;
      used.pop_back();
      std::cout<<'5'<<std::endl;
      return false;
    }
    return true;
  }
  
  // // Put ship from the longest
  // std::cout<<"                  ship"<<std::endl;
  // std::cout<<ship[ship.size()-1].get_type()<<std::endl;
  // // std::sort(ship.begin(), ship.end(), rule);
  // used.push_back(battleship(ship[ship.size()-1].get_type()));
  // ship.pop_back();
  // // std::sort(used.begin(), used.end(), rule);
  // std::cout<<"=="<<std::endl;
  //////////////////////////////////////////////////
  //////////////////////////////////////////////////
  // Horizontal
  if (ship.size() != 0) {
    // Put ship from the longest
    std::cout<<"                  ship"<<std::endl;
    std::cout<<ship[ship.size()-1].get_type()<<std::endl;
    // std::sort(ship.begin(), ship.end(), rule);
    used.push_back(battleship(ship[ship.size()-1].get_type()));
    ship.pop_back();
    // std::sort(used.begin(), used.end(), rule);
    std::cout<<"=="<<std::endl;
    
    for (int x = 0; x < row; ++x) {
      if (row_occupied[x] == 0) continue; // Skip that row if its capacity is 0
      for (int y = 0; y < col; ++y) {
        if (col_occupied[y] == 0) continue; // Skip that column if its capacity is 0
        int length = used[used.size()-1].get_len();
        
        // check_all is true only if check1 and check2 are true
        bool check_all = false;
        // check1 check if there is enough spaces and available spaces to locate a ship
        bool check1 = true;
        // check2 check if its perpendicular direction has enough space
        bool check2 = true;
        
        // check1
        if (y+length <= col && length <= row_occupied[x]) {
          for (int m = 0; m < length; ++m) {
            if (!available(loc(x, y+m), tmp_board, row, col)) {
              check1 = false;
              break;
            }
          }
          // check2
          if (check1) {
            // std::cout<<x << ' ' << y <<" h ck 1"<<std::endl;
            for (int m = 0; m < length; ++m) {
              if (col_occupied[y+m] == 0) {
                check2 = false;
                break;
              }
            }
          }
          // put the ship on game board, mark its location with 'X'
          // decrement row and column capacity
          if (check1 && check2) {
            for (int m = 0; m < length; ++m) {
              tmp_board[x][y+m] = 'X';
              col_occupied[y+m]--;
            }
            row_occupied[x] -= length;
            used[used.size()-1].set_rot("horizontal"); // Set its direction
            used[used.size()-1].set_loc(x,y); // Store its left up most location
            std::cout<<"put Horizontal ";
            std::cout<<used[used.size()-1].get_type();
            std::cout << x << ' ' << y << std::endl;
            check_all = true;
          }
          // }
          if (check_all && find_solution(x, y, board, tmp_board, row, col,
                                         row_occupied, col_occupied, ship, used, result, all_soln)) {
            return true;
          }
        }
      }
      // Recover game board only if the ship has been put on it
      if (used[used.size()-1].get_rot() == "horizontal") {
        int m = used[used.size()-1].get_row();
        int n = used[used.size()-1].get_col();
        int length = used[used.size()-1].get_len();
        for (int k = 0; k < length; ++k) {
          tmp_board[m][n+k] = board[m][n+k];
          col_occupied[n+k]++;
        }
        row_occupied[m] += length;
        std::cout<< "out-h ";
        std::cout<<used[used.size()-1].get_type()<<std::endl;
      }
      ship.push_back(battleship(used[used.size()-1].get_type()));
      used.pop_back();
      return false;
    }
  }
  
  if (ship.size() != 0) {
    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    // Vertical
    for (int x = 0; x < row; ++x) {
      // std::cout<<"   x "<<x<<std::endl;
      if (row_occupied[x] == 0) continue;
      for (int y = 0; y < col; ++y) {
        // std::cout<<"   y "<<y<<std::endl;
        if (col_occupied[y] == 0) continue;
        // std::cout<<"1"<<std::endl;
        bool check_all = false;
        // std::cout<<"2"<<std::endl;
        bool check1 = true;
        // std::cout<<"3"<<std::endl;
        bool check2 = true;
        // std::cout<<"4"<<std::endl;
        int length = used[used.size()-1].get_len();
        // std::cout<<"5"<<std::endl;
        if (x+length <= row && length <= col_occupied[y]) {
          for (int m = 0; m < length; ++m) {
            if (!available(loc(x+m, y), tmp_board, row, col)) {
              check1 = false;
              break;
            }
          }
          // std::cout<<"6"<<std::endl;
          if (check1) {
            // std::cout<<x<<' ' << y << " v ck 1"<<std::endl;
            for (int m = 0; m < length; ++m) {
              if (row_occupied[x+m] == 0) {
                check2 = false;
                break;
              }
            }
          }
          // std::cout<<"7"<<std::endl;
          if (check1 && check2) {
            for (int m = 0; m < length; ++m) {
              tmp_board[x+m][y] = 'X';
              row_occupied[x+m]--;
            }
            col_occupied[y] -= length;
            used[used.size()-1].set_rot("vertical");
            used[used.size()-1].set_loc(x,y);
            std::cout <<"put vertical ";
            std::cout<<used[used.size()-1].get_type();
            std::cout << x << ' ' << y << std::endl;
            check_all = true;
          }
          // std::cout<<"8"<<std::endl;
          // }
          // std::cout<<x<< ' '<<y<<" 9"<<std::endl;
          if (check_all && find_solution(x, y, board, tmp_board, row, col,
                                         row_occupied, col_occupied, ship, used, result, all_soln)) {
            return true;
          }
        }
        // std::cout<<x<< ' '<<y<<" 10"<<std::endl;
      }
      if (used[used.size()-1].get_rot() == "vertical") {
        int m = used[used.size()-1].get_row();
        int n = used[used.size()-1].get_col();
        int length = used[used.size()-1].get_len();
        for (int k = 0; k < length; ++k) {
          tmp_board[m+k][n] = board[m+k][n];
          row_occupied[m+k]++;
        }
        col_occupied[n] += length;
        std::cout<< "out-v ";
        std::cout<<used[used.size()-1].get_type()<<std::endl;
      }
      
      // reset the ships have been used and have not been used
      // std::sort(ship.begin(), ship.end(), rule);
      std::cout<< "out ";
      std::cout<<used[used.size()-1].get_type()<<std::endl;
      ship.push_back(battleship(used[used.size()-1].get_type()));
      used.pop_back();
      return false;
      
      
    }
    
    // if (used[used.size()-1].get_rot() == "vertical") {
    //   int m = used[used.size()-1].get_row();
    //   int n = used[used.size()-1].get_col();
    //   int length = used[used.size()-1].get_len();
    //   for (int k = 0; k < length; ++k) {
    //     tmp_board[m+k][n] = board[m+k][n];
    //     row_occupied[m+k]++;
    //   }
    //   col_occupied[n] += length;
    //   std::cout<< "out-v ";
    //   std::cout<<used[used.size()-1].get_type()<<std::endl;
    // }
    //
    // // reset the ships have been used and have not been used
    // // std::sort(ship.begin(), ship.end(), rule);
    // std::cout<< "out ";
    // std::cout<<used[used.size()-1].get_type()<<std::endl;
    // ship.push_back(battleship(used[used.size()-1].get_type()));
    // used.pop_back();
//     return false;
  }
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
  std::vector<char**> result;
  
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
  
  // Store the number occupied by ship of each row and column twice
  // One for output result, one for find the result
  // roc = row_occupied; coc = col_occupied
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
  
  // int  count = 0;
  
  for (int x = 0; x < row; ++x) {
    if (roc[x] == 0) continue; // Skip that row if its capacity is 0
    for (int y = 0; y < col; ++y) {
      if (coc[y] == 0) continue; // Skip that column if its capacity is 0
      if (find_solution(x, y, bd, tmp_bd, row, col, roc, coc, ship, used, result, all_soln)) {
        found = true;
        // result.push_back(tmp_bd);
      }
    }
  }
  
  // If no result has been found, print message
  if (result.size() == 0) {
    std::cout << "No solutions" << std::endl;
    return 0;
  }
  
  ////////////////////
  
  std::cout<<std::endl<<std::endl;
  
  // Print the position of each ship
  std::cout << "Solution:" << std::endl;
  for (unsigned int i = 0; i <used.size(); ++i) {
    std::cout << std::left << std::setw(10) << used[i].get_type();
    std::cout << ' ' << used[i].get_row() << ' ' << used[i].get_col();
    if (used[i].get_type() != "submarine")
      std::cout << ' ' << used[i].get_rot();
    std::cout << std::endl;
  }
  
  // Print the game board
  std::cout << '+' << std::string(col,'-') << '+' <<std::endl;
  for (int i = 0; i < row; ++i) {
    std::cout<< '|';
    for (int j = 0; j < col; ++j) std::cout << result[result.size()-1][i][j];
    std::cout<< '|' << row_oc[i]<< std::endl;
  }
  std::cout << '+' << std::string(col,'-') << '+' <<std::endl;
  std::cout << ' ';
  for (int i = 0; i < col; ++i) std::cout<< col_oc[i];
  std::cout<< ' ' << std::endl;
  
  for (int i = 0; i < row; ++i) delete[] bd[i];
  delete[] bd;
  for (int i = 0; i < row; ++i) delete[] tmp_bd[i];
  delete[] tmp_bd;
  
  return 0;
}
