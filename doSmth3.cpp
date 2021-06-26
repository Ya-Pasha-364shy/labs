// простой тест, реализующим потоком
#include "doSmth3.h"

void thread_func1() {
    promise1.set_exception(std::current_exception());
}

void thread_func2(const int a, const int b) {
    try {
        if (b == 0)
            std::cout << promise1.get_future().get() << std::endl;
    }
    catch (const std::exception& e) {
        // если поймал ошибку - выведет 0
        std::cout << e.what() << std::endl;
    }
}

int start4()
{
    std::thread th1(thread_func1);
    std::thread th2(thread_func2, 5, 0);
    th1.join();
    th2.join();

    return 0;
}
