#include "image-encoder-png.h"

#include <stdio.h>
#include <png.h>


bool encodeRGBtoPNG(const uint8_t* rgbBuffer, int width, int height, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        return false;
    }

    // Create and initialize the png_struct.
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        return false;
    }

    // Create and initialize the png_info.
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return false;
    }

    // Set up error handling with setjmp/longjmp.
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return false;
    }

    // Set the output file.
    png_init_io(png, fp);

    // Set the PNG header information.
    png_set_IHDR(
            png, info, width, height,
            8,                                  // bit depth.
            PNG_COLOR_TYPE_RGB,                 // color type.
            PNG_INTERLACE_NONE,                 // interlace method.
            PNG_COMPRESSION_TYPE_DEFAULT,       // compression method.
            PNG_FILTER_TYPE_DEFAULT             // filter method.
    );

    png_write_info(png, info);

    // Write the image data.
    for (int y = 0; y < height; y++) {
        png_bytep row_pointer = (png_bytep)(rgbBuffer + y * width * 3);
        png_write_row(png, row_pointer);
    }

    // Finish writing the file.
    png_write_end(png, NULL);

    // Clean up.
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return true;
}
