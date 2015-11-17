#version 330

layout (location = 0) in vec4 position;
layout (location = 3) in mat4 model;  // 3-6

uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * position;
}
