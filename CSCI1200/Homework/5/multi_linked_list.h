#ifndef multi_linked_list_h_
#define multi_linked_list_h_

#include <cassert>
#include <ctime>
#include "mtrand.h"

// ================================================================================
// ================================================================================
// NODE CLASS
template <class T>
class Node {
public:
  Node();
  Node(const T& v);
  // REPRESENTATION
  T value_;
  Node<T>* chrono_next_;
  Node<T>* chrono_prev_;
  Node<T>* sorted_next_;
  Node<T>* sorted_prev_;
  Node<T>* random_next_;
};

// ================================================================================
// ================================================================================
// NODE CLASS IMPLEMENTATION
template <class T>
Node<T>::Node() { // default constructor
  chrono_next_ = NULL;
  chrono_prev_ = NULL;
  sorted_next_ = NULL;
  sorted_prev_ = NULL;
  random_next_ = NULL;
}

template <class T>
Node<T>::Node(const T& v) { // constructor with value
  value_ = v;
  chrono_next_ = NULL;
  chrono_prev_ = NULL;
  sorted_next_ = NULL;
  sorted_prev_ = NULL;
  random_next_ = NULL;
}

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// ================================================================================
// ================================================================================
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator();
  list_iterator(const list_iterator<T>& old);
  list_iterator(std::string type, MultiLL<T>* q, MTRand_int32* seed = NULL);
  list_iterator<T>& operator=(const list_iterator<T>& old);
  ~list_iterator() {}
  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->value_;  }
  // increment & decrement operators
  list_iterator<T>& operator++();   // pre-increment, e.g., ++iter
  list_iterator<T> operator++(int); // post-increment, e.g., iter++
  list_iterator<T>& operator--();   // pre-decrement, e.g., --iter
  list_iterator<T> operator--(int); // post-decrement, e.g., iter--
  friend class MultiLL<T>;
  typedef list_iterator<T> iterator;
  // generate random pointer to next element
  Node<T>* generate_random(MultiLL<T>* multi, MTRand_int32* seed);
  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const { return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const { return ptr_ != r.ptr_; }
private:
  // REPRESENTATION
  Node<T>* ptr_; // ptr to node in the list
  Node<T>* chrono_head_;
  Node<T>* chrono_tail_;
  Node<T>* sorted_head_;
  Node<T>* sorted_tail_;
  Node<T>* random_head_;
  std::string type_;
};

// ================================================================================
// ================================================================================
// LIST ITERATION IMPLEMENTATION
template <class T>
list_iterator<T>::list_iterator() { // default constructor
  ptr_ = NULL;
  chrono_head_ = NULL;
  chrono_tail_ = NULL;
  sorted_head_ = NULL;
  sorted_tail_ = NULL;
  random_head_ = NULL;
}

template <class T>
list_iterator<T>::list_iterator(std::string type, MultiLL<T>* q, MTRand_int32* seed) {
  type_ = type;
  chrono_head_ = q->chrono_head();
  chrono_tail_ = q->chrono_tail();
  sorted_head_ = q->sorted_head();
  sorted_tail_ = q->sorted_tail();
  random_head_ = q->random_head();
  if (type == "chrono_end" || type == "sorted_end") ptr_ = NULL;
  else if (type == "chrono") ptr_ = chrono_head_;
  else if (type == "sorted") ptr_ = sorted_head_;
  // generate random pointer every time when this function is called
  else if (type == "random") {
    random_head_ = generate_random(q, seed);
    q->set_random_head(random_head_);
    ptr_ = random_head_;
  }
}

template <class T>  // copy constructor
list_iterator<T>::list_iterator(const list_iterator<T>& old) {
  ptr_ = old.ptr_;
  type_ = old.type_;
  chrono_head_ = old.chrono_head_;
  chrono_tail_ = old.chrono_tail_;
  sorted_head_ = old.sorted_head_;
  sorted_tail_ = old.sorted_tail_;
  random_head_ = old.random_head_;
}

template <class T>  // assignment operator
typename list_iterator<T>::iterator& list_iterator<T>::operator=(const list_iterator<T>& old) {
  ptr_ = old.ptr_;
  type_ = old.type_;
  chrono_head_ = old.chrono_head_;
  chrono_tail_ = old.chrono_tail_;
  sorted_head_ = old.sorted_head_;
  sorted_tail_ = old.sorted_tail_;
  random_head_ = old.random_head_;
  return *this;
}

