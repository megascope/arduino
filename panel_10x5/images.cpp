#include "images.h"


bool XBM::is_pixel(Unit x, Unit y) const {
    if (x > width || y > height) return false;

    // find the byte that contains this pixel
    unsigned int i = elements_per_row * y;

    Unit element;
    while ( x > 8 ) {
        x -= 8;
        ++i;
    }

    // which bit do we need
    unsigned char bit = 1 << x;
    return xbm[i] & bit;
}
 

// happy diwali 43x5
const unsigned char PROGMEM happy_diwali_xbm[] = {
 0x25,0x33,0x65,0x8a,0x24,0xfa,0x55,0x55,0xa5,0xaa,0x2a,0xfa,
 0x77,0x77,0xa5,0xaa,0x2e,0xfa,0x55,0x11,0xa2,0xaa,0x2a,0xfa,
 0x55,0x11,0x62,0x52,0xea,0xfa};

const XBM XBM::happy_diwali(43, 5, happy_diwali_xbm);


// test image for calibration 15x5
const unsigned char PROGMEM test_xbm[] = {
 0x1e,0xbe,0x12,0xb2,0x12,0xaa,0x12,0xa6,0x1e,0xbe};

const XBM XBM::test(15, 5, test_xbm);
