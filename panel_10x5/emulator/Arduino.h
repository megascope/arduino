#pragma once
#include <chrono>
#include <thread>

#define PROGMEM

void delay(int amount)
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    sleep_for(milliseconds(amount));
}
