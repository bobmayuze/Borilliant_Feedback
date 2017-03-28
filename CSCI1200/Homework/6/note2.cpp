#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Simple class to record the grid location. 
class loc {
public:
  loc(int r=0, int c=0) : row(r), col(c) {}
  int row, col;
};

bool search_N(loc position /* current position */,
	      const std::vector<std::string>& board, 
	      const std::string& word,  
	      std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row < 0)
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_N(loc(position.row-1, position.col), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_NE(loc position /* current position */,
	       const std::vector<std::string>& board, 
	       const std::string& word,  
	       std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row < 0 || position.col >= int(board[position.row].size()))
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_NE(loc(position.row-1, position.col+1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_E(loc position /* current position */,
	      const std::vector<std::string>& board, 
	      const std::string& word,  
	      std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.col >= int(board[position.row].size()))
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_E(loc(position.row, position.col+1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_SE(loc position /* current position */,
	       const std::vector<std::string>& board, 
	       const std::string& word,  
	       std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row >= int(board.size()) || position.col >= int(board[position.row].size()))
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_SE(loc(position.row+1, position.col+1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_S(loc position /* current position */,
	      const std::vector<std::string>& board, 
	      const std::string& word,  
	      std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row >= int(board.size()))
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_S(loc(position.row+1, position.col), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_SW(loc position /* current position */,
	       const std::vector<std::string>& board, 
	       const std::string& word,  
	       std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row >= int(board.size()) || position.col < 0)
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_SW(loc(position.row+1, position.col-1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_W(loc position /* current position */,
	      const std::vector<std::string>& board, 
	      const std::string& word,  
	      std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.col < 0)
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_W(loc(position.row, position.col-1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

bool search_NW(loc position /* current position */,
	       const std::vector<std::string>& board, 
	       const std::string& word,  
	       std::vector<loc>& path /* path leading to the current pos */ ) {
  if (path.size() == word.size())
    return true;

  if (position.row < 0 || position.col < 0)
    return false;

  if (word[path.size()] == board[position.row][position.col]) {
    path.push_back(position);
    if (search_NW(loc(position.row-1, position.col-1), board, word, path))
      return true;
    path.pop_back();
  }

  return false;
}

// Read in the letter grid, the words to search and print the results
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }

  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Couldn't open " << argv[1] << '\n';
    return 1;
  }

  std::vector<std::string> board;   
  std::string word;
  std::string line;

  //  Input of grid from a file.  Stops when character '-' is reached.
  while ((istr  >> line) && line[0] != '-')
    board.push_back(line);

  while (istr >> word) {
    bool found = false;
    std::vector<loc> path;  //  Path of locations in finding the word

    //  Check all grid locations. 
    //  Search in one of the directions to check if the  word is there.
    for (unsigned int r=0; r<board.size() && !found; ++r) {
      for (unsigned int c=0; c<board[r].size() && !found; ++c) {
	if (board[r][c] == word[0]) {
	  path.push_back(loc(r,c));
	  if (search_N(loc(r-1,c), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_NE(loc(r-1,c+1), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_E(loc(r,c+1), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_SE(loc(r+1,c+1), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_S(loc(r+1,c), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_SW(loc(r+1,c-1), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_W(loc(r,c-1), board, word, path)) {
	    found = true;
	    break;
	  }

	  if (search_NW(loc(r-1,c-1), board, word, path)) {
	    found = true;
	    break;
	  }

	  path.pop_back();
	}
      }
    }
    //  Output results
    std::cout << "\n** " << word << " ** ";
    if (found) {
      std::cout << "was found.  The path is \n";
      for(unsigned int i=0; i<path.size(); ++i)
        std::cout << "  " << word[i] << ":  (" << path[i].row << "," << path[i].col << ")\n";
    } else {
      std::cout << " was not found\n";
    }
  }
  return 0;
}