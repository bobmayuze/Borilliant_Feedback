#include <iostream>
#include <list>

void reverse_list(std::list<int>& lst) {
    int length = lst.size();
    int count;
    if (length != 0 or length != 1) {
        int temp;
        std::list<int>::iterator p = lst.begin();
        std::list<int>::reverse_iterator q = lst.rbegin();
        for (count = 0; count < length/2; ++count) {
            temp = *p;
            *p = *q;
            *q = temp;
            ++p;
            ++q;
        }
    }
}

void print_list(std::list<int>& lst) {
    std::cout << "Size: " << lst.size() << std::endl << "Content: ";
    std::list<int>::iterator p = lst.begin();
    for (; p != lst.end(); ++p) {
        std::cout << *p << ' ';
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::list<int> L1;
    for (int i = 11; i < 20; ++i)
        L1.push_back(i);
    print_list(L1);
    reverse_list(L1);
    print_list(L1);
    
    std::list<int> L2;
    for (int i = 11; i < 21; ++i)
        L2.push_back(i);
    print_list(L2);
    reverse_list(L2);
    print_list(L2);
    
    std::list<int> L3;
    L3.push_back(11);
    print_list(L3);
    reverse_list(L3);
    print_list(L3);
    
    std::list<int> L4;
    L4.push_back(11);
    L4.push_back(22);
    print_list(L4);
    reverse_list(L4);
    print_list(L4);
    
    std::list<int> L5;
    print_list(L5);
    reverse_list(L5);
    print_list(L5);
    
    return 0;
}