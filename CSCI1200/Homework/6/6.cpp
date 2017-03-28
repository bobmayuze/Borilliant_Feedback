#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

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
  else if (type_ == "unknown") length_ = 8;
}

void battleship::change_rot() {
  if (rotation_ == "horizontal") rotation_ = "vertical";
  else if (rotation_ == "vertical") rotation_ = "horizontal";
}

bool rule(const battleship& ship1, const battleship& ship2) {
  return ship1.get_len() < ship2.get_len();
}

bool find_solution(int r, int c, char** board, char** tmp_board, int row, int col,
                   int* rowx, int* colx, std::vector<battleship>& ship,
                   std::vector<battleship>& used_ship, int& count) {
  count++;
  std::cout <<std::endl<<"count "<< count << std::endl;

  if (ship.size() == 0) {
    std::cout << "HHHHHHHH"<<std::endl;
    bool finish = true;
    // for (int i = 0; i < row; ++i) {
    //   if (rowx[i] != 0) {
    //     finish = false;
    //     break;
    //   }
    // }
    // for (int i = 0; i < col; ++i) {
    //   if (colx[i] != 0) {
    //     finish = false;
    //     break;
    //   }
    // }
    if (finish) return true;
  }

  used_ship.push_back(battleship(ship[ship.size()-1].get_type()));
  // used_ship.push_back(ship[ship.size()-1]);
  std::cout << used_ship.size()<< used_ship[used_ship.size()-1].get_type() << std::endl;
  ship.pop_back();
  // bool yes = false;
  // int length = used_ship[used_ship.size()-1].get_len();

  //
  // std::cout << ship.size()<< ship[ship.size()-1].get_type() << " length " << length << std::endl;
  //
  // if (y+length <= col+1 && length <= rowx[x]) {
  //   std::cout << x << " row " << rowx[x] << std::endl;
  //   std::cout << y << " col " << colx[y] << std::endl;
  //   bool ok = true;
  //   bool haha = true;
  //   for (int m = 0; m < length; ++m) {
  //     if (!available(loc(x, y+m), tmp_board, row, col)) {
  //       ok = false;
  //       break;
  //     }
  //   }
  //   if (ok) {
  //     for (int m = 0; m < length; ++m) {
  //       if (colx[y+m] == 0) {
  //         haha = false;
  //         break;
  //       }
  //     }
  //   }
  //   if (haha) {
  //     for (int m = 0; m < length; ++m) {
  //       tmp_board[x][y+m] = 'X';
  //       colx[y+m]--;
  //     }
  //     rowx[x] -= length;
  //     used_ship[used_ship.size()-1].set_rot("horizontal");
  //     used_ship[used_ship.size()-1].set_loc(x,y);
  //     yes = true;
  //   }
  // }
  // else if (x+length <= row+1 && length <= colx[y]) {
  //   std::cout << x << " row " << rowx[x] << std::endl;
  //   std::cout << y << " col " << colx[y] << std::endl;
  //   bool ok = true;
  //   bool haha = true;
  //   for (int m = 0; m < length; ++m) {
  //     if (!available(loc(x+m, y), tmp_board, row, col)) {
  //       ok = false;
  //       break;
  //     }
  //   }
  //   if (ok) {
  //     for (int m = 0; m < length; ++m) {
  //       if (rowx[x+m] == 0) {
  //         haha = false;
  //         break;
  //       }
  //     }
  //   }
  //   if (haha) {
  //     for (int m = 0; m < length; ++m) {
  //       tmp_board[x+m][y] = 'X';
  //       rowx[x+m]--;
  //     }
  //     colx[y] -= length;
  //     used_ship[used_ship.size()-1].set_rot("vertical");
  //     used_ship[used_ship.size()-1].set_loc(x,y);
  //     yes = true;
  //   }
  // }
  /*if (yes)*/ {
    for (int x = 0; x < row; ++x) {
      if (rowx[x] == 0) continue;
      for (int y = 0; y < col; ++y) {
        if (colx[y] == 0) continue;
        bool yes = false;
        bool ok = true;
        bool haha = true;
        int length = used_ship[used_ship.size()-1].get_len();
        std::cout<<length<<std::endl;
        std::cout<<x<<' '<<y<<std::endl;
        if (/*used_ship[used_ship.size()-1].get_rot() == "horizontal" &&*/ y+length <= col+1 && length <= rowx[x]) {
          std::cout << x << " row " << rowx[x] << std::endl;
          std::cout << y << " col " << colx[y] << std::endl;
          // bool ok = true;
          // bool haha = true;
          for (int m = 0; m < length; ++m) {
            if (!available(loc(x, y+m), tmp_board, row, col)) {
              ok = false;
              std::cout<<"na1"<<std::endl;
              break;
            }
          }
          if (ok) {
            std::cout<<"ok1"<<std::endl;
            for (int m = 0; m < length; ++m) {
              if (colx[y+m] == 0) {
                haha = false;
                break;
              }
            }
          }
          if (ok && haha) {
            std::cout<<"haha"<<std::endl;
            for (int m = 0; m < length; ++m) {
              tmp_board[x][y+m] = 'X';
              colx[y+m]--;
            }
            rowx[x] -= length;
            used_ship[used_ship.size()-1].set_rot("horizontal");
            used_ship[used_ship.size()-1].set_loc(x,y);
            std::cout<<"yes1"<<std::endl;
            yes = true;
          }
        }
        // else if (/*used_ship[used_ship.size()-1].get_rot() == "vertical" &&*/ x+length <= row+1 && length <= colx[y]) {
        //   std::cout << x << " row " << rowx[x] << std::endl;
        //   std::cout << y << " col " << colx[y] << std::endl;
        //   // bool ok = true;
        //   // bool haha = true;
        //   for (int m = 0; m < length; ++m) {
        //     if (!available(loc(x+m, y), tmp_board, row, col)) {
        //       ok = false;
        //       std::cout<<"na2"<<std::endl;
        //       break;
        //     }
        //   }
        //   if (ok) {
        //     std::cout<<"ok2"<<std::endl;
        //     for (int m = 0; m < length; ++m) {
        //       if (rowx[x+m] == 0) {
        //         haha = false;
        //         break;
        //       }
        //     }
        //   }
        //   if (ok && haha) {
        //     for (int m = 0; m < length; ++m) {
        //       tmp_board[x+m][y] = 'X';
        //       rowx[x+m]--;
        //     }
        //     colx[y] -= length;
        //     used_ship[used_ship.size()-1].set_rot("vertical");
        //     used_ship[used_ship.size()-1].set_loc(x,y);
        //     std::cout<<"yes2"<<std::endl;
        //     yes = true;
        //   }
        // }
        if (yes && find_solution(x, y, board, tmp_board, row, col, rowx, colx, ship, used_ship, count)) {
          std::cout<<"true1"<<std::endl;
          return true;
        }
        // if (used_ship[used_ship.size()-1].get_rot() == "horizontal") {
        //   int m = used_ship[used_ship.size()-1].get_row();
        //   int n = used_ship[used_ship.size()-1].get_col();
        //   int length = used_ship[used_ship.size()-1].get_len();
        //   for (int k = 0; k < length; ++k) {
        //     tmp_board[m][n+k] = board[m][n+k];
        //     colx[n+k]++;
        //   }
        //   rowx[m] += length;
        //   std::cout<<"a"<<std::endl;
        //   // ship.push_back(used_ship[ship.size()-1]);
        //   std::cout<<"b"<<std::endl;
        //   // used_ship.pop_back();
        // }
        // else if (used_ship[used_ship.size()-1].get_rot() == "vertical") {
        //   int m = used_ship[used_ship.size()-1].get_row();
        //   int n = used_ship[used_ship.size()-1].get_col();
        //   int length = used_ship[used_ship.size()-1].get_len();
        //   for (int k = 0; k < length; ++k) {
        //     tmp_board[m+k][n] = board[m+k][n];
        //     rowx[m+k]++;
        //   }
        //   colx[n] += length;
        //   std::cout<<"A"<<std::endl;
        //   // ship.push_back(used_ship[ship.size()-1]);
        //   std::cout<<"B"<<std::endl;
        //   // used_ship.pop_back();
        // }
        // /*else*/ {
        //   ship.push_back(battleship(used_ship[used_ship.size()-1].get_type()));
        //   used_ship.pop_back();
        // }
        // yes = false;
        // if (x+length <= row+1 && length <= colx[y]) {
        //   std::cout << x << " row " << rowx[x] << std::endl;
        //   std::cout << y << " col " << colx[y] << std::endl;
        //   // bool ok = true;
        //   // bool haha = true;
        //   for (int m = 0; m < length; ++m) {
        //     if (!available(loc(x+m, y), tmp_board, row, col)) {
        //       ok = false;
        //       std::cout<<"na2"<<std::endl;
        //       break;
        //     }
        //   }
        //   if (ok) {
        //     std::cout<<"ok2"<<std::endl;
        //     for (int m = 0; m < length; ++m) {
        //       if (rowx[x+m] == 0) {
        //         haha = false;
        //         break;
        //       }
        //     }
        //   }
        //   if (ok && haha) {
        //     for (int m = 0; m < length; ++m) {
        //       tmp_board[x+m][y] = 'X';
        //       rowx[x+m]--;
        //     }
        //     colx[y] -= length;
        //     used_ship[used_ship.size()-1].set_rot("vertical");
        //     used_ship[used_ship.size()-1].set_loc(x,y);
        //     std::cout<<"yes2"<<std::endl;
        //     yes = true;
        //   }
        // }
        // if (yes && find_solution(x, y, board, tmp_board, row, col, rowx, colx, ship, used_ship, count)) {
        //   std::cout<<"true2"<<std::endl;
        //   return true;
        // }
        // if (used_ship[used_ship.size()-1].get_rot() == "horizontal") {
        //   int m = used_ship[used_ship.size()-1].get_row();
        //   int n = used_ship[used_ship.size()-1].get_col();
        //   int length = used_ship[used_ship.size()-1].get_len();
        //   for (int k = 0; k < length; ++k) {
        //     tmp_board[m][n+k] = board[m][n+k];
        //     colx[n+k]++;
        //   }
        //   rowx[m] += length;
        //   std::cout<<"a"<<std::endl;
        //   // ship.push_back(used_ship[ship.size()-1]);
        //   std::cout<<"b"<<std::endl;
        //   // used_ship.pop_back();
        // }
        // else if (used_ship[used_ship.size()-1].get_rot() == "vertical") {
        //   int m = used_ship[used_ship.size()-1].get_row();
        //   int n = used_ship[used_ship.size()-1].get_col();
        //   int length = used_ship[used_ship.size()-1].get_len();
        //   for (int k = 0; k < length; ++k) {
        //     tmp_board[m+k][n] = board[m+k][n];
        //     rowx[m+k]++;
        //   }
        //   colx[n] += length;
        //   std::cout<<"A"<<std::endl;
        //   // ship.push_back(used_ship[ship.size()-1]);
        //   std::cout<<"B"<<std::endl;
        //   // used_ship.pop_back();
        // }
        // /*else*/ {
        //   ship.push_back(battleship(used_ship[used_ship.size()-1].get_type()));
        //   used_ship.pop_back();
        // }
      }
    }
  }
  // int m = used_ship[used_ship.size()-1].get_row();
  // int n = used_ship[used_ship.size()-1].get_col();
  // length = used_ship[used_ship.size()-1].get_len();
  if (used_ship[used_ship.size()-1].get_rot() == "horizontal") {
    int m = used_ship[used_ship.size()-1].get_row();
    int n = used_ship[used_ship.size()-1].get_col();
    int length = used_ship[used_ship.size()-1].get_len();
    for (int k = 0; k < length; ++k) {
      tmp_board[m][n+k] = board[m][n+k];
      colx[n+k]++;
    }
    rowx[m] += length;
    std::cout<<"a"<<std::endl;
    // ship.push_back(used_ship[ship.size()-1]);
    std::cout<<"b"<<std::endl;
    // used_ship.pop_back();
  }
  // else if (used_ship[used_ship.size()-1].get_rot() == "vertical") {
  //   int m = used_ship[used_ship.size()-1].get_row();
  //   int n = used_ship[used_ship.size()-1].get_col();
  //   int length = used_ship[used_ship.size()-1].get_len();
  //   for (int k = 0; k < length; ++k) {
  //     tmp_board[m+k][n] = board[m+k][n];
  //     rowx[m+k]++;
  //   }
  //   colx[n] += length;
  //   std::cout<<"A"<<std::endl;
  //   // ship.push_back(used_ship[ship.size()-1]);
  //   std::cout<<"B"<<std::endl;
  //   // used_ship.pop_back();
  // }
  // /*else*/ {
  //   // used_ship[used_ship.size()-1].change_rot();
  //   ship.push_back(battleship(used_ship[used_ship.size()-1].get_type()));
  //   // ship.push_back(used_ship[used_ship.size()-1]);
  //   used_ship.pop_back();
  // }
  std::cout<<"cccccc"<<std::endl;

  //=================================================================

  for (int x = 0; x < row; ++x) {
    if (rowx[x] == 0) continue;
    for (int y = 0; y < col; ++y) {
      if (colx[y] == 0) continue;
      bool yes = false;
      bool ok = true;
      bool haha = true;
      int length = used_ship[used_ship.size()-1].get_len();
      std::cout<<length<<std::endl;
      std::cout<<x<<' '<<y<<std::endl;
      // if (/*used_ship[used_ship.size()-1].get_rot() == "horizontal" &&*/ y+length <= col+1 && length <= rowx[x]) {
      //   std::cout << x << " row " << rowx[x] << std::endl;
      //   std::cout << y << " col " << colx[y] << std::endl;
      //   // bool ok = true;
      //   // bool haha = true;
      //   for (int m = 0; m < length; ++m) {
      //     if (!available(loc(x, y+m), tmp_board, row, col)) {
      //       ok = false;
      //       std::cout<<"na1"<<std::endl;
      //       break;
      //     }
      //   }
      //   if (ok) {
      //     std::cout<<"ok1"<<std::endl;
      //     for (int m = 0; m < length; ++m) {
      //       if (colx[y+m] == 0) {
      //         haha = false;
      //         break;
      //       }
      //     }
      //   }
      //   if (ok && haha) {
      //     std::cout<<"haha"<<std::endl;
      //     for (int m = 0; m < length; ++m) {
      //       tmp_board[x][y+m] = 'X';
      //       colx[y+m]--;
      //     }
      //     rowx[x] -= length;
      //     used_ship[used_ship.size()-1].set_rot("horizontal");
      //     used_ship[used_ship.size()-1].set_loc(x,y);
      //     std::cout<<"yes1"<<std::endl;
      //     yes = true;
      //   }
      // }
      if (/*used_ship[used_ship.size()-1].get_rot() == "vertical" &&*/ x+length <= row+1 && length <= colx[y]) {
        std::cout << x << " row " << rowx[x] << std::endl;
        std::cout << y << " col " << colx[y] << std::endl;
        // bool ok = true;
        // bool haha = true;
        for (int m = 0; m < length; ++m) {
          if (!available(loc(x+m, y), tmp_board, row, col)) {
            ok = false;
            std::cout<<"na2"<<std::endl;
            break;
          }
        }
        if (ok) {
          std::cout<<"ok2"<<std::endl;
          for (int m = 0; m < length; ++m) {
            if (rowx[x+m] == 0) {
              haha = false;
              break;
            }
          }
        }
        if (ok && haha) {
          for (int m = 0; m < length; ++m) {
            tmp_board[x+m][y] = 'X';
            rowx[x+m]--;
          }
          colx[y] -= length;
          used_ship[used_ship.size()-1].set_rot("vertical");
          used_ship[used_ship.size()-1].set_loc(x,y);
          std::cout<<"yes2"<<std::endl;
          yes = true;
        }
      }
      if (yes && find_solution(x, y, board, tmp_board, row, col, rowx, colx, ship, used_ship, count)) {
        std::cout<<"true1"<<std::endl;
        return true;
      }
    }
  }

  // int m = used_ship[used_ship.size()-1].get_row();
  // int n = used_ship[used_ship.size()-1].get_col();
  // length = used_ship[used_ship.size()-1].get_len();
  // if (used_ship[used_ship.size()-1].get_rot() == "horizontal") {
  // int m = used_ship[used_ship.size()-1].get_row();
  // int n = used_ship[used_ship.size()-1].get_col();
  // int length = used_ship[used_ship.size()-1].get_len();
  // for (int k = 0; k < length; ++k) {
  // tmp_board[m][n+k] = board[m][n+k];
  // colx[n+k]++;
  // }
  // rowx[m] += length;
  // std::cout<<"a"<<std::endl;
  // // ship.push_back(used_ship[ship.size()-1]);
  // std::cout<<"b"<<std::endl;
  // // used_ship.pop_back();
  // }
  if (used_ship[used_ship.size()-1].get_rot() == "vertical") {
    int m = used_ship[used_ship.size()-1].get_row();
    int n = used_ship[used_ship.size()-1].get_col();
    int length = used_ship[used_ship.size()-1].get_len();
    for (int k = 0; k < length; ++k) {
      tmp_board[m+k][n] = board[m+k][n];
      rowx[m+k]++;
    }
    colx[n] += length;
    std::cout<<"A"<<std::endl;
    // ship.push_back(used_ship[ship.size()-1]);
    std::cout<<"B"<<std::endl;
    // used_ship.pop_back();
  }
  /*else*/ {
    // used_ship[used_ship.size()-1].change_rot();
    ship.push_back(battleship(used_ship[used_ship.size()-1].get_type()));
    // ship.push_back(used_ship[used_ship.size()-1]);
    used_ship.pop_back();
  }
  std::cout<<"cccccc"<<std::endl;

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
  if (argc == 3 && std::string(argv[2]) != std::string("find_all_solutions")) {
    std::cerr << "Unknown command\n";
  }

  std::string tmp;
  int row, col;

  // Store row and column number of board
  istr >> tmp;
  if (tmp != "board") std::cerr << "Unknown command\n";
  istr >> tmp;
  row = atoi(tmp.c_str());
  istr >> tmp;
  col = atoi(tmp.c_str());
  std::cout << "row: " << row << " col: " << col << std::endl;
  istr >> tmp;

  // Store the number occupied by ship of each row and column
  if (tmp != "rows") std::cerr << "Unknown command\n";
  int row_occupied[row];
  for (int i = 0; i < row; ++i) {
    istr >> tmp;
    if (tmp == "?") row_occupied[i] = -1;
    else row_occupied[i] = atoi(tmp.c_str());
  }
  istr >> tmp;
  if (tmp != "cols") std::cerr << "Unknown command\n";
  int col_occupied[col];
  for (int i = 0; i < col; ++i) {
    istr >> tmp;
    if (tmp == "?") col_occupied[i] = -1;
    else col_occupied[i] = atoi(tmp.c_str());
  }

  // Store all ship information
  std::vector<battleship> ship;
  while (istr >> tmp) {
    if (tmp == "constraint") break;
    ship.push_back(battleship(tmp));
  }
  for (unsigned int i = 0; i < ship.size(); ++i)
    std::cout << ship[i].get_type() << ' ' << ship[i].get_len() << std::endl;
  std::cout<<std::endl;
  std::sort(ship.begin(), ship.end(), rule);
  for (unsigned int i = 0; i < ship.size(); ++i)
    std::cout << ship[i].get_type() << ' ' << ship[i].get_len() << std::endl;

  // std::cout<<std::endl;

  // Create the board and a copy of it to store solution
  char** board = new char*[row];
  for (int i = 0; i < row; ++i) {
    board[i] = new char[col];
    for (int j = 0; j < col; ++j) board[i][j] = ' ';
  }
  char** tmp_board = new char*[row];
  for (int i = 0; i < row; ++i) {
    tmp_board[i] = new char[col];
    for (int j = 0; j < col; ++j) tmp_board[i][j] = board[i][j];
  }

  bool found = false;
  std::vector<loc> used_pos;
  std::vector<battleship> used_ship;
  std::vector<char**> result;

  int count = 0;
  // for (unsigned int r = 0; r < row && !found; ++r) {
  //   if (row_occupied[r] == 0) continue;
  //   for (unsigned int c = 0; c < col && !found; ++c) {
  //     if (col_occupied[c] == 0) continue;
  if (find_solution(0, 0, board, tmp_board, row, col, row_occupied, col_occupied, ship, used_ship, count))
    found = true;
  //   }
  // }

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      std::cout << ' '<<tmp_board[i][j];
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < row; ++i) {
    std::cout << i << ": " << row_occupied[i] << " \n";
  }
  for (int i = 0; i < col; ++i) {
    std::cout << i << ": " << col_occupied[i] << " \n";
  }

  std::cout<<"delete board" <<std::endl;
  for (int i = 0; i < row; ++i) delete[] board[i];
  delete[] board;
  std::cout<<"delete tmpboard" <<std::endl;
  for (int i = 0; i < row; ++i) delete[] tmp_board[i];
  delete[] tmp_board;
  std::cout<<"delete" <<std::endl;
  return 0;
}
