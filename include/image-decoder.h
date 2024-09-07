#pragma once

#include <string>
#include "image.h"

/**
 * @class ImageDecoder
 * @brief The ImageDecoder class provides functionality to decode images from files into an Image object.
 * 
 * The class supports decoding images from various file formats into an Image object that contains
 * the pixel data, dimensions, and channel information. Objects of this class are non-copyable.
 */
class ImageDecoder {
public:
    /**
     * @brief Default constructor for ImageDecoder.
     */
    ImageDecoder() = default;

    /**
     * @brief Objects of ImageDecoder class should not be copyable.
     * 
     * Copy constructor is deleted to prevent copying of decoder objects.
     */
    ImageDecoder(const ImageDecoder& other) = delete;

    /**
     * @brief Objects of ImageDecoder class should not be copyable.
     * 
     * Copy assignment operator is deleted to prevent copying of decoder objects.
     */
    ImageDecoder& operator=(const ImageDecoder& other) = delete;

    /**
     * @brief Decodes an image from a specified file path into an Image object.
     * 
     * This method reads an image file from the specified file path, decodes it, and returns an
     * Image object containing the pixel data, dimensions, and number of channels.
     * 
     * @param filepath The file path of the image to decode.
     * @return An Image object containing the decoded image data.
     */
    Image decodeImage(const std::string& filepath) const;
};
