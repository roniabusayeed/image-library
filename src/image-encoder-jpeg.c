#include <jpeglib.h>
#include <stdio.h>


bool encodeImageToJPEG(const uint8_t* buffer, int width, int height, int number_of_channels, const char* filename) {
    
    // Validate the number of channels. JPEG typically supports 3 (RGB) or 1 (grayscale) channels.
    if (number_of_channels != 3 && number_of_channels != 1) {
        return false; // Unsupported channel count for JPEG.
    }

    // Open the file for writing in binary mode.
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        return false;
    }

    // Create a JPEG compression object.
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Set the output file for compression.
    jpeg_stdio_dest(&cinfo, fp);

    // Set image properties.
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = number_of_channels;
    cinfo.in_color_space = (number_of_channels == 3) ? JCS_RGB : JCS_GRAYSCALE;

    // Set default compression parameters.
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 85, TRUE); // Set JPEG quality (0-100).

    // Start compression.
    jpeg_start_compress(&cinfo, TRUE);

    // Write the image data row by row.
    while (cinfo.next_scanline < cinfo.image_height) {
        JSAMPROW row_pointer = (JSAMPROW)(buffer + cinfo.next_scanline * width * number_of_channels);
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    // Finish compression.
    jpeg_finish_compress(&cinfo);

    // Clean up and close the file.
    jpeg_destroy_compress(&cinfo);
    fclose(fp);

    return true;
}
