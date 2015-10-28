#version 330

layout (location = 0) in vec4 position;
layout (location = 3) in mat4 WVP; // 3-6

uniform vec4 light;

void main(void)
{
    gl_Position = WVP * (position.w == 0
        ? vec4(position.xyz * light.w - light.xyz, 0) 
        : position);
}
