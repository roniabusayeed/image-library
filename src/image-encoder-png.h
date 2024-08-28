#pragma once

#include <stdbool.h>
#include <stdint.h>

bool encodeRGBtoPNG(const uint8_t* rgbBuffer, int width, int height, const char* filename);
