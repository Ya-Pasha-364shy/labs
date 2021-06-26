#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mutex4;

std::vector<int> input{ 3, 5, 7, 11, 2, 6, 8 };
std::vector<int> input1{ 2, 0, 15, 22, 14 };

std::vector<int> output;

void fill_the_vector(std::vector<int>& in, std::vector<int>& out);
int start5();
