#include <iostream>
#include <list>
#include <string>

    // if(input->ptr == NULL) return input;
    // Node *prev = NULL;
    // Node *curr = NULL;
    // Node *next = NULL;
    // curr = input->ptr;
    // while(curr != NULL){
    //     next = curr->ptr;
    //     curr->ptr = prev;
    //     prev = curr;
    //     curr = next;
    // }
    // input->ptr = prev;
    // return input;

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {

  // create a linked list chain of Nodes, populating the structure
  // with the data in the STL list
  std::list<int>::const_iterator p = lst.begin();
  Node* head = NULL;
  Node* tmp = new Node;
  head = tmp;
  while (p != lst.end()) {
      tmp->value = (*p);
      ++p;
      if (p == lst.end()) {
          break;
      }
      tmp->ptr = new Node;
      tmp = tmp->ptr;
  }
  tmp->ptr = NULL;
  return head;
  // NOTE: this code should work for input STL lists of arbitrary
  // length

}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {

  // rearrange the pointers in the linked list chain of Nodes,
  // so that the structure is reversed.    
    Node *a = input, *b = input->ptr;
    while(a->ptr!=NULL)
    {
        b = a->ptr;
        a->ptr = a->ptr->ptr;
        b->ptr = input;
        input = b;
    }
    return input;
  // NOTE: Do not edit the values of the Nodes.  Do not create any new
  // Node objects (don't call 'new').  Instead, change the ptrs of the
  // existing Nodes to shuffle the order.

}
// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  // print out this list
  print_linked_list("a",a);

  // create an STL list with 4 elements
  std::list<int> b;
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);
  b.push_back(13);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c = make_linked_list_from_STL_list(b);
  // print that data
  print_linked_list("c",c);

  // 
  // WRITE A FEW MORE TEST CASES OF make_linked_list_from_STL_list
  //
  
    std::list<int> L1;
    for (int i = 11; i < 20; ++i)
        L1.push_back(i);
    Node* c1 = make_linked_list_from_STL_list(L1);
    print_linked_list("c1",c1);
    
    std::list<int> L2;
    for (int i = 11; i < 21; ++i)
        L2.push_back(i);
    Node* c2 = make_linked_list_from_STL_list(L2);
    print_linked_list("c2",c2);
    
    std::list<int> L3;
    L3.push_back(11);
    Node* c3 = make_linked_list_from_STL_list(L3);
    print_linked_list("c3",c3);
    
    std::list<int> L4;
    L4.push_back(11);
    L4.push_back(22);
    Node* c4 = make_linked_list_from_STL_list(L4);
    print_linked_list("c4",c4);
    
    std::list<int> L5;
    Node* c5 = make_linked_list_from_STL_list(L5);
    print_linked_list("c5",c5);
    
  // reverse a linked list of nodes
  Node* d = reverse_nodes_in_linked_list(c);
  // print this data
  print_linked_list("d",d);

  // 
  // WRITE A FEW MORE TEST CASES OF reverse_nodes_in_linked_list
  //

    Node* d1 = reverse_nodes_in_linked_list(c1);
    print_linked_list("d1",d1);
    
    Node* d2 = reverse_nodes_in_linked_list(c2);
    print_linked_list("d2",d2);

    Node* d3 = reverse_nodes_in_linked_list(c3);
    print_linked_list("d3",d3);
    
    Node* d4 = reverse_nodes_in_linked_list(c4);
    print_linked_list("d4",d4);

    Node* d5 = reverse_nodes_in_linked_list(c5);
    print_linked_list("d5",d5);

  // NOTE: We are not deleting any of the Nodes we created...  so this
  //       program has some memory leaks!  More on this in future
  //       lectures & labs :)

}

// ===========================================================================
