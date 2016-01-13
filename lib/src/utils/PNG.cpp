#include "PNG.hpp"
#include "Log.hpp"
#include <stdio.h>
#include <assert.h>

using namespace Log;

PNG::PNG(const char *filename)
{
    //open file as binary
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        error("PNG not found:", filename);
    }

    //read the header
    png_byte header[8];
    fread(header, 1, 8, fp);
    assert(png_sig_cmp(header, 0, 8) == 0);

    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr);

    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr);

    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    assert(end_info);

	assert(!setjmp(png_jmpbuf(png_ptr)));
    png_init_io(png_ptr, fp); //init png reading
    png_set_sig_bytes(png_ptr, 8); //let libpng know you already read the first 8 bytes
    png_read_info(png_ptr, info_ptr); // read all the info up to the image data

	image_width = png_get_image_width(png_ptr, info_ptr);
	image_height = png_get_image_height(png_ptr, info_ptr);
	int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	int color_type = png_get_color_type(png_ptr, info_ptr);

	if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }

	if(color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
    } else if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png_ptr);
    }

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
    } else {
		png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    }

    png_read_update_info(png_ptr, info_ptr); // Update the png info struct.

    png_size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    image_data = new png_byte[rowbytes * image_height];
    assert(image_data);
    png_bytep *row_pointers = new png_bytep[image_height];
    assert(row_pointers);

    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < image_height; ++i) {
        row_pointers[image_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    fclose(fp);

    success("PNG loaded:", filename);
}

PNG::~PNG()
{
    delete[] image_data;
}

png_byte* PNG::data()
{
    return image_data;
}

png_uint_32 PNG::width()
{
    return image_width;
}

png_uint_32 PNG::height()
{
    return image_height;
}
