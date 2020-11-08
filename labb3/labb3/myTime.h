#pragma once

#include <cstdint>
#include <iostream>
#include <ostream>
using namespace std;


// описание класса
class Time
{
private:
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;

public:
    Time();
    Time(int h, int m, int s);

    friend Time addHours(const Time& t_1);
    friend Time addMinutes(const Time& t_1);
    friend Time addSeconds(const Time& t_1);

    uint32_t getCurrentH();

    uint32_t getCurrentM();

    uint32_t getCurrentS();

    friend ostream& operator<<(ostream& os, const Time& t);

    friend Time operator+(const Time& t_1, const Time& t_2);
    friend Time operator-(const Time& t_1, const Time& t_2);
    friend bool operator>(const Time& t_1, const Time& t_2);
    friend bool operator<(const Time& t_1, const Time& t_2);

    // Раздел прототипов дружественных унарных операторов
    friend Time operator+(const Time& t_1);
    friend Time operator-(const Time& t_1);

    // распечатка текущего времени
    friend void print_time(const Time& obj);


    // перегрузка оператора сравнения 
    friend bool operator==(const Time& t_1, const Time& t_2);

    void SetTime(int h, int m, int s);
};

