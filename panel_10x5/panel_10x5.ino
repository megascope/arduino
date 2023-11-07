#include <FastLED.h>
#include "characters.h"

// Silicon sealed LED braid built into 10x5 panel
// ALITOVE WS2811 12mm Diffused Digital RGB LED IP68 Waterproof DC 5V 50 lights
// using ELGOO NANO board, set target as UNO
// see https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

CRGB leds[NUM_LEDS];

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

#ifdef DEBUG
  Serial.begin(9600);
#endif
}


// loop the whole thing
void loop_xtoy()
{
  for (Unit y = 0; y < HEIGHT; ++y) {
    for (Unit x = 0; x < WIDTH; ++x) {
      Pixel p(x, y);
      auto idx = p.index();

      leds[idx] = CRGB::Red;

      #ifdef DEBUG
      char buffer[40];
      sprintf(buffer, "x=%d y=%d idx=%d prev=%d", x, y, idx, prev);
      Serial.println(buffer);
      #endif

      FastLED.delay(100); // delay also calls show

      leds[idx] = CRGB::Black; // reset after show
    }
  }
}

void draw_character(Unit startx, CRGB color, unsigned cindex)
{
  
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

void loop_lines()
{
  for (Unit x = 0; x < WIDTH; ++x) {
    FastLED.clear();
    vert_line(x, CRGB::AliceBlue);
    FastLED.delay(100);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //loop_xtoy();
  loop_lines();
}
