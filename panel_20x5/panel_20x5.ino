#include <FastLED.h>
#include "images.h"
#include "palettes.h"

// Two LED fairy strips built into 20x5 panel
// Serpentine layout is up/down rather than left->right
// . .-. .-. . <- first neopixel
// | | | | | |
// | | | | | |
// '-' '-' '-'   ... etc.
// using ELGOO NANO board, set target as UNO
// see https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

CRGB leds__[NUM_LEDS];
unsigned loop_count__;
CRGBPalette16 current_palette__;

struct Pixel {
  Unit x;
  Unit y;

  Pixel(Unit xx, Unit yy ) : x(xx), y(yy) {}

  // get led index given an x and y coordinate
  // no error checking!
  static Unit index(Unit x, Unit y)
  {
    Unit idx = (20-x)*5;
    Unit sinx = idx;
    if (x & 1) {
      // x is odd
      idx = idx-y-1;
    } else {
      idx = idx-5+y;
    }
    //std::cout << +x << ", " << +y << " = " << +sinx << " -> " << +idx << std::endl;
    return idx;
  }
  Unit index() { return Pixel::index(x, y); }
};

void draw_image(const XBM& image, const Pixel& start, const Pixel& offset) {
  Unit draw_width = min(image.width-offset.x, WIDTH-start.x);
  Unit draw_height = min(image.height-offset.y, HEIGHT-start.y);

  #ifdef DEBUG
  char buffer[40];
  sprintf(buffer, "xo=%d xr=%d xm=%d", image.width-offset.x, WIDTH-start.x, draw_width);
  Serial.println(buffer);
  sprintf(buffer, "yo=%d yr=%d ym=%d", image.height-offset.y, HEIGHT-start.y, draw_height);
  Serial.println(buffer);
  #endif

  for (Unit x=0; x < draw_width; ++x) {
    for (Unit y=0; y < draw_height; ++y) {
      Unit imagex = offset.x+x;
      Unit imagey = offset.y+y;
      if (image.is_pixel(imagex, imagey)) {
        Unit idx = Pixel::index(start.x+x, start.y+y);

        #ifdef DEBUG
        char buffer[40];
        sprintf(buffer, "ONN x=%d y=%d idx=%d", start.x+x, start.y+y, idx);
        Serial.println(buffer);
        #endif

        // colorpalette index is pseudorandom but stable for each pixel in the image as it scrolls
        leds__[idx] =  ColorFromPalette(current_palette__, (((imagex+1) + max(loop_count__, 1)) * ((imagey+1) * 54)) & 0xFF);
      } else {
        #ifdef DEBUG
        char buffer[40];
        sprintf(buffer, "OFF x=%d y=%d idx=%d", start.x+x, start.y+y, Pixel::index(start.x+x, start.y+y));
        Serial.println(buffer);
        #endif
      }
    }
  }
}

void scroll_image() {
  const XBM& image = XBM::merry_christmas;
  Pixel zero(0,0);

  // set to true to just set a static image
  if (false) {
    FastLED.clear();
    draw_image(image, zero, zero);
    FastLED.delay(DELAY);
    return;
  }

  // first scroll all the away across the screen
  for (Unit x = WIDTH-1; x>0; --x) {
    FastLED.clear();
    draw_image(image, Pixel(x, 0), zero);
    FastLED.delay(DELAY);
  }

  // then pull the image across
  for (Unit x = 0; x < image.width; ++x) {
    FastLED.clear();
    draw_image(image, zero, Pixel(x, 0));
    FastLED.delay(DELAY);
  }
}

// loop the whole thing
void loop_xtoy()
{
  for (Unit y = 0; y < HEIGHT; ++y) {
    for (Unit x = 0; x < WIDTH; ++x) {
      Pixel p(x, y);
      auto idx = p.index();

      leds__[idx] = CRGB::Red;

      #ifdef DEBUG
      char buffer[40];
      sprintf(buffer, "x=%d y=%d idx=%d", x, y, idx);
      Serial.println(buffer);
      #endif

      FastLED.delay(DELAY); // delay also calls show
      leds__[idx] = CRGB::Blue; // show where we've been after show
    }
  }
}

void vert_line(Unit x, CRGB color) {
  for (Unit y = 0; y < HEIGHT; ++y) {
    leds__[Pixel::index(x, y)] = color;
  }
}

void loop_lines()
{
  for (Unit x = 0; x < WIDTH; ++x) {
    FastLED.clear();
    vert_line(x, CRGB::AliceBlue);
    FastLED.delay(DELAY);
  }
}

void setup() {
  loop_count__ = 0;
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RBG>(leds__, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  chooseNextColorPalette(current_palette__);

#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Serial Output enabled...");
#endif
}

void loop() {
  ++loop_count__;

  // put your main code here, to run repeatedly:
  //loop_xtoy();
  //loop_lines();
  scroll_image();
  chooseNextColorPalette(current_palette__);
}
