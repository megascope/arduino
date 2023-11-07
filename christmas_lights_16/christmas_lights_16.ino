#include "FastLED.h"

// For 16 LED circular lights
// using ELGOO NANO board, set target as UNO

#define NUM_LEDS 16
#define DATA_PIN 11

CRGB leds[NUM_LEDS];

unsigned short idx = 0;
unsigned short prev = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
#ifdef DEBUG
  Serial.begin(9600);
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
  test();
}

void test()
{

  unsigned short curr = idx < NUM_LEDS ? idx : 2*NUM_LEDS-idx;
  leds[prev] = CRGB(0,0,0);
  leds[curr] = CRGB(100,0,0);
  prev = curr;
  
  FastLED.show();
  if (++idx >= 2*NUM_LEDS) { idx = 0; }
  delay(50);
}
