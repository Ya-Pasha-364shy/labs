#pragma once
#include <iostream>
#include <future>
#include <thread>

std::promise<int> promise1;

void thread_func1();
void thread_func2(const int a, const int b);
int start4();
