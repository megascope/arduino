#include "Arduino.h"
#include <unistd.h> 
void delay(int millis)
{
    ::usleep(millis * 1000);
}
