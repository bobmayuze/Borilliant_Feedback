#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

#ifndef Header_h
#define Header_h

// Simple class to record the grid location.
class loc {
public:
  loc(int r=0, int c=0) : row_(r), col_(c) {}
  int getrow() const { return row_; }
  int getcol() const { return col_; }
private:
  int row_, col_;
};

// Check if a position and its 8 adjacent cells have already been occupied by
// some ships.
bool available(const loc& pos, char** board, int row, int col) {
  if (board[pos.getrow()][pos.getcol()] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][pos.getcol()] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][pos.getcol()] == ' ' &&
      board[pos.getrow()][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[pos.getrow()][std::min(pos.getcol()+1, col-1)] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[std::max(pos.getrow()-1, 0)][std::min(pos.getcol()+1, col-1)] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][std::max(pos.getcol()-1, 0)] == ' ' &&
      board[std::min(pos.getrow()+1, row-1)][std::min(pos.getcol()+1, col-1)] == ' ')
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
  // Set the type name of the ship.
  void set_type(std::string name) { type_ = name; }
  // Set the direction of rotation of the ship.
  void set_rot(std::string rot) { rotation_ = rot; }
  // Set the length of the ship.
  void set_len(int len) { length_ = len; }
  // Set the location of the ship.
  void set_loc(int row, int col) { x = row; y = col; }
private:
  std::string type_;
  std::string rotation_;
  int length_;
  int x, y;
};

// Constructor.
battleship::battleship(std::string name) {
  type_ = name;
  rotation_ = ""; // Set rotation to none when it has not been put on board.
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

class solution {
public:
  solution(char** board, int row, int col, int* row_occupy, int* col_occupy,
    std::vector<battleship>& ship);
  char** get_board() const { return board_; }
  int get_row() const { return row_; }
  int get_col() const { return col_; }
  int* get_roc() const { return roc_; }
  int* get_coc() const { return coc_; }
  void print_soln();
  std::vector<battleship>& get_ship() { return ship_; }
private:
  char** board_;
  int row_, col_;
  int* roc_;
  int* coc_;
  std::vector<battleship> ship_;
};

solution::solution(char** board, int row, int col, int* row_occupy,
    int* col_occupy, std::vector<battleship>& ship) {
  board_ = new char*[row];
  for (int i = 0; i < row; ++i) {
    board_[i] = new char[col];
    for (int j = 0; j < col; ++j) board_[i][j] = board[i][j];
  }
  ship_ = ship;
  row_ = row;
  col_ = col;
  roc_ = new int[row];
  coc_ = new int[col];
  for (int i = 0; i < row; ++i) roc_[i] = row_occupy[i];
  for (int i = 0; i < col; ++i) coc_[i] = col_occupy[i];
}

// A member function to print the result
void solution::print_soln() {
  // Print each battleship's location and rotation
  std::cout << "Solution:" << std::endl;
  for (unsigned int i = 0; i < this->get_ship().size(); ++i) {
    // First change the type of any unknown ship to correct one.
    if (this->get_ship()[i].get_type() == "unknown") {
      if (this->get_ship()[i].get_len() == 1)
        this->get_ship()[i].set_type("submarine");
      else if (this->get_ship()[i].get_len() == 2)
        this->get_ship()[i].set_type("destroyer");
      else if (this->get_ship()[i].get_len() == 3)
        this->get_ship()[i].set_type("cruiser");
      else if (this->get_ship()[i].get_len() == 4)
        this->get_ship()[i].set_type("battleship");
      else if (this->get_ship()[i].get_len() == 5)
        this->get_ship()[i].set_type("carrier");
      else if (this->get_ship()[i].get_len() == 6)
        this->get_ship()[i].set_type("cargo");
      else if (this->get_ship()[i].get_len() == 7)
        this->get_ship()[i].set_type("tanker");
    }
    std::cout << std::left << std::setw(10) << this->get_ship()[i].get_type();
    std::cout << ' ' << this->get_ship()[i].get_row() << ' ';
    std::cout << this->get_ship()[i].get_col();
    if (this->get_ship()[i].get_type() != "submarine")
      std::cout << ' ' << this->get_ship()[i].get_rot();
    std::cout << std::endl;
  }
  // Print the game board result
  std::cout << '+' << std::string(col_,'-') << '+' <<std::endl;
  for (int i = 0; i < row_; ++i) {
    std::cout<< '|';
    for (int j = 0; j < col_; ++j) std::cout << this->get_board()[i][j];
    std::cout<< '|' << roc_[i]<< std::endl;
  }
  std::cout << '+' << std::string(col_,'-') << '+' <<std::endl;
  std::cout << ' ';
  for (int i = 0; i < col_; ++i) std::cout<< coc_[i];
  std::cout<< ' ' << std::endl;
}

// Check whether two results are the same.
bool not_same(char** board1, char** board2, int row, int col) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (board1[i][j] != board2[i][j]) return true;
    }
  }
  return false;
}

