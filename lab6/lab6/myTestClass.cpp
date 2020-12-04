#include "myTestClass.h"


ErrorTestClass::ErrorTestClass()
{
    texterror = " ";
}

ErrorTestClass::ErrorTestClass(const std::string& name) {
    texterror = name;
    ++generator;
    count = generator;
}

int ErrorTestClass::get_count() { return count; }



void print_error_list(std::vector<ErrorTestClass> lst)
{
    ErrorTestClass item = lst.back();
    int len = item.get_count();

    for (int i{ 0 }; i < len; i++) {
        static_cast<ErrorTestClass*>(&lst[i])->printError();
    }
}
