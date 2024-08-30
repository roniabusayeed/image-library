#pragma once

#include <string>
#include <cstdint>

#include "image.h"

class ImageEncoder {
public:
    enum class Type: int32_t {
        PNG = 0
    };
    
private:
    Type m_type;

public:

    // Objects of ImageEncoder class should not be copyable.
    ImageEncoder(const ImageEncoder& other) = delete;
    ImageEncoder& operator=(const ImageEncoder& other) = delete;

    explicit ImageEncoder(Type encoder_type = Type::PNG);
    void encodeImage(const uint8_t* rgb_buffer, int32_t width, int32_t height, int32_t number_of_channels, const std::string& filepath) const;
    void encodeImage(const Image& image, const std::string& filepath) const;
};
