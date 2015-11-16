#version 330

layout (location = 0) in vec4 position;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec4 light;

void main(void)
{
    gl_Position = projection * view * model * (position.w == 0 ? light : position);
}

// #version 330
//
// layout (location = 0) in vec4 position;
//
// uniform vec4 light;
// uniform mat4 WVP;
//
// void main(void)
// {
//     gl_Position = WVP * (position.w == 0 ? light : position);
// }
