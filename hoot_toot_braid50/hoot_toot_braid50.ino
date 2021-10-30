#include "FastLED.h"

// Silicon sealed LED braid
// ALITOVE WS2811 12mm Diffused Digital RGB LED IP68 Waterproof DC 5V 50 lights
// using ELGOO NANO board, set target as UNO
// see https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

#define NUM_LEDS 50
#define DATA_PIN 11
#define BRIGHTNESS 200
#define FIRST_LED 23
#define TOOT_START 28 // green
#define TOOT_END 32 // green
#define HOOT_START 42 // blue
#define HOOT_END 46 // blue

CRGB leds[NUM_LEDS];

unsigned short idx = FIRST_LED;
unsigned short prev = 0;

TBlendType    currentBlending;
//extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 HootPalette PROGMEM; // blue
extern const TProgmemPalette16 TootPalette PROGMEM; // green


void setup() {
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  currentBlending = LINEARBLEND;
#ifdef DEBUG
  Serial.begin(9600);
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
  hoot_toot();
}

void hoot_toot()
{
  ++idx;
  idx &= 0xff;

  for ( int i = FIRST_LED; i < NUM_LEDS; ++i ) {
    if ( i >= HOOT_START && i <= HOOT_END ) {
      leds[i] = ColorFromPalette( HootPalette, idx + 0, BRIGHTNESS, currentBlending);
    }
    else if ( i >= TOOT_START && i <= TOOT_END ) {
      leds[i] = ColorFromPalette( TootPalette, idx + 0, BRIGHTNESS, currentBlending);
    }
    else {
      // for the non-hoot/toot alternate the remaining leds
      int oddon = idx & 0x40 ? 1 : 0;
      leds[i] = ( i % 2 == oddon) ? CRGB::Black : CRGB::DeepPink;
    }
  }
  FastLED.show();
  FastLED.delay(10);
}

void count_leds()
{
  leds[idx] = CRGB::Black;
  ++idx;
  if ( idx > NUM_LEDS ) {
    idx = FIRST_LED;
  }
  leds[idx] = CRGB::Red;
  FastLED.show();
  FastLED.delay(10);

}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 HootPalette PROGMEM =
{
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::DarkBlue,
    CRGB::DarkBlue,
    CRGB::DarkBlue,
    CRGB::Black,
    CRGB::Black,
    CRGB::DarkBlue,
    CRGB::DarkBlue,
    CRGB::DarkBlue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue
};

const TProgmemPalette16 TootPalette PROGMEM =
{
    CRGB::Green,
    CRGB::Green,
    CRGB::Green,
    CRGB::Green,
    CRGB::DarkGreen,
    CRGB::DarkGreen,
    CRGB::DarkGreen,
    CRGB::Black,
    CRGB::Black,
    CRGB::DarkGreen,
    CRGB::DarkGreen,
    CRGB::DarkGreen,
    CRGB::Green,
    CRGB::Green,
    CRGB::Green,
    CRGB::Green
};
