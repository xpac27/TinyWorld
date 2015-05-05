#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 MVP;

out vec2 uv_0;

void main(void)
{
    uv_0 = uv;
    gl_Position = MVP * vec4(position, 1.0);
}
