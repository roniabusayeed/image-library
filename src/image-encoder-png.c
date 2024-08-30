#include "image-encoder-png.h"

#include <stdio.h>
#include <png.h>

bool encodeImageToPNG(const uint8_t* buffer, int width, int height, int number_of_channels, const char* filename) {
    
    // Determine PNG color type macro.
    int png_color_type;
    switch (number_of_channels) {
    case 1:
        png_color_type = PNG_COLOR_TYPE_GRAY;
        break;
    case 2:
        png_color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
        break;
    case 3:
        png_color_type = PNG_COLOR_TYPE_RGB;
        break;
    case 4:
        png_color_type = PNG_COLOR_TYPE_RGB_ALPHA;
        break;
    default:

        // Invalid number of color channels.
        return false;
    }

    // Open the file for writing in binary mode.
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
        8,                                  // Bit depth.
        png_color_type,                     // Color type.
        PNG_INTERLACE_NONE,                 // Interlace method.
        PNG_COMPRESSION_TYPE_DEFAULT,       // Compression method.
        PNG_FILTER_TYPE_DEFAULT             // Filter method.
    );

    // Write the header information to the file.
    png_write_info(png, info);

    // Write the image data.
    for (int y = 0; y < height; y++) {
        png_bytep row_pointer = (png_bytep)(buffer + y * width * number_of_channels);
        png_write_row(png, row_pointer);
    }

    // Finish writing the file.
    png_write_end(png, NULL);

    // Clean up.
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return true;
}
