#pragma once
#include <iosfwd>
#include <stdint.h>

#define FL_PROGMEM

static const int WS2811 = 1;
static const int DATA_PIN = 1;
static const int RGB = 1;
static const int RBG = 1;


//typedef uint64_t TProgmemRGBPalette16[16];
using TProgmemRGBPalette16 = uint64_t[16];
struct CRGB;

struct CRGBPalette16 {
    CRGBPalette16() {}
    CRGBPalette16(const TProgmemRGBPalette16 p);
    CRGB operator[](int i) const;
    TProgmemRGBPalette16 pal;
};

inline uint8_t addmod8(uint8_t a, uint8_t b, uint8_t m) {
    return (a+b)%m;
}

struct FastLEDClass {
    template<int, int, int> void addLeds(CRGB* lds, unsigned sz) {
        leds = lds;
        size = sz;
    }
    void setBrightness(int) {}
    void clear();
    void delay(int d);
    void display();
    void show() { display(); }

    CRGB* leds = nullptr;
    unsigned size = 0;

    int frame = 0;

    private:
        void display50();
        void display100();
};

struct CRGB
{
    CRGB() {}
    CRGB(char c, int ansicolor) : color(c), ansi(ansicolor) {}
    CRGB(uint64_t storage);
    CRGB(uint32_t red, uint32_t green, uint32_t blue);

    operator uint64_t() const;

    static const CRGB AliceBlue;
    static const CRGB Red;
    static const CRGB Black;
    static const CRGB GreenYellow;
    static const CRGB Green;
    static const CRGB Blue;
    static const CRGB Yellow;
    static const CRGB Gold;
    static const CRGB Orange;
    static const CRGB OrangeRed;
    static const CRGB Gray;
    static const CRGB White;
    static const CRGB MediumPurple;


    char color = ' ';
    int ansi = 0;

};

std::ostream& operator<<(std::ostream& os, const CRGB& led);

static FastLEDClass FastLED;

CRGB ColorFromPalette(const CRGBPalette16&, uint8_t index);
