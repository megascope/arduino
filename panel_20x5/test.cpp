#if EMULATOR
#include <FastLED.h>
#include <iostream>
#include "panel_20x5.ino"

int main()
{
  setup();
  while (true) {
    loop() ;
  }
}
#endif
