#version 410

layout (location = 0) in vec3 position;
uniform mat4 MVP;
out vec4 color;

void main(void)
{
    color = vec4(clamp(position, 0.0, 1.0), 1.0);
    gl_Position = MVP * vec4(position, 1.0);
}
