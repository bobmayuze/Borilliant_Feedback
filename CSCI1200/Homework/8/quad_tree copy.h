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

// -------------------------------------------------------------------
// TREE NODE CLASS
template <class number_type, class label_type>
class Node {
public:
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

// -------------------------------------------------------------------
// TREE NODE DEPTH ITERATOR CLASS
template <class number_type, class label_type>
class depth_iterator {
public:
  typedef Node<number_type, label_type> node;
  depth_iterator() : ptr_(NULL), root_(NULL) {}
  depth_iterator(node* p, node* q = NULL) : ptr_(p), root_(q) {}
  depth_iterator(const depth_iterator& old) : ptr_(old.ptr_), root_(old.root_) {}
  ~depth_iterator() {}
  depth_iterator& operator=(const depth_iterator& old) { ptr_ = old.ptr_; return *this; }

  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const depth_iterator& rgt) { return ptr_ == rgt.ptr_ && root_ == rgt.root_; }
  bool operator!= (const depth_iterator& rgt) { return ptr_ != rgt.ptr_ && root_ == rgt.root_; }

  // increment & decrement operators
  depth_iterator & operator++() {
    if (ptr_ == NULL) return *this;
    bool done = false;
    if (ptr_->children[0] != NULL) { ptr_ = ptr_->children[0]; done = true; }
    else if (ptr_->children[1] != NULL) { ptr_ = ptr_->children[1]; done = true; }
    else if (ptr_->children[2] != NULL) { ptr_ = ptr_->children[2]; done = true; }
    else if (ptr_->children[3] != NULL) { ptr_ = ptr_->children[3]; done = true; }
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
        if (!done) ptr_ = p;
      }
    }
    if (!done) ptr_ = NULL;
    return *this;
  }
  depth_iterator operator++(int) {
    depth_iterator temp(*this);
    ++(*this);
    return temp;
  }
//   iterator<T> & operator--() { /* implementation omitted */ }
//   iterator<T> operator--(int) {  iterator<T> temp(*this);  --(*this);  return temp;  }
  const label_type getLabel() const { return ptr_->label; }
  int getDepth() const {
    int depth = 0;
    node* p = root_;
    if (!p) return depth;
    while (p != NULL) {
      if (ptr_->pt.x == p->pt.x && ptr_->pt.y == p->pt.y) break;
      else if (ptr_->pt.x < p->pt.x && ptr_->pt.y < p->pt.y) p = p->children[0];
      else if (ptr_->pt.x > p->pt.x && ptr_->pt.y < p->pt.y) p = p->children[1];
      else if (ptr_->pt.x < p->pt.x && ptr_->pt.y > p->pt.y) p = p->children[2];
      else if (ptr_->pt.x > p->pt.x && ptr_->pt.y > p->pt.y) p = p->children[3];
      depth++;
    }
    return depth;
  }
private:
  // representation
  node* ptr_;
  node* root_;
};

