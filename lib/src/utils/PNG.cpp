#include "PNG.hpp"
#include "log.hpp"
#include <iostream>

PNG::PNG(const char *filename)
{
    std::vector<unsigned char> png;

    unsigned e = lodepng::load_file(png, filename);
    if (e) {
        error("PNG:", lodepng_error_text(e), filename);
        return;
    }

    e = lodepng::decode(image, imageWidth, imageHeight, png);
    if (e) {
        error("PNG:", lodepng_error_text(e), filename);
        return;
    }

    success("PNG loaded:", filename);
}

unsigned char* PNG::data()
{
    return image.data();
}

unsigned int PNG::width()
{
    return imageWidth;
}

unsigned int PNG::height()
{
    return imageHeight;
}
