#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;
layout (location = 3) in mat4 WVP; // 3-6
layout (location = 7) in mat4 W;   // 7-10
layout (location = 11) in mat4 L;  // 11-14

void main(void)
{
    gl_Position = WVP * vec4(position, 1.0f);
}
