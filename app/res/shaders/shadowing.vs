#version 330

layout (location = 0) in vec3 position;
layout (location = 3) in mat4 WVP; // 3-6

void main(void)
{
    gl_Position = WVP * vec4(position, 1.0f);
}
