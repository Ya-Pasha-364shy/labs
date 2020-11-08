#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using namespace std;
#include "frame.h"
template <class T>
void TestFramework::RunTest(T funcForTest, const string& hint)
{
    try {
        funcForTest();
    }
    catch (exception& e) {
        ++fail_test;
        cerr << hint << " fail: " << e.what() << endl;
    }
    catch (...) {
        ++fail_test;
        cerr << "Unknown exception caught: " << hint << endl;
    }
}

TestFramework::~TestFramework() {
    cerr << fail_test << " is down" << endl;
}
#include "myTime.h"

// определение перегрузок бинарных операторов
Time operator+(const Time& t_1, const Time& t_2)
{
    Time t;
    t.seconds = (t_1.seconds + t_2.seconds) % 60;
    if (t_1.seconds + t_2.seconds > 60)
    {
        t.minutes += 1;
    }
    if (t_1.minutes + t_2.minutes + t.minutes > 60)
    {
        t.hours += 1;
        t.minutes += (t_1.minutes + t_2.minutes) % 60;
    }
    if (t_1.hours + t_2.hours + t.hours > 24)
    {
        t.hours = 1;
        return t;
    }
    else
        t.hours += (t_1.hours + t_2.hours) % 25;
    return t;
}


bool operator==(const Time& t_1, const Time& t_2)
{
    if ((t_1.hours == t_2.hours) && (t_1.minutes == t_2.minutes) && (t_1.seconds == t_2.seconds))
        return true;
    else
        return false;
}


Time operator-(const Time& t_1, const Time& t_2)
{
    return Time(t_1.hours - t_2.hours, t_1.minutes - t_2.minutes, t_1.seconds - t_2.seconds);
}

bool operator>(const Time& t_1, const Time& t_2)
{
    if (t_1.hours > t_2.hours && (t_1.minutes > t_2.minutes || t_1.seconds > t_2.seconds))
        return true;
    else
        return false;
}

bool operator<(const Time& t_1, const Time& t_2)
{
    if (t_1.hours < t_2.hours && (t_1.minutes < t_2.minutes || t_1.seconds < t_2.seconds))
        return true;
    else
        return false;
}


// определение перегрузок унарных операторов
Time operator+(const Time& t_1)
{
    return Time(t_1.hours + 1, t_1.minutes + 1, t_1.seconds + 1);
}

Time operator-(const Time& t_2)
{
    return Time(t_2.hours - 1, t_2.minutes - 1, t_2.seconds - 1);
}

// дополнительная функция вывода текущего времени
void print_time(const Time& obj)
{
    cout << "Current time (hours:minutes:seconds) : " << obj.hours << ":" << obj.minutes << ":" << obj.seconds << endl;
}

// функции, возвращающие новый объект класса Time с увелченными
// часами
Time addHours(const Time& t_1)
{
    return Time(t_1.hours + 1, t_1.minutes, t_1.seconds);
}

// минутами
Time addMinutes(const Time& t_1)
{
    return Time(t_1.hours, t_1.minutes + 1, t_1.seconds);
}

// секундами
Time addSeconds(const Time& t_1)
{
    return Time(t_1.hours, t_1.minutes, t_1.seconds + 1);
}



void TestFunc1()
{
    Time t1(12, 31, 30);

    if ((t1 + t1).getCurrentH() > 24)
        throw "Invalid sum hours";
    if ((t1 + t1).getCurrentM() > 60)
        throw "Invalid sum mins";
    if ((t1 + t1).getCurrentS() > 60)
        throw "Invalid sum mins";
}

void TestFunc2()
{
    Time t1(1, 1, 1);

    if ((t1 - t1).getCurrentH() < 0)
        throw "Invalid difference hourse";
    if ((t1 - t1).getCurrentM() < 0)
        throw "Invalid dfference minutes";
    if ((t1 - t1).getCurrentS() < 0)
        throw "Invalid difference seconds";

}

void TestFunc3()
{
    Time t1(15, 30, 0);
    Time t2(17, 45, 0);

    if (t1 > t2)
        throw "Error bool";
    if (t2 < t1)
        throw "Error bool";
    if (t2 == t1)
        throw "Error! Times are not equal";
}

void ErrTestFunc4()
{
    Time t1(15, 30, 0);
    Time t2(17, 45, 0);

    print_time(t2 - t1);

    if (((t2 - t1).getCurrentH() > 24))
        throw "Error one";
    if (((t1 - t2).getCurrentH() > 24))
        throw "You set a invalid time !";
    if (t1 == t2)
        throw "This times are not equal !";

}


int main()
{
    TestFramework testfrmwrk;

    testfrmwrk.RunTest(TestFunc1, "TestOneRoot");
    testfrmwrk.RunTest(TestFunc2, "TestTwoRoot");
    testfrmwrk.RunTest(TestFunc3, "TestThreeRoot");
    testfrmwrk.RunTest(ErrTestFunc4, "TestFourthRoot");

    Time t(14, 17, 30);
    cout << t;


    ofstream fout("2.txt");
    fout << t;

    return 0;
}