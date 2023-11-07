#include <iostream>
#include "Arduino.h"
#include "FastLED.h"

const CRGB CRGB::AliceBlue = CRGB('A');
const CRGB CRGB::Red = CRGB('R');
const CRGB CRGB::Black = CRGB(' ');

void FastLEDClass::display() {

    // serpentine LED set 10x5
system("clear");
    if (size == 50) {
        std::cout << "- ";
        for (unsigned i = 0; i < 10; ++i) {
            CRGB& led = leds[i];
            std::cout << (i % 10) << ' ';
        }
        std::cout << std::endl << "0 ";
        for (unsigned i = 0; i < 10; ++i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
        std::cout << std::endl << "1 ";
        for (unsigned i = 19; i >= 10; --i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
        std::cout << std::endl << "2 ";
        for (unsigned i = 20; i < 30; ++i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
        std::cout << std::endl << "3 ";
        for (unsigned i = 39; i >= 30; --i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
        std::cout << std::endl << "4 ";
        for (unsigned i = 40; i < 50; ++i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
        std::cout << std::endl;
    } else {
        for (unsigned i = 0; i <= size; ++i) {
            CRGB& led = leds[i];
            std::cout << led.color << ' ';
        }
    }
    std::cout << "Frame:" << frame++ << std::endl;
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
