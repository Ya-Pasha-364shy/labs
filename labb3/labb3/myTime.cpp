#include "myTime.h"
// определение методов и самого класса

Time::Time()
{
    this->hours = 0;
    this->minutes = 0;
    this->seconds = 0;
}
Time::Time(int h, int m, int s)
{
    this->hours = h;
    this->minutes = m;
    this->seconds = s;
}

uint32_t Time::getCurrentH() { return hours; }
uint32_t Time::getCurrentM() { return minutes; }
uint32_t Time::getCurrentS() { return seconds; }

void Time::SetTime(int h, int m, int s)
{
    this->hours = h;
    this->minutes = m;
    this->seconds = s;
}

ostream& operator<<(ostream& os, const Time& t)
{
    os << "Current time now is: " << t.hours << " : " << t.minutes << " : " << t.seconds << '\n';
    return os;
}