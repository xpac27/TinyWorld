#version 330

layout (location = 0) in vec4 position;

uniform vec4 light;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = model * view * projection * (position.w == 0 ? light : position);
}
