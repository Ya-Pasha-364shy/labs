#pragma once

#include <iostream>
#include <cstring>


class TestFramework {
private:
    int fail_test = 0;
public:
    template <class T>
    void RunTest(T funcForTest, const std::string& hint);

    ~TestFramework();
};