#include "FastLED.h"

#define NUM_LEDS 16
#define DATA_PIN 11
#define ASTEPS 256


CRGB c1(10,0,0);
CRGB c2(0,0,10);
CRGB leds[NUM_LEDS];
unsigned short idx = 0;

#define HUE 255

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop()
{
  classic16();
}

void classic16()
{
  // math works because % 16 == &0xF
  const int LCNT = 16;
  const int MASK = 15;

  int i = idx;
  for ( int j = 0; j < LCNT; ++j ) {
    switch (j)
    {
      case 10: case 4: leds[i] = CRGB(HUE/4, 0, 0); break;
      case 9: case 5: leds[i] = CRGB(HUE/3, 0, 0); break;
      case 8: case 6: leds[i] = CRGB(HUE/2, 0, 0); break;
      case 7: leds[i] = CRGB(HUE, 0, 0); break;

      case 12: case 2: leds[i] = CRGB(0, 0, HUE/4); break;
      case 13: case 1: leds[i] = CRGB(0, 0, HUE/3); break;
      case 14: case 0: leds[i] = CRGB(0, 0, HUE/2); break;
      case 15: leds[i] = CRGB(0, 0, HUE); break;
      
      default: leds[i] = CRGB(0,0,0); break;
    }
    i = (i + 1) & MASK;
  }
  idx = (idx + 1) & MASK;
  FastLED.show();
  delay(75);
}

void alternate2()
{
  unsigned char bright = idx;
  if (bright > ASTEPS/2) { bright = ASTEPS - bright; }
  if (bright < 5) { bright = 5; }
  for (int i = 0; i < NUM_LEDS/2; ++i) {
    leds[i] = CRGB(0,bright/2,bright);
  }

  bright = idx;
  bright += 128;
  if (bright > ASTEPS/2) { bright = ASTEPS - bright; }
  if (bright < 5) { bright = 5; }
  for (int i = NUM_LEDS/2; i < NUM_LEDS; ++i) {
    leds[i] = CRGB(bright,bright/2,0);
  }

  ++idx;
  if (++idx >= ASTEPS) { idx = 0; }
  FastLED.show();
  delay(5);
}

void alternate1()
{
  if (idx == 0) {
    for (int i = NUM_LEDS/2; i < NUM_LEDS; ++i) {
      leds[i] = CRGB::Black;
    }
  } else if (idx == ASTEPS/2) {
    for (int i = 0; i < NUM_LEDS/2; ++i) {
      leds[i] = CRGB::Black;
    }
  }
  if (idx < ASTEPS/2)
  {
    unsigned char bright = idx;
    if (bright > ASTEPS/4) { bright = ASTEPS/2 - bright; }
    for (int i = 0; i < NUM_LEDS/2; ++i) {
      leds[i] = CRGB(bright,0,0);
    }
  } else {
    unsigned char bright = idx-ASTEPS/2;
    if (bright > ASTEPS/4) { bright = ASTEPS/2 - bright; }
    for (int i = NUM_LEDS/2; i < NUM_LEDS; ++i) {
      leds[i] = CRGB(0,0,bright);
    }
  }

  if (++idx >= ASTEPS) { idx = 0; }
  FastLED.show();
  delay(10);
}

void spinloop() {
  int endx = (idx+(NUM_LEDS/2));
  if (endx > NUM_LEDS) {
    endx -= NUM_LEDS;
    for (int i = 0; i < NUM_LEDS; ++i)
    {
      if (i < endx || i >= idx) { leds[i] = c1; }
      else { leds[i] = c2; }
    }
  } else {
    for (int i = 0; i < NUM_LEDS; ++i)
    {
      if (i < endx && i >= idx) { leds[i] = c1; }
      else { leds[i] = c2; }
    }
  }
  FastLED.show();
  if (++idx >= NUM_LEDS) { idx = 0; }
  delay(30);
}

void swap(int i, CRGB dflt)
{
  if ( leds[i].red > 0 )
  {
    leds[i] = CRGB::Blue;
  } else if (leds[i].blue > 0) {
    leds[i] = CRGB::Red;
  } else {
    leds[i] = dflt;
  }
}
