#pragma once
#include <iostream>
#include <future>
#include <atomic>
#include <mutex>

std::mutex mutex2;
std::atomic<int> atom;

int start2();
