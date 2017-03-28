#include <iostream>
#include <vector>

void reverse_vector(std::vector<int>& vec) {
    int length = vec.size();
    if (length != 0 or length != 1) {
        int temp;
        for (int i = 0; i < length/2; ++i) {
            temp = vec[i];
            vec[i] = vec[length-1-i];
            vec[length-1-i] = temp;
        }
    }
}

void print_vector(std::vector<int>& vec) {
    std::cout << "Size: " << vec.size() << std::endl << "Content: ";
    for (unsigned int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::vector<int> V1;
    for (int i = 1; i < 10; ++i)
        V1.push_back(i);
    print_vector(V1);
    reverse_vector(V1);
    print_vector(V1);
    
    std::vector<int> V2;
    for (int i = 1; i < 11; ++i)
        V2.push_back(i);
    print_vector(V2);
    reverse_vector(V2);
    print_vector(V2);
    
    std::vector<int> V3;
    V3.push_back(1);
    print_vector(V3);
    reverse_vector(V3);
    print_vector(V3);
    
    std::vector<int> V4;
    V4.push_back(1);
    V4.push_back(2);
    print_vector(V4);
    reverse_vector(V4);
    print_vector(V4);
    
    std::vector<int> V5;
    print_vector(V5);
    reverse_vector(V5);
    print_vector(V5);
    
    return 0;
}