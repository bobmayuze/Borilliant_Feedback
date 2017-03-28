// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).
template <class number_type>
class Point {
public:
  Point() : x(0), y(0) {}
  Point(const number_type& x_, const number_type& y_) : x(x_), y(y_) {}

  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

// ==============================================================
// ==============================================================
// TREE NODE CLASS
template <class number_type, class label_type>
class Node {
public:
  // Default constructor, set all pointers to NULL
  Node() {
    for (int i = 0; i < 4; ++ i) children.push_back(NULL);
    parent = NULL;
  }
  Node(const Point<number_type>& point_, const label_type& label_) {
    pt = point_;
    label = label_;
    for (int i = 0; i < 4; ++ i) children.push_back(NULL);
    parent = NULL;
  }

  Point<number_type> pt;
  label_type label;
  std::vector<Node<number_type, label_type>*> children;
  Node<number_type, label_type>* parent;
};

// ==============================================================
// ==============================================================
// TREE NODE DEPTH ITERATOR CLASS
template <class number_type, class label_type>
class depth_iterator {
public:
  typedef Node<number_type, label_type> node;

  depth_iterator() : ptr_(NULL), root_(NULL) {}
  depth_iterator(node* p, node* q = NULL) : ptr_(p), root_(q) {}
  depth_iterator(const depth_iterator& old) : ptr_(old.ptr_), root_(old.root_) {}
  ~depth_iterator() {}
  depth_iterator& operator=(const depth_iterator& old)
    { ptr_ = old.ptr_; return *this; }

  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const depth_iterator& rgt)
    { return ptr_ == rgt.ptr_ ; }
  bool operator!= (const depth_iterator& rgt)
    { return ptr_ != rgt.ptr_ ; }

  const label_type& getLabel() const { return ptr_->label; }

  // Get the depth of current node. If the node does not exist, return -1.
  // If the node is the root, return 0. Else count how many steps it needs to
  // get the root node
  int getDepth() const {
    if (!ptr_) return -1;
    if (ptr_->parent == NULL) return 0;
    int depth = 0;
    node* p = ptr_;
    while (p->parent != NULL) {
      depth++;
      p = p->parent;
    }
    return depth;
  }

  // increment operators
  // post-increment operator
  depth_iterator& operator++() {
    // If the quadtree is empty or the iterator is pointing to the end
    // do nothing, return itself
    if (ptr_ == NULL) return *this;
    // A bool to check whether we have incremented the iterator
    bool done = false;

    // If current tree node has children, point to its first child node.
    if (ptr_->children[0] != NULL) { ptr_ = ptr_->children[0]; done = true; }
    else if (ptr_->children[1] != NULL) { ptr_ = ptr_->children[1]; done = true; }
    else if (ptr_->children[2] != NULL) { ptr_ = ptr_->children[2]; done = true; }
    else if (ptr_->children[3] != NULL) { ptr_ = ptr_->children[3]; done = true; }

    // If current tree node does not have children nodes, check whether it has
    // younger brother nodes. If not, check whether its parent node has younger
    // brother nodes and keep checking until we get a node or reach the end
    else {
      node* p;
      while (!done && ptr_->parent != NULL) {
        p = ptr_->parent;
        if (ptr_ == p->children[0]) {
          if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
          else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
          else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
        }
        else if (ptr_ == p->children[1]) {
          if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
          else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
        }
        else if (ptr_ == p->children[2]) {
          if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
        }
        // If we cannot find a younger brother node, set the iterator to its
        // parent and check its grandparent and so on
        if (!done) ptr_ = p;
      }
    }

    // If we haven't increment the iterator, it means that we reach the end
    // of that quadtree, set the iterator to NULL
    if (!done) ptr_ = NULL;
    return *this;
  }

  // pre-increment operators
  depth_iterator operator++(int) {
    depth_iterator temp(*this);
    ++(*this);
    return temp;
  }

private:
  // representation
  node* ptr_;
  node* root_;
};

// ==============================================================
// ==============================================================
// TREE NODE BREADTH ITERATOR CLASS
template <class number_type, class label_type>
class breadth_iterator {
public:
  typedef Node<number_type, label_type> node;

