// File: main.cpp
// Author: Ziniu Yu

#include "Time.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<Time> times;
    Time t1(0,0,0);
    times.push_back(t1);
    Time t2(12,0,0);
    times.push_back(t2);
    Time t3(14,4,5);
    times.push_back(t3);
    Time t4(14,4,6);
    times.push_back(t4);
    Time t5(14,5,5);
    times.push_back(t5);
    Time t6(10,35,23);
    times.push_back(t6);
    Time t7(12,0,0);
    times.push_back(t7);
    
    t1.PrintAmPm();
    t2.PrintAmPm();
    t3.PrintAmPm();
    
    if (IsEarlierThan(t2,t3))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    if (IsEarlierThan(t3,t2))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    if (IsEarlierThan(t3,t4))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    if (IsEarlierThan(t4,t3))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    if (IsEarlierThan(t4,t5))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    if (IsEarlierThan(t5,t4))
        std::cout << "earlier" << std::endl;
    else
        std::cout << "not earlier" << std::endl;
    
    sort(times.begin(), times.end(), IsEarlierThan);
    for (unsigned int i = 0; i < times.size(); ++i)
    {
        times[i].PrintAmPm();
    }
    return 0;
}