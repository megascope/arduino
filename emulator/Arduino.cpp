#include "Arduino.h"
#include <unistd.h>
#include <iostream>
#include <chrono>

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

size_t SerialClass::readBytes(char * buffer, size_t size)
{
    size_t read = 0;
    auto beg = std::chrono::steady_clock::now();

    constexpr auto TIMEOUT = std::chrono::milliseconds(1000);

    while (read <= size) {
        int result = this->read();
        if (result < 0) {
            if ((std::chrono::steady_clock::now() - beg) < TIMEOUT) {
                continue;
            } else {
                break;
            }
         }
        buffer[read] = result;
        ++read;
    }
    return read;
}

int SerialClass::read() {
    std::lock_guard<std::mutex> guard(serial_access_);
    if ( inbound_.size() == 0 ) { return -1; }
    char front = inbound_.front();
    inbound_.pop_front();
    return front;
}

size_t SerialClass::write(char byte) {
    std::lock_guard<std::mutex> guard(serial_access_);
    outbound_.push_back(byte);
    return 1;
}

int SerialClass::hostread() {
    std::lock_guard<std::mutex> guard(serial_access_);
    if ( outbound_.size() == 0 ) { return -1; }
    char front = outbound_.front();
    outbound_.pop_front();
    return front;
}

size_t SerialClass::hostwrite(char byte) {
    std::lock_guard<std::mutex> guard(serial_access_);
    inbound_.push_back(byte);
    return 1;
}