  breadth_iterator() : ptr_(NULL), root_(NULL) {}
  breadth_iterator(node* p, node* q = NULL) : ptr_(p), root_(q) {}
  breadth_iterator(const breadth_iterator& old) : ptr_(old.ptr_), root_(old.root_) {}
  ~breadth_iterator() {}
  breadth_iterator& operator=(const breadth_iterator& old)
    { ptr_ = old.ptr_; return *this; }

  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const breadth_iterator& rgt)
    { return ptr_ == rgt.ptr_ ; }
  bool operator!= (const breadth_iterator& rgt)
    { return ptr_ != rgt.ptr_ ; }

  const label_type& getLabel() const { return ptr_->label; }

  // Get the depth of current node. If the node does not exist, return -1.
  // If the node is the root, return 0. Else count how many steps it needs to
  // get the root node
  int getDepth() const {
    if (!ptr_) return -1;
    if (ptr_->parent == NULL) return 0;
    int depth = 0;
    node* p = ptr_;
    while (p->parent != NULL) {
      depth++;
      p = p->parent;
    }
    return depth;
  }

  // Helper member function. Store all the nodes points to a list by depth.
  // Similar to breadth traversal
  std::list<node*> nodelist(node*& root) {
    std::list<node*> mylist;
    // If the tree is empty, do nothing
    if (root == NULL) return mylist;
    node* tmp;
    std::list<node*> queue;
    queue.push_back(root);
    while (queue.size() != 0) {
      tmp = queue.front();
      mylist.push_back(tmp);
      queue.pop_front();
      if (tmp->children[0] != NULL) queue.push_back(tmp->children[0]);
      if (tmp->children[1] != NULL) queue.push_back(tmp->children[1]);
      if (tmp->children[2] != NULL) queue.push_back(tmp->children[2]);
      if (tmp->children[3] != NULL) queue.push_back(tmp->children[3]);
    }
    return mylist;
  }

  // increment operators
  // Post increment operator
  breadth_iterator& operator++() {
    // If the tree is empty, do nothing
    if (ptr_ == NULL) return *this;
    // tmp pointer to find the root node
    node* root = ptr_->parent;
    // tmp node pointer to store the current pointer
    node* tmp = ptr_;
    // get the root node
    while (root != NULL) {
      ptr_ = root;
      root = ptr_->parent;
    }

    // Get a list of node pointers
    std::list<node*> mylist = nodelist(ptr_);
    // Find the current node pointer and increment to the next one
    typename std::list<node*>::iterator itr;
    itr = std::find(mylist.begin(), mylist.end(), tmp);
    itr++;
    // If current pointer is the last pointer, return NULL
    if (itr == mylist.end()) ptr_ = NULL;
    else ptr_ = *itr;
    return *this;
  }

  // Pre increment operator
  breadth_iterator operator++(int) {
    breadth_iterator temp(*this);
    ++(*this);
    return temp;
  }

private:
  // representation
  node* ptr_;
  node* root_;
};

// ==============================================================
// ==============================================================
// QuadTree Class
template <class number_type, class label_type>
class QuadTree {
public:
  typedef depth_iterator<number_type, label_type> iterator;
  typedef breadth_iterator<number_type, label_type> bf_iterator;
  typedef Node<number_type, label_type> node;
  typedef std::pair<iterator, bool> pair;
  typedef Point<number_type> point;

  QuadTree() : root_(NULL), size_(0) {}
  QuadTree(const QuadTree& old) { copy(old); }
  QuadTree& operator=(const QuadTree& old) {
    if (&old != this) {
      this->destroy(root_);
      copy(old);
      size_ = old.size_;
    }
    return *this;
  }
  ~QuadTree() { this->destroy(root_); root_ = NULL; }

  unsigned int size() const { return size_; }

  // Copy driver function. If the old tree is empty, do nothing
  void copy(const QuadTree& old) {
    size_ = old.size_;
    if (size_ == 0) {
      root_ = NULL;
      return;
    }
    else copy(root_, root_, old.root_);
  }

  void copy(node*& newtree, node*& parent, node* oldtree){
    if (oldtree == NULL) //base case to end recursion when at tree end
      newtree = NULL;
    else {
      newtree = new node;  //create the node and set the new key to original
      newtree->pt = point(oldtree->pt.x, oldtree->pt.y);
      newtree->label = oldtree->label;
      if (newtree == parent) newtree->parent = NULL;
      else newtree->parent = parent;
      // Just call recursively to copy the subtrees:
      copy(newtree->children[0], newtree, oldtree->children[0]);
      copy(newtree->children[1], newtree, oldtree->children[1]);
      copy(newtree->children[2], newtree, oldtree->children[2]);
      copy(newtree->children[3], newtree, oldtree->children[3]);
    }
  }

  // Destroy member function. Recursively get to the bottom and delete all nodes
  // from leaves to the root.
  void destroy(node*& p) {
    if (p != NULL) {
      destroy(p->children[0]);
      destroy(p->children[1]);
      destroy(p->children[2]);
      destroy(p->children[3]);
      delete p;
      p = NULL;
      size_ = 0;
    }
  }

