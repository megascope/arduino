#include <FastLED.h>
#include <curses.h>
#include <iostream>
#include "panel_10x5.ino"

int main()
{
  setup();
  while (true) { 
    loop() ;
  }
}
