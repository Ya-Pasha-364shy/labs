#include <iostream>
#include <cstring>

using namespace std;


class Time
{
private:
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;

public:
    Time() {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
    }

    Time(int h, int m, int s)
    {
        try
        {
            if ((h < 1 || h > 24) || (m < 0 || m >= 60) || (s < 0 || s >= 60))
                throw "Wrong data was called !";
            else
            {
                this->hours = h;
                this->minutes = m;
                this->seconds = s;
                cout << "All right !" << endl;
            }
        }
        catch (const char* except)
        {
            cout << "Error!\n" << except << endl;
        }

    }

    int getCurrentH() const { return hours; }
    
    int getCurrentM() const { return minutes; }

    int getCurrentS() const { return seconds; }

    
    friend Time operator+(const Time &t_1, const Time &t_2);
    friend Time operator-(const Time &t_1, const Time &t_2);
    friend Time operator>(const Time& t_1, const Time& t_2);

    ~Time()
    {
        cout << "This is end!" << endl;
    }
};

Time operator+(const Time& t_1, const Time &t_2)
{
    return Time(t_1.hours + t_2.hours, t_1.minutes + t_2.minutes, t_1.seconds + t_2.seconds);
}

Time operator-(const Time& t_1, const Time& t_2)
{
    return Time(t_1.hours - t_2.hours, t_1.minutes - t_2.minutes, t_1.seconds - t_2.seconds);
}

Time operator>(const Time& t_1, const Time& t_2)
{

}

int main()
{

}