#include <stdexcept>

#include "image-decoder.h"
#include "stb_image.h"
#include "image.h"

Image ImageDecoder::decodeImage(const std::string& filepath) const {
    int32_t width;
    int32_t height;
    int32_t channels;

    uint8_t* buffer = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (! buffer) {
        throw std::runtime_error(std::string("Failed to decode image at ") + filepath);
    }
    
    return Image(buffer, width, height, channels, [](void* data) {
        stbi_image_free(data); 
    });
}
