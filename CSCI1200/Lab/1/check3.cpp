#include <iostream>
#include <cmath>
#include <cstdlib>

int main()
{
    int num;
    float sum = 0.0, mean;
    std::cout << "Enter the length of the float array" << std::endl;
    std::cin >> num;
    std::cout << "Enter all the numbers" << std::endl;
    float myarray[num];
    for (int i = 0; i < num; i++)
    {
        std::cin >> myarray[i];
        sum += myarray[i];
    }
    mean = sum / num;
    std::cout << "The average is " << mean << "\nNumbers less than average are" << std::endl;
    for (int i = 0; i < num; i ++)
    {
        if (myarray[i] < mean)
        {
            std::cout << myarray[i] << std::endl;
        }
    }
    return 0;
}