  // ==============================================================
  // Insert
  // driver function
  pair insert(const point& point_, const label_type& label_) {
    return insert(point_, label_, root_, root_);
  }

  // actual recursive function
  pair insert(const point& point_, const label_type& label_, node*& p, node*& q) {
    if (p == NULL) {
      // allocate a new node and make p point to it
      p = new node(point_, label_);
      this->size_++;
      if (p != q) p->parent = q;
      return pair(iterator(p, root_), true);
    }

    // Insert new node by their corresponding location
    else if (point_.x < p->pt.x && point_.y < p->pt.y)
      return insert(point_, label_, p->children[0], p);
    else if (point_.x > p->pt.x && point_.y < p->pt.y)
      return insert(point_, label_, p->children[1], p);
    else if (point_.x < p->pt.x && point_.y > p->pt.y)
      return insert(point_, label_, p->children[2], p);
    else if (point_.x > p->pt.x && point_.y > p->pt.y)
      return insert(point_, label_, p->children[3], p);
    else
      return pair(iterator(p, root_), false); // we found a match, don't insert
  }

  // ==============================================================
  // Find
  iterator find(const number_type& x, const number_type& y) const {
    // If the tree is empty, do nothing.
    if (!root_) return iterator(NULL, root_);
    node* p = root_;
    while (p != NULL) {
      // Find the node
      if (x == p->pt.x && y == p->pt.y) break;
      // Go to corresponding subarea to find the node
      else if (x < p->pt.x && y < p->pt.y) p = p->children[0];
      else if (x > p->pt.x && y < p->pt.y) p = p->children[1];
      else if (x < p->pt.x && y > p->pt.y) p = p->children[2];
      else if (x > p->pt.x && y > p->pt.y) p = p->children[3];
      // Do not find that node
      else if (x == p->pt.x && y != p->pt.y) return iterator(NULL, root_);
      else if (x != p->pt.x && y == p->pt.y) return iterator(NULL, root_);
    }
    return iterator(p, root_);
  }

  // ==============================================================
  // Height
  // driver function
  int height() const { return height(root_); }

  // actual recursive function
  int height(node* p) const {
     if (p == NULL) return -1;
     int h1 = height(p->children[0]);
     int h2 = height(p->children[1]);
     int h3 = height(p->children[2]);
     int h4 = height(p->children[3]);
     return 1 + std::max(std::max(h1, h2), std::max(h3, h4));
  }

  // ==============================================================
  // begin && end
  iterator begin() const { return iterator(root_, root_); }
  iterator end() const { return iterator(NULL, root_); }
  bf_iterator bf_begin() const { return bf_iterator(root_, root_); }
  bf_iterator bf_end() const { return bf_iterator(NULL, root_); }

  // ==============================================================
  // PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
  // ==============================================================

  // NOTE: this function only works for quad trees with non negative
  // integer coordinates and char labels

  // NOTE2: this function assumes that no two points have the same x
  // coordinate or the same y coordinate.

