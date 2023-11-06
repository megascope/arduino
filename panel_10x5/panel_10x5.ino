#include <FastLED.h>
#include "characters.h"

// Silicon sealed LED braid built into 10x5 panel
// ALITOVE WS2811 12mm Diffused Digital RGB LED IP68 Waterproof DC 5V 50 lights
// using ELGOO NANO board, set target as UNO
// see https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

CRGB leds[NUM_LEDS];

Unit idx = 0;
Unit prev = 0;

TBlendType    currentBlending;
CRGBPalette16 currentPalette;
extern const TProgmemPalette16 SirenPalette PROGMEM;

struct Pixel {
  Unit x;
  Unit y;

  Pixel(Unit xx, Unit yy ) : x(xx), y(yy) {}

  // get led index given an x and y coordinate
  // no error checking!
  static Unit index(Unit x, Unit y)
  {
    switch (y) {
      case 0: return x;
      case 1: return 19-x;
      case 2: return 20+x;
      case 3: return 39-x;
      case 4: return 40+x;
      default: return 0;
    }
  }
  Unit index() { return Pixel::index(x, y); }
};

void setup() {
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  currentPalette = SirenPalette;
  currentBlending = LINEARBLEND;
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_lines();
}

void loop_lines()
{
  for (Unit x = 0; x < WIDTH; ++x) {
    FastLED.clear();
    vert_line(x, CRGB::AliceBlue);
    FastLED.delay(100);
  }
}

// loop the whole thing
void loop_xtoy()
{
  for (Unit y = 0; y < HEIGHT; ++y) {
    for (Unit x = 0; x < WIDTH; ++x) {
      Pixel p(x, y);
      idx = p.index();

      leds[idx] = CRGB::Red;

      #ifdef DEBUG
      char buffer[40];
      sprintf(buffer, "x=%d y=%d idx=%d prev=%d", x, y, idx, prev);
      Serial.println(buffer);
      #endif

      FastLED.delay(50); // delay also calls show

      leds[idx] = CRGB::Black; // reset after show
    }
  }
}

void draw_character(Unit startx, CRGB color, unsigned cindex)
{
  const char * bob = ALL_CHARS[cindex];

  for (Unit x = 0; x < CHAR_WIDTH; ++x) {
    for (Unit y = 0; y < CHAR_WIDTH; ++y) {
      Unit newx = startx + x;
    }

    if (x >= WIDTH) { return; }
  }
}

void vert_line(Unit x, CRGB color) {
  for (Unit y = 0; y < HEIGHT; ++y) {
    leds[Pixel::index(x, y)] = color;
  }
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

