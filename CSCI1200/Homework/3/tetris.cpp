#include <iostream>
#include <string>
#include <algorithm>
#include "tetris.h"

// Initialize the tetris class. Set all heights to 0, and make all data point to null.
Tetris::Tetris(int the_width) {
  width = the_width;
  heights = new int[width];
  for (int i = 0; i < width; ++i)
    heights[i] = 0;
  data = new char*[width];
  for (int i = 0; i < width; ++i)
    data[i] = NULL;
}

// Add tetris piece to the game board, update the content store in tetris.
void Tetris::add_piece(char piece, int rotation, int location) {

  // Create a temporary tetris temp_data to store old data.
  // Create a temporary int temp_height to store the old length of columns.
  char** temp_data = new char*[width];
  for (int i = 0; i < width; ++i)
    temp_data[i] = NULL;
  int temp_height = get_max_height();

  // If the max height of old tetris is greater than 0, store all the data to temp_data.
  // Else if the max height is 0, it means that the game has just started and therefore
  // there is no need to store to the temp_data. We just initialize the data with coming
  // tetris piece and its maximum height.
  if (temp_height > 0) {
    for (int i = 0; i < width; ++i) {
      temp_data[i] = new char[temp_height];
      for (int j = 0; j < temp_height; ++j)
        temp_data[i][j] = data[i][j];
    }
  }

  if (piece == 'I') {

    // Piece 'I' with no or 180 rotation.
    // I
    // I
    // I
    // I
    if (rotation == 0 || rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[4];
          for (int j = 0; j < 4; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'I';
        data[location][1] = 'I';
        data[location][2] = 'I';
        data[location][3] = 'I';
        heights[location] = 4;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.
        int final_height = heights[location];
        int new_height = std::max(temp_height, final_height + 4);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'I';
        data[location][final_height+1] = 'I';
        data[location][final_height+2] = 'I';
        data[location][final_height+3] = 'I';
        heights[location] = final_height + 4;

      }
    }

    // Piece 'I' with 90 or 270 rotaion.
    // IIII
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[1];
          for (int j = 0; j < 1; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'I';
        data[location+1][0] = 'I';
        data[location+2][0] = 'I';
        data[location+3][0] = 'I';
        heights[location] = 1;
        heights[location+1] = 1;
        heights[location+2] = 1;
        heights[location+3] = 1;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.
        int final_height = 0;
        for (int i = 0; i < 4; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'I';
        data[location+1][final_height] = 'I';
        data[location+2][final_height] = 'I';
        data[location+3][final_height] = 'I';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
        heights[location+3] = final_height + 1;
      }
    }
  }

  // Piece 'O' with all rotation.
  // OO
  // OO
  else if (piece == 'O') {

    // If the game has just started, set column length to piece's length, initialize
    // all columns with white space, put tetris piece to correct location and set
    // the height of that column to piece's length. 
    if (temp_height == 0) {
      for (int i = 0; i < width; i++)
          delete[] data[i];
      for (int i = 0; i < width; ++i) {
        data[i] = new char[2];
        for (int j = 0; j < 2; ++j)
          data[i][j] = ' ';
      }
      
      data[location][0] = 'O';
      data[location][1] = 'O';
      data[location+1][0] = 'O';
      data[location+1][1] = 'O';
      heights[location] = 2;
      heights[location+1] = 2;
    }

    // If the game is in process, delete old data, set new height to all columns,
    // initialize new data with white space, add piece to correct locations and set
    // the heights of those columns to the highest height of new piece.
    else {

      // Final_height is the height of the bottom square or what we think the bottom
      // sqaure of coming tetris piece.
      // New_height is the new length of column. It is equal to the higher value
      // of old max height and the max height of locations to which we just added
      // a tetris piece.      
      int final_height = 0;
      for (int i = 0; i < 2; ++i) {
        if (heights[location+i] > final_height)
          final_height = heights[location+i];
      }
      int new_height = std::max(temp_height, final_height + 2);

      for (int i = 0; i < width; i++)
        delete[] data[i];
      for (int i = 0; i < width; ++i) {
        data[i] = new char[new_height];
        for (int j = 0; j < new_height; ++j)
          data[i][j] = ' ';
      }
      for (int i = 0; i < width; ++i) {
        for (int j = 0; j < temp_height; ++j)
          data[i][j] = temp_data[i][j];
      }

      data[location][final_height] = 'O';
      data[location][final_height+1] = 'O';
      data[location+1][final_height] = 'O';
      data[location+1][final_height+1] = 'O';
      heights[location] = final_height + 2;
      heights[location+1] = final_height + 2;
    }
  }

  else if (piece == 'T') {

    // Piece 'T' with 0 rotation.
    // TTT
    //  T
    if (rotation == 0) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][1] = 'T';
        data[location+1][1] = 'T';
        data[location+1][0] = 'T';
        data[location+2][1] = 'T';
        heights[location] = 2;
        heights[location+1] = 2;
        heights[location+2] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+1] == 0)
          final_height++;        
        else if (data[location+1][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'T';
        data[location+1][final_height] = 'T';
        data[location+1][final_height-1] = 'T';
        data[location+2][final_height] = 'T';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
      }
    }
    
    // Piece 'T' with 90 rotation.
    //  T
    // TT
    //  T
    else if (rotation == 90) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][1] = 'T';
        data[location+1][0] = 'T';
        data[location+1][1] = 'T';
        data[location+1][2] = 'T';
        heights[location] = 2;
        heights[location+1] = 3;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+1] == 0)
          final_height++;        
        else if (data[location+1][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'T';
        data[location+1][final_height-1] = 'T';
        data[location+1][final_height] = 'T';
        data[location+1][final_height+1] = 'T';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 2;
      }
    }

    // Piece 'T' with 180 rotation.
    //  T
    // TTT
    else if (rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'T';
        data[location+1][0] = 'T';
        data[location+1][1] = 'T';
        data[location+2][0] = 'T';
        heights[location] = 1;
        heights[location+1] = 2;
        heights[location+2] = 1;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'T';
        data[location+1][final_height] = 'T';
        data[location+1][final_height+1] = 'T';
        data[location+2][final_height] = 'T';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 2;
        heights[location+2] = final_height + 1;
      }
    }

    // Piece 'T' with 270 rotation.
    // T
    // TT
    // T
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'T';
        data[location][1] = 'T';
        data[location][2] = 'T';
        data[location+1][1] = 'T';
        heights[location] = 3;
        heights[location+1] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location] == 0)
          final_height++;        
        else if (data[location][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height-1] = 'T';
        data[location][final_height] = 'T';
        data[location][final_height+1] = 'T';
        data[location+1][final_height] = 'T';
        heights[location] = final_height + 2;
        heights[location+1] = final_height + 1;
      }
    }
  }
  
  else if (piece == 'Z') {

    // Piece 'Z' with 0 and 180 rotation.
    // ZZ
    //  ZZ
    if (rotation == 0 || rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][1] = 'Z';
        data[location+1][0] = 'Z';
        data[location+1][1] = 'Z';
        data[location+2][0] = 'Z';
        heights[location] = 2;
        heights[location+1] = 2;
        heights[location+2] = 1;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+1] == 0 || heights[location+2] == 0)
          final_height++;        
        else if (data[location+1][final_height-1] != ' ' || data[location+2][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'Z';
        data[location+1][final_height-1] = 'Z';
        data[location+1][final_height] = 'Z';
        data[location+2][final_height-1] = 'Z';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height;
      }
    }

    // Piece 'Z' with 90 and 270 rotation.
    //  Z
    // ZZ
    // Z
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'Z';
        data[location][1] = 'Z';
        data[location+1][1] = 'Z';
        data[location+1][2] = 'Z';
        heights[location] = 2;
        heights[location+1] = 3;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location] == 0)
          final_height++;
        else if (data[location][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height-1] = 'Z';
        data[location][final_height] = 'Z';
        data[location+1][final_height] = 'Z';
        data[location+1][final_height+1] = 'Z';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 2;
      }
    }
  }

  else if (piece == 'S') {

    // Piece 'S' with 0 and 180 rotation.
    //  SS
    // SS
    if (rotation == 0 || rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'S';
        data[location+1][0] = 'S';
        data[location+1][1] = 'S';
        data[location+2][1] = 'S';
        heights[location] = 1;
        heights[location+1] = 2;
        heights[location+2] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location] == 0 || heights[location+1] == 0)
          final_height++;
        else if (data[location][final_height-1] != ' ' || data[location+1][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height-1] = 'S';
        data[location+1][final_height-1] = 'S';
        data[location+1][final_height] = 'S';
        data[location+2][final_height] = 'S';
        heights[location] = final_height;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
      }
    }

    // Piece 'S' with 90 and 270 rotation.
    // S
    // SS
    //  S
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][1] = 'S';
        data[location][2] = 'S';
        data[location+1][0] = 'S';
        data[location+1][1] = 'S';
        heights[location] = 3;
        heights[location+1] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+1] == 0)
          final_height++;
        else if (data[location+1][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'S';
        data[location][final_height+1] = 'S';
        data[location+1][final_height-1] = 'S';
        data[location+1][final_height] = 'S';
        heights[location] = final_height + 2;
        heights[location+1] = final_height + 1;
      }
    }
  }

  else if (piece == 'L') {

    // Piece 'L' with 0 rotation.
    // L
    // L
    // LL
    if (rotation == 0) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'L';
        data[location][1] = 'L';
        data[location][2] = 'L';
        data[location+1][0] = 'L';
        heights[location] = 3;
        heights[location+1] = 1;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 3);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'L';
        data[location][final_height+1] = 'L';
        data[location][final_height+2] = 'L';
        data[location+1][final_height] = 'L';
        heights[location] = final_height + 3;
        heights[location+1] = final_height + 1;
      }
    }

    // Piece 'L' with 90 rotation.
    // LLL
    // L
    else if (rotation == 90) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'L';
        data[location][1] = 'L';
        data[location+1][1] = 'L';
        data[location+2][1] = 'L';
        heights[location] = 2;
        heights[location+1] = 2;
        heights[location+2] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location] == 0)
          final_height++;        
        else if (data[location][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height-1] = 'L';
        data[location][final_height] = 'L';
        data[location+1][final_height] = 'L';
        data[location+2][final_height] = 'L';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
      }
      

    }

    // Piece 'L' with 180 rotation.
    // LL
    //  L
    //  L
    else if (rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][2] = 'L';
        data[location+1][0] = 'L';
        data[location+1][1] = 'L';
        data[location+1][2] = 'L';
        heights[location] = 3;
        heights[location+1] = 3;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+1] == 0)
          final_height += 2;        
        else if (data[location+1][final_height-1] != ' ')
          final_height += 2;
        else if (data[location+1][final_height-2] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'L';
        data[location+1][final_height-2] = 'L';
        data[location+1][final_height-1] = 'L';
        data[location+1][final_height] = 'L';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
      }
    }

    // Piece 'L' with 270 rotation.
    //   L
    // LLL
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'L';
        data[location+1][0] = 'L';
        data[location+2][0] = 'L';
        data[location+2][1] = 'L';
        heights[location] = 1;
        heights[location+1] = 1;
        heights[location+2] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'L';
        data[location+1][final_height] = 'L';
        data[location+2][final_height] = 'L';
        data[location+2][final_height+1] = 'L';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 2;
      }
    }
  }

  else if (piece == 'J') {

    // Piece 'J' with 0 rotation.
    //  J
    //  J
    // JJ
    if (rotation == 0) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'J';
        data[location+1][0] = 'J';
        data[location+1][1] = 'J';
        data[location+1][2] = 'J';
        heights[location] = 1;
        heights[location+1] = 3;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 3);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'J';
        data[location+1][final_height] = 'J';
        data[location+1][final_height+1] = 'J';
        data[location+1][final_height+2] = 'J';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 3;
      }
    }

    // Piece 'J' with 90 rotation.
    // J
    // JJJ
    else if (rotation == 90) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'J';
        data[location][1] = 'J';
        data[location+1][0] = 'J';
        data[location+2][0] = 'J';
        heights[location] = 2;
        heights[location+1] = 1;
        heights[location+2] = 1;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.      
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        int new_height = std::max(temp_height, final_height + 2);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'J';
        data[location][final_height+1] = 'J';
        data[location+1][final_height] = 'J';
        data[location+2][final_height] = 'J';
        heights[location] = final_height + 2;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
      }
    }

    // Piece 'J' with 180 rotation.
    // JJ
    // J
    // J
    else if (rotation == 180) {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[3];
          for (int j = 0; j < 3; ++j)
            data[i][j] = ' ';
        }

        data[location][0] = 'J';
        data[location][1] = 'J';
        data[location][2] = 'J';
        data[location+1][2] = 'J';
        heights[location] = 3;
        heights[location+1] = 3;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.        
        int final_height = 0;
        for (int i = 0; i < 2; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location] == 0)
          final_height += 2;        
        else if (data[location][final_height-1] != ' ')
          final_height += 2;
        else if (data[location][final_height-2] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height-2] = 'J';
        data[location][final_height-1] = 'J';
        data[location][final_height] = 'J';
        data[location+1][final_height] = 'J';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
      }
    }

    // Piece 'J' with 270 rotation.
    // JJJ
    //   J
    else {

      // If the game has just started, set column length to piece's length, initialize
      // all columns with white space, put tetris piece to correct locations and set
      // the height of those columns to piece's length. 
      if (temp_height == 0) {
        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[2];
          for (int j = 0; j < 2; ++j)
            data[i][j] = ' ';
        }

        data[location][1] = 'J';
        data[location+1][1] = 'J';
        data[location+2][0] = 'J';
        data[location+2][1] = 'J';
        heights[location] = 2;
        heights[location+1] = 2;
        heights[location+2] = 2;
      }

      // If the game is in process, delete old data, set new height to all columns,
      // initialize new data with white space, rewrite them with old data, add piece
      // to correct locations and set the heights of those columns to the highest height
      // of new piece.
      else {

        // Final_height is the height of the bottom square or what we think the bottom
        // sqaure of coming tetris piece.
        // New_height is the new length of column. It is equal to the higher value
        // of old max height and the max height of locations to which we just added
        // a tetris piece.         
        int final_height = 0;
        for (int i = 0; i < 3; ++i) {
          if (heights[location+i] > final_height)
            final_height = heights[location+i];
        }
        if (heights[location+2] == 0)
          final_height++;        
        else if (data[location+2][final_height-1] != ' ')
          final_height++;
        int new_height = std::max(temp_height, final_height + 1);

        for (int i = 0; i < width; i++)
          delete[] data[i];
        for (int i = 0; i < width; ++i) {
          data[i] = new char[new_height];
          for (int j = 0; j < new_height; ++j)
            data[i][j] = ' ';
        }
        for (int i = 0; i < width; ++i) {
          for (int j = 0; j < temp_height; ++j)
            data[i][j] = temp_data[i][j];
        }

        data[location][final_height] = 'J';
        data[location+1][final_height] = 'J';
        data[location+2][final_height-1] = 'J';
        data[location+2][final_height] = 'J';
        heights[location] = final_height + 1;
        heights[location+1] = final_height + 1;
        heights[location+2] = final_height + 1;
      }
    }
  }

  // Delete all contents of temp_data.
  for (int i = 0; i < width; ++i) 
    delete[] temp_data[i];
  delete[] temp_data;
}

