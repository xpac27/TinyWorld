#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

out vec2 uv0;
out vec3 normal0;
out vec3 worldPosition0;

uniform mat4 WVP;
uniform mat4 W;

void main(void)
{
    gl_Position = WVP * vec4(position, 1.0f);

    uv0 = textureCoords;
    normal0 = (W * vec4(normals, 0.0f)).xyz;
    worldPosition0 = (W * vec4(position, 1.0f)).xyz;
}
