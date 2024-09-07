#include <stdexcept>

#include "image-encoder.h"

extern "C" {
#include "image-encoder-png.h"
#include "image-encoder-jpeg.h"
}

ImageEncoder::ImageEncoder(Type encoder_type) : m_type(encoder_type) {}

void ImageEncoder::encodeImage(const uint8_t* rgb_buffer, int32_t width, int32_t height, int32_t number_of_channels, const std::string& filepath) const {
    switch (m_type)
    {
    case Type::PNG:
        if (! encodeImageToPNG(rgb_buffer, width, height, number_of_channels, filepath.c_str())) {
            throw std::runtime_error(std::string("PNG: Failed to encode image at ") + filepath);
        }
    case Type::JPEG:
        if (! encodeImageToJPEG(rgb_buffer, width, height, number_of_channels, filepath.c_str())) {
            throw std::runtime_error(std::string("JPEG: Failed to encode image at ") + filepath);
        }
    }
}

void ImageEncoder::encodeImage(const Image& image, const std::string& filepath) const {
    encodeImage(image.getBuffer(), image.getWidth(), image.getHeight(), image.getChannels(), filepath);
}
