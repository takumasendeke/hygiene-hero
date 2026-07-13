#ifndef BITMAPS_H
#define BITMAPS_H

#include <Arduino.h>

// dimensions
const int ICON_WIDTH  = 128;
const int ICON_HEIGHT = 64;
const int ICON_FRAMES = 2;
const int ICON_BYTES  = 1024; 

// pointer to external bitmap
extern const uint8_t* const bitmapSteps[6][2];

#endif