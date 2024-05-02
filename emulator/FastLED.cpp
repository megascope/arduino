#include <iostream>
#include "Arduino.h"
#include "FastLED.h"

#define ANSICODE(code) "\x1b[" #code
#define ANSICOLORPRE ANSICODE(38;5;)
#define ANSIRESET ANSICODE(0m)
#define ANSIHOME ANSICODE(H)
#define ANSICLEAR ANSICODE(2J)

const CRGB CRGB::AliceBlue = CRGB('A', 6);
const CRGB CRGB::GreenYellow = CRGB('G', 154);
const CRGB CRGB::Red = CRGB('R', 1);
const CRGB CRGB::Black = CRGB(' ', 0);
const CRGB CRGB::Green = CRGB('G', 40);
const CRGB CRGB::Blue = CRGB('B', 21);
const CRGB CRGB::Yellow = CRGB('Y', 226);
const CRGB CRGB::Gold = CRGB('G', 220);
const CRGB CRGB::Orange = CRGB('O', 208);
const CRGB CRGB::OrangeRed = CRGB('o', 202);
const CRGB CRGB::Gray = CRGB('G', 243);
const CRGB CRGB::White = CRGB('W', 255);
const CRGB CRGB::MediumPurple = CRGB('P', 165);


CRGB::operator uint64_t() const
{
    // return storage
    uint64_t storage = (uint64_t(color) << 48)
                    | (uint64_t(ansi) << 32);
    return storage;
}

CRGB::CRGB(uint32_t red, uint32_t green, uint32_t blue) :
 CRGB((red << 16) | (green << 8) | blue)
{

}

CRGB::CRGB(uint64_t storage) {

    // check if upper 4 bytes set
    uint32_t upper = storage >> 32;
    if (upper > 0) {
        ansi = upper & 0xffff;
        color = upper >> 16;

    } else {
        // is just an rgb color code

        uint32_t rgb = storage & 0xffffff;
        // 4 bytes, 0, R, G, B
        int red = (rgb & 0xff0000) >> 16;
        int green = (rgb & 0x00ff00) >> 8;
        int blue = (rgb & 0x0000ff);

        // ansi extended colors in 6x6x6 grid
        // 16-231:  6 × 6 × 6 cube (216 colors):
        // 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)
        // 255/6 = 42.5
        red /= 43;
        green /= 43;
        blue /= 43;
        ansi = 16 + (36 * red) + (6 * green) + blue;
        color = '*';
    }

}

CRGB ColorFromPalette(const CRGBPalette16& p, uint8_t index)
{
    // just get nearest 16
    return p[index/16];
}

std::ostream& operator<<(std::ostream& os, const CRGB& led)
{
    os << ANSICOLORPRE << led.ansi << "m" << led.color << ANSIRESET;
    return os;
}

void FastLEDClass::display() {

    // serpentine LED set 10x5

    // uncomment one of the below to update in place
    //system("clear");
    //std::cout << ANSIHOME;
    if (size == 50) {
        std::cout << "- ";
        for (unsigned i = 0; i < 10; ++i) {
            CRGB& led = leds[i];
            std::cout << (i % 10) << ' ';
        }
        std::cout << std::endl << "0 ";
        for (unsigned i = 0; i < 10; ++i) {
            CRGB& led = leds[i];
            std::cout << led << ' ';
        }
        std::cout << std::endl << "1 ";
        for (unsigned i = 19; i >= 10; --i) {
            CRGB& led = leds[i];
            std::cout << led << ' ';
        }
        std::cout << std::endl << "2 ";
        for (unsigned i = 20; i < 30; ++i) {
            CRGB& led = leds[i];
            std::cout << led << ' ';
        }
        std::cout << std::endl << "3 ";
        for (unsigned i = 39; i >= 30; --i) {
            CRGB& led = leds[i];
            std::cout << led << ' ';
        }
        std::cout << std::endl << "4 ";
        for (unsigned i = 40; i < 50; ++i) {
            CRGB& led = leds[i];
            std::cout << led << ' ';
        }
        std::cout << std::endl;
    } else {
        for (unsigned i = 0; i <= size; ++i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
    }
    std::cout << "Frame: " << frame++ << std::endl;
}

void FastLEDClass::delay(int d) {
    display();
    ::delay(d);
}

void FastLEDClass::clear() {
    for (unsigned i = 0; i < size; ++i) {
        leds[i] = CRGB::Black;
    }
}

CRGBPalette16::CRGBPalette16(const TProgmemRGBPalette16 p)
{
    for (int i = 0; i < 16; ++i) {
        pal[i] = p[i];
    }
}

CRGB CRGBPalette16::operator[](int i) const {
    return pal[i];
}
