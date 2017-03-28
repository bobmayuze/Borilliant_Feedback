// File: Time.cpp
// Author: Ziniu Yu

#include "Time.h"
#include <iostream>
#include <iomanip>
#include <string>

Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int thehour, int themin, int thesec)
{
    hour = thehour;
    minute = themin;
    second = thesec;
}

int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

void Time::setHour(int h)
{
    hour = h;
}

void Time::setMinute(int m)
{
    minute = m;
}

void Time::setSecond(int s)
{
    second = s;
}

void Time::PrintAmPm() const
{
    int h;
    std::string AP;
    if (hour == 0)
    {
        h = hour + 12;
        AP = "am";
    }
    else if (0 < hour and hour < 12)
    {
        h = hour;
        AP = "am";
    }
    else if (hour == 12)
    {
        h = hour;
        AP = "pm";
    }
    else
    {
        h = hour - 12;
        AP = "pm";
    }
    std::cout << h << ":";
    std::cout << std::setw(2) << std::setfill('0') << minute << ":";
    std::cout << std::setw(2) << std::setfill('0') << second << " ";
    std::cout << AP << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
    if (t1.getHour() < t2.getHour())
        return true;
    else if (t1.getHour() > t2.getHour())
        return false;
    else
    {
        if (t1.getMinute() < t2.getMinute())
            return true;
        else if (t1.getMinute() > t2.getMinute())
            return false;
        else
        {
            if (t1.getSecond() < t2.getSecond())
                return true;
            else
                return false;
        }
    }
}