// -------------------------------------------------------------------
// TREE NODE BREADTH ITERATOR CLASS
template <class number_type, class label_type>
class breadth_iterator {
public:
  typedef Node<number_type, label_type> node;
  breadth_iterator() : ptr_(NULL), root_(NULL) {}
  breadth_iterator(node* p, node* q = NULL) : ptr_(p), root_(q) {}
  breadth_iterator(const breadth_iterator& old) : ptr_(old.ptr_), root_(old.root_) {}
  ~breadth_iterator() {}
  breadth_iterator& operator=(const breadth_iterator& old) { ptr_ = old.ptr_; return *this; }

  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const breadth_iterator& rgt) { return ptr_ == rgt.ptr_ && root_ == rgt.root_; }
  bool operator!= (const breadth_iterator& rgt) { return ptr_ != rgt.ptr_ && root_ == rgt.root_; }

  std::list<node*> nodelist(node*& root) {
    std::list<node*> mylist;
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

  // increment & decrement operators
  breadth_iterator& operator++() {
    if (ptr_ == NULL) return *this;
    node* root = ptr_->parent;
    node* tmp = ptr_;
    while (root != NULL) {
      ptr_ = root;
      root = ptr_->parent;
    }
    std::list<node*> mylist = nodelist(ptr_);
    typename std::list<node*>::iterator itr;
    itr = std::find(mylist.begin(), mylist.end(), tmp);
    itr++;
    if (itr == mylist.end()) ptr_ = NULL;
    else ptr_ = *itr;
    // bool done = false;
    // if (ptr_->parent == NULL) {
    //   if (ptr_->children[0] != NULL) { ptr_ = ptr_->children[0]; done = true; }
    //   else if (ptr_->children[1] != NULL) { ptr_ = ptr_->children[1]; done = true; }
    //   else if (ptr_->children[2] != NULL) { ptr_ = ptr_->children[2]; done = true; }
    //   else if (ptr_->children[3] != NULL) { ptr_ = ptr_->children[3]; done = true; }
    // }
    // else {
    //   node* p;
    //   while (!done && ptr_->parent != NULL) {
    //     p = ptr_->parent;
    //     if (ptr_ == p->children[0]) {
    //       if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
    //       else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
    //       else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
    //     }
    //     else if (ptr_ == p->children[1]) {
    //       if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
    //       else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
    //     }
    //     else if (ptr_ == p->children[2]) {
    //       if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
    //     }
    //     bool done2 = false;
    //     int current_level = p->getDepth();
    //     if (!done) {
    //       node* q;
    //       while (!done && !done2 && p->parent != NULL) {
    //         q = p->parent;
    //         if (p == q->children[0]) {
    //           if (q->children[1] != NULL) { p = q->children[1]; }
    //           else if (q->children[2] != NULL) { p = q->children[2]; }
    //           else if (q->children[3] != NULL) { p = q->children[3]; }
    //         }
    //         else if (p == q->children[1]) {
    //           if (q->children[2] != NULL) { p = q->children[2]; }
    //           else if (q->children[3] != NULL) { p = q->children[3]; }
    //         }
    //         else if (p == q->children[2]) {
    //           if (q->children[3] != NULL) { p = q->children[3]; }
    //         }
    //         if (!done2) p = q;
    //       }
    //     }
    //   }
      // node* p;
      // while (!done && ptr_->parent != NULL) {
      // p = ptr_->parent;
      // if (ptr_ == p->children[0]) {
      //   if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
      //   else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //   else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      // }
      // else if (ptr_ == p->children[1]) {
      //   if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //   else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      // }
      // else if (ptr_ == p->children[2]) {
      //   if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      // }
      // // while (!done && ptr_->parent != NULL) {
      // else {
      //   // ptr_ = p;
      //   // std::cout<<"no"<<std::endl;
      //   // Node<number_type, label_type>* p;
      //   // while (!done && ptr_->parent != NULL) {
      //   p = ptr_->parent;
      //   if (p->children[0] != NULL) {
      //     p = p->children[0];
      //     if (p->children[0] != NULL) { ptr_ = p->children[0]; done = true; }
      //     else if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
      //     else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //     else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      //   }
      //   else if (p->children[1] != NULL) {
      //     p = p->children[1];
      //     if (p->children[0] != NULL) { ptr_ = p->children[0]; done = true; }
      //     else if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
      //     else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //     else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      //   }
      //   else if (p->children[2] != NULL) {
      //     p = p->children[2];
      //     if (p->children[0] != NULL) { ptr_ = p->children[0]; done = true; }
      //     else if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
      //     else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //     else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      //   }
      //   else if (p->children[3] != NULL) {
      //     p = p->children[3];
      //     if (p->children[0] != NULL) { ptr_ = p->children[0]; done = true; }
      //     else if (p->children[1] != NULL) { ptr_ = p->children[1]; done = true; }
      //     else if (p->children[2] != NULL) { ptr_ = p->children[2]; done = true; }
      //     else if (p->children[3] != NULL) { ptr_ = p->children[3]; done = true; }
      //   }
      //   if (!done) ptr_ = p;
        // }
      // }
    // }
    // }
    // if (!done) ptr_ = NULL;
    return *this;
  }

  breadth_iterator operator++(int) {
    breadth_iterator temp(*this);
    ++(*this);
    return temp;
  }

//   iterator<T> & operator--() { /* implementation omitted */ }
//   iterator<T> operator--(int) {  iterator<T> temp(*this);  --(*this);  return temp;  }
  const label_type getLabel() const { return ptr_->label; }
  int getDepth() const {
    int depth = 0;
    node* p = root_;
    if (!p) return depth;
    while (p != NULL) {
      if (ptr_->pt.x == p->pt.x && ptr_->pt.y == p->pt.y) break;
      else if (ptr_->pt.x < p->pt.x && ptr_->pt.y < p->pt.y) p = p->children[0];
      else if (ptr_->pt.x > p->pt.x && ptr_->pt.y < p->pt.y) p = p->children[1];
      else if (ptr_->pt.x < p->pt.x && ptr_->pt.y > p->pt.y) p = p->children[2];
      else if (ptr_->pt.x > p->pt.x && ptr_->pt.y > p->pt.y) p = p->children[3];
      depth++;
    }
    return depth;
  }
private:
  // representation
  node* ptr_;
  node* root_;
  // std::list<node*> queue;
};


