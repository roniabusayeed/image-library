#pragma once

#include <string>
#include "image.h"

class ImageDecoder {
public:
    Image decodeImage(const std::string& filepath) const;
};
