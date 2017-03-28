#include <iostream>

#ifndef tetris_h
#define tetris_h

// For more specific comment, please see tetris.cpp.

class Tetris {
public:
  Tetris(int the_width);
  void add_piece(char piece, int rotation, int location);
  void add_left_column();
  void add_right_column();
  void remove_left_column();
  void remove_right_column();
  void destroy();
  void print() const;
  int get_width() const { return (width); }
  int get_max_height() const;
  int count_squares() const;
  int remove_full_rows();

private:
  int width;
  int* heights;
  char** data;
};

#endif