// This member function add a column to the left of current game board. It first create
// a temporary 2D array temp_data to store the old data, then erase the content of data
// and heights, finally modify them to new width and rewrite them with old data.
void Tetris::add_left_column() {

  // Create temp_data to store old data.
  int temp_height = get_max_height();
  char** temp_data = new char*[width];
  for (int i = 0; i < width; ++i) {
    temp_data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      temp_data[i][j] = data[i][j];
  }

  // Erase the content of data and heights.
  for (int i = 0; i < width; ++i)
    delete[] data[i];
  delete[] data;
  delete[] heights;

  // Increment the width, modify the data and initialize it with white space, store
  // old data to it from second column.
  width++;
  data = new char*[width];
  for (int i = 0; i < width; ++i) {
    data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = ' ';
  }
  for (int i = 1; i < width; ++i) {
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = temp_data[i-1][j];
  }

  // Modify the heights array, find the highest square of each column and store to
  // heights.
  heights = new int[width];
  for (int i = 0; i < width; ++i) {
    heights[i] = 0;
    for (int j = temp_height-1; j >= 0; --j) {
      if (data[i][j] != ' ') {
        heights[i] = j+1;
        break;
      }
    }
  } 

  // Delete all contents of temp_data.
  for (int i = 0; i < width-1; ++i)
    delete[] temp_data[i];
  delete[] temp_data;
}

