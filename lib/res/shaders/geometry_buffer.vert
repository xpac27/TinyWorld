layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in mat4 model;  // 5-8

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 Bitangent;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * position;

    gl_Position = projection * view * model * position;

    FragPos   = worldPos.xyz;
    TexCoords = texCoords;
    Normal    = normalize(model * vec4(normal, 0.0)).xyz;
    Tangent   = normalize(model * vec4(tangent, 0.0)).xyz;
    Bitangent = normalize(model * vec4(bitangent, 0.0)).xyz;
}
