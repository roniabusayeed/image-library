#pragma once

#include <string>
#include <cstdint>

class ImageEncoder {
public:
    enum class Type: int32_t {
        PNG = 0
    };
    
private:
    Type m_type;

public:
    explicit ImageEncoder(const Type& encoder_type = Type::PNG);
    void encodeImage(const uint8_t* rgb_buffer, int32_t width, int32_t height, const std::string& filepath) const;
};
