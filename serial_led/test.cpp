#include <FastLED.h>
#include <iostream>
#include "serial_led.ino"

int main()
{
  setup();
  while (true) {
    loop() ;
  }
}