template <class T>  // pre-increment, e.g., ++iter
typename list_iterator<T>::iterator& list_iterator<T>::operator++() {
  if (type_ == "chrono"){
    ptr_ = ptr_->chrono_next_;
    // change the type of iterator when it reaches the last element
    if (ptr_ == NULL) type_ = "chrono_end";
  }
  else if (type_ == "sorted"){
    ptr_ = ptr_->sorted_next_;
    // change the type of iterator when it reaches the last element
    if (ptr_ == NULL) type_ = "sorted_end";
  }
  else if (type_ == "random") ptr_ = ptr_->random_next_;
  // change the type of iterator when it points from head to the first element
  else if (type_ == "chrono_begin") {
    ptr_ = chrono_head_;
    type_ = "chrono";
  }
  // change the type of iterator when it points from head to the first element
  else if (type_ == "sorted_begin") {
    ptr_ = sorted_head_;
    type_ = "sorted";
  }
  return *this;
}

template <class T>  // post-increment, e.g., iter++
typename list_iterator<T>::iterator list_iterator<T>::operator++(int) {
  list_iterator<T> temp(*this);
  if (type_ == "chrono"){
    ptr_ = ptr_->chrono_next_;
    // change the type of iterator when it reaches the last element
    if (ptr_ == NULL) type_ = "chrono_end";
  }
  else if (type_ == "sorted"){
    ptr_ = ptr_->sorted_next_;
    // change the type of iterator when it reaches the last element
    if (ptr_ == NULL) type_ = "sorted_end";
  }
  else if (type_ == "random") ptr_ = ptr_->random_next_;
  else if (type_ == "chrono_begin") {
    ptr_ = chrono_head_;
    // change the type of iterator when it points from head to the first element
    type_ = "chrono";
  }
  else if (type_ == "sorted_begin") {
    ptr_ = sorted_head_;
    // change the type of iterator when it points from head to the first element
    type_ = "sorted";
  }
  return temp;
}

template <class T>  // pre-decrement, e.g., --iter
typename list_iterator<T>::iterator& list_iterator<T>::operator--() {
  if (type_ == "chrono") {
    ptr_ = ptr_->chrono_prev_;
    // change the type of iterator when it reaches the first element
    if (ptr_ == NULL) type_ = "chrono_begin";
  }
  else if (type_ == "sorted") {
    ptr_ = ptr_->sorted_prev_;
    // change the type of iterator when it reaches the first element
    if (ptr_ == NULL) type_ = "sorted_begin";
  }
  else if (type_ == "chrono_end") {
    ptr_ = chrono_tail_;
    // change the type of iterator when it points from end to the last element
    type_ = "chrono";
  }
  else if (type_ == "sorted_end") {
    ptr_ = sorted_tail_;
    // change the type of iterator when it points from end to the last element
    type_ = "sorted";
  }
  return *this;
}

template <class T>  // post-decrement, e.g., iter--
typename list_iterator<T>::iterator list_iterator<T>::operator--(int) {
  list_iterator<T> temp(*this);
  if (type_ == "chrono") {
    ptr_ = ptr_->chrono_prev_;
    // change the type of iterator when it reaches the first element
    if (ptr_ == NULL) type_ = "chrono_begin";
  }
  else if (type_ == "sorted") {
    ptr_ = ptr_->sorted_prev_;
    // change the type of iterator when it reaches the first element
    if (ptr_ == NULL) type_ = "sorted_begin";
  }
  else if (type_ == "chrono_end") {
    ptr_ = chrono_tail_;
    // change the type of iterator when it points from end to the last element
    type_ = "chrono";
  }
  else if (type_ == "sorted_end") {
    ptr_ = sorted_tail_;
    // change the type of iterator when it points from end to the last element
    type_ = "sorted";
  }
  return temp;
}

