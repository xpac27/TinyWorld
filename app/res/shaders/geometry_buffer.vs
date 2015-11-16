#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in mat4 model;  // 3-6

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0f);

    gl_Position = projection * view * worldPos;

    FragPos = worldPos.xyz;
    TexCoords = texCoords;
    Normal = transpose(inverse(mat3(model))) * normal;
}
