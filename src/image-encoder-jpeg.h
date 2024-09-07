#pragma once
#include <stdint.h>
#include <stdbool.h>

bool encodeImageToJPEG(const uint8_t* buffer, int width, int height, int number_of_channels, const char* filename);
