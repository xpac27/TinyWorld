#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

out vec2 uv;
out vec3 normal;

uniform mat4 WVP;
uniform mat4 W;

void main(void)
{
    uv = textureCoords;
    normal = (W * vec4(normals, 0.0f)).xyz;
    gl_Position = WVP * vec4(position, 1.0f);
}
