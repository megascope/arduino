#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "defines.h"

// x bitmap formed image
// see https://xbm.jazzychad.net/
struct XBM
{
    XBM(Unit w, Unit h, const DataByte* x) 
    : width(w), height(h), xbm(x) {
        // XBM format has width/8 characters (i.e. 8 bits)
        elements_per_row = 1+(width/8);
    }

    unsigned short elements_per_row;
    Unit width;
    Unit height;
    const DataByte * xbm;

    // is a given pixel at coordinate x, y set
    bool is_pixel(Unit x, Unit y) const;

    // images
    static const XBM happy_diwali;
    static const XBM test;

};