// This member function add a column to the right of current game board. It first create
// a temporary 2D array temp_data to store the old data, then erase the content of data
// and heights, finally modify them to new width and rewrite them with old data.
void Tetris::add_right_column() {

  // Create temp_data to store old data.
  int temp_height = get_max_height();
  char** temp_data = new char*[width];
  for (int i = 0; i < width; ++i) {
    temp_data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      temp_data[i][j] = data[i][j];
  }

  // Erase the content of data and heights.
  for (int i = 0; i < width; ++i)
    delete[] data[i];
  delete[] data;
  delete[] heights;

  // Increment the width, modify the data and initialize it with white space, store
  // old data to it from first column and leave the last column blank.
  width++;
  data = new char*[width];
  for (int i = 0; i < width; ++i) {
    data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = ' ';
  }
  for (int i = 0; i < width-1; ++i) {
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = temp_data[i][j];
  }

  // Modify the heights array, find the highest square of each column and store to
  // heights.
  heights = new int[width];
  for (int i = 0; i < width; ++i) {
    heights[i] = 0;
    for (int j = temp_height-1; j >= 0; --j) {
      if (data[i][j] != ' ') {
        heights[i] = j+1;
        break;
      }
    }
  } 

  // Delete all contents of temp_data.
  for (int i = 0; i < width-1; ++i)
    delete[] temp_data[i];
  delete[] temp_data;
}

