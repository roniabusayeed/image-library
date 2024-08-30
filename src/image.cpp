#include "image.h"

/**
 * @brief Default constructor that initializes an empty image.
 */
Image::Image() : m_buffer(nullptr), m_width(0), m_height(0), m_channels(0), m_deallocator(nullptr) {}

/**
 * @brief Constructs an image with a specified buffer, width, height, and channels.
 */
Image::Image(const uint8_t* buffer, int32_t width, int32_t height, int32_t channels)
    : m_buffer(nullptr), m_width(width), m_height(height), m_channels(channels), m_deallocator(nullptr) {
    size_t buffer_size = static_cast<size_t>(width) * height * channels;
    m_buffer = new uint8_t[buffer_size];
    std::memcpy(m_buffer, buffer, buffer_size);
}

/**
 * @brief Constructs an image with a specified buffer and deallocator.
 */
Image::Image(uint8_t* buffer, int32_t width, int32_t height, int32_t channels, std::function<void(void*)> deallocator)
    : m_buffer(buffer), m_width(width), m_height(height), m_channels(channels), m_deallocator(deallocator) {}

/**
 * @brief Copy constructor that performs a deep copy of the image.
 */
Image::Image(const Image& other)
    : m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels), m_deallocator(nullptr) {
    size_t buffer_size = static_cast<size_t>(m_width) * m_height * m_channels;
    m_buffer = new uint8_t[buffer_size];
    std::memcpy(m_buffer, other.m_buffer, buffer_size);
}

/**
 * @brief Move constructor that transfers ownership of resources.
 */
Image::Image(Image&& other) noexcept
    : m_buffer(other.m_buffer), m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels), m_deallocator(std::move(other.m_deallocator)) {
    other.m_buffer = nullptr;
    other.m_width = 0;
    other.m_height = 0;
    other.m_channels = 0;
}

/**
 * @brief Copy assignment operator that performs a deep copy of the image.
 */
Image& Image::operator=(const Image& other) {
    if (this != &other) {
        if (m_buffer && m_deallocator) {
            m_deallocator(m_buffer);
        } else {
            delete[] m_buffer;
        }

        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        m_deallocator = nullptr;

        size_t buffer_size = static_cast<size_t>(m_width) * m_height * m_channels;
        m_buffer = new uint8_t[buffer_size];
        std::memcpy(m_buffer, other.m_buffer, buffer_size);
    }
    return *this;
}

/**
 * @brief Move assignment operator that transfers ownership of resources.
 */
Image& Image::operator=(Image&& other) noexcept {
    if (this != &other) {
        if (m_buffer && m_deallocator) {
            m_deallocator(m_buffer);
        } else {
            delete[] m_buffer;
        }

        m_buffer = other.m_buffer;
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        m_deallocator = std::move(other.m_deallocator);

        other.m_buffer = nullptr;
        other.m_width = 0;
        other.m_height = 0;
        other.m_channels = 0;
    }
    return *this;
}

/**
 * @brief Retrieves the image data buffer.
 */
const uint8_t* Image::getBuffer() const {
    return m_buffer;
}

/**
 * @brief Retrives the buffer size in bytes.
 */
size_t Image::getBufferSize() const {
    return static_cast<size_t>(m_width) * m_height * m_channels;
}

/**
 * @brief Retrieves the width of the image.
 */
int32_t Image::getWidth() const {
    return m_width;
}

/**
 * @brief Retrieves the height of the image.
 */
int32_t Image::getHeight() const {
    return m_height;
}

/**
 * @brief Retrieves the number of channels in the image.
 */
int32_t Image::getChannels() const {
    return m_channels;
}

/**
 * @brief Destructor that releases the allocated buffer memory.
 */
Image::~Image() {
    if (m_buffer) {
        if (m_deallocator) {
            m_deallocator(m_buffer);
        } else {
            delete[] m_buffer;
        }
    }
}
