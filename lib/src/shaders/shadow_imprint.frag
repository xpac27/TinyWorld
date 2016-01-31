#version 330 core

layout (location = 3) out vec3 gMRS;

void main()
{
    // Store shadow mask
    gMRS.b = 0.5;
}
