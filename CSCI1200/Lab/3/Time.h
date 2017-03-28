// File: Time.h
// Auther: Ziniu Yu

class Time
{
public:
    Time();
    Time(int thehour, int themin, int thesec);
    
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    
    void setHour(int thehour);
    void setMinute(int themin);
    void setSecond(int thesec);
    
    void PrintAmPm() const;
    
private:
    int hour;
    int minute;
    int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);