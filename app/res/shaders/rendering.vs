#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;
layout (location = 3) in mat4 WVP; // 3-6
layout (location = 7) in mat4 W;   // 7-10

out vec2 uv0;
out vec3 normal0;
out vec3 worldPosition0;

void main(void)
{
    gl_Position = WVP * vec4(position, 1.0f);

    uv0 = textureCoords;
    normal0 = (W * vec4(normals, 0.0f)).xyz;
    worldPosition0 = (W * vec4(position, 1.0f)).xyz;
}
