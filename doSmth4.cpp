// загрузка данных в результирующий вектор только чётных значений
#include "doSmth4.h"


void fill_the_vector(std::vector<int>& in, std::vector<int>& out)
{
	for (const int& elem : in)
		if (elem % 2 == 0)
			out.push_back(elem);
}

int start5()
{
	std::thread t([] {
		std::lock_guard<std::mutex> lock(mutex4);
		fill_the_vector(input, output);
		});

	atomic_thread_fence(std::memory_order_release);

	std::thread t1([] {
		std::lock_guard<std::mutex> lock(mutex4);
		fill_the_vector(input1, output);
		});

	atomic_thread_fence(std::memory_order_acquire);

	t.join();
	t1.join();

	for (int& elem : output)
	{
		std::cout << elem << "; ";
	}
	return 0;
}