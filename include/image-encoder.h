#pragma once

#include <string>
#include <cstdint>

#include "image.h"

/**
 * @class ImageEncoder
 * @brief The ImageEncoder class provides functionality to encode images into various formats.
 * 
 * The class currently supports encoding images into PNG format. It offers methods to encode images
 * from raw pixel data or from an Image object. Objects of this class are non-copyable.
 */
class ImageEncoder {
public:

    /**
     * @enum Type
     * @brief Specifies the supported image encoding formats.
     * 
     * Currently, only PNG format is supported.
     */
    enum class Type: int32_t {
        PNG     = 0,
        JPEG    = 1
    };
    
private:
    Type m_type;    // Type of the encoder. Determines the format of the encoded image.

public:

    /**
     * @brief Objects of ImageEncoder class should not be copyable.
     * 
     * Copy constructor is deleted to prevent copying of encoder objects.
     */
    ImageEncoder(const ImageEncoder& other) = delete;
    
    /**
     * @brief Objects of ImageEncoder class should not be copyable.
     * 
     * Copy assignment operator is deleted to prevent copying of encoder objects.
     */
    ImageEncoder& operator=(const ImageEncoder& other) = delete;

   /**
     * @brief Constructs a default (PNG) encoder object.
     * 
     * Initializes an encoder object with the specified type. As of now, only PNG type is available.
     * 
     * @param encoder_type Type of the encoder. Default is Type::PNG.
     */
    explicit ImageEncoder(Type encoder_type = Type::PNG);
    

    /**
     * @brief Encodes an image given a raw pixel buffer with specified dimensions and number of channels.
     * The output image is saved to the specified file path.
     * 
     * @param rgb_buffer Pointer to the raw pixel data buffer.
     * @param width Width of the image in pixels.
     * @param height Height of the image in pixels.
     * @param number_of_channels Number of channels in the image (e.g.,1 for Grayscale, 2 for Grayscale with Alpha, 3 for RGB, 4 for RGB with Alpha, i.e., RGBA).
     * @param filepath The file path where the encoded image will be saved.
     */
    void encodeImage(const uint8_t* rgb_buffer, int32_t width, int32_t height, int32_t number_of_channels, const std::string& filepath) const;
    
    /**
     * @brief Encodes an image from an Image object to the specified file path.
     * 
     * @param image The Image object to encode.
     * @param filepath The file path where the encoded image will be saved.
     */
    void encodeImage(const Image& image, const std::string& filepath) const;
};