// This member function remove a column from the left of current game board. It first create
// a temporary 2D array temp_data to store the old data, then erase the content of data and
// heights, finally modify them to new width and rewrite them with old data.
void Tetris::remove_left_column() {

  // Create temp_data to store old data.
  int temp_height = get_max_height();
  char** temp_data = new char*[width];
  for (int i = 0; i < width; ++i) {
    temp_data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      temp_data[i][j] = data[i][j];
  }

  // Erase the content of data and heights.  
  for (int i = 0; i < width; ++i)
    delete[] data[i];
  delete[] data;
  delete[] heights;

  // Decrement the width, modify the data and initialize it with white space, store
  // old data from second column to new one.
  width--;
  data = new char*[width];
  for (int i = 0; i < width; ++i) {
    data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = ' ';
  }
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = temp_data[i+1][j];
  }

  // Modify the heights array, find the highest square of each column and store to
  // heights.
  heights = new int[width];
  for (int i = 0; i < width; ++i) {
    heights[i] = 0;
    for (int j = temp_height-1; j >= 0; --j) {
      if (data[i][j] != ' ') {
        heights[i] = j+1;
        break;
      }
    }
  } 

  // Delete all contents of temp_data.
  for (int i = 0; i < width+1; ++i)
    delete[] temp_data[i];
  delete[] temp_data;
}

