#include "FastLED.h"

// Silicon sealed LED braid
// ALITOVE WS2811 12mm Diffused Digital RGB LED IP68 Waterproof DC 5V 50 lights
// using ELGOO NANO board, set target as UNO
// see https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

#define NUM_LEDS 50
#define DATA_PIN 11
#define BRIGHTNESS 200

CRGB leds[NUM_LEDS];

unsigned short idx = 0;
unsigned short prev = 0;

TBlendType    currentBlending;
CRGBPalette16 currentPalette;
//extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 SirenPalette PROGMEM;


void setup() {
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  currentPalette = SirenPalette;
  currentBlending = LINEARBLEND;
#ifdef DEBUG
  Serial.begin(9600);
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
  cp_test();
}

void cp_test()
{
  // only lighting up some of the LEDS for the fire engine costume
  ++idx;
  idx &= 0xff;
  leds[1] = ColorFromPalette( currentPalette, idx + 0, BRIGHTNESS, currentBlending);
  leds[2] = ColorFromPalette( currentPalette, (idx + 64) & 0xff, BRIGHTNESS, currentBlending);

  // phase difference gives a kind of circular effect
  leds[8] = ColorFromPalette( currentPalette, idx, BRIGHTNESS, currentBlending);
  leds[9] = ColorFromPalette( currentPalette, (idx + 8) & 0xff, BRIGHTNESS, currentBlending);
  leds[10] = ColorFromPalette( currentPalette, (idx + 16) & 0xff, BRIGHTNESS, currentBlending);
  leds[11] = ColorFromPalette( currentPalette, (idx + 32) & 0xff, BRIGHTNESS, currentBlending);

  leds[30] = ColorFromPalette( currentPalette, idx, BRIGHTNESS, currentBlending);
  leds[31] = ColorFromPalette( currentPalette, (idx + 64) & 0xff, BRIGHTNESS, currentBlending);

  // reverse indexes so they go from front to back, du to circular mounting
  leds[47] = ColorFromPalette( currentPalette, idx, BRIGHTNESS, currentBlending);
  leds[46] = ColorFromPalette( currentPalette, (idx + 8) & 0xff, BRIGHTNESS, currentBlending);
  leds[45] = ColorFromPalette( currentPalette, (idx + 16) & 0xff, BRIGHTNESS, currentBlending);
  leds[44] = ColorFromPalette( currentPalette, (idx + 32) & 0xff, BRIGHTNESS, currentBlending);


  // crazy strobe effect
  /*
  if ( idx <= 50 ) {
    if ( idx > 0 ) {
      leds[idx-1]  = CRGB::Black;
    }
    if ( idx < 50 ) {
      leds[idx]  = CRGB::White;
    }
  }  
  */
  FastLED.show();
  FastLED.delay(10);
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


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 SirenPalette PROGMEM =
{
    CRGB::Black,
    CRGB::DarkRed,
    CRGB::Red,
    CRGB::DarkRed,
    
    CRGB::Black,
    CRGB::DarkBlue,
    CRGB::Blue,
    CRGB::DarkBlue,
    
    CRGB::Black,
    CRGB::DarkRed,
    CRGB::Red,
    CRGB::DarkRed,
    
    CRGB::Black,
    CRGB::DarkBlue,
    CRGB::Blue,
    CRGB::DarkBlue
};
