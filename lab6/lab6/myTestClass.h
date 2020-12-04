#pragma once
#include <vector>
#include <string>
#include <iostream>

class ErrorTestClass
{
private:
    static int generator;

protected:

    std::string texterror;
    int count;

public:
    ErrorTestClass();

    ErrorTestClass(const std::string& name);

    virtual void printError() {
        std::cout << texterror << std::endl;
    }

    int get_count();

    friend void print_error_list(std::vector<ErrorTestClass> lst);

    ~ErrorTestClass() {}
};