// This member function remove a column from the right of current game board. It first create
// a temporary 2D array temp_data to store the old data, then erase the content of data and
// heights, finally modify them to new width and rewrite them with old data.
void Tetris::remove_right_column() {

  // Create temp_data to store old data.
  int temp_height = get_max_height();
  char** temp_data = new char*[width];
  for (int i = 0; i < width; ++i) {
    temp_data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      temp_data[i][j] = data[i][j];
  }

  // Erase the content of data and heights.   
  for (int i = 0; i < width; ++i)
    delete[] data[i];
  delete[] data;
  delete[] heights;

  // Decrement the width, modify the data and initialize it with white space, store
  // old data from first column to new one, leave the last column of new data blank.
  width--;
  data = new char*[width];
  for (int i = 0; i < width; ++i) {
    data[i] = new char[temp_height];
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = ' ';
  }
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < temp_height; ++j)
      data[i][j] = temp_data[i][j];
  }

  // Modify the heights array, find the highest square of each column and store to
  // heights.
  heights = new int[width];
  for (int i = 0; i < width; ++i) {
    heights[i] = 0;
    for (int j = temp_height-1; j >= 0; --j) {
      if (data[i][j] != ' ') {
        heights[i] = j+1;
        break;
      }
    }
  } 

  // Modify the heights array, find the highest square of each column and store to
  // heights.
  for (int i = 0; i < width+1; ++i)
    delete[] temp_data[i];
  delete[] temp_data;
}

