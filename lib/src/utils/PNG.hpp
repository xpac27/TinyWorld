#pragma once
#include "png.h"

class PNG
{

public:

    PNG(const char *filename);

    ~PNG();

    png_byte* data();
    png_uint_32 width();
    png_uint_32 height();

private:

    png_byte *image_data;
	png_uint_32 image_width;
	png_uint_32 image_height;

};
