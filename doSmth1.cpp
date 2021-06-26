// алгоритм нахождения факториала
// n! = 1*2*3*...*n

#include "doSmth1.h"

int start2()
{

    std::cout << "Enter an integer number for result of factorial of this number: ";
    int number;
    std::cin >> number;

    atom = number;

    int result(1);
    while (atom != 1)
    {
        std::thread t([&result] {
            std::lock_guard<std::mutex> lock(mutex2);
            if (atom) {
                result *= atom;
                --atom;
            }});
        t.join();
    }
    std::cout << "Your result is: " << result << std::endl;

    return 0;
}

