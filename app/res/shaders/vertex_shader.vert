#version 410

uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

out vec2 uv;

void main(void)
{
    uv = textureCoords;
    gl_Position = projection * vec4(position, 1.0);
}
