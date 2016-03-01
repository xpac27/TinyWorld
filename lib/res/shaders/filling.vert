layout (location = 0) in vec4 position;
layout (location = 5) in mat4 model;  // 4-7

uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * view * model * position;
}
