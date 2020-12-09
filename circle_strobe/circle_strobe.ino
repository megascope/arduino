#include "FastLED.h"

// For 16 LED circular lights
// using ELGOO NANO board, set target as UNO

#define NUM_LEDS 16
#define DATA_PIN 11
#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];

unsigned short idx = 0;
unsigned short prev = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

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
  idx = (idx + 1)% 127;

  switch (idx) {
    case 1:
    case 10:
    case 20:
    case 30:
    case 40:
    case 50:
    case 60:
    case 70:
    case 80:
    case 90:
    {
      for ( int i = 0; i < NUM_LEDS; ++i) {
         leds[i] = CRGB::White;
      }
      prev = idx + 1;
    }
    break;

    default:
      if ( idx == prev ) {
        for ( int i = 0; i < NUM_LEDS; ++i) {
           leds[i] = CRGB::Black;
        }
      }
    break;
  }
 
  FastLED.show();
  FastLED.delay(100);

}
