#pragma once
#include <iosfwd>

static const int WS2811 = 1;
static const int DATA_PIN = 1;
static const int RGB = 1;

struct CRGB;

struct FastLEDClass {
    template<int, int, int> void addLeds(CRGB* lds, unsigned sz) {
        leds = lds;
        size = sz;
    }
    void setBrightness(int) {}
    void clear();
    void delay(int d);
    void display();

    CRGB* leds = nullptr;
    unsigned size = 0;

    int frame = 0;
};

struct CRGB
{
    CRGB() {}
    CRGB(char c, int ansicolor) : color(c), ansi(ansicolor) {}

    static const CRGB AliceBlue;
    static const CRGB Red;
    static const CRGB Black;
    static const CRGB GreenYellow;

    char color = ' ';
    int ansi = 0;

};

std::ostream& operator<<(std::ostream& os, const CRGB& led);

static FastLEDClass FastLED;
