#version 330 core

layout (location = 4) out vec3 gShadow;

void main()
{
    // Store shadow mask
    gShadow.r = 1.;

    // gShadow.g = ...?
    // gShadow.b = ...?
}
