#include "palettes.h"

// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
const TProgmemRGBPalette16* ActivePaletteList[] = {
  &GoldOrange_p,
  //&RetroC9_p,
  //&RainbowColors_p,
  //&RedGreenWhite_p,
  //&PartyColors_p,
  &RedPurple_p,
};

// Advance to the next color palette in the list (above).
void chooseNextColorPalette( CRGBPalette16& pal)
{
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1; 
  whichPalette = addmod8( whichPalette, 1, numberOfPalettes);
  pal = *(ActivePaletteList[whichPalette]);
}