// ==============================================================
// ==============================================================
// QuadTree Class
template <class number_type, class label_type>
class QuadTree {
public:
  typedef depth_iterator<number_type, label_type> iterator;
  typedef breadth_iterator<number_type, label_type> bf_iterator;
  typedef Point<number_type> point;
  typedef Node<number_type, label_type> node;
  typedef std::pair<iterator, bool> pair;

  QuadTree() {
    root_ = NULL;
    size_ = 0;
  }
  QuadTree(const QuadTree& old) { copy(old); }
  QuadTree& operator=(const iterator& old) {
    // if (root_ != NULL) destroy(root_);
    copy(old);
    return *this;
  }

  void copy(const QuadTree& old) {
    // destroy(root_);
    size_ = old.size_;
    if (size_ == 0) {
      root_ = NULL;
      return;
    }
    else {
      // root_ = new node(old.root_->pt, old.root_->label);
      // node* c0 = root_->children[0];
      // node* c1 = root_->children[1];
      // node* c2 = root_->children[2];
      // node* c3 = root_->children[3];
      copyNode(root_, root_, old.root_);
    }
  }
  void copyNode(node*& newtree, node*& parent, node* oldtree){
    if (oldtree == NULL) //base case to end recursion when at tree end
      newtree = NULL;
    else {
      // std::cout<<"1"<<std::endl;
      newtree = new node;  //create the node and set the new key to original
      // std::cout<<"2"<<std::endl;
      newtree->pt = point(oldtree->pt.x, oldtree->pt.y);
      newtree->label = oldtree->label;
      // std::cout<<"3"<<std::endl;
      if(newtree == parent) newtree->parent = NULL;
      else newtree->parent = parent;
      // std::cout<<"4"<<std::endl;
      // Just call recursively to copy the subtrees:
      copyNode(newtree->children[0], newtree, oldtree->children[0]);
      copyNode(newtree->children[1], newtree, oldtree->children[1]);
      copyNode(newtree->children[2], newtree, oldtree->children[2]);
      copyNode(newtree->children[3], newtree, oldtree->children[3]);
    }
  }

  ~QuadTree() { this->destroy(root_); root_ = NULL; }
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
  unsigned int size() const { return size_; }

  // ==============================================================
  // Insert
  // driver function
  pair insert(const point& point_, const label_type& label_) {
    return insert(point_, label_, root_, root_);
  }
  // actual recursive function
  pair insert(const point& point_, const label_type& label_, node*& p, node*& q) {
    // std::cout<<q<<std::endl;
    if (p == NULL) {
      // allocate a new node and make p point to it
      p = new node(point_, label_);
      this->size_++;
      // std::cout<<q<<std::endl;
      if (p != q) p->parent = q;
      return pair(iterator(p, root_), true);
    }
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
    node* p = root_;
    if (!p) return iterator(NULL, root_);
    while (p != NULL) {
      if (x == p->pt.x && y == p->pt.y) break;
      else if (x < p->pt.x && y < p->pt.y) p = p->children[0];
      else if (x > p->pt.x && y < p->pt.y) p = p->children[1];
      else if (x < p->pt.x && y > p->pt.y) p = p->children[2];
      else if (x > p->pt.x && y > p->pt.y) p = p->children[3];
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
  int height(node* p) const
  {
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


#endif
