#pragma once

#include <string>
#include "image.h"

class ImageDecoder {
public:

    // Objects of ImageDecoder class should not be copyable.
    ImageDecoder(const ImageDecoder& other) = delete;
    ImageDecoder& operator=(const ImageDecoder& other) = delete;

    Image decodeImage(const std::string& filepath) const;
};