// generate random pointer based on current time. Suppose 1 means there is
// something, 0 means NULL, R means random, and there are 10 element in the
// beginning. The MultiLL pointers array looks like this: pointer 11111111111
// We create a copy of it tmp_pointer 1111111111
// After we randomly choose an element: pointer 1111R11111
// We set random head to that R, and copy the rest elements to tmp_pointer
// (skip that element) and pointer: tmp_pointer 111111110 pointer 111111110
// and we choose the next one in the first 9 elements: pointer 111111R110
// and keep copying and choosing until there are no elements in the tmp_pointer
// tmp_pointer 0000000000, which also means the counter is equal to the size
template <class T>
Node<T>* list_iterator<T>::generate_random(MultiLL<T>* multi, MTRand_int32* seed) {
  int size = multi->size();
  if (size == 0) return NULL;
  // create two array pointer and tmp_pointer to store all elements in MultiLL
  // by chronological order
  Node<T>* tmp = multi->chrono_head();
  Node<T>** pointer = new Node<T>*[size];
  Node<T>** tmp_pointer = new Node<T>*[size];
  for (int i = 0; i < size; ++i) {
    pointer[i] = tmp;
    tmp = tmp->chrono_next_;
  }
  // randomly choose the head element
  int count = 1;
  int random = (*seed)() % (size+1);
  Node<T>* random_head = pointer[random];
  tmp = random_head;
  while (count != size) {
    // initialize tmp_pointer
    for (int i = 0; i < size; ++i) tmp_pointer[i] = NULL;
    // copy the rest element to tmp_pointer
    for (int i = 0, j = 0; i < size-count; ++i && ++j) {
      if (j == random) ++j;
      tmp_pointer[i] = pointer[j];
    }
    // choose the next element from tmp_pointer
    random = (*seed)() % (size-count);
    tmp->random_next_ = tmp_pointer[random];
    tmp = tmp->random_next_;
    count++;
    // initialize pointer and copy the rest of tmp_pointer to it
    for (int i = 0; i < size; ++i) pointer[i] = NULL;
    for (int i = 0; i < size; ++i) pointer[i] = tmp_pointer[i];
  }
  delete[] pointer;
  delete[] tmp_pointer;
  // set the last random_next_ to random_head to form a circular link list
  tmp->random_next_ = random_head;
  return random_head;
}

// ================================================================================
// ================================================================================
// LIST CLASS DECLARATION
template <class T>
class MultiLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  MultiLL();
  MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
  MultiLL& operator= (const MultiLL<T>& old);
  ~MultiLL() { this->destroy_list(); }
  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return chrono_head_ == NULL; }
  void clear() { this->destroy_list(); }
  // read/write access to contents
  const Node<T>* chrono_head() const { return chrono_head_;  }
  Node<T>* chrono_head() { return chrono_head_; }
  const Node<T>* chrono_tail() const { return chrono_tail_; }
  Node<T>* chrono_tail() { return chrono_tail_; }
  const Node<T>* sorted_head() const { return sorted_head_;  }
  Node<T>* sorted_head() { return sorted_head_; }
  const Node<T>* sorted_tail() const { return sorted_tail_; }
  Node<T>* sorted_tail() { return sorted_tail_; }
  const Node<T>* random_head() const { return random_head_;  }
  Node<T>* random_head() { return random_head_; }
  void set_random_head(Node<T>* random_head) { random_head_ = random_head; }
  void add(T& v);
  // other modifiers and accessors to certain elements
  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator begin_chronological() { return iterator("chrono", this); }
  iterator begin_sorted() { return iterator("sorted", this); }
  iterator begin_random() { return iterator("random", this, seed_); }
  iterator end_chronological() { return iterator("chrono_end", this); }
  iterator end_sorted() { return iterator("sorted_end", this); }
private:
  // private helper functions
  void copy_list(const MultiLL<T>& old);
  void destroy_list();
  //REPRESENTATION
  Node<T>* chrono_head_;
  Node<T>* chrono_tail_;
  Node<T>* sorted_head_;
  Node<T>* sorted_tail_;
  Node<T>* random_head_;
  unsigned int size_;
  MTRand_int32* seed_;
};

// ================================================================================
// ================================================================================
// LIST CLASS IMPLEMENTATION
template <class T>
MultiLL<T>::MultiLL() { // default constructor
  chrono_head_ = NULL;
  chrono_tail_ = NULL;
  sorted_head_ = NULL;
  sorted_tail_ = NULL;
  random_head_ = NULL;
  size_ = 0;
  // set the seed at the very beginning
  MTRand_int32 mtrand_autoseed(time(NULL));
  seed_ = &mtrand_autoseed;
}

// copy constructor
// create a new MultiLL, add all values of old MultiLL to it
template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>& old) {
  if (old.chrono_head() == NULL) return;
  chrono_head_ = NULL;
  chrono_tail_ = NULL;
  sorted_head_ = NULL;
  sorted_tail_ = NULL;
  random_head_ = NULL;
  size_ = 0;
  const Node<T>* tmp = old.chrono_head();
  // check if it is an empty MultiLL
  while (tmp != NULL) {
    T val = tmp->value_;
    this->add(val);
    tmp = tmp->chrono_next_;
  }
}

template <class T>  // assignment operator
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

