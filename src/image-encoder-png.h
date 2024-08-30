#pragma once

#include <stdbool.h>
#include <stdint.h>

bool encodeImageToPNG(const uint8_t* rgbBuffer, int width, int height, int number_of_channels, const char* filename);
