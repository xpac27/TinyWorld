#pragma once
#include "lodepng.h"
#include <vector>

class PNG
{

public:

    PNG(const char *filename);

    unsigned char* data();
    unsigned int width();
    unsigned int height();

private:

    std::vector<unsigned char> image; //the raw pixels

    unsigned int imageWidth;
    unsigned int imageHeight;

};
