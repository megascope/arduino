#include <FastLED.h>
#include "images.h"

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

Unit min(Unit a, Unit b) {
  if (a < b) return a;
  return b;
}

void draw_image(const XBM& image, const Pixel& start, const Pixel& offset, const CRGB& color) {
  Unit draw_width = min(image.width-offset.x, WIDTH-start.x);
  Unit draw_height = min(image.height-offset.y, HEIGHT-start.y);
  for (Unit x=0; x < draw_width; ++x) {
    for (Unit y=0; y < draw_height; ++y) {
      if (image.is_pixel(offset.x+x, offset.y+y)) {
        leds[Pixel::index(start.x+x, start.y+y)] = color;
      }
    }
  }
  
}

void scroll_image() {
  const int delayms = 100;
  const XBM& image = XBM::happy_diwali;
  Pixel zero(0,0);

  // first scroll all the away across the screen
  for (Unit x = WIDTH-1; x>0; --x) {
    FastLED.clear();
    draw_image(image, Pixel(x, 0), zero, CRGB::AliceBlue);
    FastLED.delay(delayms);
  }

  // then pull the image across
  for (Unit x = 0; x < image.width; ++x) {
    FastLED.clear();
    draw_image(image, zero, Pixel(x, 0), CRGB::AliceBlue);
    FastLED.delay(delayms);
  }
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
  //loop_lines();
  scroll_image();
}
