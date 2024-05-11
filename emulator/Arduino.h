#pragma once

#include <list>
#include <mutex>

#define PROGMEM
#define FL_PROGMEM
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define pgm_read_byte(x) *(x)
void delay(int millis);

struct SerialClass
{
    void begin(int);
    void println(const char*);
    int read();
    size_t readBytes(char * buffer, size_t size);
    size_t write(char byte);

    // methods for the "host" computer to read/write serial
    int hostread();
    size_t hostwrite(char byte);

private:
    std::mutex serial_access_;
    std::list<char> outbound_;
    std::list<char> inbound_;

};

static SerialClass Serial;