  // plot driver function
  // takes in the maximum x and y coordinates for these data points
  // the optional argument draw_lines defaults to true
  void plot(int max_x, int max_y, bool draw_lines=true) const {
    // allocate blank space for the center of the board
    std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
    // edit the board to add the point labels and draw vertical and
    // horizontal subdivisions
    plot(root_,board,0,max_x,0,max_y,draw_lines);
    // print the top border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
    for (int i = 0; i <= max_y; i++) {
      // print each row of the board between vertical border bars
      std::cout << "|" << board[i] << "|" << std::endl;
    }
    // print the bottom border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  }

  // actual recursive function for plotting
  void plot(node *p, std::vector<std::string> &board,
            int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
    // base case, draw nothing if this node is NULL
    if (p == NULL) return;
    // check that the dimensions range of this node make sense
    assert (x_min >= 0 && x_min <= x_max);
    assert (y_min >= 0 && y_min <= y_max);
    assert (board.size() >= y_max);
    assert (board[0].size() >= x_max);
    // verify that the point stored at this node fits on the board
    assert (p->pt.y >= 0 && p->pt.y < board.size());
    assert (p->pt.x >= 0 && p->pt.x < board[0].size());
    // draw the vertical and horizontal bars extending across the
    // range of this node
    if (draw_lines) {
      for (int x = x_min; x <= x_max; x++) {
        board[p->pt.y][x] = '-';
      }
      for (int y = y_min; y <= y_max; y++) {
        board[y][p->pt.x] = '|';
      }
    }
    // draw this label
    board[p->pt.y][p->pt.x] = p->label;
    // recurse on the 4 children
    plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
    plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
  }

  // ==============================================================
  // prints all of the tree data with a pre-order (node first, then
  // children) traversal of the tree structure

  // driver function
  void print_sideways() const { print_sideways(root_,""); }
  // actual recursive function
  void print_sideways(node* p, const std::string &indent) const {
    // base case
    if (p == NULL) return;
    // print out this node
    std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
    // recurse on each of the children trees
    // increasing the indentation
    print_sideways(p->children[0],indent+"  ");
    print_sideways(p->children[1],indent+"  ");
    print_sideways(p->children[2],indent+"  ");
    print_sideways(p->children[3],indent+"  ");
  }

private:
  node* root_;
  unsigned int size_;
};

// ==============================================================
// ==============================================================
// Codes for my BalanceTree part

// Helper function to sort the vector by x coordinates of points
template <class number_type, class label_type>
bool rule(const std::pair<Point<number_type>,label_type>& pt1,
  const std::pair<Point<number_type>,label_type>& pt2) {
  return pt1.first.x < pt2.first.x;
}

// Helper function to sort the vector by y coordinates of points
template <class number_type, class label_type>
bool rule2(const std::pair<Point<number_type>,label_type>& pt1,
  const std::pair<Point<number_type>,label_type>& pt2) {
  return pt1.first.y < pt2.first.y;
}

// BalanceTree dirver function
// Replace the old vector with new result vector
template <class number_type, class label_type>
void BalanceTree(std::vector<std::pair<Point<number_type>,label_type> >& points) {
  if (points.size() == 0) return;
  std::vector<std::pair<Point<number_type>,label_type> > new_pts;
  points = BalanceTree(points, new_pts);
  return;
}

// BalaceTree actual recurse function
template <class number_type, class label_type>
std::vector<std::pair<Point<number_type>,label_type> >&
BalanceTree(std::vector<std::pair<Point<number_type>,label_type> >& points,
  std::vector<std::pair<Point<number_type>,label_type> >& new_pts) {
  // If the size of vector is 0, do nothing
  if (points.size() == 0) return new_pts;
  // If the size of vector is 1, add it to the new vector
  if (points.size() == 1) {
    new_pts.push_back(points[0]);
    return new_pts;
  }
  // Sort the vector
  std::sort(points.begin(), points.end(), rule<number_type, label_type>);
  unsigned int length = points.size();
  int mid;
  // Add the median point to the new vector depend on whether the size of vector
  // is even or odd
  if (length % 2 == 0) {
    mid = length / 2 - 1;
    new_pts.push_back(points[mid]);
  }
  else {
    mid = length / 2;
    new_pts.push_back(points[mid]);
  }
  // Create left sub vector and right sub vector for recursion
  std::vector<std::pair<Point<number_type>,label_type> > lpts;
  for (int i = 0; i < mid; ++i) lpts.push_back(points[i]);
  std::sort(lpts.begin(), lpts.end(), rule2<number_type, label_type>);

  std::vector<std::pair<Point<number_type>,label_type> > rpts;
  for (unsigned int i = mid+1; i < length; ++i) rpts.push_back(points[i]);
  std::sort(rpts.begin(), rpts.end(), rule2<number_type, label_type>);

  // Create upper half and lower half of left sub vector for recursion
  std::vector<std::pair<Point<number_type>,label_type> > lpts_up;
  std::vector<std::pair<Point<number_type>,label_type> > lpts_low;
  for (unsigned int i=0; i < lpts.size()/2; ++i) lpts_up.push_back(lpts[i]);
  for (unsigned int i=lpts.size()/2; i < lpts.size(); ++i) lpts_low.push_back(lpts[i]);

  // Create upper half and lower half of right sub vector for recursion
  std::vector<std::pair<Point<number_type>,label_type> > rpts_up;
  std::vector<std::pair<Point<number_type>,label_type> > rpts_low;
  for (unsigned int i=0; i < rpts.size()/2; ++i) rpts_up.push_back(rpts[i]);
  for (unsigned int i=rpts.size()/2; i < rpts.size(); ++i) rpts_low.push_back(rpts[i]);

  // Recursively find the median points of each sub vector
  BalanceTree(lpts_up, new_pts);
  BalanceTree(lpts_low, new_pts);
  BalanceTree(rpts_up, new_pts);
  BalanceTree(rpts_low, new_pts);

  return new_pts;
}

#endif
