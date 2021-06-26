// файлы с доп заданиями компилировать отдельно
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>

std::mutex mutex;

// ping - pong
// два потока по очереди выводят в консоль сообщение
// первый - ping
// второй - pong
// вывести ping-pong по 500 000 раз каждый


int main()
{
    std::atomic<bool> done(false);
    std::atomic<int> couter(1);

    while (couter != 1000000)
    {
        std::thread t([&done] {
            std::lock_guard<std::mutex> lock(mutex);
            if (!done) {
                std::cout << "ping" << std::endl;
                done = true;
            }});

        t.join();

        std::thread t1([&done] {if (done) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "pong" << std::endl;
            done = false;
        }});

        t1.join();

        ++couter;
    }

    return 0;
}