// This member function erase and delete all the content of data and heights.
void Tetris::destroy() {
  for (int i = 0; i < width; ++i)
    delete[] data[i];
  delete[] data;
  delete[] heights;
}

// This member function find the length of highest column in the game board.
int Tetris::get_max_height() const {
  int max_height = 0;
  for (int i = 0; i < width; ++i) {
    if (heights[i] > max_height)
      max_height = heights[i];
    }
  return max_height;
}

// This member function search the board for rows that are full and should be removed.
// This function returns the number of rows removed.
int Tetris::remove_full_rows() {
  int score = 0;
  int count;

  // If a space is not white space, count as one. If the counter in a row is equal to
  // the width, then we earn a score, and we should remove that row.
  for (int j = 0; j < get_max_height(); ++j) {
    count = 0;
    for (int i = 0; i < width; ++i) {
      if (data[i][j] != ' ')
        count++;
    }

    if (count == width) {
      score++;

      // Create a temp_data to store old data.
      int temp_height = get_max_height();
      char** temp_data = new char*[width];
      for (int m = 0; m < width; ++m) {
        temp_data[m] = new char[temp_height];
        for (int n = 0; n < temp_height; ++n)
          temp_data[m][n] = data[m][n];
      }

      // Erase the content of data, modify it with arrays with length of former max
      // height -1. Rewrite it with old data, if we meet the row to be remove, skip
      // that row
      for (int k = 0; k < width; ++k) {
        delete[] data[k];
        data[k] = new char[temp_height-1];
        int p = 0;
        for (int l = 0; l < temp_height-1; ++l && ++p) {
          if (l == j)
            ++p;
          data[k][l] = temp_data[k][p];
        }
      }

      // Modify the heights array, find the highest square of each column and store to
      // heights.
      for (int i = 0; i < width; ++i) {
        heights[i] = 0;
        for (int j = temp_height-2; j >= 0; --j) {
          if (data[i][j] != ' ') {
            heights[i] = j+1;
            break;
          }
        }
      } 

      // Delete the temp_data. Since one row has been removed, we have to decrement the
      // iteration to read new row.
      for (int q = 0; q < width; ++q)
        delete[] temp_data[q];
      delete[] temp_data;
      --j;
    }
  }
  return score;  
}

// This member function counts the number of squares in game board.
int Tetris::count_squares() const {
  int num = 0;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < get_max_height(); ++j) {
      if (data[i][j] != ' ')
        num++;
    }
  }
  return num;
}