class constraint {
public:
  constraint (loc loc, std::string type) : location_(loc), type_(type) {}
  const loc get_loc() const { return location_; }
  const std::string get_type() const { return type_; }
private:
  loc location_;
  std::string type_;
};

// Check the locations of each constraint
bool check_cstr(std::vector<constraint>& cstr, char** board, int row, int col) {
  for (unsigned int i = 0; i < cstr.size(); ++i) {
    int r = cstr[i].get_loc().getrow();
    int c = cstr[i].get_loc().getcol();
    // If the constraint type is 'o', first check whether the location has been
    // occupied by a ship, remove it and check if its neighbours are empty.
    // Recover the board after checking
    if (cstr[i].get_type() == "o") {
      if (board[r][c] == 'X') {
        board[r][c] = ' ';
        if (available(cstr[i].get_loc(), board, row, col)) board[r][c] = 'X';
        else {
          board[r][c] = 'X';
          return false;
        }
      }
      else return false;
    }
    // If the constraint type is '<', first check whether the location and the
    // location right to it have been occupied by ships, then check the location
    // left to it is empty.
    else if (cstr[i].get_type() == "<") {
      if (board[r][c] == 'X' && board[r][c+1] == 'X') {
        if (c != 0) {
          if (board[r][c-1] == 'X') return false;
        }
      }
      else return false;
    }
    // If the constraint type is '>', first check whether the location and the
    // location left to it have been occupied by ships, then check the location
    // right to it is empty.
    else if (cstr[i].get_type() == ">") {
      if (board[r][c] == 'X' && board[r][c-1] == 'X') {
        if (c != col-1) {
          if (board[r][c+1] == 'X') return false;
        }
      }
      else return false;
    }
    // If the constraint type is '^', first check whether the location and the
    // location below it have been occupied by ships, then check the location
    // above it is empty.
    else if (cstr[i].get_type() == "^") {
      if (board[r][c] == 'X' && board[r+1][c] == 'X') {
        if (c != 0) {
          if (board[r-1][c] == 'X') return false;
        }
      }
      else return false;
    }
    // If the constraint type is 'v', first check whether the location and the
    // location below it have been occupied by ships, then check the location
    // above it is empty.
    else if (cstr[i].get_type() == "v") {
      if (board[r][c] == 'X' && board[r-1][c] == 'X') {
        if (c != row-1) {
          if (board[r+1][c] == 'X') return false;
        }
      }
      else return false;
    }
    // If the constraint type is 'X', first check whether the location, the
    // location left to it and the location right to it have been occupied by
    // ships, or then check the vertical situation.
    else if (cstr[i].get_type() == "X") {
      if (board[r][c] != 'X' && ((board[r-1][c] != 'X' || board[r+1][c] != 'X')
          || (board[r][c-1] != 'X' || board[r][c+1] != 'X'))) return false;
    }
    // If the constraint type is '_', just check whether the location is empty.
    else if (cstr[i].get_type() == "_") {
      if (board[r][c] != ' ') return false;
    }
  }
  return true;
}

// Helper function to check whether we used up all the location available.
// If some of the row_occupy and col_occupy are unknown, set them to correct
// number.
bool filled(char** board, int row, int col, int* row_occupy, int* col_occupy,
    int* roc, int* coc) {
  for (int i = 0; i < row; ++i) {
    if (roc[i] != -1) {
      if (row_occupy[i] != 0) return false;
    }
    else {
      int count = 0;
      for (int j = 0; j < col; ++j) {
        if (board[i][j] != ' ') count++;
      }
      row_occupy[i] = count;
    }
  }
  for (int j = 0; j < col; ++j) {
    if (coc[j] != -1) {
      if (col_occupy[j] != 0) return false;
    }
    else {
      int count = 0;
      for (int i = 0; i < row; ++i) {
        if (board[i][j] != ' ') count++;
      }
      col_occupy[j] = count;
    }
  }
  return true;
}

// Helper function to sort the ship, from the shortest to longest.
// It will make pop_back() easy, and improve the performance significantly.
bool rule(const battleship& ship1, const battleship& ship2) {
  return ship1.get_len() < ship2.get_len();
}

#endif /* Header_h */
