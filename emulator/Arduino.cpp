#include "Arduino.h"
#include <unistd.h>
#include <iostream>
void delay(int millis)
{
    ::usleep(millis * 1000);
}

void SerialClass::println(const char* str)
{
    std::cout << "< " << str << std::endl;
}

void SerialClass::begin(int baud)
{
    std::cout << "< [Serial Output enabled @ " << baud << " baud]" << std::endl;;
}
