#pragma once
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

void do_start(int& a);
void write_ping_there();
void write_pong_there();
int start1();
