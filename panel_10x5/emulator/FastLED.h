#pragma once
#include <Arduino.h>

static const int WS2811 = 1;
static const int DATA_PIN = 1;
static const int RGB = 1;

struct CRGB;

struct FastLEDClass {
    template<int, int, int> void addLeds(CRGB* , int) {}
    void setBrightness(int) {}
    void clear() {}
    void delay(int d) {
        delay(d);
    }
};

struct CRGB
{
    CRGB() : color(' ') {}
    CRGB(char c) : color(c) {}
    static const CRGB AliceBlue;
    static const CRGB Red;
    static const CRGB Black;

    char color;
};
