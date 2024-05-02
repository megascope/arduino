#include <Arduino.h>
#include <FastLED.h>
#include "defines.h"

CRGB leds__[NUM_LEDS];
unsigned loop_count__;

void setup() {
  loop_count__ = 0;
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds__, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Serial Output enabled...");
#endif
}

void loop() {
  ++loop_count__;

}
