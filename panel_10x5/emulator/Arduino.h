#pragma once

#define PROGMEM
#define FL_PROGMEM
#define min(a,b) ((a)<(b)?(a):(b))
#define pgm_read_byte(x) *(x)
void delay(int millis);

