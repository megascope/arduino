#pragma once
#include <FastLED.h>

// Yellow/orange/gold
const TProgmemRGBPalette16 GoldOrange_p FL_PROGMEM =
{  CRGB::Yellow,  CRGB::Yellow,  CRGB::Gold,  CRGB::Orange, 
   CRGB::OrangeRed, CRGB::OrangeRed, CRGB::Orange, CRGB::Gold,
   CRGB::Yellow,  CRGB::Yellow,  CRGB::Gold,  CRGB::Orange, 
   CRGB::OrangeRed, CRGB::OrangeRed, CRGB::Orange, CRGB::Gold };


// A mostly red palette with green accents and white trim.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
{  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray, 
   CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green };

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red    0xB80400
#define C9_Orange 0x902C02
#define C9_Green  0x046002
#define C9_Blue   0x070758
#define C9_White  0x606820
const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
{  C9_Red,    C9_Orange, C9_Red,    C9_Orange,
   C9_Orange, C9_Red,    C9_Orange, C9_Red,
   C9_Green,  C9_Green,  C9_Green,  C9_Green,
   C9_Blue,   C9_Blue,   C9_Blue,
   C9_White
};

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedPurple_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::MediumPurple, CRGB::MediumPurple, CRGB::MediumPurple, CRGB::MediumPurple,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::MediumPurple, CRGB::MediumPurple, CRGB::MediumPurple, CRGB::MediumPurple };


// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
extern const TProgmemRGBPalette16* ActivePaletteList[];

// Advance to the next color palette in the list (above).
void chooseNextColorPalette( CRGBPalette16& pal);
