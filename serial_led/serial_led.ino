#include <Arduino.h>
#include <FastLED.h>
#include "defines.h"

CRGB leds__[NUM_LEDS];
unsigned loop_count__;
unsigned serial_read_index__;

void setup() {
  loop_count__ = 0;
  serial_read_index__ = 0;
  delay( 2000 ); // power-up safety delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds__, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);

  // strip startup loop
  FastLED.clear();
  constexpr int TESTSIZE = 5;
  for (int offset = 0; offset < TESTSIZE; ++offset) {
    for (int i = 0; i < NUM_LEDS; i+=TESTSIZE) {
      leds__[(i+offset) % NUM_LEDS] = CRGB::Red;
      leds__[(i+offset+1) % NUM_LEDS] = CRGB::Green;
      leds__[(i+offset+2) % NUM_LEDS] = CRGB::Blue;
      leds__[(i+offset+3) % NUM_LEDS] = CRGB::White;
      leds__[(i+offset+4) % NUM_LEDS] = CRGB::Black;
    }
    FastLED.delay(333);
  }
  FastLED.clear();
  FastLED.show();
}

// protocol defines
constexpr char DATA_AVAIL = 0x80; // first bit
constexpr char NUM_PIXELS_MASK = 0x7f; // last 7 bits
constexpr char DATA_PLEASE_SEND = '>';
constexpr char DATA_CHUNK_PROCESSING = '=';
constexpr char DATA_NOT_SEND = ':';
constexpr size_t PROTOCOL_CHUNK = 4;
char protocol_buffer__[PROTOCOL_CHUNK];

void loop() {
  ++loop_count__;

  int firstByte = Serial.read();
  if ( firstByte < 0 ) {
    return;
  }

  if (!(firstByte & DATA_AVAIL)) {
    return;
  }

  Serial.write(DATA_PLEASE_SEND);

  // wait for data
  int pixelsToRead = firstByte & NUM_PIXELS_MASK;

  FastLED.clear();
  // protocol is 4 bytes per pixel, first byte is index, next 3 bytes are rgb
  for (int i = 0; i < pixelsToRead; ++i) {
    Serial.write(DATA_CHUNK_PROCESSING);
    size_t sizeread = Serial.readBytes(protocol_buffer__, PROTOCOL_CHUNK);
    if (sizeread != PROTOCOL_CHUNK) {
      Serial.println("! Error in protocol");
      break;
    }
    leds__[protocol_buffer__[0] % NUM_LEDS] = CRGB(
      protocol_buffer__[1],
      protocol_buffer__[2],
      protocol_buffer__[3]);
  }
  Serial.write(DATA_NOT_SEND);
  FastLED.show();
}
