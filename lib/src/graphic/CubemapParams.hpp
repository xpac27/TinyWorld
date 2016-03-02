#pragma once

// TODO use File instead of const char*
struct CubemapParams
{
    const char* right;
    const char* left;
    const char* bottom;
    const char* top;
    const char* back;
    const char* front;
};
