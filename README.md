# Image Library

An image encoding and decoding library with C++ API.

## Dependencies
- **`libpng`** Required for PNG encoding.
- **`libjpeg`** Required for JPEG encoding.

## Installation

The project uses [Meson](https://mesonbuild.com/) as its build system. To build the library, ensure you have `Meson` and `Ninja` installed, along with dependencies for PNG and JPEG handling (`libpng`, `libjpeg`).

### Building the Library

Clone the repository and navigate to the project directory. Run the following commands:

```sh
./build.sh
```

This script cleans previous builds, sets up the build directory, and compiles the library using `Meson` and `Ninja`.

## Usage

### `Image` Class

The `Image` class represents a 2D image with pixel data stored in a buffer.

#### Basic Usage

```cpp
#include "image.h"

// Creating an empty image.
Image emptyImage;

// Creating an image from raw data.
uint8_t* buffer = /* Your image buffer */;
int width = 800, height = 600, channels = 4; // Example dimensions and channels.
Image image(buffer, width, height, channels);

// Accessing image properties
const uint8_t* data = image.getBuffer();
int imgWidth = image.getWidth();
int imgHeight = image.getHeight();
int imgChannels = image.getChannels();
```

### `ImageDecoder` Class

The `ImageDecoder` class provides functionality to decode images from files into `Image` objects.

#### Decoding an Image

```cpp
#include "image-decoder.h"

ImageDecoder decoder;
Image decodedImage = decoder.decodeImage("path/to/image.png");
```

### `ImageEncoder` Class

The `ImageEncoder` class provides functionality to encode images into various formats like PNG and JPEG.

#### Encoding an Image

```cpp
#include "image-encoder.h"

// Encoding an image to a file.
ImageEncoder encoder(ImageEncoder::Type::PNG);
encoder.encodeImage(image, "path/to/output.png");
```

## Contributing

Contributions are welcome! Please open issues or pull requests to help improve the library.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
