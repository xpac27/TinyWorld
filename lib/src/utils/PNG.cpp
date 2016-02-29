#include "PNG.hpp"
#include "log.hpp"
#include <iostream>

PNG::PNG(const char *filename)
{
    std::vector<unsigned char> png;

    //load and decode
    unsigned error = lodepng::load_file(png, filename);
    if(!error) error = lodepng::decode(image, imageWidth, imageHeight, png);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

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
