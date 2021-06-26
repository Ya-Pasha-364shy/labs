// алгоритм сортировки с барьером
#include "doSmth2.h"

// вывод массива
void printArray(std::vector<int>& arr) {

    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void mySort(std::vector<int>& my_array) {

    int length = static_cast<int>(my_array.size());
    for (int i{ 0 }; i < length; i++)
    {
        int smlIdx = i;
        for (int j = smlIdx + 1; j < length; j++)
        {
            if (my_array[smlIdx] > my_array[j]) { smlIdx = j; }
        }

        std::swap(my_array[i], my_array[smlIdx]);
    }
}


int start3()
{
	std::vector<int> my_array = { 5, 3, 4, 11, 12, 9, 0, 1, 15 };
    mySort(my_array);

	bool ready;
	// не будем ничего записывать, пока не выполнятся инструкции до барьера
	atomic_thread_fence(std::memory_order_release);
	ready = true;

    if (ready)
    {
        printArray(my_array);
    }
    // ничего не делать, пока не завершится считывание
    atomic_thread_fence(std::memory_order_acquire);

    std::cout << "This is end" << std::endl;

    return 0;
}
