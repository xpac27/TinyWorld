#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gDiffuse;
layout (location = 3) out vec3 gMRAO;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_metallic;
uniform sampler2D texture_rough;
uniform sampler2D texture_normal;

void main()
{
    // Store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    // Also store the per-fragment normals into the gbuffer
    gNormal.rgb = normalize(Normal).xyz;
    // And the diffuse per-fragment color
    gDiffuse.rgb = texture(texture_diffuse, TexCoords).rgb;
    // Store metallicness
    gMRAO.r = texture(texture_metallic, TexCoords).r;
    // Store roughness
    gMRAO.g = texture(texture_rough, TexCoords).r;
    // Store AO
    /* gMRAO.b = TODO ambiant oclusion */
}
