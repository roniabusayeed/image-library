#pragma once
#include <cstdint>
#include <cstring>
#include <functional>

/**
 * @class Image
 * @brief The Image class represents a 2D image with pixel data stored in a buffer.
 * 
 * The class provides constructors, destructors, and assignment operators 
 * for managing image data, including deep copying and move semantics.
 * It also supports custom deallocation functions for externally allocated buffers.
 */
class Image {
    uint8_t* m_buffer;                          // Raw image pixel data.
    int32_t m_width;                            // Width of the image in pixels.
    int32_t m_height;                           // Height of the image in pixels.
    int32_t m_channels;                         // Number of channels (e.g., red, green, blue, and alpha).
    std::function<void(void*)> m_deallocator;   // Custom deallocator function.

public:
    /**
     * @brief Default constructor that initializes an empty image.
     */
    Image();

    /**
     * @brief Constructs an image with a specified buffer, width, height, and channels. The object
     * doesn't take ownership of the buffer memory, i.e., the external buffer can be freed after construction.
     * 
     * @param buffer Pointer to the image data buffer.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param channels Number of channels in the image.
     */
    Image(const uint8_t* buffer, int32_t width, int32_t height, int32_t channels);

    /**
     * @brief Constructs an image with a specified buffer and deallocator. The object
     * takes the ownership of the buffer memory upon construction, i.e., the caller
     * shouldn't free the external buffer after calling the constructor.
     * 
     * @param buffer Pointer to the image data buffer.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param channels Number of channels in the image.
     * @param deallocator Function to deallocate the buffer memory.
     */
    Image(uint8_t* buffer, int32_t width, int32_t height, int32_t channels, std::function<void(void*)> deallocator);

    /**
     * @brief Copy constructor that performs a deep copy of the image.
     * 
     * @param other The other image to copy from.
     */
    Image(const Image& other);

    /**
     * @brief Move constructor that transfers ownership of resources.
     * 
     * @param other The other image to move from.
     */
    Image(Image&& other) noexcept;

    /**
     * @brief Copy assignment operator that performs a deep copy of the image.
     * 
     * @param other The other image to copy from.
     * @return Reference to the assigned image.
     */
    Image& operator=(const Image& other);

    /**
     * @brief Move assignment operator that transfers ownership of resources.
     * 
     * @param other The other image to move from.
     * @return Reference to the assigned image.
     */
    Image& operator=(Image&& other) noexcept;

    /**
     * @brief Retrieves the image data buffer. Calling this function doesn't
     * transfer ownership to the caller. I.e., pointer returned will point to
     * valid memory only as long as the object is alive.
     * 
     * @return Pointer to the image data buffer.
     */
    const uint8_t* getBuffer() const;

    /**
     * @brief Retrieves the size of the buffer containing image data in bytes.
     * 
     * @return Size of the image buffer in bytes.
     */
    size_t getBufferSize() const;

    /**
     * @brief Retrieves the width of the image in pixels.
     * 
     * @return Width of the image in pixels.
     */
    int32_t getWidth() const;

    /**
     * @brief Retrieves the height of the image in pixels.
     * 
     * @return Height of the image pixels.
     */
    int32_t getHeight() const;

    /**
     * @brief Retrieves the number of channels in the image.
     * 
     * @return Number of channels in the image.
     */
    int32_t getChannels() const;

    /**
     * @brief Destructor that releases the allocated buffer memory.
     */
    ~Image();
};
