#version 330

layout (location = 0) in vec4 position;

uniform vec4 light;
uniform mat4 WVP;

void main(void)
{
    gl_Position = WVP * (position.w == 0 ? light : position);
}
