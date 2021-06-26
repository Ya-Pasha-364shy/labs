#include "for_ping_pong_realise.h"

std::mutex mutex1;
std::promise<int> promise;

void do_start(int& a)
{
    promise.set_value(a);
}

void write_ping_there()
{
    mutex1.lock();
    std::cout << "ping" << std::endl;
    mutex1.unlock();
}

void write_pong_there()
{
    std::lock_guard<std::mutex> lock(mutex1);
    std::cout << "pong" << std::endl;
}

int start1()
{
    int spam;
    std::cout << "Enter an integer iteration with will the start: " << std::endl;
    std::cin >> spam;

    std::atomic<int> arg(spam);

    
    std::thread thr(do_start, std::ref(arg));
    thr.join();

    int v = promise.get_future().get();
    std::cout << v << std::endl;

    // решение в лоб
    while (arg != 1000000)
    {

        std::thread t1(write_ping_there);
        t1.join();


        std::thread t2(write_pong_there);
        t2.join();

        ++arg;
    }
    return 0;
}