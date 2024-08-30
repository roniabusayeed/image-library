#include <stdexcept>

#include "image-encoder.h"

extern "C" {
#include "image-encoder-png.h"
}

ImageEncoder::ImageEncoder(const Type& encoder_type) : m_type(encoder_type) {}

void ImageEncoder::encodeImage(const uint8_t* rgb_buffer, int32_t width, int32_t height, const std::string& filepath) const {
    switch (m_type)
    {
    case Type::PNG:
        if (! encodeRGBtoPNG(rgb_buffer, width, height, filepath.c_str())) {
            throw std::runtime_error(std::string("Failed to encode image at ") + filepath);
        }
    }
}

void ImageEncoder::encodeImage(const Image& image, const std::string& filepath) const {
    encodeImage(image.getBuffer(), image.getWidth(), image.getHeight(), filepath);
}