template <class T>  // add functiion
void MultiLL<T>::add(T& v) {
  Node<T>* tmp = new Node<T>;
  Node<T>* ptr = sorted_head_;
  bool added = false;
  tmp->value_ = v;
  size_++;
  // The chronological list is empty
  if (chrono_head_ == NULL) {
    tmp->chrono_next_ = NULL;
    tmp->chrono_prev_ = NULL;
    chrono_head_ = tmp;
    chrono_tail_ = tmp;
  }
  // The chronological list is not empty
  else {
    tmp->chrono_next_ = NULL;
    tmp->chrono_prev_ = chrono_tail_;
    chrono_tail_->chrono_next_ = tmp;
    chrono_tail_ = tmp;
  }
  // The sorted list is empty.
  if (sorted_head_ == NULL) {
    tmp->sorted_next_ = NULL;
    tmp->sorted_prev_ = NULL;
    sorted_head_ = tmp;
    sorted_tail_ = tmp;
  }
  // The sorted list is not empty
  else {
    // The first element to be added
    if (tmp->value_ < ptr->value_) {
      ptr->sorted_prev_ = tmp;
      tmp->sorted_prev_ = NULL;
      tmp->sorted_next_ = ptr;
      sorted_head_ = tmp;
      added = true;
    }
    // The middle element to be added
    while (ptr != NULL && !added) {
      if (tmp->value_ < ptr->value_) {
        ptr->sorted_prev_->sorted_next_ = tmp;
        tmp->sorted_prev_ = ptr->sorted_prev_;
        tmp->sorted_next_ = ptr;
        ptr->sorted_prev_ = tmp;
        added = true;
        break;
      }
      ptr = ptr->sorted_next_;
    }
    // The last element to be added
    if (!added) {
      sorted_tail_->sorted_next_ = tmp;
      tmp->sorted_prev_ = sorted_tail_;
      tmp->sorted_next_ = NULL;
      sorted_tail_ = tmp;
    }
  }
}

// Erase function. Erase some element, return the next element
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
  Node<T>* tmp = itr.ptr_;
  iterator result = itr;
  result.type_ = itr.type_;
  // Make sure only valid element can be erased
  if (itr.type_ == "chrono" || itr.type_ == "sorted" || itr.type_ == "random") {
    --size_;  // decrement the size
    if (itr.type_ == "chrono") {
      result.ptr_ = tmp->chrono_next_;
      // change the type of iterator when it reaches the last element
      if (result.ptr_ == NULL) result.type_ = "chrono_end";
    }
    else if (itr.type_ == "sorted") {
      result.ptr_ = tmp->sorted_next_;
      // change the type of iterator when it reaches the last element
      if (result.ptr_ == NULL) result.type_ = "sorted_end";
    }
    else if (itr.type_ == "random") result.ptr_ = tmp->random_next_;
    // After change the iterator, change the pointers of element
    // If no element remains in MultiLL, set head and tail to NULL
    if (size_ == 0) {
      chrono_head_ = NULL;
      chrono_tail_ = NULL;
      sorted_head_ = NULL;
      sorted_tail_ = NULL;
      random_head_ = NULL;
    }
    else {
      // chronological list
      // if the Node to be erased is the first element, set the head point to
      // the second Node
      if (tmp->chrono_prev_ == NULL && tmp->chrono_next_ != NULL) {
        tmp->chrono_next_->chrono_prev_ = NULL;
        chrono_head_ = tmp->chrono_next_;
      }
      // if the Node to be erased is the last element, set the tail point to
      // the last but one Node
      else if (tmp->chrono_prev_ != NULL && tmp->chrono_next_ == NULL) {
        tmp->chrono_prev_->chrono_next_ = NULL;
        chrono_tail_ = tmp->chrono_prev_;
      }
      // Normal cases
      else {
        tmp->chrono_prev_->chrono_next_ = tmp->chrono_next_;
        tmp->chrono_next_->chrono_prev_ = tmp->chrono_prev_;
      }
      // sorted list
      // if the Node to be erased is the first element, set the head point to
      // the second Node
      if (tmp->sorted_prev_ == NULL && tmp->sorted_next_ != NULL) {
        tmp->sorted_next_->sorted_prev_ = NULL;
        sorted_head_ = tmp->sorted_next_;
      }
      // if the Node to be erased is the last element, set the tail point to
      // the last but one Node
      else if (tmp->sorted_prev_ != NULL && tmp->sorted_next_ == NULL) {
        tmp->sorted_prev_->sorted_next_ = NULL;
        sorted_tail_ = tmp->sorted_prev_;
      }
      // Normal cases
      else {
        tmp->sorted_prev_->sorted_next_ = tmp->sorted_next_;
        tmp->sorted_next_->sorted_prev_ = tmp->sorted_prev_;
      }
    }
    delete tmp;
  }
return result;
}

template <class T>
void MultiLL<T>::destroy_list() {
  while (chrono_head_ != NULL) {
    Node<T>* p = chrono_head_;   // save current head pointer
    chrono_head_ = chrono_head_->chrono_next_;
    delete p;
    size_--;
  }
}

#endif
